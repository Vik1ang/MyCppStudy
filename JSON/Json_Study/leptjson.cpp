#ifdef _WIN64
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "leptjson.h"

#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#ifndef LEPT_PARSE_STACK_INIT_SIZE
#define LEPT_PARSE_STACK_INIT_SIZE 256
#endif

# ifndef LEPT_PARSE_STRINGIFY_INIT_SIZE
#define LEPT_PARSE_STRINGIFY_INIT_SIZE 256
#endif

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)
#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define PUTC(c, ch)			do { *(char*)lept_context_push(c, sizeof(char)) = (ch); } while(0)
#define PUTS(c, s, len)     memcpy(lept_context_push(c, len), s, len)

struct lept_context
{
	const char* json;
	char* stack;
	size_t size, top;
};

static void* lept_context_push(lept_context* c, size_t size)
{
	assert(size > 0);
	if (c->top + size >= c->size)
	{
		if (c->size == 0)
		{
			c->size = LEPT_PARSE_STACK_INIT_SIZE;
		}
		while (c->top + size >= c->size)
		{
			c->size += c->size >> 1; // 扩容1.5倍
		}
		c->stack = static_cast<char*>(realloc(c->stack, c->size));
	}
	void* ret = c->stack + c->top;
	c->top += size;
	return ret;
}

static void* lept_context_pop(lept_context* c, size_t size)
{
	assert(c->top >= size);
	return c->stack + (c->top -= size);
}

static void lept_parse_whitespace(lept_context* c)
{
	const char* p = c->json;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
	{
		p++;
	}
	c->json = p;
}

static int lept_parse_literal(lept_context* c, leptjson::lept_value* v, const char* literal, leptjson::lept_type type)
{
	size_t i;
	EXPECT(c, literal[0]);
	for (i = 0; literal[i + 1]; ++i)
	{
		if (c->json[i] != literal[i + 1])
		{
			return leptjson::PARSE_INVALID_VALUE;
		}
	}
	c->json += i;
	v->type = type;
	return leptjson::PARSE_OK;
}

static int lept_parse_number(lept_context* c, leptjson::lept_value* v)
{
	const char* p = c->json;
	// 负号
	if (*p == '-') p++;
	// 整数
	if (*p == '0') p++;
	else
	{
		if (!ISDIGIT1TO9(*p)) return leptjson::PARSE_INVALID_VALUE;
		for (p++; ISDIGIT(*p); p++);
	}
	// 小数
	if (*p == '.')
	{
		p++;
		if (!ISDIGIT(*p)) return leptjson::PARSE_INVALID_VALUE;
		for (p++; ISDIGIT(*p); p++);
	}
	// 指数
	if (*p == 'e' || *p == 'E') {
		p++;
		if (*p == '+' || *p == '-') p++;
		if (!ISDIGIT(*p)) return leptjson::PARSE_INVALID_VALUE;
		for (p++; ISDIGIT(*p); p++);
	}
	errno = 0;
	v->u.n = strtod(c->json, nullptr);
	if (errno == ERANGE && (v->u.n == HUGE_VAL || v->u.n == -HUGE_VAL))
	{
		return leptjson::PARSE_NUMBER_TOO_BIG;
	}
	v->type = leptjson::LEPT_NUMBER;
	c->json = p;
	return leptjson::PARSE_OK;
}

static const char* lept_parse_hex4(const char* p, unsigned* u)
{
	int i = 0;
	*u = 0;
	for (i = 0; i < 4; ++i)
	{
		char ch = *p++;
		*u <<= 4;
		if (ch >= '0' && ch <= '9') { *u |= ch - '0'; }
		else if (ch >= 'A' && ch <= 'F') { *u |= ch - ('A' - 10); }
		else if (ch >= 'a' && ch <= 'f') { *u |= ch - ('a' - 10); }
		else return nullptr;
	}
	return p;
}

static void lept_encode_utf8(lept_context* c, unsigned u)
{
	if (u <= 0x7F)
	{
		PUTC(c, u & 0xFF);
	}
	else if (u <= 0x7FF)
	{
		PUTC(c, 0xC0 | ((u >> 6) & 0xFF));
		PUTC(c, 0x80 | (u & 0x3F));
	}
	else if (u <= 0xFFFF)
	{
		PUTC(c, 0xE0 | ((u >> 12) & 0xFF));
		PUTC(c, 0x80 | ((u >> 6) & 0x3F));
		PUTC(c, 0x80 | (u & 0x3F));
	}
	else
	{
		assert(u <= 0x10FFFF);
		PUTC(c, 0xF0 | ((u >> 18) & 0xFF));
		PUTC(c, 0x80 | ((u >> 12) & 0x3F));
		PUTC(c, 0x80 | ((u >> 6) & 0x3F));
		PUTC(c, 0x80 | (u & 0x3F));
	}
}

#define STRING_ERROR(ret) do { c->top = head; return ret; } while(0)

static int lept_parse_string_raw(lept_context* c, char** str, size_t* len)
{
	const size_t head = c->top;
	unsigned u, u2;
	EXPECT(c, '\"');
	const char* p = c->json;
	for (;;)
	{
		const char ch = *p++;
		switch (ch)
		{
		case '\"':
			*len = c->top - head;
			*str = static_cast<char*>(lept_context_pop(c, *len));
			c->json = p;
			return leptjson::PARSE_OK;
		case '\\':
			switch (*p++)
			{
			case '\"': PUTC(c, '\"'); break;
			case '\\': PUTC(c, '\\'); break;
			case '/':  PUTC(c, '/'); break;
			case 'b':  PUTC(c, '\b'); break;
			case 'f':  PUTC(c, '\f'); break;
			case 'n':  PUTC(c, '\n'); break;
			case 'r':  PUTC(c, '\r'); break;
			case 't':  PUTC(c, '\t'); break;
			case 'u':
				if (!((p = lept_parse_hex4(p, &u))))
				{
					STRING_ERROR(leptjson::PARSE_INVALID_UNICODE_HEX);
				}
				if (u >= 0xD800 && u <= 0xDBFF) { /* surrogate pair */
					if (*p++ != '\\')
						STRING_ERROR(leptjson::PARSE_INVALID_UNICODE_SURROGATE);
					if (*p++ != 'u')
						STRING_ERROR(leptjson::PARSE_INVALID_UNICODE_SURROGATE);
					if (!(p = lept_parse_hex4(p, &u2)))
						STRING_ERROR(leptjson::PARSE_INVALID_UNICODE_HEX);
					if (u2 < 0xDC00 || u2 > 0xDFFF)
						STRING_ERROR(leptjson::PARSE_INVALID_UNICODE_SURROGATE);
					u = (((u - 0xD800) << 10) | (u2 - 0xDC00)) + 0x10000;
				}
				lept_encode_utf8(c, u);
				break;
			default:
				return leptjson::PARSE_INVALID_STRING_ESCAPE;
			}
			break;
		case '\0':
			STRING_ERROR(leptjson::PARSE_MISS_QUOTATION_MARK);
		default:
			if (static_cast<unsigned char>(ch) < 0x20)
			{
				STRING_ERROR(leptjson::PARSE_INVALID_STRING_CHAR);
			}
			PUTC(c, ch);
		}
	}
}

static int lept_parse_string(lept_context* c, leptjson::lept_value* v)
{
	int ret;
	char* s;
	size_t len;
	if ((ret = lept_parse_string_raw(c, &s, &len)) == leptjson::PARSE_OK)
	{
		leptjson::lept_set_string(v, s, len);
	}
	return ret;
}

static int lept_parse_value(lept_context* c, leptjson::lept_value* v);

static int lept_parse_array(lept_context* c, leptjson::lept_value* v)
{
	size_t size = 0;
	int ret;
	EXPECT(c, '[');
	lept_parse_whitespace(c);
	if (*c->json == ']')
	{
		c->json++;
		v->type = leptjson::LEPT_ARRAY;
		v->u.a.size = 0;
		v->u.a.e = nullptr;
		return leptjson::PARSE_OK;
	}
	for (;;)
	{
		leptjson::lept_value e;
		lept_init(&e);
		if ((ret = lept_parse_value(c, &e)) != leptjson::PARSE_OK)
		{
			return ret;
		}
		memcpy(lept_context_push(c, sizeof(leptjson::lept_value)), &e, sizeof(leptjson::lept_value));
		size++;
		lept_parse_whitespace(c);
		if (*c->json == ',')
		{
			c->json++;
			lept_parse_whitespace(c);
		}
		else if (*c->json == ']')
		{
			c->json++;
			v->type = leptjson::LEPT_ARRAY;
			v->u.a.size = size;
			size *= sizeof(leptjson::lept_value);
			memcpy(v->u.a.e = static_cast<leptjson::lept_value*>(malloc(size)), lept_context_pop(c, size), size);
			return leptjson::PARSE_OK;
		}
		else
		{
			ret = leptjson::PARSE_MISS_COMMA_OR_SQUARE_BRACKET;
			break;
		}
	}

	/* Pop and free values on the stack */
	for (size_t i = 0; i < size; ++i)
	{
		lept_free(static_cast<leptjson::lept_value*>(lept_context_pop(c, sizeof(leptjson::lept_value))));
	}

	return ret;
}

static int lept_parse_object(lept_context* c, leptjson::lept_value* v)
{
	leptjson::lept_member m;
	int ret;
	EXPECT(c, '{');
	lept_parse_whitespace(c);
	if (*c->json == '}')
	{
		c->json++;
		v->type = leptjson::LEPT_OBJECT;
		v->u.o.m = nullptr;
		v->u.o.size = 0;
		return leptjson::PARSE_OK;
	}
	m.k = nullptr;
	size_t size = 0;
	for (;;)
	{
		char* str;
		lept_init(&m.v);
		/* parse key */
		if (*c->json != '"')
		{
			ret = leptjson::PARSE_MISS_KEY;
			break;
		}
		if ((ret = lept_parse_string_raw(c, &str, &m.k_len)) != leptjson::PARSE_OK)
		{
			break;
		}
		memcpy(m.k = static_cast<char*>(malloc(m.k_len + 1)), str, m.k_len);
		m.k[m.k_len] = '\0';
		/* parse ws colon ws */
		lept_parse_whitespace(c);
		if (*c->json != ':')
		{
			ret = leptjson::PARSE_MISS_COLON;
			break;
		}
		c->json++;
		lept_parse_whitespace(c);
		/* parse value */
		if ((ret = lept_parse_value(c, &m.v)) != leptjson::PARSE_OK)
		{
			break;
		}
		memcpy(lept_context_push(c, sizeof(leptjson::lept_member)), &m, sizeof(leptjson::lept_member));
		size++;
		m.k = nullptr; /* ownership is transferred to member on stack */
		/* parse ws [comma | right-curly-brace] ws */
		lept_parse_whitespace(c);
		if (*c->json == ',')
		{
			c->json++;
			lept_parse_whitespace(c);
		}
		else if (*c->json == '}')
		{
			size_t s = sizeof(leptjson::lept_member) * size;
			c->json++;
			v->type = leptjson::LEPT_OBJECT;
			v->u.o.size = size;
			memcpy(v->u.o.m = static_cast<leptjson::lept_member*>(malloc(s)), lept_context_pop(c, s), s);
			return leptjson::PARSE_OK;
		}
		else
		{
			ret = leptjson::PARSE_MISS_COMMA_OR_CURLY_BRACKET;
			break;
		}
	}

	/* Pop and free members on the stack */
	free(m.k);
	for (size_t i = 0; i < size; ++i)
	{
		leptjson::lept_member* m = static_cast<leptjson::lept_member*>(lept_context_pop(c, sizeof(leptjson::lept_member)));
		free(m->k);
		lept_free(&m->v);
	}
	v->type = leptjson::LEPT_NULL;
	return ret;
}

static int lept_parse_value(lept_context* c, leptjson::lept_value* v) {
	switch (*c->json) {
	case 't':  return lept_parse_literal(c, v, "true", leptjson::LEPT_TRUE);
	case 'f':  return lept_parse_literal(c, v, "false", leptjson::LEPT_FALSE);
	case 'n':  return lept_parse_literal(c, v, "null", leptjson::LEPT_NULL);
	default:   return lept_parse_number(c, v);
	case '"': return lept_parse_string(c, v);
	case '[': return lept_parse_array(c, v);
	case '{':  return lept_parse_object(c, v);
	case '\0': return leptjson::PARSE_EXPECT_VALUE;
	}
}

int leptjson::lept_parse(lept_value* v, const char* json)
{
	lept_context c;
	int ret = 0;
	assert(v != nullptr);
	// 初始化
	c.json = json;
	c.stack = nullptr;
	c.size = c.top = 0;
	lept_init(v);
	lept_parse_whitespace(&c);
	if ((ret = lept_parse_value(&c, v)) == PARSE_OK)
	{
		lept_parse_whitespace(&c);
		if (*c.json != '\0')
		{
			v->type = LEPT_NULL;
			ret = PARSE_ROOT_NOT_SINGULAR;
		}
	}
	assert(c.top == 0);
	free(c.stack);
	return ret;
}

static void lept_stringify_value(lept_context* c, const leptjson::lept_value* v)
{
	switch (v->type)
	{
	case leptjson::LEPT_NULL: PUTS(c, "null", 4); break;
	case leptjson::LEPT_FALSE: PUTS(c, "false", 5); break;
	case leptjson::LEPT_TRUE: PUTS(c, "true", 4); break;
	case leptjson::LEPT_NUMBER:
		c->top -= 32 - sprintf(static_cast<char*>(lept_context_push(c, 32)), "%.17g", v->u.n);
		break;
	case leptjson::LEPT_STRING:
		break;
	case leptjson::LEPT_ARRAY:
		break;
	case leptjson::LEPT_OBJECT:
		break;
	default:assert(0 && "invalid type");
	}
}

char* lept_stringify(const leptjson::lept_value* v, size_t* length)
{
	lept_context c;
	assert(v != nullptr);
	c.stack = (char*)malloc(c.size = LEPT_PARSE_STRINGIFY_INIT_SIZE);
	c.top = 0;
	lept_stringify_value(&c, v);
}

void leptjson::lept_free(lept_value* v)
{
	assert(v != nullptr);
	switch (v->type)
	{
	case LEPT_STRING:
		free(v->u.s.s);
		break;
	case LEPT_ARRAY:
		for (int i = 0; i < v->u.a.size; ++i)
		{
			lept_free(&v->u.a.e[i]);
		}
		free(v->u.a.e);
		break;
	case LEPT_OBJECT:
		for (int i = 0; i < v->u.o.size; ++i)
		{
			free(v->u.o.m[i].k);
			lept_free(&v->u.o.m[i].v);
		}
		free(v->u.o.m);
		break;
	default: break;
	}
	v->type = LEPT_NULL;
}

leptjson::lept_type leptjson::lept_get_type(const lept_value* v)
{
	assert(v != nullptr);
	return v->type;
}

int leptjson::lept_get_boolean(const lept_value* v)
{
	assert(v != nullptr && (v->type == LEPT_TRUE || v->type == LEPT_FALSE));
	return v->type == LEPT_TRUE;
}

void leptjson::lept_set_boolean(lept_value* v, int b)
{
	lept_free(v);
	v->type = b ? LEPT_TRUE : LEPT_FALSE;
}

double leptjson::lept_get_number(const lept_value* v)
{
	assert(v != nullptr && v->type == LEPT_NUMBER);
	return v->u.n;
}

void leptjson::lept_set_number(lept_value* v, double n)
{
	lept_free(v);
	v->u.n = n;
	v->type = LEPT_NUMBER;
}

const char* leptjson::lept_get_string(const lept_value* v)
{
	assert(v != nullptr && v->type == LEPT_STRING);
	return v->u.s.s;
}

size_t leptjson::lept_get_string_length(const lept_value* v)
{
	assert(v != nullptr && v->type == LEPT_STRING);
	return v->u.s.len;
}

void leptjson::lept_set_string(lept_value* v, const char* s, size_t len)
{
	assert(v != nullptr && (s != nullptr || len == 0));
	lept_free(v);
	v->u.s.s = static_cast<char*>(malloc(len + 1));
	memcpy(v->u.s.s, s, len);
	v->u.s.s[len] = '\0';
	v->u.s.len = len;
	v->type = LEPT_STRING;
}

size_t leptjson::lept_get_array_size(const lept_value* v)
{
	assert(v != nullptr && v->type == LEPT_ARRAY);
	return v->u.a.size;
}

leptjson::lept_value* leptjson::lept_get_array_element(const lept_value* v, size_t index)
{
	assert(v != nullptr && v->type == LEPT_ARRAY);
	assert(index < v->u.a.size);
	return &v->u.a.e[index];
}

size_t leptjson::lept_get_object_size(const lept_value* v)
{
	assert(v != nullptr && v->type == LEPT_OBJECT);
	return v->u.o.size;
}

const char* leptjson::lept_get_object_key(const lept_value* v, size_t index)
{
	assert(v != nullptr && v->type == LEPT_OBJECT);
	assert(index < v->u.o.size);
	return v->u.o.m[index].k;
}

size_t leptjson::lept_get_object_key_length(const lept_value* v, size_t index)
{
	assert(v != nullptr && v->type == LEPT_OBJECT);
	assert(index < v->u.o.size);
	return v->u.o.m[index].k_len;
}

leptjson::lept_value* leptjson::lept_get_object_value(const lept_value* v, size_t index)
{
	assert(v != nullptr && v->type == LEPT_OBJECT);
	assert(index < v->u.o.size);
	return &v->u.o.m[index].v;
}
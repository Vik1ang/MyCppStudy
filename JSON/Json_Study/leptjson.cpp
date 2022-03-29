#ifdef _WIN64
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "leptjson.h"

#include <cassert>
#include <cerrno>
#include <cstdlib>
#include <cstring>

#ifndef LEPT_PARSE_STACK_INIT_SIZE
#define LEPT_PARSE_STACK_INIT_SIZE 256
#endif

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)
#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')
#define PUTC(c, ch)			do { *(char*)lept_context_push(c, sizeof(char)) = (ch); } while(0)

struct lept_context
{
	const char* json;
	char* stack;
	size_t size, top;
};

static void* lept_context_push(lept_context* c, size_t size)
{
	void* ret;
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
		c->stack = (char*)realloc(c->stack, c->size);
	}
	ret = c->stack + c->top;
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

static int lept_parse_string(lept_context* c, leptjson::lept_value* v)
{
	size_t head = c->top, len;
	const char* p;
	EXPECT(c, '\"');
	p = c->json;
	for (;;)
	{
		char ch = *p++;
		switch (ch)
		{
		case '\"':
			len = c->top - head;
			lept_set_string(v, (const char*)lept_context_pop(c, len), len);
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
			default: 
				c->top = head;
				return leptjson::PARSE_INVALID_STRING_ESCAPE;
			}
			break;
		case '\0':
			c->top = head;
			return leptjson::PARSE_MISS_QUOTATION_MARK;
		default:
			if ((unsigned char)ch < 0x20)
			{
				c->top = head;
				return leptjson::PARSE_INVALID_STRING_CHAR;
			}
			PUTC(c, ch);
		}
	}
}

static int lept_parse_value(lept_context* c, leptjson::lept_value* v) {
	switch (*c->json) {
	case 't':  return lept_parse_literal(c, v, "true", leptjson::LEPT_TRUE);
	case 'f':  return lept_parse_literal(c, v, "false", leptjson::LEPT_FALSE);
	case 'n':  return lept_parse_literal(c, v, "null", leptjson::LEPT_NULL);
	default:   return lept_parse_number(c, v);
	case '"': return lept_parse_string(c, v);
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

void leptjson::lept_free(lept_value* v)
{
	assert(v != nullptr);
	if (v->type == LEPT_STRING)
	{
		free(v->u.s.s);
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
	v->u.s.s = (char*)malloc(len + 1);
	memcpy(v->u.s.s, s, len);
	v->u.s.s[len] = '\0';
	v->u.s.len = len;
	v->type = LEPT_STRING;
}
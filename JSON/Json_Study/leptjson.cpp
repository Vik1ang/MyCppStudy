#include <cassert>

#include "leptjson.h"

#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

struct lept_context
{
	const char* json;
};

static void lept_parse_whitespace(lept_context* c)
{
	const char* p = c->json;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
	{
		p++;
	}
	c->json = p;
}

static int lept_parse_true(lept_context* c, leptjson::lept_value* v) {
	EXPECT(c, 't');
	if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
		return leptjson::PARSE_INVALID_VALUE;
	c->json += 3;
	v->type = leptjson::LEPT_TRUE;
	return leptjson::PARSE_OK;
}

static int lept_parse_false(lept_context* c, leptjson::lept_value* v) {
	EXPECT(c, 'f');
	if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
		return leptjson::PARSE_INVALID_VALUE;
	c->json += 4;
	v->type = leptjson::LEPT_FALSE;
	return leptjson::PARSE_OK;
}

static int lept_parse_null(lept_context* c, leptjson::lept_value* v)
{
	EXPECT(c, 'n');
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
	{
		return leptjson::PARSE_INVALID_VALUE;
	}
	c->json += 3;
	v->type = leptjson::LEPT_NULL;
	return leptjson::PARSE_OK;
}

static int lept_parse_value(lept_context* c, leptjson::lept_value* v) {
	switch (*c->json) {
	case 't':  return lept_parse_true(c, v);
	case 'f':  return lept_parse_false(c, v);
	case 'n':  return lept_parse_null(c, v);
	case '\0': return leptjson::PARSE_EXPECT_VALUE;
	default:   return leptjson::PARSE_INVALID_VALUE;
	}
}

int leptjson::lept_parse(lept_value* v, const char* json)
{
	lept_context c;
	int ret = 0;
	assert(v != nullptr);
	c.json = json;
	v->type = LEPT_NULL;
	lept_parse_whitespace(&c);
	if ((ret = lept_parse_value(&c, v)) == PARSE_OK)
	{
		lept_parse_whitespace(&c);
		if (*c.json != '\0')
		{
			ret = PARSE_ROOT_NOT_SINGULAR;
		}
	}
	return ret;
}

leptjson::lept_type leptjson::lept_get_type(const lept_value* v)
{
	assert(v != nullptr);
	return v->type;
}
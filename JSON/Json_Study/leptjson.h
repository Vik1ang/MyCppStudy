#ifndef LEPTJSON_H_
#define LEPTJSON_H_

namespace leptjson
{
	enum lept_type
	{
		LEPT_NULL,
		LEPT_FALSE,
		LEPT_TRUE,
		LEPT_NUMBER,
		LEPT_STRING,
		LEPT_ARRAY,
		LEPT_OBJECT
	};

	enum
	{
		PARSE_OK = 0,
		PARSE_EXPECT_VALUE,
		PARSE_INVALID_VALUE,
		PARSE_ROOT_NOT_SINGULAR
	};

	struct lept_value
	{
		lept_type type;
	};

	int lept_parse(lept_value* v, const char* json);

	lept_type lept_get_type(const lept_value* v);
} // namespace leptjson

#endif // LEPTJSON_H_

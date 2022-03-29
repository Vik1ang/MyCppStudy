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
		PARSE_ROOT_NOT_SINGULAR,
		PARSE_NUMBER_TOO_BIG,
		PARSE_MISS_QUOTATION_MARK,
		PARSE_INVALID_STRING_ESCAPE,
		PARSE_INVALID_STRING_CHAR
	};

	struct lept_value
	{
		union
		{
			struct
			{
				char* s;
				size_t len;
			} s;
			double n;
		} u;
		lept_type type;
	};

#define lept_init(v) do { (v)->type = leptjson::LEPT_NULL; } while(0)

	int lept_parse(lept_value* v, const char* json);

	void lept_free(lept_value* v);

	lept_type lept_get_type(const lept_value* v);

#define lept_set_null(v) lept_free(v)

	int lept_get_boolean(const lept_value* v);
	void lept_set_boolean(lept_value* v, int b);

	double lept_get_number(const lept_value* v);
	void lept_set_number(lept_value* v, double n);

	const char* lept_get_string(const lept_value* v);
	size_t lept_get_string_length(const lept_value* v);
	void lept_set_string(lept_value* v, const char* s, size_t len);
} // namespace leptjson

#endif // LEPTJSON_H_

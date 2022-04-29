#ifndef LEPTJSON_H_
#define LEPTJSON_H_

namespace leptjson
{
# define LEPT_KEY_NOT_EXIST ((size_t)-1)

	struct lept_member;

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
		PARSE_INVALID_STRING_CHAR,
		PARSE_INVALID_UNICODE_HEX,
		PARSE_INVALID_UNICODE_SURROGATE,
		PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
		PARSE_MISS_KEY,
		PARSE_MISS_COLON,
		PARSE_MISS_COMMA_OR_CURLY_BRACKET
	};

	struct lept_value
	{
		union
		{
			struct { lept_member* m; size_t size; } o;	// object
			struct { lept_value* e; size_t size; } a;	// array
			struct { char* s; size_t len; } s;			// string
			double n;									// number
		} u;
		lept_type type;
	};

	struct lept_member
	{
		char* k;		// member key
		size_t k_len;	// member key length
		lept_value v;	// member value
	};

#define lept_init(v) do { (v)->type = leptjson::LEPT_NULL; } while(0)

	int lept_parse(lept_value* v, const char* json);

	char* lept_stringify(const lept_value* v, size_t* length);

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

	size_t lept_get_array_size(const lept_value* v);
	lept_value* lept_get_array_element(const lept_value* v, size_t index);

	size_t lept_get_object_size(const lept_value* v);
	const char* lept_get_object_key(const lept_value* v, size_t index);
	size_t lept_get_object_key_length(const lept_value* v, size_t index);
	lept_value* lept_get_object_value(const lept_value* v, size_t index);

	size_t lept_find_object_index(const lept_value* v, const char* key, size_t klen);
	lept_value* lept_find_object_value(lept_value* v, const char* key, size_t klen);
	lept_value* lept_set_object_value(lept_value* v, const char* key, size_t klen);
	void lept_remove_object_value(lept_value* v, size_t index);

} // namespace leptjson

#endif // LEPTJSON_H_

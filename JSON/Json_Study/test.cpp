#include <cstdio>

#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

template <typename T, typename K, typename S, typename M>
void expect_eq_base(T equality, K expect, S actual, M format)
{
	do {
		test_count++;
		if (equality) {
			test_pass++;
		}
		else {
			fprintf(stderr, "%s:%d: expect: %d actual: %d", __FILE__, __LINE__, expect, actual);
			main_ret = 1;
		}
	} while (true);
}

template <typename T, typename K>
void expect_eq_int(T expect, K actual)
{
	expect_eq_base((expect) == (actual), expect, actual, "%d");
}

static void test_parse_null()
{
	lept_value v;
	v.type = LEPT_TRUE;
	expect_eq_int(LEPT_PARSE_OK, lept_parse(&v, "null"));
	expect_eq_int(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_expect_value()
{
	lept_value v;

	v.type = LEPT_FALSE;
	expect_eq_int(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, ""));
	expect_eq_int(LEPT_NULL, lept_get_type(&v));

	v.type = LEPT_FALSE;
	expect_eq_int(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, " "));
	expect_eq_int(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_invalid_value()
{
	lept_value v;
	v.type = LEPT_FALSE;
	expect_eq_int(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "nul"));
	expect_eq_int(LEPT_NULL, lept_get_type(&v));

	v.type = LEPT_FALSE;
	expect_eq_int(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "?"));
	expect_eq_int(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_root_not_singular()
{
	lept_value v;
	v.type = LEPT_FALSE;
	expect_eq_int(LEPT_PARSE_ROOT_NOT_SINGULAR, lept_parse(&v, "null x"));
	expect_eq_int(LEPT_NULL, lept_get_type(&v));
}

static void test_parse()
{
	test_parse_null();
	test_parse_expect_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();
}

int main(int argc, char* argv[])
{
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);

	return main_ret;
}
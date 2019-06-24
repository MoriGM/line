#include <test/test.h>
#include <nonamedef.h>

void test1(void)
{
	char *c = char_to_hex('a');
	
	if (c[0] == '6' && c[1] == '1')
		test_correct("Correct test1");
	else
		test_error("Cannoct Transform test1");
	
	free(c);
}

void test2(void)
{
	char *c = char_to_hex('f');
	
	if (c[0] == '6' && c[1] == '6')
		test_correct("Correct test2");
	else
		test_error("Cannoct Transform test2");
	
	free(c);
}

void test3(void)
{
	char *c = char_to_hex('D');
	
	if (c[0] == '4' && c[1] == '4')
		test_correct("Correct test3");
	else
		test_error("Cannoct Transform test3");
	
	free(c);
}

void test4(void)
{
	char *c = int_to_hex(0xABCDEF12);
	
	if (c[0] == 'A' && c[1] == 'B' && c[2] == 'C' && c[3] == 'D' && c[4] == 'E' && c[5] == 'F' && c[6] == '1' && c[7] == '2')
		test_correct("Correct test4");
	else
		test_error("Cannoct Transform test4");
	
	free(c);
}

void test5(void)
{
	char *c = int_to_hex(0xFFEEBBCC);
	
	if (c[0] == 'F' && c[1] == 'F' && c[2] == 'E' && c[3] == 'E' && c[4] == 'B' && c[5] == 'B' && c[6] == 'C' && c[7] == 'C')
		test_correct("Correct test5");
	else
		test_error("Cannoct Transform test5");
	
	free(c);
}

void test6(void)
{
	char *c = int_to_hex(0x12345678);
	
	if (c[0] == '1' && c[1] == '2' && c[2] == '3' && c[3] == '4' && c[4] == '5' && c[5] == '6' && c[6] == '7' && c[7] == '8')
		test_correct("Correct test6");
	else
		test_error("Cannoct Transform test6");
	
	free(c);
}

int main(void)
{
	test_start_check("Char to Hex Test");

	test1();
	test2();
	test3();

	test_stop_check();
	test_start_check("Int to Hex Test");

	test4();
	test5();
	test6();

	test_stop_check();

	test_print_result();

	return 0;
}

#include <nonamedef.h>

#define PECA(x, y) ((y * 100) / x)

int all = 0,error = 0, warning = 0, correct = 0;
char* test_text;

void test_start_check(char* test)
{
	test_text = test;
	printf("Started Test %s\n\n", test_text);
}

void test_stop_check(void)
{
	printf("Stopped Test %s\n\n", test_text);
	test_text = NULL;
}

void test_correct(char* text)
{
	all++;
	correct++;
	printf("Correct Test in %s\n", test_text);
	printf("%s\n\n", text);
}

void test_error(char* text)
{
	all++;
	error++;
	printf("Correct Test in %s\n", test_text);
	printf("%s\n\n", text);
}

void test_warning(char* text)
{
	all++;
	warning++;
	printf("Correct Test in %s\n", test_text);
	printf("%s\n\n", text);
	
}

void test_print_result(void)
{
	printf("All: %d\nCorrect:%d\nWarnings:%d\nErrors:%d\n", all, correct, warning, error);
	printf("%d%% Errors and %d%% Correct and %d%% Warnings\n", PECA(all, error), PECA(all, correct), PECA(all, warning));
}

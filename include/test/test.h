#ifndef TEST_TEST_H
#define TEST_TEST_H

extern int all, error, warning, correct;

void test_start_check(char* test);
void test_stop_check(void);
void test_correct(char* text);
void test_error(char* text);
void test_warning(char* text);
void test_print_result(void);

#endif

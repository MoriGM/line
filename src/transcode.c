#include <nonamedef.h>

char* char_to_hex(char c)
{
	char hex[] = "0123456789ABCDEF";

	char* cc = malloc(sizeof(char) * 3);
       	cc[2] = '\0';
	cc[0] = hex[((c & 0xF0) >> 4)];
	cc[1] = hex[(c & 0x0F)];

	return cc;
}

/*
 * cc = int nible count and added 1 for the zero byte
 * for = from 0 to the nible count of a int added by 1
 * cc[i] = shift c int nible count - i to the right and make an 0xF and to get the nible positon and then get the char from hex[]
 * cc[] = add \0 to the end of the array
 *
 * int nible count = byte size of a int multiplied by 2
 */
char* int_to_hex(int c)
{
	char hex[] = "0123456789ABCDEF";

	char* cc = malloc((sizeof(char) * (sizeof(int) * 2)) + 1);
	for (int i = 0; i < ((sizeof(int) * 2) + 1);i++)
		cc[i] = hex[(c >> (4 * ((sizeof(int) * 2) - i))) & 0xF];
	cc[(sizeof(int) * 2) + 1] = '\0';
	return cc;
}

#include <nonamedef.h>

bool color = FALSE;

void init_colormode(void)
{
	if (has_colors() == FALSE)
		return;
	color = TRUE;
	start_color();
}

int has_colormode(void)
{
	return color;
}

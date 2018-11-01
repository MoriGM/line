#include "nonamedef.h"

bool color = FALSE;

void init_colormode()
{
	if (has_colors() == FALSE)
		return;
	color = TRUE;
	start_color();
}

int has_colormode()
{
	return color;
}

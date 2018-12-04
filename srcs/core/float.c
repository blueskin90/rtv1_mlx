#include "rtv1.h"

int				is_equal_float(float a, float b)
{
	float		c;

	c = a - b;
	c = (c < 0) ? -c : c;
	if (c < TOLERANCE)
		return (1);
	return (0);
}

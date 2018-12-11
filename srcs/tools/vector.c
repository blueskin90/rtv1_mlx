#include "rtv1.h"

int				is_equal_vec(t_vec a, t_vec b)
{
	if (is_equal_float(a.x, b.x) && is_equal_float(a.y, b.y)
			&& is_equal_float(a.z, b.z))
		return (1);
	return (0);
}

int				is_opposite_vec(t_vec a, t_vec b)
{
	return (is_equal_vec(a, vec_opposite(b)));
}

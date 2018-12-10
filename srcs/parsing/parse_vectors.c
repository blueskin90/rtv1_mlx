#include "rtv1.h"

float		get_vec_float(t_elem *elem)
{
	if (elem != NULL)
	{
		if (!check_type_of_key(elem->key, elem->type))
			ft_error(VECTOR_BAD_FORMAT);
		return elem->value->floaty;
	}
	else if (VECTOR_POINT_REQUIRED)
		ft_error(VECTOR_POINT_IS_REQUIRED);
	return (INFINITY);
}

t_vec		parse_vector(t_elem *elem)
{
	//t_vec	vec;
	t_elem	*child_elem;
	
	if (elem != NULL)
	{
		if (!check_type_of_key(elem->key, elem->type))
			ft_error(VECTOR_BAD_FORMAT);
		child_elem = elem->value.objecty;
		return (vec_init0(get_vec_float(
			find_elem_by_key(child_elem, "x")),
			get_vec_float(
			find_elem_by_key(child_elem, "y")),
			get_vec_float(
			find_elem_by_key(child_elem, "z"))));
	}
	else if (VECTOR_REQUIRED)
		ft_error(VECTOR_IS_REQUIRED);
	return vec_init0(INFINITY, INFINITY, INFINITY);
}

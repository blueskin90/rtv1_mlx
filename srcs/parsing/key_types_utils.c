#include "rtv1.h"

static bool		check_float_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "specular") || 
		!compare(key, "diffuse") ||
		!compare(key, "ambiant") ||
		!compare(key, "radius") ||
		!compare(key, "x") ||
		!compare(key, "y") ||
		!compare(key, "z"))
			return (true);
	return (false);
}

static bool		check_array_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "parent_element") ||
		!compare(key, "spheres") ||
		!compare(key, "cylinders") ||
		!compare(key, "planes") ||
		!compare(key, "cones") ||
		!compare(key, "lights")
		)
			return (true);
	return (false);
}
static bool		check_object_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "scene") || 
		!compare(key, "objects") ||
		!compare(key, "camera") ||
		!compare(key, "rotation") ||
		!compare(key, "orientation") ||
		!compare(key, "position") ||
		!compare(key, "rotation") ||
		!compare(key, "color") ||
		!compare(key, "lookat")
		)
			return (true);
	return (false);
}
static bool		check_int_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "r") || 
		!compare(key, "g") ||
		!compare(key, "b"))
			return (true);
	return (false);

}

static bool		check_string_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "name") || 
		!compare(key, "hex"))
			return (true);
	return (false);
}

static bool		check_null_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "specular") || 
		!compare(key, "diffuse") ||
		!compare(key, "ambiant") ||
		!compare(key, "radius") ||
		!compare(key, "x") ||
		!compare(key, "y") ||
		!compare(key, "z") || 
		!compare(key, "r") || 
		!compare(key, "g") ||
		!compare(key, "b"))
			return (true);
	return (false);

}

bool	check_type_of_key(char *key, e_type type)
{
	if (type == FLOAT)	
			return (check_float_keys(key));
	else if (type == OBJECT)
			return (check_object_keys(key));
	else if (type == ARRAY)
			return (check_array_keys(key));
	else if (type == INTEGER)
			return (check_int_keys(key));
	else if (type == NULL_ELEM)
			return (check_null_keys(key));
	else if (type == STRING)
			return (check_string_keys(key));
	return (false);
}

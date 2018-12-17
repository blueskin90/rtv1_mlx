#include "rtv1.h"

// BRILLANCE BRILLANCE INT OU FOAT
// AMBIANT TYPE A CONFIRMER SOIT FLOAT SOIT RGB
// POUR TOUT OBJET : 
// Soit on donne rien => tout a zero, couleur a blanc direction 0.0.1 
// SPHERE DEFAULT : radius est a 1 
// LOOKAT doit etre different que pos
// CYLINDRE DEFAULT : radius est a 1 
// CONE DEFAULT : angle est a 22.5
// soit on donne direction, soit on donne lookat
// direction : vecteur directionel normalize
// lookat : point du lookat - position => normalize
// rotation : en degree
//  SOIT ROLL/dir SOIT up/right
//  SI ON A les troisi/quatre up/right/dir => VERIFIER INTEGRITE
//
// TODO distance cam to viewplane
/* 
			"union" : [
				{
					"methode": "add/sub",
					"objects": [

					]
				}

			],
			*/
static bool		check_float_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "ambiant") ||
		!compare(key, "radius") ||
		!compare(key, "roll") ||
		!compare(key, "r") ||
		!compare(key, "g") ||
		!compare(key, "b") ||
		!compare(key, "x") ||
		!compare(key, "y") ||
		!compare(key, "z"))
			return (true);
	wrong_format(key, FLOAT);
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
		!compare(key, "cameras") ||
		!compare(key, "lights")
		)
			return (true);
	wrong_format(key, ARRAY);
	return (false);
}
static bool		check_object_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "specular") || 
		!compare(key, "diffuse") ||
		!compare(key, "translation") ||
		!compare(key, "up") ||
		!compare(key, "right") ||
		!compare(key, "diffuse") ||
		!compare(key, "scene") || 
		!compare(key, "objects") ||
		!compare(key, "object") ||
		!compare(key, "light") ||
		!compare(key, "camera") ||
		!compare(key, "rotation") ||
		!compare(key, "direction") ||
		!compare(key, "position") ||
		!compare(key, "rotation") ||
		!compare(key, "color") ||
		!compare(key, "lookat")
		)
			return (true);
	wrong_format(key, OBJECT);
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
	wrong_format(key, INTEGER);
	return (false);
}

static bool		check_string_keys(char *key)
{
	int		(*compare)(const char *, const char *);	

	compare = &ft_strcmp;
	if (!compare(key, "name") || 
		!compare(key, "hex"))
			return (true);
	wrong_format(key, STRING);
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
	wrong_format(key, NULL_ELEM);
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

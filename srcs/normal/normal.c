#include "rtv1.h"

void				get_normal(t_ray *ray)
{
	if (ray->obj_hit->type == SPHERE)
		get_spherenormal(ray);
	else if (ray->obj_hit->type == PLANE)
		get_planenormal(ray);
	else if (ray->obj_hit->type == CYLINDER)
		get_cylindernormal(ray);
	else if (ray->obj_hit->type == CONE)
		get_conenormal(ray);
	else
		ray->normal = vec_normalize(ray->obj_hit->dir);
}

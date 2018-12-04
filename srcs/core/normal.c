#include "rtv1.h"

void				get_spherenormal(t_ray *ray)
{
	ray->normal = vec_norm(vec_init(ray->obj_hit->pos, ray->hit_pos));
}

void				get_planenormal(t_ray *ray)
{
	t_vec	vec1;
	t_vec	vec2;

	vec1 = vec_add(ray->obj_hit->pos, ray->obj_hit->dir);
	vec2 = vec_add(ray->obj_hit->pos, vec_opposite(ray->obj_hit->dir));
	if (vec_magnitude(vec_init(ray->pos, vec1)) < vec_magnitude(vec_init(ray->pos, vec2)))
		ray->normal = ray->obj_hit->dir; // prendre celle qui fait le plus face au viewer
	else
		ray->normal = vec_opposite(ray->obj_hit->dir);
}

void				get_cylindernormal(t_ray *ray)
{
	t_vec	center_to_hit;
	float	len;
	t_vec	center_under_hit;

	center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos);
	len = vec_dotproduct(center_to_hit, ray->obj_hit->dir);
	center_under_hit = vec_add(ray->obj_hit->pos, vec_mul(ray->obj_hit->dir, len));
	ray->normal = vec_normalize(vec_init(center_under_hit, ray->hit_pos));
}

void				get_conenormal(t_ray *ray)
{
	t_vec	center_to_hit;
	t_vec	axis1;
	t_vec	axis2;
	t_vec	hit_to_axis1;
	t_vec	hit_to_axis2;
	t_vec	real_axis;
	t_vec	rot_axis;
	t_vec	hypotenuse;
	float	hypotenuse_len;
	t_vec	normal;

	center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos); // a
	axis1 = vec_add(ray->obj_hit->dir, ray->obj_hit->pos);	
	axis2 = vec_add(vec_opposite(ray->obj_hit->dir), ray->obj_hit->pos);
	hit_to_axis1 = vec_init(ray->hit_pos, axis1);
	hit_to_axis2 = vec_init(ray->hit_pos, axis2);
	if (vec_magnitude(hit_to_axis1) < vec_magnitude(hit_to_axis2))
		real_axis = axis1;
	else
		real_axis = axis2;
	real_axis = vec_normalize(vec_sub(real_axis, ray->obj_hit->pos));
	rot_axis = vec_normalize(vec_opposite(vec_crossproduct(vec_normalize(center_to_hit), real_axis)));
	hypotenuse = vec_normalize(matrix_mult_vec(rotmatrix_axis_angle(rot_axis, degtorad(90)), real_axis));
	hypotenuse_len = vec_magnitude(center_to_hit) / cosf(degtorad(90) - ray->obj_hit->params.cone.angle);
	hypotenuse = vec_add(vec_mul(hypotenuse, hypotenuse_len), ray->obj_hit->pos);
	normal = vec_init(ray->hit_pos, hypotenuse);
	normal = vec_normalize(normal);
	ray->normal = normal;
	// marche pas, faire les derivees partielles de fonctions :D

}

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

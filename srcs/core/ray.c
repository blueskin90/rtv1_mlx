#include "rtv1.h"

t_ray			ray_init_lookat(t_vec pos, t_vec lookat)
{
	return (ray_init(pos, vec_sub(lookat, pos)));
}

t_ray			ray_init(t_vec pos, t_vec dir)
{
	t_ray		ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray.length = INFINITY;
	ray.pos = pos;
	ray.dir = vec_norm(dir);
	return (ray);
}
t_ray			ray_to_obj(t_ray ray, t_obj *cyl)
{
	t_ray		new_ray;

	new_ray = ray_init(ray.pos, ray.dir);
	new_ray.pos = vec_sub(ray.pos, cyl->pos);
	new_ray.pos = matrix_mult_vec(cyl->obj_to_world, new_ray.pos);
	new_ray.dir = vec_add(ray.pos, ray.dir);
	new_ray.dir = vec_sub(new_ray.dir, cyl->pos);
	new_ray.dir = matrix_mult_vec(cyl->obj_to_world, new_ray.dir);
	new_ray.dir = vec_sub(new_ray.dir, new_ray.pos);
	new_ray.dir = vec_norm(new_ray.dir);
	return (new_ray);
}

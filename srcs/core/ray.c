#include "rtv1.h"

t_ray			ray_init_lookat(t_vec pos, t_vec lookat)
{
	t_ray		ray;

	ray = ray_init(pos, vec_init(pos, lookat));
	ray.lookat = lookat;
	return (ray_init(pos, vec_init(pos, lookat)));
}

t_ray			ray_init(t_vec pos, t_vec dir)
{
	t_ray		ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray.length = INFINITY;
	ray.pos = pos;
	ray.dir = vec_norm(dir);
	ray.lookat = vec_init0(INFINITY, INFINITY, INFINITY);
	return (ray);
}

t_ray			ray_to_obj(t_ray ray, t_obj *obj)
{
	t_vec		new_pos;
	t_vec		new_dir;

	new_pos = vec_sub(ray.pos, obj->pos);
	new_pos = matrix_mult_vec(obj->world_to_obj, new_pos);

	new_dir = vec_norm(matrix_mult_vec(obj->world_to_obj, ray.dir));
	ray.pos = new_pos;
	ray.dir = new_dir;

	return (ray);
}

t_ray			ray_to_world(t_ray ray, t_obj *obj)
{
	t_vec		new_pos;
	t_vec		new_dir;

	new_pos = matrix_mult_vec(obj->obj_to_world, ray.pos);
	new_pos = vec_add(ray.pos, obj->pos);

	new_dir = vec_add(ray.pos, ray.dir);
	new_dir = matrix_mult_vec(obj->obj_to_world, new_dir);
	new_dir = vec_add(new_dir, obj->pos);
	ray.pos = new_pos;
	ray.dir = vec_norm(vec_init(new_pos, new_dir));
	return (ray);
}



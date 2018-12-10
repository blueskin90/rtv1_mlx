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
t_ray			ray_to_obj(t_ray ray, t_obj *cyl)
{
	t_ray		new_ray;
	t_vec		new_pos;
	t_vec		new_dir;

	new_pos = matrix_mult_vec(cyl->world_to_obj, ray.pos);
	new_pos = vec_sub(new_pos, cyl->pos);


	new_dir = vec_add(ray.pos, ray.dir);
	new_dir = matrix_mult_vec(cyl->world_to_obj, new_dir);
	new_dir = vec_sub(new_dir, cyl->pos);
	new_dir = vec_normalize(vec_init(new_pos, new_dir));
	new_ray = ray_init(new_pos, new_dir);


	return (new_ray);
	new_ray = ray_init(ray.pos, ray.dir);
	new_ray.pos = vec_sub(ray.pos, cyl->pos);
	new_ray.pos = matrix_mult_vec(cyl->world_to_obj, ray.pos);

//	new_ray.dir = vec_sub(new_ray.dir, cyl->pos);
//	if (ray.lookat.x != INFINITY)
//	{
//		new_ray.lookat = vec_sub(ray.lookat, cyl->pos);
//		new_ray.lookat = matrix_mult_vec(cyl->world_to_obj, ray.lookat);
//		new_ray = ray_init_lookat(new_ray.pos, new_ray.lookat);
//	}
//	else
//	{
		new_ray.dir = matrix_mult_vec(cyl->world_to_obj, ray.dir);
		new_ray.dir = vec_norm(new_ray.dir);
//		new_ray.dir = vec_init(new_ray.pos, new_ray.dir);
		new_ray.dir = vec_norm(new_ray.dir);
//	}
	return (new_ray);
}

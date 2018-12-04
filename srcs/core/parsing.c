#include "rtv1.h"

void				obj_add(t_scene *scene, t_obj *obj)
{
	t_obj			*ptr;

	ptr = scene->objs;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = obj;
	}
	else
		scene->objs = obj;
}

void				light_add(t_scene *scene, t_obj *light)
{
	t_obj			*ptr;

	ptr = scene->lights;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = light;
	}
	else
		scene->lights = light;
}

void				camera_add(t_scene *scene, t_obj *camera)
{
	t_obj			*ptr;

	ptr = scene->cameras;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = camera;
	}
	else
		scene->cameras = camera;
}

int					parse_scene(t_env *env)
{
	t_scene			*scene;
	t_vec			pos;
	t_vec			lookat;
	t_RGB			color;
	t_obj			*objptr;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));

	// 10 obj
	pos = vec_init0(-35, 30, -30);
	lookat = vec_init0(0, 0, 6);
	color = rgb_init(0xa610ff);
//	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
//	obj_sphere_params(objptr, 5);
//	obj_add(scene, objptr);
	
	pos = vec_init0(5, 0, 20);
	lookat = vec_init0(0, 0, 6);
	color = rgb_init(0xffaaaa);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 5);
	obj_add(scene, objptr);


	pos = vec_init0(25, 12, -12);
	lookat = vec_init0(0, 0, 6);
	color = rgb_init(0x10ff10);
//	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
//	obj_sphere_params(objptr, 7);
//	obj_add(scene, objptr);


	pos = vec_init0(-10, 0, 20);
	color = rgb_init(0x30ff30);
//	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
//	obj_sphere_params(objptr, 0.5);
//	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	lookat = vec_init0(0, -9, 0);
	pos = vec_init0(0, -10, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	lookat = vec_init0(6, 6, 6);
	pos = vec_init0(10, -2, -3);
	color = rgb_init(0xaaff00);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cylinder_params(objptr, 1);
	obj_add(scene, objptr);
	
	pos = vec_init0(6, 6, 6);
	color = rgb_init(0x9010f0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 2);
	obj_add(scene, objptr);

	pos = vec_init0(10, -2, -3);
	color = rgb_init(0x9010f0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 2);
	obj_add(scene, objptr);

	pos = vec_init0(-11, 1, 21);
	color = rgb_init(0x8080ff);
//	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
//	obj_sphere_params(objptr, 0.7);
//	obj_add(scene, objptr);


	pos = vec_init0(-10, 0, 20);
	lookat = vec_init0(-11, 1, 21);
	color = rgb_init(0xaabbcc);
//	color = rgb_init(0xff5050);
//	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
//	obj_cone_params(objptr, 22);
//	obj_add(scene, objptr);
	
	color = rgb_init(0xaabbcc);
	lookat = vec_init0(0, 50, 0);
	pos = vec_init0(0, 51, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	lookat = vec_init0(49, 0, 0);
	pos = vec_init0(50, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	lookat = vec_init0(-49, 0, 0);
	pos = vec_init0(-50, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	lookat = vec_init0(0, 0, 50);
	pos = vec_init0(0, 0, 49);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

// 2 lights

	lookat = vec_init0(0, -3, 1);
	pos = vec_init0(15, 25, -15);
	color = rgb_init(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.6);
	light_add(scene, objptr);

	pos = vec_init0(-15, 25, -15);
	color = rgb_init(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.9);
	light_add(scene, objptr);

// 1 camera

	env->scene = scene;
	pos = vec_init0(-30, 10, 20);
	lookat = vec_init0(5, 0, 20);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_camera_params(objptr, 60.0);
	camera_add(scene, objptr);
	return (1);
}

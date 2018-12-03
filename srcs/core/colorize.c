/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/03 09:13:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

float			get_ratio(t_vec hit_pos, t_vec normal)
{
	t_obj		*ptr;
	float		total;
	float		actual;
	t_vec		to_light;
	t_ray		to_light_ray;

	total = 0.0;
	actual = 0.1;
	ptr = scene_get()->lights;
	while (ptr)
	{
		to_light = vec_norm(vec_init(hit_pos, ptr->pos));
		to_light_ray = ray_init(hit_pos, to_light);
		shoot_ray(&to_light_ray);
		if (!(to_light_ray.length != INFINITY && to_light_ray.length < vec_magnitude(vec_init(hit_pos, ptr->pos))))
			actual += ptr->params.light.intensity * vec_dotproduct(normal, to_light);
		total += ptr->params.light.intensity;
		ptr = ptr->next;
	}
	return (actual / total);
}

float			get_ambiant(t_ray *ray)
{
	(void)ray;
	return (0.2); // 0.1 * ray->obj_hit->ambient_value; tweak la value (0.2 trop clair la ou rien n;est allume)
}

float			get_diffuse(t_ray *ray, t_scene *scene) // reduire cette fonction plus tard
{
	t_obj		*ptr;
	float		total;
	float		actual;
	t_vec		to_light;
	t_ray		to_light_ray;
	float		dotproduct;

	total = 0.0;
	actual = 0.0;
	ptr = scene->lights;
	while (ptr)
	{
		to_light = vec_norm(vec_init(ray->hit_pos, ptr->pos));
		to_light_ray = ray_init(ray->hit_pos, to_light);
		shoot_ray(&to_light_ray);
		if (!(to_light_ray.length != INFINITY && to_light_ray.length < vec_magnitude(vec_init(ray->hit_pos, ptr->pos)) && to_light_ray.obj_hit->color.value != 0xffffff))
		{// enlever le x0fffff
			dotproduct = vec_dotproduct(ray->normal, to_light);
			dotproduct = (dotproduct >= 0) ? dotproduct : 0;
			actual += ptr->params.light.intensity * dotproduct;
		}
		total += ptr->params.light.intensity;
		ptr = ptr->next;
	}
	return (actual / total);
}

float			get_specular(t_ray *ray, t_scene *scene, t_obj *cam)
{
	t_obj		*ptr;
	float		total;
	float		actual;
	t_ray		to_light_ray;
	t_ray		reflection;
	float		dotproduct;
	t_vec		to_light;

	total = 0.0;
	actual = 0.0;
	ptr = scene->lights;
	while (ptr)
	{
		to_light = vec_norm(vec_init(ray->hit_pos, ptr->pos));
		to_light_ray = ray_init(ray->hit_pos, to_light);
		shoot_ray(&to_light_ray);
		if (!(to_light_ray.length != INFINITY && to_light_ray.length < vec_magnitude(vec_init(ray->hit_pos, ptr->pos))))
		{
			to_light_ray.pos = ray->hit_pos;
			to_light_ray.dir = vec_opposite(to_light);
			to_light_ray.normal = ray->normal;
			reflection = reflect_ray(&to_light_ray);
			dotproduct = vec_dotproduct(reflection.dir, vec_norm(vec_init(ray->hit_pos, cam->pos)));
			dotproduct = (dotproduct >= 0) ? dotproduct : 0;
			dotproduct = powf(dotproduct, 100);
			actual += dotproduct * ptr->params.light.intensity; // * ptr->obj_hit->specular_value
		}
		total += ptr->params.light.intensity;
		ptr = ptr->next;
	}
	return (actual / total);
}
/*
int				colorization(t_ray *ray, t_env *env)
{
	float		ambiant;
	float		diffuse;
	float		specular;

	t_obj		*ptr;

	ptr = scene_get()->lights;
	ambiant = get_ambiant(ray);
	diffuse = get_diffuse(ray, env->scene);
	specular = get_specular(ray, scene_get(), camera_get());

	t_RGB		rgb;
	rgb = ray->obj_hit->color;
	rgb = rgb_mul(rgb, ambiant + diffuse + specular);
	return (rgb.value);
}
*/


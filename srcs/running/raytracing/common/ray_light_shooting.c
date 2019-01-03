/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_light_shooting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 08:50:30 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 17:52:32 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_RGB			rgb_add(t_RGB a, t_RGB b)
{
	t_RGB		c;

	c.r = clampf(a.r + b.r, 0, 1);
	c.g = clampf(a.g + b.g, 0, 1);
	c.b = clampf(a.b + b.b, 0, 1);
	rgb_updatevalue(&c);
	return (c);
}

t_RGB			rgb_init(int value)
{
	t_RGB		rgb;
	int			r;
	int			g;
	int			b;

	r = (value & 0xff0000) >> 16;
	g = (value & 0xff00) >> 8;
	b = value & 0xff;
	rgb.r = (float)r / 255.0;
	rgb.g = (float)g / 255.0;
	rgb.b = (float)b / 255.0;
	rgb.value = value;
	return (rgb);
}

void			rgb_updatevalue(t_RGB *rgb)
{
	int			r;
	int			g;
	int			b;

	r = (int)roundf(rgb->r * 255);
	g = (int)roundf(rgb->g * 255);
	b = (int)roundf(rgb->b * 255);
	rgb->value = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

t_RGB			rgb_mul_rgb(t_RGB a, t_RGB b)
{
	t_RGB		c;

	c.r = clampf(a.r * b.r, 0, 1);
	c.g = clampf(a.g * b.g, 0, 1);
	c.b = clampf(a.b * b.b, 0, 1);
	rgb_updatevalue(&c);
	return (c);
}


t_RGB			rgb_mul(t_RGB a, float scalar)
{
	t_RGB		b;

	b.r = clampf(a.r * scalar, 0, 1);
	b.g = clampf(a.g * scalar, 0, 1);
	b.b = clampf(a.b * scalar, 0, 1);
	rgb_updatevalue(&b);
	return (b);
}

t_RGB			rgb_div(t_RGB a, float scalar)
{
	t_RGB		b;

	b.r = clampf(a.r / scalar, 0, 1);
	b.g = clampf(a.g / scalar, 0, 1);
	b.b = clampf(a.b / scalar, 0, 1);
	rgb_updatevalue(&b);
	return (b);
}

// prendre en compte toutes les lights et faire la moyenne des couleurs
t_RGB			get_ambiant(t_ray *ray)
{
	return (rgb_mul_rgb(ray->obj_hit->color, rgb_mul(rgb_init(0xffffff), 0.2)));
}

t_ray			reflect_ray(t_ray *ray)
{
	t_matrix	rotmatrix;
	t_vec		reflected;

	rotmatrix = rotmatrix_axis_angle(ray->normal, degtorad(180));
	reflected = matrix_mult_vec(rotmatrix, vec_opposite(ray->dir));
	return (ray_init(ray->hit_pos, vec_norm(reflected)));
}

t_vec			reflect_vector(t_vec vec, t_vec axis)
{
	t_matrix	rotmatrix;

	rotmatrix = rotmatrix_axis_angle(axis, degtorad(180));
	return (vec_normalize(matrix_mult_vec(rotmatrix, vec)));
}

t_RGB			get_specular(t_ray *ray, t_ray to_light, t_obj light, t_obj *cam)
{
	t_RGB		rgb;
	t_vec		reflect;
	t_vec		to_view;
	float		mult_value;
	float		dotproduct;

	dotproduct = vec_dotproduct(vec_normalize(
				vec_init(ray->hit_pos, light.pos)), ray->normal);
	if (dotproduct <= 0)
		return (rgb_init(0));
	reflect = reflect_vector(vec_normalize(vec_init(ray->hit_pos, light.pos)),
			ray->normal);
	to_view = vec_normalize(vec_init(ray->hit_pos, cam->pos));
	mult_value = maxf(0, vec_dotproduct(reflect, to_view));
	mult_value = powf(mult_value, ray->obj_hit->brillance);
	mult_value *= light.params.light.intensity;
	rgb = rgb_mul(light.color, mult_value);
	rgb = rgb_mul_rgb(rgb, ray->obj_hit->specular);
	(void)to_light;
	return (rgb);
}

t_RGB			get_diffuse(t_ray *ray, t_ray to_light, t_obj light)
{
	t_RGB		rgb;
	float		dotproduct;

	dotproduct = vec_dotproduct(ray->normal,
			vec_normalize(vec_init(ray->hit_pos, light.pos)));
	if (dotproduct <= 0)
		return (rgb_init(0));
	dotproduct *= light.params.light.intensity;
	rgb = rgb_mul(light.color, dotproduct);
	rgb = rgb_mul_rgb(rgb, ray->obj_hit->diffuse);
	(void)to_light;
	return (rgb);
}


void			shoot_ray_lights(t_scene *scene, t_ray *ray, t_obj *cam)
{
	t_RGB		finalcolor;
	t_obj		*ptr;
	t_ray		to_light;

	if (ray->length == INFINITY)
		return ;
	finalcolor = get_ambiant(ray);
	ptr = scene->lights;
	while (ptr)
	{
		to_light = ray_init_lookat(ray->hit_pos, ptr->pos);
		shoot_ray(scene, &to_light);
		if (to_light.length > vec_magnitude(vec_init(ray->hit_pos, ptr->pos)))
		{
			finalcolor = rgb_add(finalcolor, get_diffuse(ray, to_light, *ptr));
			finalcolor = rgb_add(finalcolor, get_specular(ray, to_light, *ptr, cam));
		}
		ptr = ptr->next;
	}
	ray->color = finalcolor;
}

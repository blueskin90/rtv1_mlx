/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/25 05:42:29 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

float			get_ratio(t_env *env, t_vec hit_pos, t_vec normal)
{
	t_light		*ptr;
	float		total;
	float		actual;
	t_vec		to_light;
	t_ray		to_light_ray;

	total = 0.0;
	actual = 0.1;
	ptr = env->scene->light;
	while (ptr)
	{
		to_light = vec_norm(vec_init(hit_pos, ptr->pos));
		to_light_ray = ray_init(hit_pos, to_light);
		shoot_ray(&to_light_ray, env->scene);
		if (!(to_light_ray.length != INFINITY && to_light_ray.length < vec_magnitude(vec_init(hit_pos, env->scene->light->pos))))
			actual += ptr->intensity * vec_dotproduct(normal, to_light);
		total += ptr->intensity;
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
	t_light		*ptr;
	float		total;
	float		actual;
	t_vec		to_light;
	t_ray		to_light_ray;
	float		dotproduct;

	total = 0.0;
	actual = 0.0;
	ptr = scene->light;
	while (ptr)
	{
		to_light = vec_norm(vec_init(ray->hit_pos, ptr->pos));
		to_light_ray = ray_init(ray->hit_pos, to_light);
		shoot_ray(&to_light_ray, scene);
		if (!(to_light_ray.length != INFINITY && to_light_ray.length < vec_magnitude(vec_init(ray->hit_pos, ptr->pos))))
		{
			dotproduct = vec_dotproduct(ray->normal, to_light);
			dotproduct = (dotproduct >= 0) ? dotproduct : 0;
			actual += ptr->intensity * dotproduct;
		}
		total += ptr->intensity;
		ptr = ptr->next;
	}
	return (actual / total);
}

t_ray			reflect_ray(t_ray *ray)
{
	t_matrix	rotmatrix;
	t_vec		reflected;

	rotmatrix = rotmatrix_axis_angle(ray->normal, degtorad(180));
	reflected = matrix_mult_vec(rotmatrix, vec_opposite(ray->direction));
	return (ray_init(ray->hit_pos, vec_norm(reflected)));
}

float			get_specular(t_ray *ray, t_scene *scene, t_camera *cam)
{
	t_light		*ptr;
	float		total;
	float		actual;
	t_ray		to_light_ray;
	t_ray		reflection;
	float		dotproduct;
	t_vec		to_light;

	total = 0.0;
	actual = 0.0;
	ptr = scene->light;
	while (ptr)
	{
		to_light = vec_norm(vec_init(ray->hit_pos, ptr->pos));
		to_light_ray = ray_init(ray->hit_pos, to_light);
		shoot_ray(&to_light_ray, scene);
		if (!(to_light_ray.length != INFINITY && to_light_ray.length < vec_magnitude(vec_init(ray->hit_pos, ptr->pos))))
		{
			to_light_ray.origin = ray->hit_pos;
			to_light_ray.direction = vec_opposite(to_light);
			to_light_ray.normal = ray->normal;
			reflection = reflect_ray(&to_light_ray);
			dotproduct = vec_dotproduct(reflection.direction, vec_norm(vec_init(ray->hit_pos, cam->pos)));
			dotproduct = (dotproduct >= 0) ? dotproduct : 0;
			dotproduct = powf(dotproduct, 100);
			actual += dotproduct * ptr->intensity; // * ptr->obj_hit->specular_value
		}
		total += ptr->intensity;
		ptr = ptr->next;
	}
	return (actual / total);
}

int				colorization(t_ray *ray, t_env *env)
{
//	t_hsl		color;

	float		ambiant;
	float		diffuse;
	float		specular;

//	color = ray->obj_hit->color.type.hsl;
	ambiant = get_ambiant(ray);
	diffuse = get_diffuse(ray, env->scene);
	specular = get_specular(ray, env->scene, env->camera);
//	color.l *= (ambiant + diffuse + specular);
//	color.l = (color.l > 1) ? 1 : color.l;

	t_color		rgb;
	rgb = ray->obj_hit->color;
	rgb.rgb.r *= (ambiant + diffuse + specular);
	rgb.rgb.r = (rgb.rgb.r > 255) ? 255 : rgb.rgb.r;
	rgb.rgb.g *= (ambiant + diffuse + specular);
	rgb.rgb.g = (rgb.rgb.g > 255) ? 255 : rgb.rgb.g;
	rgb.rgb.b *= (ambiant + diffuse + specular);
	rgb.rgb.b = (rgb.rgb.b > 255) ? 255 : rgb.rgb.b;
	return (get_rgb(rgb.rgb.r, rgb.rgb.g, rgb.rgb.b));
//	return (hsl_to_rgb(color));
}
/*
int		colorization(t_env *env, t_ray ray, float nearest, t_obj *obj_hit)
{
	t_vec		hit_pos;
	t_vec		normal
	t_vec		to_light;
	t_hsl		color;
	float		ratio;
	float		to_light_hit;
	t_ray		to_light_ray;

	if (obj_hit->type == CYLINDER)
		return(0xffffff);
	hit_pos = vec_add(vec_mul(ray.direction, nearest), ray.origin);
	to_light = vec_norm(vec_init(hit_pos, env->scene->light->pos));
	to_light_ray = ray_init(hit_pos, to_light);
	shoot_ray(&to_light_ray, env->scene);
	to_light_hit = to_light_ray.length;
	color.h = obj_hit->color.type.hsl.h;
	color.s = obj_hit->color.type.hsl.s;
	color.l = obj_hit->color.type.hsl.l;
	if (to_light_hit != INFINITY && to_light_hit < vec_magnitude(vec_init(hit_pos, env->scene->light->pos)))
		ratio = 0.01;
	if (obj_hit->type == SPHERE)
		normal = vec_norm(vec_init(obj_hit->pos, hit_pos));
	else if (obj_hit->type == PLANE)
	{
		normal = vec_norm(obj_hit->params.plane.normal); // prendre celle qui fait le plus face au viewer
	}
	else if (obj_hit->type == CYLINDER)
	{
		normal = vec_normalize(vec_add(vec_init0(hit_pos.x, 0, hit_pos.z), vec_opposite(vec_init0(obj_hit->pos.x, 0, obj_hit->pos.z))));
	}
	else
		normal = obj_hit->rot;
	ratio = get_ratio(env, hit_pos, normal);
//	ratio = env->scene->light->intensity * vec_dotproduct(normal, to_light); // ici faire que le ratio soit le ratio de toutes les lampes genre : 2 lampes a 0.6 et a 0.9 = total a 1.5, on divise le resultat des 2 ratios par 1.5 et on a notre ratio final (je crois);
	ratio = (ratio < 0.01 ) ? 0.01 : ratio;
	color.l *= ratio;
	return (hsl_to_rgb(color));
}	
*/

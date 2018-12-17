/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/16 17:59:43 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

t_obj	*parse_dir_lookat_pos(t_elem *elem, t_obj *obj)
{
	t_vec	dir;
	t_vec	lookat;

	obj->pos = default_vec(required_vec(parse_vector(
					find_elem_by_key(elem, "position")),
				POSITION_REQUIRED,"Position"),
			vec_init0(0.0, 0.0, 0.0));
	dir = parse_vector(find_elem_by_key(elem, "direction"));
	lookat = parse_vector(find_elem_by_key(elem, "lookat"));
	if (min_of_vec(dir) != INFINITY && min_of_vec(lookat) != INFINITY)
	{
		if (vec_is_0((dir = default_vec(dir, vec_init0(0.0, 0.0, 0.0)))))
			ft_error(DIR_CANNOT_POINT_0);
		dir = vec_normalize(dir);
		if (vec_is_0(lookat = vec_sub(
						default_vec(lookat, vec_init0(0.0, 0.0, 0.0)), obj->pos)))
			ft_error(LOOKAT_CANNOT_POINT_0);
		lookat = vec_normalize(lookat);
		if (!is_equal_vec(dir, lookat))
			ft_error(LOOKAT_DIRECTION_CONFLICT);
		obj->dir = dir;	
}
	else if (min_of_vec(dir) != INFINITY)
	{
		if (vec_is_0((dir =  default_vec(dir, vec_init0(0.0, 0.0, 0.0)))))
			ft_error(DIR_CANNOT_POINT_0);
		obj->dir = vec_normalize(dir);
	}
	else if (min_of_vec(lookat) != INFINITY)
	{
		if (vec_is_0(lookat = vec_sub(
						default_vec(lookat, vec_init0(0.0, 0.0, 0.0)), obj->pos)))
			ft_error(LOOKAT_CANNOT_POINT_0);
		obj->dir = vec_normalize(lookat);
	}
	else if (min_of_vec(dir) == INFINITY && min_of_vec(lookat) == INFINITY)
		obj->dir = vec_init0(0.0, 0.0, 1);
	return (obj);
}

t_obj	*parse_rotation_translation(t_elem *elem, t_obj *obj)
{
	t_vec	translation;
	t_vec	rotation;

	translation = default_vec(required_vec(
		parse_vector(find_elem_by_key(elem, "translation")),
		TRANSLATION_REQUIRED,"translation"),vec_init0(0.0, 0.0, 0.0));
	rotation = default_vec(required_vec(
		parse_vector(find_elem_by_key(elem, "rotation")),
		ROTATION_REQUIRED,"translation"), vec_init0(0.0, 0.0, 0.0));
	return (obj);
}

t_obj	*parse_one_object(t_elem *elem, t_obj *(*parse_obj)(t_elem *, t_obj *))
{
	t_obj			*obj;
	t_elem			*child_elem;

	// TODO check type of key
	check_type_of_key("object", elem->type);
	obj = new_obj();
	child_elem = elem->value.objecty;
	obj = parse_dir_lookat_pos(child_elem, obj);
	obj = parse_obj(child_elem, obj);
	obj->color = parse_color(find_elem_by_key(child_elem, "color"));
	obj->specular = parse_color(find_elem_by_key(child_elem, "specular"));
	printf("RGB : [%f, %f, %f]\n", obj->specular.r, obj->specular.g, obj->specular.b);
	printf("HEX : %X\n", obj->specular.value);
	obj->diffuse = parse_color(find_elem_by_key(child_elem, "diffuse"));
	obj->ambiant = default_float(parse_float(
					find_elem_by_key(child_elem, "ambiant")), 0.0);
	obj = parse_roll_up_right(child_elem, obj);
	obj = parse_rotation_translation(child_elem, obj);

	/*
	obj->position = parse_vector(find_elem_by_key(child_elem, "specular"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "diffuse"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "position"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "direction"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "lookat"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "translation"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "rotation"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "up"));
	obj->direction = parse_vector(find_elem_by_key(child_elem, "right"));
	obj->brillance = get_vec_float(find_elem_by_key(child_elem, "brillance"));
	obj->ambiant = get_vec_float(find_elem_by_key(child_elem, "ambiant"));
	obj->roll = get_vec_float(find_elem_by_key(child_elem, "roll"));
	*/
	return (obj);
	// si l objet est vide
}


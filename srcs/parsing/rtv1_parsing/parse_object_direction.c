/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_direction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 19:37:59 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/18 16:57:24 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec			get_right_dir(t_vec dir)
{
	if (is_equal_vec(dir, vec_y()))
		return (vec_x());
	else if (is_equal_vec(dir, vec_opposite(vec_y())))
		return (vec_x());
	return (vec_normalize(vec_opposite(vec_crossproduct(dir, vec_y()))));
}

t_vec			get_up_dir(t_vec dir, t_vec right)
{
	return (vec_norm(vec_crossproduct(dir, right)));
}

static t_vec			vec_rot_zaxis_angle(t_vec v, t_vec zaxis, float angle)
{
	t_matrix	rotmatrix;

	rotmatrix = rotmatrix_axis_angle(zaxis, -angle);
	return (matrix_mult_vec(rotmatrix, v)); 	
}

void					parse_up_right_vec(t_elem *elem, t_obj *obj)
{
	obj->roll = default_float(required_float(parse_degree_to_rad(
					parse_float(find_elem_by_key(elem, "roll"))),
				ROLL_REQUIRED, "Roll"), 0.0);
	obj->right = get_right_dir(obj->dir);
	obj->right = vec_rot_zaxis_angle(obj->right, obj->dir, obj->roll);
	obj->up = get_up_dir(obj->dir, obj->right);
	obj->world_to_obj = world_to_obj_matrix(obj);
	obj->obj_to_world = obj_to_world_matrix(obj);
}

void					parse_dir_lookat_pos(t_elem *elem, t_obj *obj)
{
	t_vec	dir;
	t_vec	lookat;

	obj->pos = default_vec(required_vec(parse_vector(
					find_elem_by_key(elem, "position")),
				POSITION_REQUIRED,"Position"),
			vec_init0(0.0, 0.0, 0.0));
	dir = parse_vector(find_elem_by_key(elem, "direction"));
	print_vec(dir);
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
		obj->dir = vec_init0(0.0, 0.0, 1.0);
}

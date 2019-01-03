/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_direction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 19:37:59 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/17 23:59:41 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
// TODO ON LA FOUT OU ELLE
static t_vec			vec_rot_zaxis_angle(t_vec v, t_vec zaxis, float angle)
{
	t_matrix	rotmatrix;

	rotmatrix = rotmatrix_axis_angle(zaxis, -angle);
	return (matrix_mult_vec(rotmatrix, v)); 	
}

static bool	not_zero_or_inf(t_vec vec)
{
	t_vec	tmp;

	tmp = default_vec(vec, vec_init0(0.0, 0.0, 0.0));
	if (tmp.x == 0 && tmp.y == 0.0 && tmp.z == 0.0)
		return (false);
	return (true);
}
static void get_direction_info(t_elem *elem, t_obj *obj)
{
	obj->pos = default_vec(required_vec(parse_vector(
					find_elem_by_key(elem, "position")),
				POSITION_REQUIRED,"Position"),
			vec_init0(0.0, 0.0, 0.0));
	obj->dir = required_vec(parse_vector(find_elem_by_key(elem, "direction")),
			DIR_REQUIRED,"direction");
	obj->up = required_vec(parse_vector(find_elem_by_key(elem, "up")),
			UP_REQUIRED,"up");
	obj->right = required_vec(parse_vector(find_elem_by_key(elem, "right")),
			RIGHT_REQUIRED,"right");
	obj->roll = required_float(parse_degree_to_rad(parse_float(find_elem_by_key(elem, "roll"))), ROLL_REQUIRED, "Roll");
	printf("roll : %f\n", obj->roll);
}

static t_vec	get_dir(t_vec dir, char axis)
{
	t_vec	tmp;

	tmp = vec_init0(0.0, 0.0, 0.0);
	if (axis == 'r')
	{
		if (dir.x == 0.0 && fabs(dir.y) == 1.0 && dir.z == 0.0)
			tmp =  vec_init0(0.0, 0.0, 1.0);
		else
			tmp = vec_normalize(
					vec_crossproduct(
						dir, 
						vec_init0(0.0,1.0,0.0)
						)
					);
	}
	//if (roll != INFINITY)
	//	tmp = vec_rot_zaxis_angle(tmp, dir, roll);
	return (tmp);
}

static t_vec	get_right(t_vec dir, float roll, char axis)
{
	t_vec	right;

	right = vec_init0(0.0, 0.0, 0.0);
	if (axis == 'd')
	{
		if (dir.x == 0.0 && fabs(dir.y) == 1.0 && dir.z == 0.0)
			right =  vec_init0(1.0, 0.0, 0.0);
		else
			right = vec_normalize(
					vec_opposite(
						vec_crossproduct(
							dir, 
							vec_init0(0.0,1.0,0.0)
							)
						)
					);
		if (roll != INFINITY)
			right = vec_rot_zaxis_angle(right, dir, roll);
	}
	else if (axis == 'u')
	{
		if (dir.x == 0.0 && dir.y == 0.0 && fabs(dir.z) == 1.0)
			right =  vec_init0(1.0, 0.0, 0.0);
		else
			right = vec_normalize(
					vec_crossproduct(
						dir, 
						vec_init0(0.0,0.0,1.0)
						)
					);
	}
	return (right);
}



static void		simulate_obj_dir_vectors(t_obj *obj, char axis)
{
	if (axis == 'd')
	{
		obj->dir = vec_normalize(default_vec(obj->dir, vec_init0(0.0, 0.0, 0.0)));
		obj->right = get_right(obj->dir, obj->roll, axis);
		obj->up = vec_normalize(vec_crossproduct(obj->dir, obj->right));
	}
	else if (axis == 'u')
	{
		obj->up = vec_normalize(default_vec(obj->up, vec_init0(0.0, 0.0, 0.0)));
		obj->right = get_right(obj->up, obj->roll, axis);
		obj->dir = vec_normalize(vec_crossproduct(obj->right, obj->up));
	}
	else if (axis == 'r')
	{
		printf("ONLY R\n\n\n\n");
		obj->right = vec_normalize(default_vec(obj->right, vec_init0(0.0, 0.0, 0.0)));
		obj->dir = get_dir(obj->right, 'r');
		obj->up = vec_normalize(vec_crossproduct(obj->dir, obj->right));
	}
}

static t_obj	*get_temp_direction_info(t_obj *obj)
{
	t_obj	*temp_obj;

	temp_obj = new_obj();
	ft_bzero(temp_obj, sizeof(t_obj));
	//if (min_of_vec(obj->pos) == INFINITY)
	//	ft_error(CANNOT_POSITION);
	temp_obj->pos = vec_init0(obj->pos.x, obj->pos.y, obj->pos.z);
	temp_obj->dir = vec_init0(obj->dir.x, obj->dir.y, obj->dir.z);
	temp_obj->up = vec_init0(obj->up.x, obj->up.y, obj->up.z);
	temp_obj->right = vec_init0(obj->right.x, obj->right.y, obj->right.z);
	temp_obj->roll = obj->roll;	
	if (min_of_vec(obj->dir) != INFINITY && not_zero_or_inf(obj->dir))
		simulate_obj_dir_vectors(temp_obj, 'd');
	else if (min_of_vec(obj->up) != INFINITY && not_zero_or_inf(obj->up))
		simulate_obj_dir_vectors(temp_obj, 'u');
	else if (min_of_vec(obj->right) != INFINITY && not_zero_or_inf(obj->right))
		simulate_obj_dir_vectors(temp_obj, 'r');
	else{
		printf("roll : %f\n", obj->roll);
		if (ROLL_OR_UP_OR_RIGHT_REQUIRED && obj->roll == INFINITY)
			ft_error(DIR_UP_RIGHT_ROLL_IS_REQUIRED);
		temp_obj->dir = vec_init0(0.0, 0.0, 1.0);
		simulate_obj_dir_vectors(temp_obj, 'd');
	}
	return (temp_obj);
}

static bool	equal_vec_inf(t_vec a, t_vec b)
{
	if (a.x == INFINITY && a.y == INFINITY && a.z == INFINITY)
		return (true);
	a = vec_normalize(default_vec(a, vec_init0(0.0, 0.0, 0.0)));
	b = vec_normalize(default_vec(b, vec_init0(0.0, 0.0, 0.0)));
	if (is_equal_vec(a ,b))
		return (true);
	return (false);
}

t_obj	*parse_object_direction(t_elem *elem, t_obj *obj)
{
	t_obj	*tmp;
	t_vec	vec0;

	vec0 = vec_init0(0.0, 0.0, 0.0);
	get_direction_info(elem, obj);
	tmp = get_temp_direction_info(obj);
	printf("OBJ : \n");
	printf("right : ");
	print_vec(obj->right);
	printf("up : ");
	print_vec(obj->up);
	printf("dir : ");
	print_vec(obj->dir);
	// TODO gerer lookat et verifier que pas 0,0,0 sur les 3 autres vec
	// et le 0,0,0 de lookat SI pos est egal a 0,0,0
	printf("TMP OBJ : \n");
	printf("right : ");
	print_vec(tmp->right);
	printf("up : ");
	print_vec(tmp->up);
	printf("dir : ");
	print_vec(tmp->dir);

	if (!equal_vec_inf(obj->dir, tmp->dir) ||
			!equal_vec_inf(obj->right, tmp->right) ||
			!equal_vec_inf(obj->up, tmp->up))
		ft_error(DIRECTION_CONFLICT);
	obj->pos = vec_init0(tmp->pos.x, tmp->pos.y, tmp->pos.z);
	obj->dir = vec_init0(tmp->dir.x, tmp->dir.y, tmp->dir.z);
	obj->up = vec_init0(tmp->up.x, tmp->up.y, tmp->up.z);
	obj->right = vec_init0(tmp->right.x, tmp->right.y, tmp->right.z);
	obj->roll = default_float(tmp->roll, 0.0);
	free(tmp);
	return (obj);
}

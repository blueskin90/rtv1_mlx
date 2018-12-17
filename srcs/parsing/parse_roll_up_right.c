/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_roll_up_right.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:24:53 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/16 18:10:47 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec			vec_rot_zaxis_angle(t_vec v, t_vec zaxis, float angle)
{
		t_matrix	rotmatrix;

		rotmatrix = rotmatrix_axis_angle(zaxis, -angle);
		return (matrix_mult_vec(rotmatrix, v)); 	
}

static t_obj	*up_right_roll_all_given(t_obj *obj, float roll)
{
		t_vec	tmpRight;
		t_vec	tmpUp;

		obj->right = vec_normalize(default_vec(obj->right, vec_init0(0.0, 0.0, 0.0)));
		obj->up = vec_normalize(default_vec(obj->up, vec_init0(0.0, 0.0, 0.0)));
		if (obj->dir.x == 0.0 && fabs(obj->dir.y) == 1.0 && obj->dir.z == 0.0)
				tmpRight =  vec_init0(1.0, 0.0, 0.0);
		else
				tmpRight = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, 
												vec_init0(0.0,1.0,0.0))));
		tmpRight = vec_rot_zaxis_angle(tmpRight, obj->dir, roll);
		printf("tmpRight : ");
		print_vec(tmpRight);
		printf("Right : ");
		print_vec(obj->right);
		if (!is_equal_vec(tmpRight, obj->right))
				ft_error(ROLL_RIGHT_UP_CONFLICT);
		tmpUp = vec_normalize(vec_crossproduct(obj->dir, obj->right));
		printf("tmpUp : ");
		print_vec(tmpUp);
		if (!is_equal_vec(tmpUp, obj->up))
				ft_error(ROLL_RIGHT_UP_CONFLICT);
		return (obj);
}

static t_obj	*up_right_roll_infinity(t_obj *obj)
{

		printf("NEITHER RIGHT ROLL OR UP GIVEN\n");
		if (obj->dir.x == 0.0 && fabs(obj->dir.y) == 1.0 && obj->dir.z == 0.0)
				obj->right =  vec_init0(1.0, 0.0, 0.0);
		else
				obj->right = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, 
												vec_init0(0.0,1.0,0.0))));
		obj->up = vec_normalize(vec_crossproduct(obj->dir, obj->right));
		return (obj);	
}

static t_obj	*up_right_roll_one_given(t_obj *obj, float roll, float minUp, float minRight)
{
		t_vec tmpUp;
		t_vec tmpRight;

		if (minUp != INFINITY) 
		{
				obj->up = vec_normalize(default_vec(obj->up, vec_init0(0.0, 0.0, 0.0)));
				obj->right = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, obj->up)));
				tmpUp = vec_normalize(vec_crossproduct(obj->dir, obj->right));
				if (!is_equal_vec(tmpUp, obj->up))
						ft_error(UP_DIR_CONFLICT);
		}
		else if (minRight != INFINITY) 
		{
				printf("ONLY RIGHT GIVEN\n");
				obj->right = vec_normalize(default_vec(obj->right, vec_init0(0.0, 0.0, 0.0)));
				obj->up = vec_normalize(vec_crossproduct(obj->dir, obj->right));
				tmpRight = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, obj->up)));
				if (!is_equal_vec(tmpRight, obj->right))
						ft_error(RIGHT_DIR_CONFLICT);

		}
		else if(roll != INFINITY)
		{
				obj = up_right_roll_infinity(obj);
				obj->right = vec_rot_zaxis_angle(obj->right, obj->dir, roll);
				obj->up = vec_rot_zaxis_angle(obj->up, obj->dir, roll);
		}
		return (obj);

}

static t_obj	*up_right_roll_two_given(t_obj *obj, float roll, float minUp, float minRight)
{
		t_vec	tmpRight;
		t_vec	tmpUp;

		if (minUp != INFINITY && minRight != INFINITY)
		{
				obj->up = vec_normalize(default_vec(obj->up, vec_init0(0.0, 0.0, 0.0)));
				obj->right = vec_normalize(default_vec(obj->right, vec_init0(0.0, 0.0, 0.0)));
				tmpRight = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, obj->up)));
				if (!is_equal_vec(tmpRight, obj->right))
						ft_error(RIGHT_UP_CONFLICT);
				tmpUp = vec_normalize(vec_crossproduct(obj->dir, obj->right));
				if (!is_equal_vec(tmpUp, obj->up))
						ft_error(RIGHT_UP_CONFLICT);
		}
		else if (minUp != INFINITY && roll != INFINITY) 
		{
				obj->up = vec_normalize(default_vec(obj->up, vec_init0(0.0, 0.0, 0.0)));
				obj->up = vec_rot_zaxis_angle(obj->up, obj->dir, roll);
				obj->right = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, obj->up)));
				obj->right = vec_rot_zaxis_angle(obj->right, obj->dir, roll);
				tmpUp = vec_normalize(vec_crossproduct(obj->dir, obj->right));
				if (!is_equal_vec(tmpUp, obj->up))
						ft_error(UP_ROLL_CONFLICT);
		}
		else if (minRight != INFINITY && roll != INFINITY)
		{
				obj->right = vec_normalize(default_vec(obj->right, vec_init0(0.0, 0.0, 0.0)));
				obj->right = vec_rot_zaxis_angle(obj->right, obj->dir, roll);
				obj->up = vec_normalize(vec_crossproduct(obj->dir, obj->right));
				obj->up = vec_rot_zaxis_angle(obj->up, obj->dir, roll);
				tmpRight = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, obj->up)));
				if (!is_equal_vec(tmpRight, obj->right))
						ft_error(RIGHT_ROLL_CONFLICT);
		}
		return (obj);
}

t_obj	*parse_roll_up_right(t_elem *elem, t_obj *obj)
{
		float	roll;
		float	minUp;
		float	minRight;

		if (elem != NULL)
		{
				obj->up = parse_vector(find_elem_by_key(elem, "up"));
				obj->right = parse_vector(find_elem_by_key(elem, "right"));
				roll = parse_degree_to_rad(parse_float(find_elem_by_key(elem, "roll")));
				minUp = min_of_vec(obj->up);
				minRight = min_of_vec(obj->right);
				if (minUp == INFINITY && minRight == INFINITY && roll == INFINITY)
						obj = up_right_roll_infinity(obj);
				else if (minUp != INFINITY && minRight != INFINITY && roll != INFINITY)
						obj = up_right_roll_all_given(obj, roll);
				else if ((minUp != INFINITY && minRight != INFINITY) || (minUp != INFINITY &&
										roll != INFINITY) || (minRight != INFINITY && roll != INFINITY))
						obj = up_right_roll_two_given(obj, roll, minUp, minRight);
				else if (minUp != INFINITY || minRight != INFINITY || roll != INFINITY )
						obj = up_right_roll_one_given(obj, roll, minUp, minRight);
		}
		else if (ROLL_OR_UP_OR_RIGHT_REQUIRED)
				is_required("roll or UP or RIGHT ", true);
		else {
				obj->up = vec_init0(0.0, 1.0, 0.0);
				obj->right = vec_init0(1.0, 0.0, 0.0);
		}
		return (obj);
}

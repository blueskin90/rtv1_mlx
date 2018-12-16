/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_roll_up_right.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 15:24:53 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/16 16:25:38 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
static t_obj	*up_right_roll_all_given(t_obj *obj)
{
	/*t_vec	tmpRight;
	t_vec	tmpUp;

	if (obj->dir.x == 0.0 && fabs(obj->dir.y) == 1.0 && obj->dir.z == 0.0)
		tmpRight =  vec_init0(1.0, 0.0, 0.0);
	else
		tmpRight = vec_normalize(vec_opposite(vec_crossproduct(dir, 
						vec_init0(0.0,1.0,0.0)));
		// TODO faire un vec rot axis angle 
	*/	
}

static t_obj	*up_right_roll_infinity(t_obj *obj)
{
	/*if (obj->dir.x == 0.0 && fabs(obj->dir.y) == 1.0 && obj->dir.z == 0.0)
		obj->right =  vec_init0(1.0, 0.0, 0.0);
	else
		obj->right = vec_normalize(vec_opposite(vec_crossproduct(dir, 
						vec_init0(0.0,1.0,0.0)));
	obj->up = vec_normalize(vec_crossproduct(dir, right);
	*/
}

t_obj	*parse_roll_up_right(t_elem *elem, t_obj *obj)
{
	/*float	roll;
	float	minUp;
	float	minRight;
	
	if (elem != NULL)
	{
		obj->up = parse_vector(find_elem_by_key(elem, "up"));
		obj->right = parse_vector(find_elem_by_key(elem, "right"));
		minUp = min_of_vec(obj->up);
		minRight = min_of_vec(obj->right);
		if (minUp == INFINITY && minRight == INFINITY && roll == INFINITY)
			obj = up_right_roll_infinity(obj);
		else if (minUp != INFINITY && minRight != INFINITY && roll != INFINITY)
			obj = up_right_roll_all_given(obj);
	}
	else if (ROLL_OR_UP_OR_RIGHT_REQUIRED)
		is_required("roll or UP or RIGHT ", true);
	else{
		obj->up = vec_init0(0.0, 1.0, 0.0);
		obj->right = vec_init0(1.0, 0.0, 0.0);
		obj->roll = 0.0;
	}
	*/
	return (obj);
}

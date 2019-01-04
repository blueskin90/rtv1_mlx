/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_direction_extension.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 17:33:05 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/04 17:46:18 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec			get_right_dir(t_vec dir)
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

t_vec			vec_rot_zaxis_angle(t_vec v, t_vec zaxis, float angle)
{
	t_matrix	rotmatrix;

	rotmatrix = rotmatrix_axis_angle(zaxis, -angle);
	return (matrix_mult_vec(rotmatrix, v));
}

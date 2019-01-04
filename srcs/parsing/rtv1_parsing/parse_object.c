/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:52 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/04 23:00:56 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_obj	*parse_rotation_translation(t_elem *elem, t_obj *obj)
{
	t_vec	translation;
	t_vec	rotation;

	translation = default_vec(required_vec(
		parse_vector(find_elem_by_key(elem, "translation")),
		TRANSLATION_REQUIRED, "translation"), vec_init0(0.0, 0.0, 0.0));
	obj->pos = vec_add(obj->pos, translation);
	rotation = default_vec(required_vec(
		parse_angle_vector(find_elem_by_key(elem, "rotation")),
		ROTATION_REQUIRED, "rotation"), vec_init0(0.0, 0.0, 0.0));
	// CEST ICI BETRAVE (POUR LA ROTATION)
	return (obj);
}

static void		parse_color_information(t_elem *child_elem, t_obj *obj)
{
	obj->color = parse_color(find_elem_by_key(child_elem, "color"), COLOR_REQ);
	obj->specular = default_float(required_float(
				parse_float(find_elem_by_key(child_elem, "specular")),
				SPECULAR_REQ, "Specular"), 1.0);
	obj->diffuse = default_float(required_float(
				parse_float(find_elem_by_key(child_elem, "diffuse")),
				DIFFUSE_REQ, "Diffuse"), 1.0);
	obj->ambiant = default_float(required_float(
				parse_float(find_elem_by_key(child_elem, "ambiant")),
				AMBIANT_REQ, "Ambiant"), 0.0);
	obj->brillance = default_float(required_float(
				parse_float(find_elem_by_key(child_elem, "brillance")),
				BRILLANCE_REQ, "Brillance"), 1.0);
}

t_obj			*parse_one_object(t_elem *elem,
								void (*parse_obj)(t_elem *, t_obj *))
{
	t_obj			*obj;
	t_elem			*child_elem;

	obj = new_obj();
	child_elem = elem->value.objecty;
	parse_dir_lookat_pos(child_elem, obj);
	parse_up_right_vec(child_elem, obj);
	parse_obj(child_elem, obj);
	parse_color_information(child_elem, obj);
	if (obj->brillance < 1.0 || obj->brillance > 128)
		ft_error(BRILLANCE_BAD_FORMAT);
	obj->brillance = obj->brillance / 128.0;
	obj = parse_rotation_translation(child_elem, obj);
	return (obj);
}

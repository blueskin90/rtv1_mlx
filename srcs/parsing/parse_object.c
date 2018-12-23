/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/18 16:55:27 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"


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

t_obj	*parse_one_object(t_elem *elem, void (*parse_obj)(t_elem *, t_obj *))
{
	t_obj			*obj;
	t_elem			*child_elem;

	// TODO key peut pas etre trop long
	obj = new_obj();
	child_elem = elem->value.objecty;
	parse_dir_lookat_pos(child_elem, obj);
	parse_up_right_vec(child_elem, obj);
	parse_obj(child_elem, obj);
	obj->color = parse_color(find_elem_by_key(child_elem, "color"), COLOR_REQ);
	obj->specular = 
		parse_color(find_elem_by_key(child_elem, "specular"), SPECULAR_REQ);
	obj->diffuse = parse_color(find_elem_by_key(child_elem, "diffuse"), 
			DIFFUSE_REQ);
	obj->ambiant = default_float(required_float(
				parse_float(find_elem_by_key(child_elem, "ambiant")), 
				AMBIANT_REQ, "Ambiant"), 0.0);
	obj->brillance = default_float(required_float(
				parse_float(find_elem_by_key(child_elem, "ambiant")), 
				BRILLANCE_REQ, "Brillance"), 0.0);
	obj = parse_rotation_translation(child_elem, obj);
// TODO : creer renderer camera > scene > projet
	return (obj);
	// si l objet est vide
}


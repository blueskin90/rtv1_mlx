/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/11 14:55:36 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

t_obj	*parse_one_object(t_elem *elem, void (*parse_obj)(t_elem *elem, t_obj *obj))
{
	t_obj			*obj;
	t_parse_obj		*parse_obj;
	t_elem			*child_elem;

	check_type_of_key("object", elem->type);
	obj = new_parse_obj();
	child_elem = elem->value.objecty;
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
	return (obj);
	// si l objet est vide
}

t_obj	*parse_dir_lookat_pos(t_elem *elem, t_obj *obj)
{
	t_vec	*dir;
	t_vec	*lookat;

	obj->pos = default_vec(required_vec(parse_vector(
					find_elem_by_key(child_elem, "position")),
				POSITION_REQUIRED,"Position"),
			vec_init0(0.0, 0.0, 0.0));
	dir = find_elem_by_key(child_elem, "direction");
	lookat = find_elem_by_key(child_elem, "lookat");
	if ()


}

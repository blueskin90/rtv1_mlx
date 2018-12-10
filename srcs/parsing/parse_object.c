/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/10 20:12:03 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

t_obj	*parse_one_object(t_elem *elem, void (*parse_obj)(t_elem *elem))
{
	t_obj			*obj;
	t_parse_obj		*parse_obj;
	t_elem			*child_elem;

	check_type_of_key("object", elem->type);
	obj = new_parse_obj();
	child_elem = elem->value.objecty;
	obj->position = parse_vector(
			find_elem_by_key(child_elem, "specular"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "diffuse"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "position"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "direction"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "lookat"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "translation"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "rotation"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "up"));
	obj->direction = parse_vector(
			find_elem_by_key(child_elem, "right"));
	obj->brillance = get_vec_float(
			find_elem_by_key(child_elem, "brillance"));
	obj->ambiant = get_vec_float(
			find_elem_by_key(child_elem, "ambiant"));
	obj->roll = get_vec_float(
			find_elem_by_key(child_elem, "roll"));
	return (obj);
	// si l objet est vide
}

t_obj	*parse_one_cone(t_elem *elem)
{
	t_obj	*obj;
	t_parse_obj;
	t_elem	*child_elem;

	check_type_of_key("object", elem->type);
	obj = new_obj();
	child_elem = elem->value.arrayi;
	obj->type = CONE;
	obj->pos = parse_vector(
			find_elem_by_key(child_elem, "position"));
	obj->dir = parse_vector(
			find_elem_by_key(child_elem, "direction"));

	
	return (obj);
	// si l objet est vide
}

t_obj	*parse_one_cylinder(t_elem *elem)
{
	t_obj	*obj;
	t_elem	*child_elem;

	check_type_of_key("object", elem->type);
	obj = new_obj();
	obj->type = CYLINDER;
	child_elem = elem->value.arrayi;
	obj->pos = parse_vector(
			find_elem_by_key(child_elem, "position"));
	obj->dir = parse_vector(
			find_elem_by_key(child_elem, "direction"));
	return (obj);
	// si l objet est vide
}

t_obj	*parse_one_plane(t_elem *elem)
{
	t_obj	*obj;
	t_elem	*child_elem;

	check_type_of_key("object", elem->type);
	obj = new_obj();
	obj->type = PLANE;
	child_elem = elem->value.arrayi;
	obj->pos = parse_vector(
			find_elem_by_key(child_elem, "position"));
	obj->dir = parse_vector(
			find_elem_by_key(child_elem, "direction"));
	return (obj);
	// si l objet est vide
}

t_obj	*parse_one_sphere(t_elem *elem)
{
	t_obj	*obj;
	t_elem	*child_elem;

	check_type_of_key("object", elem->type);
	obj = new_obj();
	obj->type = SPHERE;
	child_elem = elem->value.arrayi;
	obj->pos = parse_vector(
			find_elem_by_key(child_elem, "position"));
	obj->dir = parse_vector(
			find_elem_by_key(child_elem, "direction"));
	return (obj);
	// si l objet est vide
}

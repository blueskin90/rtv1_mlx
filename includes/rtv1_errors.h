/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_errors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:21:48 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/05 18:43:32 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_ERRORS_H
# define RTV1_ERRORS_H

/*
**	WRONG FORMAT
*/
# define FIRST_ELEM_BAD_FORMAT "FIRST ELEMENT MUST BE ARRAY\n"
# define SCENE_BAD_FORMAT "Wrong format for SCENE, must be OBJECT\n"
# define SCENE_NAME_BAD_FORMAT "Wrong format for NAME, must be STRING\n"
# define OBJECTS_BAD_FORMAT "Wrong format for OBJECTS, must be OBJECT type\n"
# define VECTOR_BAD_FORMAT "Wrong format for VECTOR, must be OBJECT type\n"
# define SPHERES_BAD_FORMAT "Wrong format for SPHERES, must be STRING type\n"
# define SPHERE_BAD_FORMAT "Wrong format for elements of SPHERES, must be OBJECT\n"

/*
** INFORMATION REQUIRED
*/
# define SCENE_IS_REQUIRED "At least one SCENE is required\n" 
# define NAME_IS_REQUIRED "Name is required\n"
# define SPHERES_IS_REQUIRED "Spheres is required\n"
# define ONE_SPHERE_IS_REQUIRED "At least one SPHERE is required\n"
# define OBJECTS_IS_REQUIRED "Their must be at least one object in your SCENE\n"
# define VECTOR_IS_REQUIRED "Vector is required\n"
# define VECTOR_POINT_IS_REQUIRED "Vector point is required \n"
#endif

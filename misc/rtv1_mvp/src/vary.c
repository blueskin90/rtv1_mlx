/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 20:51:28 by nfinkel           #+#    #+#             */
/*   Updated: 2018/11/05 15:48:28 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

static t_vary	g_vary_stack = {NULL, 0, 0, sizeof(t_obj *)};
static t_vary	*g_vary = &g_vary_stack;

static inline void	objdtor(void *data)
{
	ft_memdtor((void **)&*(t_obj **)data);
}

inline void			terminate(t_env *env)
{
	ft_varydtor(&g_vary, (t_vdtor)objdtor);
	ftx_mlxdtor(env->mlx);
	exit(EXIT_SUCCESS);
}

static inline t_obj	*objctor(t_v3 pt, double scale, t_type type)
{
	t_obj	*obj;

	obj = (t_obj *)ft_memalloc(sizeof(t_obj));
	obj->pt = pt;
	obj->scale = scale;
	obj->type = type;
	GIMME(obj);
}

inline t_obj		**add_objs(void)
{
	*(t_obj **)ft_varypush(g_vary) = objctor(ft_v3new(-5, 0, -25), 2, E_SPHERE);
	*(t_obj **)ft_varypush(g_vary) = objctor(ft_v3new(5, 0, -15), 2, E_SPHERE);
	*(t_obj **)ft_varypush(g_vary) = objctor(ft_v3new(5, 0, -50), 2, E_SPHERE);
	*(t_obj **)ft_varypush(g_vary) = NULL;
	GIMME(g_vary->buff);
}

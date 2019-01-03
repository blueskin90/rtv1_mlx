/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 06:28:48 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 15:02:38 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_renderer(t_renderer *renderer)
{
	ft_printf("\t\trenderer width = %d, renderer height = %d\n",
			renderer->width, renderer->height);
	ft_printf("\t\trenderer depth = %d (not used at the moment, for AA later\n",
			renderer->depth);
	ft_printf("\t");
	print_renderer_mode(renderer->renderer_mode);
	ft_printf("\t");
	print_print_mode(renderer->print_mode);
	ft_printf("\t\ttop left vec for the renderer is : ");
	print_vec(renderer->top_left_vec);
	ft_printf("\t\tincrement vec for the renderer is : ");
	print_vec(renderer->increment);
	ft_printf("\t\tFirst ray address is %p\n\n", renderer->renderer);
}

void				print_renderers(t_scene *scene)
{
	t_scene			*scenes;
	t_obj			*cameras;

	ft_printf("\t^^ printing renderers ^^\n");
	scenes = scene;
	while (scenes)
	{
		cameras = scenes->cameras;
		while (cameras)
		{
			print_renderer(cameras->params.camera.renderer);
			cameras = cameras->next;
		}
		scenes = scenes->next;
	}
	ft_printf("\t^^ end of printing renderers ^^\n");
}

void				verbose_settings(t_args *args, t_env *env)
{
	ft_printf("/!\\ == Verbose for settings === /!\\\n\n");
	if (args->renderer_mode == NO_RENDERER)
		ft_printf("\tNO_RENDERER mode set, nothing done\n");
	else if (!env->scene)
		ft_printf("\tNo scenes were allocated !!!\n");
	else
		print_renderers(env->scene);
	ft_printf("\n===== end of settings verbose ======\n\n");
}

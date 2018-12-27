/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 06:28:48 by toliver           #+#    #+#             */
/*   Updated: 2018/12/27 03:06:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_renderer(t_renderer *renderer)
{
	ft_printf("\t\trenderer width = %d, renderer height = %d\n",
			renderer->width, renderer->height);
	ft_printf("\t\trenderer depth = %d (not used at the moment, for AA later\n",
			renderer->depth);
	print_renderer_mode(renderer->renderer_mode);
	print_print_mode(renderer->print_mode);
	printf("\t\ttop left vec for the renderer is :\n\t\t\t");
	print_vec(renderer->top_left_vec);
	printf("\t\tincrement vec for the renderer is :\n\t\t\t");
	print_vec(renderer->increment);
	ft_printf("\t\tFirst ray address is %p\n", renderer->renderer);
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
	ft_printf("\t^^ end lf printing renderers ^^\n");
}

void				verbose_settings(t_args *args, t_env *env)
{
	printf("/!\\ == Verbose for settings === /!\\\n\n");
	if (args->renderer_mode == NO_RENDERER)
		ft_printf("\tNO_RENDERER mode set, nothing done\n");
	else if (!env->scene)
		ft_printf("\tNo scenes were allocated !!!\n");
	else
		print_renderers(env->scene);
	// ptet penser a faire un numerotage et autre des scenes 
	printf("\n===== end of settings verbose ======\n\n");
}

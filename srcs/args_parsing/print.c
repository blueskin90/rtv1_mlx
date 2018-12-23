/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 01:49:05 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 03:56:57 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		print_args_files(void)
{
	char		**files;
	int			i;

	files = files_get();
	i = 0;
	if (files == NULL || files[0] == NULL)
		printf("	There are no files\n");
	else
	{
		printf("	Files in argument are :\n");
		while (files[i])
		{
			printf("		- %s\n", files[i]);
			i++;
		}
	}
	printf("\n");
}

static void		print_parsing_mode(void)
{
	char		*mode;

	mode = (parse_mode_get() == 0) ? "STANDARD" : "JSON";
	printf("	Parsing mode is : %s\n", mode);
}

static char		*verbose_mode_string(int mode)
{
	if (mode == ARGS_PARSING)
		return ("ARGS_PARSING");
	if (mode == INIT)
		return ("INIT");
	if (mode == PARSING)
		return ("PARSING");
	if (mode == SETTINGS)
		return ("SETTINGS");
	if (mode == RUNNING)
		return ("RUNNING");
	return ("ERROR, BAD VERBOSE MODE !\n");
}

static void		print_verbose_mode(void)
{
	char		*mode;

	mode = NULL;
	if (verbose_mode_get() == NO_VERBOSE)
		printf("	Verbose is OFF (should be impossible)\n");
	else if (verbose_mode_get() >= MAX_VERBOSE_MODE)
		printf("	Verbose is higher than verbose max !\n");
	else if (verbose_mode_get() == ALL_VERBOSE)
		printf("	Verbose is ON for all steps\n");
	else
	{
		mode = verbose_mode_string(verbose_mode_get());
		printf("	Verbose is ON for %s\n", mode);
	}
}

static char		*render_mode_string(int mode)
{
	if (mode == HIT_COLOR)
		return ("HIT_COLOR");
	if (mode == DEPTH_COLOR)
		return ("DEPTH_COLOR");
	if (mode == TOTAL_COLOR)
		return ("TOTAL_COLOR");
	if (mode == TEST_COLOR)
		return ("TEST_COLOR");
	if (mode == EDITOR)
		return ("EDITOR");
	return ("ERROR, BAD RENDER MODE !\n");
}

static void		print_render_mode(void)
{
	char		*mode;

	mode = NULL;
	if (render_mode_get() == NO_RENDER)
		printf("	No rendering will be done\n");
	else if (render_mode_get() >= MAX_RENDER_MODE)
		printf("	Render mode is higher than mode max !\n");
	else
	{
		mode = render_mode_string(render_mode_get());
		printf("	Render mode is : %s\n", mode);
	}
}

static void		print_debug_mode(void)
{
	char		*mode;

	mode = (debug_mode_get() ? "ON" : "OFF");
	printf("	Debug mode is %s\n", mode);
}

static char		*renderer_mode_string(int mode)
{
	if (mode == STACK)
		return ("STACK");
	if (mode == MALLOC)
		return ("MALLOC");
	if (mode == MULTITHREAD)
		return ("MULTITHREAD");
	if (mode == GRAPHIQUE)
		return ("GRAPHIQUE");
	if (mode == CLUSTERING)
		return ("CLUSTERING");
	return ("ERROR, BAD RENDERER MODE !\n");
}

static void		print_renderer_mode(void)
{
	char		*mode;

	if (renderer_mode_get() >= MAX_RENDERER_MODE)
		printf("	Renderer mode is higher than the max !\n");
	else
	{
		mode = renderer_mode_string(renderer_mode_get());
		printf("	Renderer mode is : %s\n", mode);
	}
}

static void		print_args_modes(void)
{
	print_parsing_mode();
	print_renderer_mode();
	print_render_mode();
	print_verbose_mode();
	print_debug_mode();
}

void			print_args(void)
{
	printf("\n/!\\ == Verbose for args == /!\\\n\n");
	print_args_modes();
	print_args_files();
	printf("===== end of args verbose =====\n\n");
}

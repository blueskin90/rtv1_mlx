/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:05:48 by nfinkel           #+#    #+#             */
/*   Updated: 2018/06/24 17:20:55 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <math.h>

extern void		screen_ratio(int width, int height, double *ratio_x, 
		double *ratio_y);
/*
** COLOR
*/
unsigned int	hsv_calculator(double hue, double saturation, double bright);
unsigned int	merging(unsigned int a, unsigned int o,
		double alpha, double beta);
unsigned int	rgb_to_hex(int r, int g, int b);
#endif

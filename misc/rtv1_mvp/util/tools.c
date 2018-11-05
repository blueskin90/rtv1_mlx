/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 20:36:09 by nfinkel           #+#    #+#             */
/*   Updated: 2018/06/24 17:20:14 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	screen_ratio(int width, int height, double *ratio_x, double *ratio_y )
{
	if (width >= height){
		*ratio_x = (double)width / (double)height;
		*ratio_y = 1;
	}
	else{
		*ratio_y = (double)height / (double)width;
		*ratio_x = 1;
	}
}

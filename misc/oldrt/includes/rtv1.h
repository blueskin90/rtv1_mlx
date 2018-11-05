/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:56:14 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 20:50:24 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../libmatrice/includes/libmatrice.h"
# include "../minilibx_macos/mlx.h"
# include "mlx_keys_macos.h"
# define WIDTH_SCREEN 1550
# define HEIGHT_SCREEN 750

typedef struct			s_scr
{
	double				ratio_x;
	double				ratio_y;
	double				zoom;
	int					width;
	int					half_width;
	int					height;
	int					half_height;

}						t_scr;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	unsigned int		*data_addr;
	char				*title;
	int					bits_per_pixel;
	int					bytes_per_line;
	int					endian;
	t_scr				scr;
	
}						t_env;

/*
** ENV
*/
char			init_env(t_env *env);
/*
**	SCREEN
*/
void		get_screen_ratio(t_scr *scr);
int			reverse_scale_screen_x(t_scr *scr, double x);
int			reverse_scale_screen_y(t_scr *scr, double y);
double		scale_screen_y(t_scr *scr, int y);
double		scale_screen_x(t_scr *scr, int x);
int			get_pixel_index(int pixel_x, int pixel_y);
/*
**	OBJS
*/
int			in_sphere(t_vector *vec);
/*
**	EXIT
*/
void			safe_exit(t_env *env);
void			safe_error_exit(t_env *env, char *str);
#endif

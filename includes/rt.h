/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:16:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/01/21 18:10:09 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rtstruct.h"
# include "ftlist.h"
# include "libui.h"

/*
** Definition for the RTV1 :
** Config :
*/

# define BACK_COLOR		0x000000
# define AMB_LIGHT		0.0625f
# define NO_LIGHT		0
# define NO_FACING		0
# define NO_I_LIGHT		0
# define NO_SHINE		0
# define NO_SHADOW		0

# define DEBUG			1
# define DEBUG_LEAK		0
# define MAC			IMAC
# define MTHR			1

/*
** Static def :
*/

# define FOV			60.0f

# define DEV			0
# define MACB			1
# define IMAC			2
# define IMAC4K			3

# define PLANE			0
# define SPHERE			1
# define CONE			2
# define CYLINDER		3

# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

/*
** Automatic parameters :
*/

# if (MAC == MACB)
#  define WIDTH			1680
#  define HEIGHT		1000
# elif (MAC == IMAC)
#  define WIDTH			2560
#  define HEIGHT		1400
# elif (MAC == IMAC4K)
#  define WIDTH			3200
#  define HEIGHT		1800
# else
#  define WIDTH			840
#  define HEIGHT		500
# endif

/*
** Messages for RTV1 :
*/

# define USAGE "usage : ./rtv1 scenes/map_name"

/*
** Structures :
*/

typedef struct	s_data
{
	int			stage;
	t_sdl		sdl;
	t_list		*lst_obj;
	t_list		*lst_light;
	int			nb_light;
	t_cam		cam;
	t_matrix	matrix_camera[2];
	t_inter		*core;
}				t_data;

/*
** Prototypes :
*/

/*
** Call by main.c :
*/

int				reader(char *str, t_data *data);
void			init_render(t_data *data);
int				process_pixel(int x, int y, void *arg);
void			exit_safe(t_data *data);

/*
** Call by parse.c :
*/

void			parsing_error(int l_idx, char *error, t_data *d, char **greed);
int				parse_light(char **greed, t_data *data, int l_idx);
int				parse_shape(char **greed, t_data *data, int l_idx, int type);

/*
** Call by inter.c :
*/

void			light_intensity(t_inter *inter, t_color *color, t_ray *ray);
void			cast_shadow(t_data *data, t_inter *inter);
void			cast_primary(t_data *data, t_inter *inter);

#endif

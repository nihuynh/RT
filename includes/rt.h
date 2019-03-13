/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:16:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/07 18:33:17 by nihuynh          ###   ########.fr       */
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
# define NO_DEFLECT		0
# define NO_ABSORB		1
# define DEPTH_MAX		1

# define DEBUG			0
# define DEBUG_LEAK		0
# define MAC			DEV
# define MTHR			1

/*
** User def :
*/

# define T_STEP			10
# define Z_STEP			1
# define A_STEP			10.0f

/*
** Static def :
*/

# define FOV			45.0f

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
	t_sdl		sdl;
	t_list		*lst_obj;
	t_list		*lst_light;
	int			nb_light;
	t_cam		cam;
	t_matrix	matrix_camera[2];
	t_inter		*core;
	char		*arg;
}				t_data;

/*
** Prototypes :
*/

int				reader(char *str, t_data *data);
void			init_render(t_data *data);
int				process_pixel(int x, int y, void *arg);
void			exit_safe(t_data *data);
void			key_mapping(int *quit, SDL_Keycode key, void *arg);
void			mouse_mapping(SDL_Event *event, void *arg);
void			parsing_error(int l_idx, char *error, t_data *d, char **greed);
int				parse_light(char **greed, t_data *data, int l_idx);
int				parse_shape(char **greed, t_data *data, int l_idx, int type);
void			light_intensity(t_inter *inter, t_color *color, t_ray *ray);
void			cast_shadow(t_data *data, t_inter *inter);
void			cast_primary(t_data *data, t_inter *inter);
void			cast_light_primary(t_data *data, t_inter *inter);
void			camera_angle(t_data *data, int pan, int pitch);
void			camera_zoom(t_data *data, float value);
void			camera_height(t_data *data, float value);
void			camera_side(t_data *data, float value);
void			camera_pitch(t_data *data, float angle);
void			camera_pan(t_data *data, float angle);

#endif
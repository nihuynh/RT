/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 00:06:56 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/25 23:22:11 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DATA_H
# define T_DATA_H

# include "option.h"
# include "rtstruct.h"
# include "t_scene.h"
# include "ftlist.h"
# include "libui.h"
# include "t_gui.h"
# include "t_settings.h"

typedef struct	s_data
{
	char		*arg;
	t_option	option;
	t_cam		cam;
	t_scene		scene;
	t_list		*lst_mat;
	t_list		*lst_tex;
	t_list		*lst_scenes;
	t_sdl		*sdl;
	t_gui		gui;
	t_settings	settings;
}				t_data;

/*
** Core :
*/

int				process_pixel(int x, int y, void *arg);
t_obj			*find_obj_at_pixel(t_data *app, int x, int y);
void			interface(t_data *app);
t_data			*get_app(t_data *app);
void			free_app(t_data *app);
/*
** Loading :
*/

void			hook_sdl(t_data *app);
void			init_textures(t_data *app);
void			parse_material_csv(t_data *app, char *csv_file);
void			get_scenes(t_data *app);
int				reader(char *str, t_data *app);
void			load_scene(t_data *app, char *filename);
void			reload(t_data *app, char *filename);

/*
** Unloading :
*/

void			free_scene(t_data *app);
void			free_lst(t_data *data);

/*
** Others :
*/

void			record_frame(t_data *app);

#endif

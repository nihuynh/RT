/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:55:09 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/27 12:53:30 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include "ftlist.h"
# include <SDL.h>
# include "libui.h"

/*
** Structures :
*/

typedef struct		s_gui
{
	t_data			*app;
	t_sdl			*sdl;
	uint32_t		texture_id;
	SDL_GLContext	gl_context;

	int				flags_render;
	char			err_msg[50];
	bool			err_open;
	bool			load_open;
	bool			export_open;
	bool			stats_open;
	bool			edit_open;
	bool			tree_open;
	bool			del_obj_open;
	bool			add_obj_open;
	int				add_obj_type;
	bool			render_open;
	bool			scene_open;
	// t_gui_data		ui;
	t_cam			cam_cpy;
	char			*scene_name;
	bool			fullscreen;
	uint32_t		texture_id;
	bool			render_focused;
	bool			stats_open;
	bool			export_open;
	bool			new_obj_open;
	bool			delete_obj_open;
	bool			load_open;
	bool			error_open;
	int				new_obj_type;
	t_list			*light_set;
	t_obj			*obj_set;
	t_pt3			pos_render;
	int				flags_render;
	SDL_GLContext	gl_context;
}					t_gui;

typedef struct		s_settings
{
	t_color			back_color;
	t_color			amb_light;
	t_color			filter;
	bool			light;
	bool			facing;
	bool			i_light;
	bool			shine;
	bool			shadow;
	bool			deflect;
	bool			absorb;
	bool			anti_a;
	int				depth_max;
	float			fov;
}					t_settings;

typedef struct		s_scene
{
	t_list			*lst_obj;
	t_list			*lst_light;
}					t_scene;

typedef struct		s_data
{
	t_settings		settings;
	t_sdl			sdl;
	t_gui			gui;
	t_scene			scene;
	t_list			*lst_mat;
	t_list			*lst_tex;
	t_cam			cam;
	char			*arg;
}					t_data;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:55:09 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/28 14:50:04 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include "ftlist.h"
# include <SDL.h>
# include "libui.h"
# include "color.h"
# include "option.h"
# include "rtstruct.h"

/*
** Structures :
*/

typedef struct s_scene		t_scene;
typedef struct s_data		t_data;
typedef struct s_gui		t_gui;
typedef struct s_settings	t_settings;
typedef struct s_scene_name	t_scene_name;


struct				s_gui
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
	bool			del_obj_open;
	bool			add_obj_open;
	int				add_obj_type;
	bool			render_open;
	bool			scene_open;
	bool			demo_open;
	bool			render_set_open;
	// t_gui_data		ui;
	t_cam			cam_cpy;
	char			*scene_name;
	bool			fullscreen;
	bool			render_focused;
	int				new_obj_type;
	t_light			*light_set;
	t_obj			*obj_set;
	t_pt3			pos_render;
};

struct				s_settings
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
	bool			debug_normal;
	int				depth_max;
	float			fov;
};

struct				s_scene
{
	t_list			*lst_obj;
	t_list			*lst_light;
	int				nb_objs[5];
	int				nb_light;
};

struct				s_scene_name
{
	char			*name;
	char			*dir;
};

struct				s_data
{
	char			*arg;
	t_option		option;
	t_cam			cam;
	t_scene			scene;
	t_list			*lst_mat;
	t_list			*lst_tex;
	t_list			*lst_scenes;
	t_sdl			*sdl;
	t_gui			gui;
	t_settings		settings;
};

t_data				*get_app(t_data *app);
char				*get_obj_str(int type);
int					get_obj_type(char *obj_type);
void				obj_set(t_obj *obj, int type, void *shape);

#endif

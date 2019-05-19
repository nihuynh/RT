/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:55:09 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/19 20:56:39 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include "ftlist.h"
# include <SDL.h>
# include "libui.h"
# include "color.h"
# include "rtstruct.h"

/*
** Structures :
*/

typedef struct s_ui_func	t_ui_func;
typedef struct s_data		t_data;

struct				s_ui_func
{
	t_data			*app;
	int				flags_render;
	char			err_msg[50];
	bool			err_open;
	bool			load_open;
	bool			export_open;
	bool			stats_open;
	bool			del_obj_open;
	bool			add_obj_open;
	int				add_obj_type;
	bool			render_open;
	bool			scene_open;
	void			(*err_win)		(t_ui_func*);
	void			(*load_win)		(t_ui_func*);
	void			(*export_win)	(t_ui_func*);
	void			(*stats_win)	(t_ui_func*);
	void			(*del_obj_win)	(t_ui_func*);
	void			(*add_obj_win)	(t_ui_func*);
	void			(*render_win)	(t_ui_func*);
	void			(*scene_win)	(t_ui_func*);
};

typedef struct		s_gui
{
	t_ui_func		ui;
	t_cam			cam_cpy;
	char			*scene_name;
	bool			fullscreen;
	uint32_t		texture_id;
	bool			render_focused;
	t_list			*light_set;
	t_obj			*obj_set;
	t_pt3			pos_render;
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

struct				s_data
{
	t_settings		settings;
	t_sdl			sdl;
	t_gui			gui;
	t_scene			scene;
	t_list			*lst_mat;
	t_list			*lst_tex;
	t_cam			cam;
	char			*arg;
};

#endif

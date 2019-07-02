/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_gui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 00:05:12 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/02 03:40:53 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_GUI_H
# define T_GUI_H

# include <SDL.h>
# include "t_data.h"
# include "animate.h"
# include "t_cluster.h"

typedef struct		s_gui
{
	struct s_data	*app;
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
	bool			del_light_open;
	bool			add_obj_open;
	int				add_obj_type;
	bool			render_open;
	bool			scene_open;
	bool			demo_open;
	bool			render_set_open;
	bool			cam_open;
	bool			anim_win_open;
	bool			add_cluster_open;
	bool			keymap_open;
	bool			about_open;
	t_texture		keymap;
	t_cam			cam_cpy;
	bool			render_focused;
	bool			animate;
	bool			record;
	int				frame_limit;
	long			frames_render_time;
	int				animated_frames;
	t_cluster		cluster;
	t_light			*light_set;
	t_obj			*obj_set;
	t_anim			*anim_set;
	t_list			*lst_anim_set;
	t_list			**alst;
	t_pt3			pos_render;
}					t_gui;


void				exit_ui(t_gui *gui);
#endif

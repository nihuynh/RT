/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_gui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 00:05:12 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/09 17:41:56 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_GUI_H
# define T_GUI_H

# include <SDL.h>
# include "t_data.h"
# include "animate.h"

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
	t_cam			cam_cpy;
	bool			fullscreen;
	bool			render_focused;
	bool			animate;
	int				new_obj_type;
	t_light			*light_set;
	t_obj			*obj_set;
	t_anim			*anim_set;
	t_pt3			pos_render;
}					t_gui;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 00:06:56 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/12 01:48:40 by sklepper         ###   ########.fr       */
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

t_data		*get_app(t_data *app);

#endif

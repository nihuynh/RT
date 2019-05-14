/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/14 19:08:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# define GL_SILENCE_DEPRECATION

# include "rt.h"
# include "cimgui.h"

# define FLAGS1	ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
# define FLAGS2	ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar
# define FLAGS3	ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse
# define FLAGS4	ImGuiWindowFlags_NoBringToFrontOnFocus
# define RENDER_FLAGS FLAGS1 | FLAGS2 | FLAGS3 | FLAGS4

/*
** Config :
*/

# define RENDER_STATIC	1
# define SHOW_DEMO		1

/*
** Prototypes :
*/

void	export_window(t_data *app);
void	window_scene(t_data *app);
void	icolortogui(int src, float dest[3]);
void	guicolortoi(float src[3], int *dest);
void	colortogui(t_color src, float dest[3]);
void	guitocolor(float src[3], t_color *dest);
void	object_settings(t_data *app);
void	material_list(t_list *lst_mat, t_obj *obj);
void	texture_list(t_list *lst_tex, t_obj *obj);
void	new_obj_list(int *type);
t_obj	*find_obj_at_pixel(t_data *app, int x, int y);
void	new_light(t_data *app);
void	new_obj(t_data *app, int type);
void	new_obj_window(t_data *app);
void	delete_obj_window(t_data *app);
void	delete_obj(t_data *app);
void	load_window(t_data *app);
bool	check_file(char *filename);
void	error_window(t_data *app);
void	init_gui(t_gui *gui, t_data *app);

#endif

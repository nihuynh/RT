/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/29 19:55:37 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
# define GL_SILENCE_DEPRECATION

# include "data_struct.h"
# include "cimgui.h"

# define FLAGS1	ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
# define FLAGS2	ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar
# define FLAGS3	ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse
# define FLAGS4	ImGuiWindowFlags_NoBringToFrontOnFocus
# define RENDER_FLAGS FLAGS1 | FLAGS2 | FLAGS3 | FLAGS4

/*
** Hooks :
*/

void	fullscreen(t_sdl *sdl, t_gui *gui);
void	err_win(t_gui *gui);
void	export_win(t_gui *gui);
void	load_win(t_gui *gui);
void	stats_win(t_gui *gui);
void	selector(t_gui *gui);

void	add_obj_win(t_gui *gui);
void	del_obj_win(t_gui *gui);
void	del_light_win(t_gui *gui);

void	render_win(t_gui *gui);
void	scene_win(t_gui *gui);
void	interface_mainmenu(t_gui *gui);
void	render_settings(t_data *app);


int		export_scene(t_data *app, char *filename);
void	export_material(int fd, t_material *mat);

void	load_scene(t_data *app, char *filename);
void	reload_scene(t_data *app, char *filename);

/*
** Prototypes :
*/

void	icolortogui(int src, float dest[3]);
void	guicolortoi(float src[3], int *dest);
void	colortogui(t_color src, float dest[3]);
void	guitocolor(float src[3], t_color *dest);
void	object_settings(t_data *app);
void	material_list(t_list *lst_mat, t_obj *obj);
void	texture_list(t_list *lst_tex, t_obj *obj);
void	node_type_list(t_csg_op *csg_op);
void	new_obj_list(int *type);
void	list_scenes(t_gui *gui);
t_obj	*find_obj_at_pixel(t_data *app, int x, int y);
void	new_light(t_data *app);
void	new_obj(t_data *app, int type);
void	delete_obj(t_data *app);
void	delete_light(t_data *app);
bool	check_file(char *filename);
void	object(t_data *app, t_obj *obj);

/*
** UI SHAPES
*/

void	ui_csg(void *app_v, void *shape);
void	ui_sphere(void *app_v, void *shape);
void	ui_plane(void *app_v, void *shape);
void	ui_cone(void *app_v, void *shape);
void	ui_cylinder(void *app_v, void *shape);
void	ui_light(t_light *light);
void	ui_cam_win(t_gui *gui);

#endif

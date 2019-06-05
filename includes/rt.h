/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:16:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/05 03:26:07 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rtstruct.h"
# include "t_data.h"

/*
** Usage :
*/

# define USAGE "Usage : ./RT <scene.rt> [options]\nOptions : hlt"

/*
** Prototypes :
*/

int			reader_no_exit(char *filename, t_data *app);
t_data		*get_app(t_data *app);

/*
** Render :
*/

t_shading	get_shading_data(t_inter *inter);
void		render_gui(void *arg);
int			process_pixel(int x, int y, void *arg);
void		light_intensity(t_inter *inter, t_color *color, t_ray *ray);
void		cast_shadow(t_data *app, t_inter *inter);
t_color		get_lighting(t_shading s, t_scene scene, t_settings *setng);
void		cast_primary(t_list *obj_list, t_inter *inter);
t_color		recursive_cast(t_scene scene, t_settings s, t_ray r, int depth);
void		set_direction(t_cam *cam, t_vec3 direction);
void		cam_ray(t_data *app, t_ray *res, float x, float y);
t_color		cast_light_primary(t_list *obj_list, t_inter *inter);
t_vec3		compute_shading_normal(t_material mat, t_vec3 uv, t_vec3 geo_n);

/*
** Init :
*/

void		hook_sdl(t_data *app);
void		init_textures(t_data *app);
int			reader(char *str, t_data *app);
void		update(void *data);
void		update_camera(t_cam *cam, bool *needs_render);
void		key_event(int *quit, SDL_Keycode key, void *arg, bool state);
void		mouse_motion(SDL_Event *event, void *arg);
void		click_event(SDL_Event *event, void *arg);
void		get_scenes(t_data *app);

/*
** Exit :
*/

void		del_light(void *content, size_t content_size);
void		free_scene(t_data *app);
void		free_app(t_data *app);
void		exit_safe(int err_code);
/*
** Textures :
*/

t_color		texture_checkers(t_material *mat, t_texture *texture, t_vec3 uv);
t_color		texture_strips(t_material *mat, t_texture *texture, t_vec3 uv);
t_color		sample(t_material *material, t_texture *texture, t_vec3 uv);

void		init_interface(t_gui *gui, SDL_Window *window, t_data *app);
void		init(t_data	*data);
void		init_textures(t_data *app);
void		init_settings(t_settings *settings);
void		interface(t_data *app);
void		update_texture(t_img img, t_gui gui);
void		render_gui(void *arg);
void		ui_sphere(void *data_v, void *res);
void		ui_plane(void *data_v, void *res);
void		ui_cylinder(void *data_v, void *res);
void		ui_cone(void *data_v, void *res);
void		change_window_title(SDL_Window *win, t_data *app);
void		fullscreen(t_sdl *sdl, t_gui *gui);
void		resize_app(int width, int height, t_data *app);
int			export_scene(t_data *data, char *filename);
void		export_material(int fd, t_material *mat);
void		free_lst(t_data *data);
int			texcmp(void *content, void *key);
void		reload(t_data *app, char *filename);

/*
** Post-process :
*/

t_color		sepia(t_color in);
t_color		grayscale(t_color in);
t_color		anti_aliasing(t_color col_prim, t_data *app, int x, int y);

/*
** Interface :
*/

void		interface(t_data *app);

/*
** Loading :
*/

void		parse_material_csv(t_data *app, char *csv_file);

/*
** Static def :
*/

# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

#endif

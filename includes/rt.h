/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:16:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/12 07:56:33 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rtstruct.h"
# include "data_struct.h"
# include <SDL.h>
# include "libui.h"

/*
** Definition for the RT :
** Config :
*/

# define BACK_COLOR		0x000000
# define FOV			40.0f
# define DEPTH_MAX		0

# define DEBUG			0
# define MAC			MACB

/*
** User def :
*/

# define T_STEP			5
# define Z_STEP			1
# define A_STEP			5 * DEG_TO_RAD
# define MOUSE_SCALING	0.005f

/*
** Static def :
*/

# define DEV			0
# define MACB			1
# define IMAC			2
# define IMAC4K			3

# define PLANE			0
# define SPHERE			1
# define CONE			2
# define CYLINDER		3

# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

# define RM_UNIT_TEST	0
# define RM_NORMAL		1

/*
** Automatic parameters :
*/

# if (MAC == MACB)
#  define WIDTH			1680
#  define HEIGHT		700
# elif (MAC == IMAC)
#  define WIDTH			2560
#  define HEIGHT		1400
# elif (MAC == IMAC4K)
#  define WIDTH			3200
#  define HEIGHT		1800
# else
#  define WIDTH			840
#  define HEIGHT		500
# endif

/*
** Messages for RT :
*/

# define USAGE "Usage : ./RT <scene.rt> [options]\nOptions : hlt"

/*
** Prototypes :
*/

int				reader(char *str, t_data *data);
void			init_render(t_data *data);
void			update(void *data);
void			update_camera(t_cam *cam, bool *needs_render);
int				process_pixel(int x, int y, void *arg);
void			exit_safe(t_data *data);
void			key_event(int *quit, SDL_Keycode key, void *arg, bool state);
void			mouse_motion(SDL_Event *event, void *arg);
void			click_event(SDL_Event *event, void *arg);
void			parsing_error(int l_idx, char *error, t_data *d, char **greed);
int				parse_light(char **greed, t_data *data, int l_idx);
int				parse_shape(char **greed, t_data *data, int l_idx, int type);
void			light_intensity(t_inter *inter, t_color *color, t_ray *ray);
void			cast_shadow(t_data *data, t_inter *inter);
t_color			get_lighting(t_shading s, t_scene scene, t_settings *setng);
void			cast_primary(t_list *obj_list, t_inter *inter);
t_color			recursive_cast(t_scene scene, t_settings s, t_ray r, int depth);
void			set_direction(t_cam *cam, t_vec3 direction);
void			cam_ray(t_data *data, t_ray *res, float x, float y);
t_color			cast_light_primary(t_list *obj_list, t_inter *inter);
t_color			anti_aliasing(t_color col_prim, t_data *app, int x, int y);

void			camera_angle(t_data *data, int pan, int pitch);
void			camera_zoom(t_data *data, float value);
void			camera_height(t_data *data, float value);
void			camera_side(t_data *data, float value);
void			camera_pitch(t_data *data, float angle);
void			camera_pan(t_data *data, float angle);

/*
** Textures :
*/

t_color			texture_checkers(t_material *mat, t_vec3 uv);
t_color			texture_strips(t_material *mat, t_vec3 uv);
t_color 		sample(t_material *texture, t_vec3 uv);
char			*load_texture(char *filename, int *width, int *height);

void			init_interface(t_gui *gui, SDL_Window *window, t_data *app);
void			init(t_data	*data);
void			init_textures(t_data *app);
void			init_settings(t_settings *settings);
void			interface(t_data *app);
void			update_texture(t_img img, t_gui gui);
void			render_gui(void *arg);
void			ui_sphere(void *res);
void			ui_plane(void *res);
void			ui_cylinder(void *res);
void			ui_cone(void *res);
void			change_window_title(SDL_Window *win, t_data *app);
void			fullscreen(t_sdl *sdl, t_gui *gui);
int				export_scene(t_data *data, char *filename);
void			export_material(int fd, t_material *mat);
int				texcmp(void *content, void *key);
void			del_obj(void *content, size_t content_size);
void			del_mat(void *content, size_t content_size);
void			reload(t_data *app, char *filename);

t_color			sepia(t_color in);
t_color			grayscale(t_color in);

t_shading		get_shading_data(t_inter *inter);

#endif

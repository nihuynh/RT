/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:16:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/25 22:41:50 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rtstruct.h"
# include "t_data.h"

/*
** Prototypes :
*/

int			reader_no_exit(char *filename, t_data *app);



/*
** Init :
*/

int			reader(char *str, t_data *app);

/*
** Exit :
*/

void		del_light(void *content, size_t content_size);
void		free_scene(t_data *app);
void		exit_safe(int err_code);
void		init_interface(t_gui *gui, SDL_Window *window, t_data *app);
void		init(t_data	*data);
void		update_texture(t_img img, t_gui gui);
void		change_window_title(SDL_Window *win, t_data *app);
void		resize_app(int width, int height, t_data *app);
int			export_scene(t_data *data, char *filename);
void		export_material(int fd, t_material *mat);
void		free_lst(t_data *data);
void		reload(t_data *app, char *filename);
void		record_frame(t_data *app);

/*
** Interface :
*/

void		interface(t_data *app);

/*
** Hooks :
*/

void				render_gui(void *arg);
void				update(void *data);
void				update_camera(t_cam *cam, bool *needs_render);
void				key_event(int *quit, SDL_Keycode key, void *arg, bool state);
void				mouse_motion(SDL_Event *event, void *arg);
void				click_event(SDL_Event *event, void *arg);

#endif

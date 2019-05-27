/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:14:02 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/27 18:38:45 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "config.h"
#include "libft.h"
#include "interface.h"
#include <fcntl.h>
#include <unistd.h>

#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#if defined(__APPLE__)
# define GL_SILENCE_DEPRECATION
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

static inline void
	default_gui_settings(t_gui *gui, t_data *app)
{
	gui->export_open = false;
	gui->light_set = app->scene.lst_light;
	gui->obj_set = NULL;
	gui->flags_render = 2;
	gui->add_obj_type = 0;
	gui->stats_open = true;
	gui->edit_open = true;
	gui->render_set_open = true;
}

void
	hook_render_to_gui(t_gui *gui, SDL_Window *window)
{
	if (!(gui->gl_context = SDL_GL_CreateContext(window)))
		ft_error(__func__, __LINE__);
	igCreateContext(NULL);
	ImGui_ImplSDL2_InitForOpenGL(window, &gui->gl_context);
	ImGui_ImplOpenGL2_Init();
	glGenTextures(1, &gui->texture_id);
	glBindTexture(GL_TEXTURE_2D, gui->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

static inline void
	hook_cam_to_gui(t_data *app)
{
	set_direction(&app->cam, app->cam.dir);
	if (DEBUG)
		print_matrix(&app->cam.rotation);
	app->gui.cam_cpy = app->cam;
}

static inline void
	default_settings(t_settings *settings)
{
	settings->back_color = itocolor(BACK_COLOR);
	settings->depth_max = DEPTH_MAX;
	settings->filter = (t_color){1, 1, 1};
	settings->fov = FOV;
	settings->absorb = 1;
	settings->deflect = 1;
	settings->facing = 1;
	settings->i_light = 1;
	settings->light = 1;
	settings->shadow = 1;
	settings->shine = 1;
	settings->debug_normal = 0;
}

static inline void
	set_win_title(SDL_Window *win, t_data *app)
{
	char	*title;

	if (app->gui.scene_name == NULL)
		return ;
	if (!(app->gui.scene_name = ft_strrchr(app->arg, '/')))
		app->gui.scene_name = app->arg;
	else
		app->gui.scene_name++;
	if (!(title = ft_strjoin("RT - ", app->gui.scene_name)))
		ft_error(__func__, __LINE__);
	SDL_SetWindowTitle(win, title);
	ft_strdel(&title);
}

void
	hook_sdl(t_data *app)
{
	app->sdl->key_map = &key_event;
	app->sdl->mouse_map = &mouse_motion;
	app->sdl->update = &update;
	app->sdl->render_gui = &render_gui;
	app->sdl->click_map = &click_event;
	app->gui.app = app;
	app->gui.sdl = app->sdl;
	hook_render_to_gui(&app->gui, app->sdl->win);
	default_settings(&app->settings);
	default_gui_settings(&app->gui, app);
	app->sdl->needs_render = true;
	app->sdl->partial_render = false;
}

bool
	check_file(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (false);
	close(fd);
	return (true);
}

void
	load_scene(t_data *app, char *filename)
{
	free_scene(app);
	if (!(app->arg = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	if (reader(filename, app) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	default_settings(&app->settings);
	default_gui_settings(&app->gui, app);
	hook_cam_to_gui(app);
	set_win_title(app->sdl->win, app);
	app->sdl->needs_render = true;
	app->sdl->partial_render = false;
	if (DEBUG)
		ft_printf("Loading of the scene is completed\n");
}

void
	reload_scene(t_data *app, char *filename)
{
	char *tmp;

	if (!(tmp = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	load_scene(app, tmp);
	free(tmp);
}

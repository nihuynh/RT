/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:29:28 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/21 19:24:04 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "librt.h"
#include "ftio.h"
#include "ftstring.h"
#include "export.h"
#include <stdio.h>
#include <locale.h>
#include <fcntl.h>
#include <unistd.h>

static inline void
	export_camera(int fd, t_cam *cam, t_color amb_light, t_texture *skybox)
{
	t_vec3	direction;

	vec3_new(&direction, 0.0f, 0.0f, -1.0f);
	apply_matrix(&direction, &cam->rotation);
	vec3_normalize(&direction);
	write(fd, "camera\n{\n", 9);
	export_tvec3(fd, "origin", cam->pos);
	export_tvec3(fd, "direction", direction);
	export_color(fd, "amb_light", amb_light);
	if (skybox->pixels)
		dprintf(fd, "\tskybox(%s)\n", skybox->name);
	write(fd, "}\n", 2);
}

static inline void
	export_light(int fd, t_list *node)
{
	t_light *light;

	light = node->content;
	write(fd, "\tobject(light)\n\t{\n", 18);
	export_color(fd, "\tcolor", light->color);
	export_tvec3(fd, "\torigin", light->origin);
	dprintf(fd, "\t\tintensity(%.3f)\n", light->intensity);
	write(fd, "\t}\n", 3);
}

static inline void
	export_obj_from_lst(int fd, t_list *node)
{
	t_obj		*obj;

	obj = node->content;
	dprintf(fd, "\tobject(%s)\n\t{\n", get_obj_str(obj->type));
	dprintf(fd, "\t\tname(%s)\n", obj->name);
	obj->export(fd, obj->shape);
	export_material(fd, &obj->material);
	write(fd, "\t}\n", 3);
}

static inline void
	export_content(int fd, t_scene *scene)
{
	write(fd, "content\n{\n", 10);
	ft_lstiter_arg(fd, scene->lst_light, &export_light);
	ft_lstiter_arg(fd, scene->lst_obj, &export_obj_from_lst);
	write(fd, "}\n", 2);
}

int
	export_scene(t_data *app, char *filename)
{
	int fd;

	if (ft_strcmp(filename, "scenes/") == 0)
	{
		app->gui.export_open = true;
		return (0);
	}
	setlocale(LC_NUMERIC, "C");
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf("Error during export [%s]\n", filename);
		return (-1);
	}
	export_camera(fd, &app->cam, app->settings.amb_light, app->scene.skybox);
	export_content(fd, &app->scene);
	export_animation(fd, app);
	close(fd);
	setlocale(LC_NUMERIC, NULL);
	set_win_title(app->sdl->win, app->arg);
	return (0);
}

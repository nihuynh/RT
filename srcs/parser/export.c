/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:29:28 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/17 19:38:03 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"
#include <stdio.h>
#include <locale.h>
#include <fcntl.h>
#include <unistd.h>

static inline void
	export_camera(int fd, t_cam *cam, t_color amb_light)
{
	t_pt3	direction;

	direction = cam->dir;
	apply_matrix(&direction, &cam->rotation);
	vec3_normalize(&direction);
	write(fd, "camera\n{\n", 9);
	dprintf(fd, "\torigin(%.3f %.3f %.3f)\n", cam->pos.x, cam->pos.y,
		cam->pos.z);
	dprintf(fd, "\tdirection(%.3f %.3f %.3f)\n", direction.x, direction.y,
		direction.z);
	dprintf(fd, "\tamb_light(%.3f %.3f %.3f)", amb_light.r, amb_light.g,
		amb_light.b);
	write(fd, "\n}\n", 3);
}

static inline void
	export_light(int fd, t_list *node)
{
	t_light *light;

	light = node->content;
	write(fd, "\tobject(light)\n\t{\n", 18);
	dprintf(fd, "\t\tcolor(%.3f %.3f %.3f)\n", light->color.r, light->color.g,
		light->color.b);
	dprintf(fd, "\t\torigin(%.3f %.3f %.3f)", light->origin.x, light->origin.y,
		light->origin.z);
	dprintf(fd, "\n\t\tintensity(%.3f)\n", light->intensity);
	write(fd, "\t}\n", 3);
}

static inline void
	export_obj(int fd, t_list *node)
{
	t_obj		*obj;

	obj = node->content;
	dprintf(fd, "\tobject(%s)\n\t{\n", get_obj_str(obj->type));
	obj->export(fd, obj->shape);
	export_material(fd, &obj->material);
	write(fd, "\t}\n", 3);
}

static inline void
	export_content(int fd, t_scene *scene)
{
	write(fd, "content\n{\n", 10);
	ft_lstiter_arg(fd, scene->lst_light, &export_light);
	ft_lstiter_arg(fd, scene->lst_obj, &export_obj);
	write(fd, "}\n", 2);
}

int
	export_scene(t_data *data, char *filename)
{
	int fd;

	setlocale(LC_NUMERIC, "C");
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		ft_printf("Error during export [%s]\n", filename);
		return (-1);
	}
	export_camera(fd, &data->cam, data->settings.amb_light);
	export_content(fd, &data->scene);
	close(fd);
	setlocale(LC_NUMERIC, NULL);
	return (0);
}

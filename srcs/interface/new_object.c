/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:21:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/18 16:00:37 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "t_data.h"
#include "tools.h"
#include "parse.h"
#include "libft.h"
#include "export.h"

static inline t_built
	get_built_func(int type)
{
	const t_built built_func[] = {
		{&plane_new},
		{&sphere_new},
		{&cone_new},
		{&cylinder_new},
		{&cube_new}
	};

	return (built_func[type]);
}

void
	new_obj(t_data *app, int type)
{
	t_obj		new;
	t_parse		cfg;
	void		*shape;

	init_parse_cfg(type, &cfg);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	obj_set(&new, type);
	(get_built_func(type)).setter(&new, shape);
	new.shape = shape;
	new.export = cfg.export;
	new.material = app->gui.mat_set;
	new.name = name_obj(type, &app->scene.nb_objs[type]);
	ft_lstpushnew(&app->scene.lst_obj, &new, sizeof(t_obj));
	app->gui.obj_set = app->scene.lst_obj->content;
	ft_lstsort(&app->scene.lst_obj, &obj_cmp);
}

void
	new_axis_debug(t_data *app, t_pt3 origin, t_vec3 vec, t_color color)
{
	t_obj		obj;
	t_cylinder	*cylinder;
	int			cyl_type;

	cyl_type = get_obj_type("cylinder");
	if (!(cylinder = malloc(sizeof(t_cylinder))))
		ft_error(__func__, __LINE__);
	obj_set(&obj, cyl_type);
	cylinder_new(&obj, cylinder);
	cylinder->n = vec;
	cylinder->radius = 0.25;
	cylinder->size = 15.0;
	cylinder->origin = origin;
	vec3_normalize(&cylinder->n);
	create_orthobasis_from_y_axis(cylinder->n, &cylinder->x, &cylinder->z);
	obj.shape = cylinder;
	obj.export = &cylinder_export;
	obj.material = app->gui.mat_set;
	obj.material.color_diffuse = color;
	obj.name = name_obj(cyl_type, &app->scene.nb_objs[cyl_type]);
	ft_lstpushnew(&app->scene.lst_obj, &obj, sizeof(t_obj));
	ft_lstsort(&app->scene.lst_obj, &obj_cmp);
}

void
	new_light(t_data *app)
{
	t_light	light;

	light.color = (t_color){1, 1, 1};
	light.origin = (t_pt3){0, 0, 0};
	light.intensity = 100;
	light.name = name_obj(-1, &app->scene.nb_light);
	ft_lstpushnew(&app->scene.lst_light, &light, sizeof(t_light));
	app->sdl->needs_render = true;
	app->sdl->partial_render = false;
	ft_lstsort(&app->scene.lst_light, &light_cmp);
}

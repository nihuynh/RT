/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:21:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/14 02:21:23 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"

static inline t_built
	get_built_func(int type)
{
	const t_built built_func[] = {
		{&plane_new},
		{&sphere_new},
		{&cone_new},
		{&cylinder_new}
	};

	return (built_func[type]);
}

void
	new_obj(t_data *app, int type)
{
	t_obj		new;
	t_parse		cfg;
	void		*shape;
	t_material	*tmp;

	init_parse_cfg(type, &cfg);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	obj_set(&new, type);
	(get_built_func(type)).setter(shape);
	new.shape = shape;
	new.export = cfg.export;
	tmp = ft_lstgetelt(app->lst_mat, &matcmp, "white plastic");
	new.material = *tmp;
	new.name = name_obj(type, &app->scene.nb_objs[type]);
	ft_lstpushnew(&app->scene.lst_obj, &new, sizeof(t_obj));
	app->gui.obj_set = app->scene.lst_obj->content;
}

void
	new_light(t_data *app)
{
	t_light	light;

	light.color = (t_color){1, 1, 1};
	light.origin = (t_pt3){0, 0, 0};
	light.intensity = 100;
	light.name = name_obj(5, &app->scene.nb_light);
	ft_lstpushnew(&app->scene.lst_light, &light, sizeof(t_light));
	app->sdl->needs_render = true;
	app->sdl->partial_render = false;
}

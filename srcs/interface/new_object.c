/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:21:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/14 21:51:16 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"

static inline void
	init_new(int type, t_parse *config)
{
	const t_parse index_config[] = {
		{"plane", sizeof(t_plane), &plane_new, &plane_export, 6},
		{"sphere", sizeof(t_sphere), &sphere_new, &sphere_export, 5},
		{"cone", sizeof(t_cone), &cone_new, &cone_export, 7},
		{"cylinder", sizeof(t_cylinder), &cylinder_new, &cylinder_export, 7}
	};

	config = ft_memcpy(config, &index_config[type], sizeof(t_parse));
}

void
	new_obj(t_data *app, int type)
{
	t_obj		new;
	t_parse		cfg;
	void		*shape;
	t_material	*tmp;

	init_new(type, &cfg);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	cfg.setter(shape, NULL, 0);
	obj_set(&new, type, shape);
	new.export = cfg.export;
	tmp = ft_lstgetelt(app->lst_mat, &matcmp, "white plastic");
	new.material = *tmp;
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
	ft_lstpushnew(&app->scene.lst_light, &light, sizeof(t_light));
}

int
	obj_cmp(void *content, void *key)
{
	return (content == key);
}

void
	delete_obj(t_data *app)
{
	t_list	*ptr;
	t_list	*to_del;

	ptr = app->scene.lst_obj;
	if (!(to_del = ft_lstgetnode(ptr, &obj_cmp, app->gui.obj_set)))
		ft_error(__func__, __LINE__);
	if (ptr == to_del)
	{
		app->scene.lst_obj = to_del->next;
		ft_lstdelone(&to_del, &del_obj);
	}
	else
	{
		while (ptr->next != to_del && ptr->next != NULL)
			ptr = ptr->next;
		if (ptr->next != to_del)
			ft_error(__func__, __LINE__);
		ptr->next = to_del->next;
		ft_lstdelone(&to_del, &del_obj);
	}
	app->gui.obj_set = NULL;
}

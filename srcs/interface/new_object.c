/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:21:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 13:30:39 by sklepper         ###   ########.fr       */
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
	(get_built_func(type)).setter(shape);
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

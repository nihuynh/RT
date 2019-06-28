/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:39:30 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/26 18:01:02 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "librt.h"
#include "parse.h"

void
	update_obj(void *content, size_t content_size)
{
	t_obj	*obj;

	if (content_size != sizeof(t_obj))
		return ;
	obj = content;
	if (obj->type == get_obj_type("cube"))
	{
		set_min_max_corner(obj->shape);
	}
}

void
	check_all_obj(t_list *obj_list, void (*func)(void *c, size_t c_s))
{
	t_obj	*obj;
	t_csg	*csg;

	while (obj_list != NULL)
	{
		obj = obj_list->content;
		if (obj->type == get_obj_type("csg"))
		{
			csg = obj->shape;
			ft_b3apply_prefix(csg->root, func);
		}
		else
			func(obj_list->content, obj_list->content_size);
		obj_list = obj_list->next;
	}
}

void
	prep_render(t_sdl *sdl)
{
	t_data *app;

	app = get_app(NULL);
	(void)sdl;
	check_all_obj(app->scene.lst_obj, &update_obj);
}

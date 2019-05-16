/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:28:14 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/16 15:07:29 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "libui.h"

void
	del_obj(void *content, size_t content_size)
{
	t_obj *obj;

	(void)content_size;
	obj = content;
	free(obj->shape);
	free(obj);
}

static inline void
	del_light(void *content, size_t content_size)
{
	t_light *light;

	(void)content_size;
	light = content;
	free(light);
}

static inline void
	del_tex(void *content, size_t content_size)
{
	t_texture *texture;

	(void)content_size;
	texture = content;
	if (texture->pixels)
	{
		free(texture->pixels);
		free(texture->name);
	}
	free(texture);
}

static inline void
	del_mat(void *content, size_t content_size)
{
	t_material *mat;

	(void)content_size;
	mat = content;
	free(mat->name);
	free(mat);
}

void
	free_lst(t_data *data)
{
	if (data->scene.lst_obj)
		ft_lstdel(&data->scene.lst_obj, &del_obj);
	if (data->scene.lst_light)
		ft_lstdel(&data->scene.lst_light, &del_light);
	if (data->lst_mat)
		ft_lstdel(&data->lst_mat, &del_mat);
	if (data->lst_tex)
		ft_lstdel(&data->lst_tex, &del_tex);
}

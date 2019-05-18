/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:28:14 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/18 01:56:58 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "libui.h"
#include "config.h"

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
	free_scene(t_data *app)
{
	if (app->scene.lst_obj)
		ft_lstdel(&app->scene.lst_obj, &del_obj);
	if (app->scene.lst_light)
		ft_lstdel(&app->scene.lst_light, &del_light);
	if (DEBUG)
		ft_printf("Scene [%s] deallocated.\n", app->arg);
	ft_strdel(&app->arg);
}

void
	free_lst(t_data *app)
{
	free_scene(app);
	if (app->lst_mat)
		ft_lstdel(&app->lst_mat, &del_mat);
	if (app->lst_tex)
		ft_lstdel(&app->lst_tex, &del_tex);
	if (DEBUG)
		ft_printf("Texture and material deallocated.\n");
}

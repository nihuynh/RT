/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:53:33 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/24 18:28:43 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_data.h"
#include "config.h"
#include "tools.h"

static inline void
	del_tex(void *content, size_t content_size)
{
	t_texture *texture;

	(void)content_size;
	texture = content;
	ft_strdel(&texture->pixels);
	ft_strdel(&texture->name);
	ft_strdel(&texture->dir);
	ft_memdel((void **)&texture);
}

static inline void
	del_mat(void *content, size_t content_size)
{
	t_material *mat;

	(void)content_size;
	mat = content;
	ft_strdel(&mat->name);
	ft_memdel((void **)&mat);
}

static inline void
	del_scene_lst(void *content, size_t content_size)
{
	t_scene_name *scene;

	(void)content_size;
	scene = content;
	ft_strdel(&scene->dir);
	ft_strdel(&scene->name);
	ft_memdel((void **)&scene);
}

void
	free_scene(t_data *app)
{
	if (app->scene.lst_anim)
		ft_lstdel(&app->scene.lst_anim, &del_anim);
	if (app->scene.lst_anim_light)
		ft_lstdel(&app->scene.lst_anim_light, &del_anim);
	if (app->scene.lst_obj)
		ft_lstdel(&app->scene.lst_obj, &del_obj);
	if (app->scene.lst_light)
		ft_lstdel(&app->scene.lst_light, &del_light);
	if (app->cam.anim)
		del_anim(app->cam.anim, 0);
	ft_bzero(app->scene.nb_objs, sizeof(app->scene.nb_objs));
	app->scene.nb_light = 0;
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
	if (app->lst_scenes)
		ft_lstdel(&app->lst_scenes, &del_scene_lst);
	if (DEBUG)
		ft_printf("Texture and material deallocated.\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:28:14 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/28 15:29:24 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "libui.h"
#include "config.h"

void free_btree(t_btree *node)
{
	t_obj *obj_in_btree;

	if (node->content_size == sizeof(t_obj))
	{
		obj_in_btree = node->content;
		free(obj_in_btree->shape);
		obj_in_btree->shape = NULL;
	}
	free(node->content);
	node->content = NULL;
	free(node);
	node = NULL;
}

void
	del_obj(void *content, size_t content_size)
{
	t_obj	*obj;
	t_csg	*csg;
	int		type_csg;
	t_btree *root;


	(void)content_size;
	obj = (t_obj*)content;
	type_csg = get_obj_type("csg");
	csg = obj->shape;
	if (obj->type == type_csg)
	{
		root = csg->root;
		ft_b3del(&root, free_btree);
	}
	free(obj->shape);
	obj->shape = NULL;
	free(obj->name);
	free(obj);
}

void
	del_light(void *content, size_t content_size)
{
	t_light *light;

	(void)content_size;
	light = content;
	free(light->name);
	free(light);
	light = NULL;
}

static inline void
	del_tex(void *content, size_t content_size)
{
	t_texture *texture;

	(void)content_size;
	texture = content;
	ft_strdel(&texture->pixels);
	ft_strdel(&texture->name);
	ft_strdel(&texture->dir);
	free(texture);
}

static inline void
	del_mat(void *content, size_t content_size)
{
	t_material *mat;

	(void)content_size;
	mat = content;
	ft_strdel(&mat->name);
	free(mat);
}

static inline void
	del_scene_lst(void *content, size_t content_size)
{
	t_scene_name *scene;

	(void)content_size;
	scene = content;
	free(scene->dir);
	free(scene->name);
	free(scene);
}

void
	free_scene(t_data *app)
{
	if (app->scene.lst_obj)
		ft_lstdel(&app->scene.lst_obj, &del_obj);
	if (app->scene.lst_light)
		ft_lstdel(&app->scene.lst_light, &del_light);
	ft_bzero(app->scene.nb_objs, sizeof(int) * 5);
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

void	exit_ui(SDL_GLContext *gl_context);

void
	free_app(t_data *app)
{
	int		debug_leak;

	free_lst(app);
	exit_ui(app->gui.gl_context);
	exit_sdl(app->sdl);
	debug_leak = app->option.key_found_bitrpz & (1UL << ('l' - 'a'));
	while (debug_leak)
		;
	get_app(app);
}

void
	exit_safe(int err_code)
{
	int		debug_leak;
	t_data	*app;

	app = get_app(NULL);
	debug_leak = app->option.key_found_bitrpz & (1UL << ('l' - 'a'));
	(app->option.key_found_bitrpz &= ~(1UL << ('l' - 'a')));
	free_app(app);
	while (debug_leak)
		;
	exit(err_code);
}

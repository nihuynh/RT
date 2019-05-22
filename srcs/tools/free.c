/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:28:14 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/22 22:16:17 by nihuynh          ###   ########.fr       */
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
	free(obj);
}

static inline void
	del_light(void *content, size_t content_size)
{
	t_light *light;

	(void)content_size;
	light = content;
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

void
	free_app(t_data *app)
{
	int		debug_leak;

	free_lst(app);
	SDL_GL_DeleteContext(app->gui.gl_context);
	exit_sdl(app->sdl);
	debug_leak = app->option.key_found_bitrpz & (1 << ('l' - 'a'));
	// free(app);
	while (debug_leak)
		;
	get_app(app);
}

void
	exit_safe(int err_code)
{
	free(get_app(NULL));
	exit(err_code);
}

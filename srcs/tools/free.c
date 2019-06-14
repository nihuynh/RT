/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:28:14 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/14 15:44:18 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "libui.h"
#include "rt.h"
#include "config.h"

static inline void
	free_btree(t_btree *node)
{
	if (node->content_size == sizeof(t_obj))
		del_obj(node->content, node->content_size);
	else
	{
		free(node->content);
		node->content = NULL;
	}
	free(node);
	node = NULL;
}

void
	del_obj(void *content, size_t content_size)
{
	t_obj	*obj;
	t_csg	*csg;
	t_btree *root;

	(void)content_size;
	obj = (t_obj*)content;
	csg = obj->shape;
	if (obj->type == get_obj_type("csg"))
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

void
	free_app(t_data *app)
{
	int		debug_leak;

	free_lst(app);
	exit_ui(app->gui.gl_context);
	exit_sdl(app->sdl);
	ft_strdel(&app->option.path);
	debug_leak = app->option.key_found_bitrpz & (1UL << ('l' - 'a'));
	free(app);
	get_app(app);
	app = NULL;
	while (debug_leak)
		;
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

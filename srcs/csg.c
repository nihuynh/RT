/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:22:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/17 08:08:42 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftbtree.h"
#include "rtstruct.h"
#include "data_struct.h"

void 	csg_set(void *root_bad, char **greed, int i)
{
	// Do stuff
	(void)root_bad;
	(void)greed;
	(void)i;
}


void 	inter_csg(t_inter *data, t_obj *node)
{
	// Do stuff
	(void)data;
	(void)node;
}


/*
** UI :
*/

void 	ui_csg(void *shape)
{
	t_btree *root;

	root = shape;
	// built interface with imgui
}

void 	csg_export(int fd, void *shape)
{
	t_btree *root;

	root = shape;
	// Dump position and orientation
	// Dump the tree
	// ft_b3apply_infix_arg(root, fd, btree_export);
	(void)fd;
}

/*
** Useless for csg because it's not the primitives :
*/

void 	normal_csg(t_inter *inter)
{
	// Do stuff
	(void)inter;
}

t_vec3 get_csg_uv(t_inter *inter)
{
	t_vec3 tmp;

	tmp = inter->obj->get_uv(inter);
	return (tmp);
}


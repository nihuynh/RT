/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:22:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/19 07:40:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftbtree.h"
#include "ftstring.h"
#include "ftio.h"
#include "rtstruct.h"
#include "parse.h"
#include "data_struct.h"

typedef struct	s_csg_op
{
	int			type;
}				t_csg_op;

t_btree	*csg_parse_op(t_parse_txt *scene_file, int type)
{
	t_csg_op res;

	scene_file->line_idx++;
	res.type = type;
	return (ft_b3new(&res, sizeof(t_csg_op)));
}

t_btree	*csg_parse_obj(t_parse_txt *scene_file, int type)
{
	t_obj res;

	scene_file->line_idx++;
	create_obj(&res, scene_file, type);
	return (ft_b3new(&res, sizeof(t_obj)));
}

int			csg_is_op(t_parse_txt *scene_file)
{
	if (ft_strstr(scene_file->get_curr_line(scene_file), "AND") != NULL)
		return (1);
	if (ft_strstr(scene_file->get_curr_line(scene_file), "NOT") != NULL)
		return (2);
	if (ft_strstr(scene_file->get_curr_line(scene_file), "UNION") != NULL)
		return (3);
	return (0);
}

int			csg_is_obj(t_parse_txt *scene_file)
{
	char	*type_tested;
	int		type;

	type = -1;
	type_tested = NULL;
	while ((type_tested = get_obj_str(++type)))
	{
		if (ft_strstr(scene_file->get_curr_line(scene_file), type_tested) != NULL)
			return (type);
	}
	return (-1);
}

t_btree	*csg_tree_parse(t_parse_txt *scene_file)
{
	t_btree		*root;
	int			type_csg_node;

	root = NULL;
	type_csg_node = -1;
	if ((type_csg_node = csg_is_op(scene_file)))
		root = csg_parse_op(scene_file, type_csg_node);
	else if ((type_csg_node = csg_is_obj(scene_file)) != -1)
		root = csg_parse_obj(scene_file, type_csg_node);
	else
		ft_error(__func__, __LINE__);
	if (root->content_size == sizeof(t_obj))
		return (root);
	root->right = csg_tree_parse(scene_file);
	root->left = csg_tree_parse(scene_file);
	return (root);
}

void 	csg_set(void *csg, t_parse_txt *scene_file)
{
	t_csg		*pcsg;

	if (csg == NULL)
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_SET_CSG, scene_file);
	}
	pcsg = csg;
	parse_vector(&pcsg->origin, "origin(", scene_file);
	parse_vector(&pcsg->n, "normal(", scene_file);
	// parse tree
	pcsg->root = csg_tree_parse(scene_file);
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


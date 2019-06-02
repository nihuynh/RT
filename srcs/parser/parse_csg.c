/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_csg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:02:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/03 00:28:45 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftbtree.h"
#include "ftstring.h"
#include "rtstruct.h"
#include "parse.h"

int
	csg_is_obj(t_parse_txt *scene_file)
{
	char *line;

	line = get_args_key_require(scene_file, "object(");
	return (get_obj_type(line));
}

t_btree
	*csg_parse_obj(t_parse_txt *scene_file, int type)
{
	t_obj res;

	create_obj_from_txt(&res, scene_file, type);
	return (ft_b3new(&res, sizeof(t_obj)));
}

t_btree
	*csg_parse_op(t_parse_txt *scene_file, int type)
{
	t_csg_op res;

	scene_file->line_idx++;
	res.type = type;
	return (ft_b3new(&res, sizeof(t_csg_op)));
}

t_btree
	*csg_tree_parse(t_parse_txt *scene_file)
{
	t_btree		*root;
	int			type_csg_node;

	root = NULL;
	type_csg_node = -1;
	if ((type_csg_node = csg_is_op(scene_file)))
		root = csg_parse_op(scene_file, type_csg_node);
	else if ((type_csg_node = csg_is_obj(scene_file)) != -1)
		root = csg_parse_obj(scene_file, type_csg_node);
	if (root->content_size == sizeof(t_obj))
		return (root);
	root->left = csg_tree_parse(scene_file);
	root->right = csg_tree_parse(scene_file);
	return (root);
}

void
	csg_set(void *csg, t_parse_txt *scene_file)
{
	t_csg		*pcsg;

	if (sizeof(t_obj) == sizeof(t_csg_op))
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_OP_EQUAL_OBJ, scene_file);
	}
	if (csg == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_CSG, scene_file);
	}
	pcsg = csg;
	pcsg->origin = parse_vector("origin(", scene_file);
	pcsg->n = parse_vector("normal(", scene_file);
	pcsg->root = csg_tree_parse(scene_file);
}

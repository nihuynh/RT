/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:22:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/17 21:17:24 by nihuynh          ###   ########.fr       */
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

t_btree	*csg_parse_op(int *line_idx, int type)
{
	t_csg_op res;

	line_idx++;
	res.type = type;
	return (ft_b3new(&res, sizeof(t_csg_op)));
}
t_btree	*csg_parse_obj(char **greed, int *line_idx, int type)
{
	t_obj res;

	create_obj(&res, greed, line_idx, type);
	return (ft_b3new(&res, sizeof(t_obj)));
}

int			csg_is_op(char **greed, int *i)
{
	if (ft_strstr(greed[*i], "AND") != NULL)
		return (1);
	if (ft_strstr(greed[*i], "NOT") != NULL)
		return (2);
	if (ft_strstr(greed[*i], "UNION") != NULL)
		return (3);
	return (0);
}
int			csg_is_obj(char **greed, int *i)
{
	char	*type_tested;
	int		type;

	type = -1;
	type_tested = NULL;
	while ((type_tested = get_obj_str(++type)))
	{
		if (ft_strstr(greed[*i], type_tested) != NULL)
			return (type);
	}
	return (-1);
}

t_btree	*csg_parse(char **greed, int *i)
{
	t_btree		*root;
	int			type_csg_node;

	root = NULL;
	type_csg_node = -1;
	if ((type_csg_node = csg_is_op(greed, i)))
		root = csg_parse_op(i, type_csg_node);
	else if ((type_csg_node = csg_is_obj(greed, i)) != -1)
		root = csg_parse_obj(greed, i, type_csg_node);
	else
		ft_error(__func__, __LINE__);
	if (root->content_size == sizeof(t_obj))
		return (root);
	root->right = csg_parse(greed, i);
	root->left = csg_parse(greed, i);
	return (root);
}

void 	csg_set(void *root, char **greed, int i)
{
	free(&root);
	root = csg_parse(greed, &i);
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


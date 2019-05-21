/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_csg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:02:38 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/21 03:11:26 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "rtstruct.h"
#include "export.h"

static inline void
	export_obj_from_btree(int fd, t_obj *node_content)
{
	dprintf(fd, "\t\tobject(%s)\n\t\t{\n", get_obj_str(node_content->type));
	node_content->export(fd, node_content->shape);
	export_material(fd, &node_content->material);
	dprintf(fd, "\t\t}\n");
}

static inline void
	export_csg_op(int fd, t_csg_op *node_content)
{
	int type;

	type = node_content->type;
	if (type == AND)
		dprintf(fd, "\t\t%s\n", AND_STR);
	if (type == NOT)
		dprintf(fd, "\t\t%s\n", NOT_STR);
	if (type == UNION)
		dprintf(fd, "\t\t%s\n", UNION_STR);
}

static inline void
	export_btree(int fd, void *content, size_t content_size)
{
	if (content_size == sizeof(t_obj))
		export_obj_from_btree(fd, (t_obj*)content);
	else
		export_csg_op(fd, (t_csg_op*)content);
}

void
	csg_export(int fd, void *shape)
{
	t_csg *pcsg;

	pcsg = shape;
	dprintf(fd, "\t\torigin(%.3f %.3f %.3f)", pcsg->origin.x, pcsg->origin.y,
		pcsg->origin.z);
	dprintf(fd, "\n\t\tnormal(%.3f %.3f %.3f)\n", pcsg->n.x, pcsg->n.y, pcsg->n.z);
	ft_b3apply_prefix_wtarg(fd, pcsg->root, &export_btree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:21:36 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/07 18:24:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "export.h"
#include <stdio.h>

void
	plane_export(int fd, void *shape)
{
	t_plane		*plane;

	plane = shape;
	export_tvec3(fd, "\torigin", plane->origin);
	export_tvec3(fd, "\tnormal", plane->n);
	dprintf(fd, "\t\tlimit(%.3f %.3f)\n", plane->size.x, plane->size.y);
}

void
	sphere_export(int fd, void *shape)
{
	t_sphere	*sphere;

	sphere = shape;
	export_tvec3(fd, "\torigin", sphere->origin);
	dprintf(fd, "\t\tradius(%.3f)\n", sphere->radius);
}

void
	cone_export(int fd, void *shape)
{
	t_cone	*cone;

	cone = shape;
	export_tvec3(fd, "\torigin", cone->origin);
	export_tvec3(fd, "\tnormal", cone->n);
	dprintf(fd, "\t\ttheta(%.3f)\n", cone->theta);
	dprintf(fd, "\t\tsize(%.3f)\n", cone->size);
}

void
	cylinder_export(int fd, void *shape)
{
	t_cylinder	*cylinder;

	cylinder = shape;
	export_tvec3(fd, "\torigin", cylinder->origin);
	export_tvec3(fd, "\tnormal", cylinder->n);
	dprintf(fd, "\t\tradius(%.3f)\n", cylinder->radius);
	dprintf(fd, "\t\tsize(%.3f)\n", cylinder->size);
}

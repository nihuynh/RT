/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:21:36 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/06 19:04:07 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include <stdio.h>

void	plane_export(int fd, void *shape)
{
	t_plane		*p;

	p = shape;
	dprintf(fd, "\t\torigin(%f %f %f)", p->origin.x, p->origin.y, p->origin.z);
	dprintf(fd, "\n\t\tnormal(%f %f %f)\n", p->n.x, p->n.y, p->n.z);
	dprintf(fd, "\t\tlimit(%f %f)\n", p->size_x, p->size_y);
}

void	sphere_export(int fd, void *shape)
{
	t_sphere	*s;

	s = shape;
	dprintf(fd, "\t\torigin(%f %f %f)", s->origin.x, s->origin.y, s->origin.z);
	dprintf(fd, "\n\t\tradius(%f)\n", s->radius);
}

void	cone_export(int fd, void *shape)
{
	t_cone	*c;

	c = shape;
	dprintf(fd, "\t\torigin(%f %f %f)", c->origin.x, c->origin.y, c->origin.z);
	dprintf(fd, "\n\t\tnormal(%f %f %f)\n", c->n.x, c->n.y, c->n.z);
	dprintf(fd, "\t\ttheta(%f)\n", c->theta);
	dprintf(fd, "\t\tsize(%f)\n", c->size);
}

void	cylinder_export(int fd, void *shape)
{
	t_cylinder	*c;

	c = shape;
	dprintf(fd, "\t\torigin(%f %f %f)", c->origin.x, c->origin.y, c->origin.z);
	dprintf(fd, "\n\t\tnormal(%f %f %f)\n", c->n.x, c->n.y, c->n.z);
	dprintf(fd, "\t\tradius(%f)\n", c->radius);
	dprintf(fd, "\t\tsize(%f)\n", c->size);
}

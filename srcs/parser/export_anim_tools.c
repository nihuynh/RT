/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_anim_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 22:12:49 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/26 01:25:00 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include <stdio.h>

void	export_translate(int fd, t_anim *anim)
{
	t_translate	*translate;

	translate = anim->res;
	dprintf(fd, "\t\t\tdir(%f %f %f)\n", translate->dir.x, translate->dir.y,
		translate->dir.z);
	dprintf(fd, "\t\t\tspeed(%f)\n", translate->speed);
}

void	export_orbit(int fd, t_anim *anim)
{
	t_orbit	*orbit;

	orbit = anim->res;
	dprintf(fd, "\t\t\tcenter_obj(%s)\n", orbit->obj_center->name);
	dprintf(fd, "\t\t\taxis(%f %f %f)\n", orbit->axis.x, orbit->axis.y,
		orbit->axis.z);
	dprintf(fd, "\t\t\tdeg(%f)\n", orbit->deg);
}

void	export_rotate(int fd, t_anim *anim)
{
	t_rotate	*rotate;

	rotate = anim->res;
	dprintf(fd, "\t\t\taxis(%f %f %f)\n", rotate->axis.x, rotate->axis.y,
		rotate->axis.z);
	dprintf(fd, "\t\t\tdeg(%f)\n", rotate->deg);
}

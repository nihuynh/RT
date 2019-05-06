/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_toolbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:57:38 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/06 19:38:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include <stdio.h>

static inline void
	export_color(int fd, char *name, t_color color)
{
	dprintf(fd, "\t\t%s(%f %f %f)\n", name, color.r, color.g, color.b);
}

void
	export_material(int fd, t_material *mat)
{
	dprintf(fd, "\t\ttexture(%s)\n", mat->tex->name);
	export_color(fd, "color_diffuse", mat->color_diffuse);
	export_color(fd, "color_specular", mat->color_specular);
	export_color(fd, "self_light", mat->self_light);
	dprintf(fd, "\t\tspec_idx(%f)\n", mat->spec_idx);
	dprintf(fd, "\t\tspec_power(%f)\n", mat->spec_power);
	export_color(fd, "refraction_color", mat->refraction_color);
	export_color(fd, "reflection_color", mat->reflection_color);
	dprintf(fd, "\t\trefraction_idx(%f)\n", mat->refraction_idx);
}

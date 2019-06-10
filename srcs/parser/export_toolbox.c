/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_toolbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:57:38 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/07 19:51:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include <stdio.h>

void
	export_color(int fd, char *name, t_color color)
{
	dprintf(fd, "\t%s(%.3f %.3f %.3f)\n", name, color.r, color.g, color.b);
}

static inline void
	export_tvec2(int fd, char *name, t_vec2 vec)
{
	dprintf(fd, "\t\t%s(%.3f %.3f)\n", name, vec.x, vec.y);
}

void
	export_tvec3(int fd, char *name, t_vec3 vector)
{
	dprintf(fd, "\t%s(%.3f %.3f %.3f)\n", name, vector.x, vector.y, vector.z);
}

void
	export_material(int fd, t_material *mat)
{
	dprintf(fd, "\t\ttexture(%s)\n", mat->tex->name);
	dprintf(fd, "\t\tnormal_map(%s)\n", mat->normal_map->name);
	dprintf(fd, "\t\tspec_map(%s)\n", mat->spec_map->name);
	export_color(fd, "\tcolor_diffuse", mat->color_diffuse);
	export_color(fd, "\tcolor_specular", mat->color_specular);
	export_color(fd, "\tcolor_tex", mat->color_tex);
	dprintf(fd, "\t\tspec_idx(%.3f)\n", mat->spec_idx);
	dprintf(fd, "\t\tspec_power(%.3f)\n", mat->spec_power);
	export_color(fd, "\trefraction_color", mat->refraction_color);
	export_color(fd, "\treflection_color", mat->reflection_color);
	dprintf(fd, "\t\trefraction_idx(%.3f)\n", mat->refraction_idx);
	export_tvec2(fd, "uv_scale", mat->uv_mapping.scale);
	export_tvec2(fd, "uv_offset", mat->uv_mapping.offset);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:38:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/04 15:08:32 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

uint32_t	sepia(uint32_t in_col)
{
	t_color in;
	t_color out;

	in = itocolor(in_col);
	out.r = (in.r * .393) + (in.g *.769) + (in.b * .189);
	out.r = (in.r * .349) + (in.g *.686) + (in.b * .168);
	out.r = (in.r * .272) + (in.g *.534) + (in.b * .131);
	return (colortoi(out));
}

t_color	anti_aliasing(t_color col_prim, t_data *app, int x, int y)
{
	t_ray	ray;

	cam_ray(app, &ray, x, y);
	color_add(&col_prim, recursive_cast(app->scene, app->settings, ray, 0));
	cam_ray(app, &ray, x + 1, y);
	color_add(&col_prim, recursive_cast(app->scene, app->settings, ray, 0));
	cam_ray(app, &ray, x, y + 1);
	color_add(&col_prim, recursive_cast(app->scene, app->settings, ray, 0));
	cam_ray(app, &ray, x + 1, y + 1);
	color_add(&col_prim, recursive_cast(app->scene, app->settings, ray, 0));
	color_scalar(&col_prim, 0.2);
	return (col_prim);
}

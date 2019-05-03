/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:38:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/03 15:58:12 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

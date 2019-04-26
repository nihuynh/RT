/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:41:32 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/24 12:31:27 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"

t_obj	*find_obj_at_pixel(t_data *app, int x, int y)
{
	t_inter	inter;
	t_ray	ray;

	cam_ray(app, &ray, x + 0.5, y + 0.5);
	inter_set(&inter, ray);
	cast_primary(app->scene.lst_obj, &inter);
	return (inter.obj);
}

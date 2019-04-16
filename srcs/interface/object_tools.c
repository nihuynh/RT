/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:41:32 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 17:54:47 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*find_obj_at_pixel(t_data *app, int x, int y)
{
	t_inter	inter;

	cam_ray(app, &inter.ray, x + 0.5, y + 0.5);
	cast_primary(app, &inter);
	return (inter.obj);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_setdeflect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/05 14:26:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	inter_setdeflect(t_inter *inter, t_vec3 shading_normal)
{
	inter->deflected.origin = inter->point;
	inter->deflected.dir = vec3_deflect(inter->ray.dir, shading_normal);
	ray_offset_origin(&inter->deflected, inter->n);
}

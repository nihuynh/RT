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

void	inter_setdeflect(t_inter *inter, t_ray *res)
{
	res->origin = inter->point;
	res->dir = vec3_deflect(inter->ray.dir, inter->n);
	ray_offset_origin(res, inter->n);
}

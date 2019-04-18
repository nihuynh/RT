/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_setrefract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:26:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/14 14:27:47 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	inter_setrefract(t_inter *inter, t_ray *res)
{
	res->origin = inter->point;
	res->dir = vec3_refract(inter->ray.dir, inter->n, 1.5);
	ray_offset_origin(res, inter->n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 00:59:23 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 18:51:32 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	normal_plane(t_inter *inter)
{
	t_plane	*plane;

	plane = inter->obj->shape;
	vec3_cpy(&inter->n, &plane->n);
	if (vec3_dot(&plane->n, &inter->ray.n) > 0)
		vec3_scalar(&inter->n, -1);
}

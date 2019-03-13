/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 04:28:37 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:16:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <stdlib.h>

void	ray_new(t_ray *res, t_pt3 *origin, t_vec3 *n)
{
	if (!res || !origin || !n)
		return ;
	vec3_cpy((t_vec3*)&(res->origin), (t_vec3*)origin);
	vec3_cpy(&(res->n), n);
	vec3_normalize(&res->n);
}

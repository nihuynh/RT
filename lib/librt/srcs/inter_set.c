/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:31:55 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/18 23:48:37 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>
#include "ftmem.h"

void	inter_set(t_inter *inter, t_ray ray)
{
	ft_bzero(inter, sizeof(t_inter));
	inter->dist = INFINITY;
	inter->hit_pts.x = INFINITY;
	inter->hit_pts.y = INFINITY;
	inter->obj = NULL;
	inter->ray = ray;
}

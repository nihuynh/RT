/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:31:55 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 03:47:03 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmem.h"

void	inter_set(t_inter *inter, t_ray ray)
{
	ft_bzero(inter, sizeof(t_inter));
	inter->dist = HUGEVAL;
	inter->hit_pts.x = HUGEVAL;
	inter->hit_pts.y = HUGEVAL;
	inter->obj = NULL;
	inter->ray = ray;
}

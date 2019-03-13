/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:31:55 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:20:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmem.h"

void	inter_set(t_inter *inter, t_ray *ray)
{
	inter->dist = HUGEVAL;
	inter->obj = NULL;
	ft_memcpy(&inter->ray, ray, sizeof(t_ray));
}

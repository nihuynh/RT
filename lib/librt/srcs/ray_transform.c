/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 19:29:20 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/07/20 19:29:23 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

t_ray	ray_transform(t_ray ray, t_matrix m)
{
	apply_matrix(&ray.dir, &m);
	apply_matrix(&ray.origin, &m);
	return (ray);
}

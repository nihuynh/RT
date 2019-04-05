/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_spherical_cartesian.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:59:42 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/04/05 17:59:45 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtstruct.h>
#include <math.h>

/*
** acos() maps [-1, 1] to [0, PI]
** atan() maps [-inf, +inf] to [-PI, PI]
*/

void vec3_cartesian_to_spherical(t_vec3 direction, float *azimuth, float *polar)
{
	*polar = acosf(direction.y);
	*azimuth = atan2f(direction.x, direction.z);
}

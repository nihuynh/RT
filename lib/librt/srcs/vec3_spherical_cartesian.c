/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_spherical_cartesian.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:59:42 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/12 07:10:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include <math.h>

/*
** acos() maps [-1, 1] to [0, PI]
** atan() maps [-inf, +inf] to [-PI, PI]
*/

void	vec3_cartesian_to_spherical(t_vec3 dir, float *azimuth, float *polar)
{
	*polar = acosf(dir.y);
	*azimuth = atan2f(dir.x, dir.z);
}

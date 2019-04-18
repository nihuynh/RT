/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_refract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:33:27 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/08 21:00:54 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "libft.h"
#include <math.h>

t_vec3
	vec3_refract(t_vec3 ray, t_vec3 normal, float ior)
{
	float	toby[5];
	t_vec3	refracted;

	refracted = normal;
	AAAA = ft_clampf(vec3_dot(&ray, &normal), -1, 1);
	BBBB = 1;
	CCCC = ior;
	if (AAAA < 0)
		AAAA = -AAAA;
	else
	{
		ft_swapf(&BBBB, &CCCC);
		vec3_scalar(&refracted, -1);
	}
	if ((EEEE = 1 - (BBBB / CCCC) * (BBBB / CCCC) * (1 - AAAA * AAAA)) < 0)
		ft_bzero(&refracted, sizeof(t_vec3));
	else
	{
		vec3_scalar(&ray, (BBBB / CCCC));
		vec3_scalar(&normal, (BBBB / CCCC) * AAAA - sqrtf(EEEE));
		vec3_add(&refracted, &ray, &normal);
		vec3_normalize(&refracted);
	}
	return (refracted);
}

/*
** Vec3f refract(const Vec3f &I, const Vec3f &N, const float &ior)
** {
**     float cosi = clamp(-1, 1, dotProduct(I, N));
**     float etai = 1, etat = ior;
**     Vec3f n = N;
**     if (cosi < 0)
** 	{
** 		cosi = -cosi;
** 	} else
** 	{
** 		std::swap(etai, etat);
** 		n= -N;
** 	}
**     float eta = etai / etat;
**     float k = 1 - eta * eta * (1 - cosi * cosi);
**     return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n;
** }
*/

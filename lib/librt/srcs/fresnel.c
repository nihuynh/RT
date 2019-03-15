/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:56:28 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/15 14:20:34 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>
#include "libft.h"

void	fresnel(t_inter *inter, float ior)
{
	float	toby[5];
	float	result[2];

	AAAA = ft_clampf(vec3_dot(&inter->ray.n, &inter->n), -1, 1);
	BBBB = 1;
	CCCC = ior;
	if (AAAA < 0)
		ft_swapf(&BBBB, &CCCC);
	DDDD = BBBB / CCCC * sqrtf(fmaxf(0.f, 1 - AAAA * AAAA));
	if (DDDD >= 1 && AAAA < 0)
		inter->kr = 1;
	else
	{
		EEEE = sqrtf(fmaxf(0.f, 1 - DDDD * DDDD));
		AAAA = fabsf(AAAA);
		result[0] = ((CCCC * AAAA) - (BBBB * EEEE)) / ((CCCC * AAAA) + (BBBB * EEEE));
		result[1] = ((BBBB * AAAA) - (CCCC * EEEE)) / ((BBBB * AAAA) + (CCCC * EEEE));
		inter->kr = (result[0] * result[0] + result[1] * result[1]) / 2;
	}
}



// void fresnel(const Vec3f &I, const Vec3f &N, const float &ior, float &kr) 
// { 
//     float cosi = clamp(-1, 1, dotProduct(I, N)); 
//     float etai = 1, etat = ior; 
//     if (cosi > 0)
//		{
// 			std::swap(etai, etat); } 
//     // Compute sini using Snell's law
//     float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi)); 
//     // Total internal reflection
//     if (sint >= 1) { 
//         kr = 1; 
//     } 
//     else { 
//         float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
//         cosi = fabsf(cosi); 
//         float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
//         float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
//         kr = (Rs * Rs + Rp * Rp) / 2; 
//     } 
//     // As a consequence of the conservation of energy, transmittance is given by:
//     // kt = 1 - kr;
// } 

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_refract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:33:27 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/14 14:54:47 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "libft.h"
#include <math.h>

void	vec3_refract(t_inter *inter, t_vec3 *vf, float ior)
{
	float	toby[5];
	t_vec3	tmpi;
	t_vec3	tmpn;

	tmpi = inter->ray.n;
	tmpn = inter->n;
	*vf = inter->n;
	AAAA = ft_clampf(vec3_dot(&inter->ray.n, &inter->n), -1, 1);
	BBBB = 1;
	CCCC = ior;
	if (AAAA < 0)
		AAAA = -AAAA;
	else
	{
		ft_swapf(&BBBB, &CCCC);
		vf->x = -vf->x;
		vf->y = -vf->y;
		vf->z = -vf->z;
	}
	DDDD = BBBB / CCCC;
	EEEE = 1 - DDDD * DDDD * (1 - AAAA * AAAA);
	if (EEEE < 0)
		ft_bzero(vf, sizeof(vf));
	else
	{
		vec3_scalar(&tmpi, DDDD);
		vec3_scalar(&tmpn, DDDD * AAAA - sqrtf(EEEE));
		vec3_add(vf, &tmpi, &tmpn);
		vec3_normalize(vf);
	}
}

// Vec3f refract(const Vec3f &I, const Vec3f &N, const float &ior) 
// { 
//     float cosi = clamp(-1, 1, dotProduct(I, N)); 
//     float etai = 1, etat = ior; 
//     Vec3f n = N; 
//     if (cosi < 0)
// 	{
// 		cosi = -cosi;
// 	} else
// 	{
// 		std::swap(etai, etat);
// 		n= -N;
// 	} 
//     float eta = etai / etat; 
//     float k = 1 - eta * eta * (1 - cosi * cosi); 
//     return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n; 
// } 

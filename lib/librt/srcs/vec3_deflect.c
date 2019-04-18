/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_deflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:31:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/01 21:29:47 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

t_vec3
	vec3_deflect(t_vec3 vec, t_vec3 normal)
{
	t_vec3	reflected;
	float	dot;

	dot = vec3_dot(&normal, &vec);
	vec3_scalar(&normal, 2 * dot);
	vec3_sub(&reflected, &vec, &normal);
	vec3_normalize(&reflected);
	return (reflected);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_setlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:26:29 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/20 23:18:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmem.h"

void	inter_setlight(t_inter *inter, t_inter *light_inter, t_light *light)
{
	t_ray	ray;
	float	rene;
	t_vec3	toby;

	inter_find(inter, &ray.origin);
	rene = vec3_dot(&inter->ray.n, &inter->n);
	vec3_cpy(&toby, &inter->n);
	vec3_scalar(&toby, SHADOW_BIAS);
	(rene > 0) ? vec3_sub((t_vec3*)&ray.origin, (t_vec3*)&ray.origin, &toby)
		: vec3_add((t_vec3*)&ray.origin, (t_vec3*)&ray.origin, &toby);
	vec3_find(&ray.origin, &light->origin, &ray.n);
	light_inter->dist = vec3_mag(&ray.n);
	vec3_normalize(&ray.n);
	light_inter->obj = NULL;
	ft_memcpy(&light_inter->ray, &ray, sizeof(t_ray));
	ft_memcpy(&light_inter->n, &inter->n, sizeof(t_vec3));
	ft_memcpy(&light_inter->color, &light->color, sizeof(t_color));
}

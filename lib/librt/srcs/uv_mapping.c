/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:34:35 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/16 15:34:38 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include "rtstruct.h"
#include <math.h>

void	apply_uv_mapping(t_vec3 *uv, t_uv_mapping mapping)
{
	uv->x = uv->x * mapping.scale.x + mapping.offset.x;
	uv->y = uv->y * mapping.scale.y + mapping.offset.y;
	if (mapping.repeat)
	{
		uv->x = fmodf(uv->x, 1) + (uv->x < 0);
		uv->y = fmodf(uv->y, 1) + (uv->y < 0);
	}
	else
	{
		uv->x = ft_clampf(uv->x, 0, 1);
		uv->y = ft_clampf(uv->y, 0, 1);
	}
}

/*
** Remap a float from [-1, 1] to [0, 1]
*/

float	remap_to_0_to_1(float x)
{
	return (x * 0.5f + 0.5f);
}

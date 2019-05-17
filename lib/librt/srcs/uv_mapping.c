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

#include "rtstruct.h"

void	apply_uv_mapping(t_vec3 *uv, t_uv_mapping mapping)
{
	uv->x = uv->x * mapping.scale_x + mapping.offset_x;
	uv->y = uv->y * mapping.scale_y + mapping.offset_y;
}

/*
** Remap a float from [-1, 1] to [0, 1]
*/

float	remap_to_0_to_1(float x)
{
	return (x * 0.5f + 0.5f);
}

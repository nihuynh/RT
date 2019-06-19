/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:22:48 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/06/19 03:19:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftstring.h"
#include "rt.h"

/*
** Adapted from Quick'n'Dirty method from here
** https://blog.selfshadow.com/2011/10/17/perp-vectors/
*/

void
	create_orthobasis_qnd(t_vec3 vec, t_vec3 *t, t_vec3 *b)
{
	t_vec3 orthogonal;

	if (fabsf(vec.y) > 0.9999f)
		orthogonal = (t_vec3) {0, 0, 1};
	else
		orthogonal = (t_vec3) {0, -1, 0};
	*t = vec3_cross(vec, orthogonal);
	vec3_normalize(t);
	*b = vec3_cross(vec, *t);
	vec3_normalize(b);
}

t_vec3
	compute_shading_normal(t_material mat, t_vec3 uv, t_vec3 geo_n)
{
	t_vec3	tex_n;
	t_vec3	n;
	t_vec3	t;
	t_vec3	b;

	if (mat.normal_map == NULL || ft_strequ(mat.normal_map->name, "none"))
		return (geo_n);
	*((t_color*)&tex_n) = mat.normal_map->f_texture(&mat, mat.normal_map, uv);
	if (mat.normal_map->pixels == NULL)
	{
		vec3_add(&n, &geo_n, &tex_n);
		vec3_normalize(&n);
		return (n);
	}
	tex_n.x = tex_n.x * 2 - 1;
	tex_n.y = tex_n.y * 2 - 1;
	tex_n.z = tex_n.z * 2 - 1;
	vec3_normalize(&tex_n);
	create_orthobasis_qnd(geo_n, &t, &b);
	n.x = tex_n.x * t.x + tex_n.y * b.x + tex_n.z * geo_n.x;
	n.y = tex_n.x * t.y + tex_n.y * b.y + tex_n.z * geo_n.y;
	n.z = tex_n.x * t.z + tex_n.y * b.z + tex_n.z * geo_n.z;
	vec3_normalize(&n);
	return (n);
}

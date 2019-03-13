/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_matrix_apply.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:07:50 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/20 23:17:17 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "ftmem.h"

static inline void	apply_matrix(t_vec3 *v, t_matrix *mat)
{
	t_vec3	res;

	res.x = v->x * mat->m[0][0] + v->y * mat->m[0][1] + v->z * mat->m[0][2];
	res.y = v->x * mat->m[1][0] + v->y * mat->m[1][1] + v->z * mat->m[1][2];
	res.z = v->x * mat->m[2][0] + v->y * mat->m[2][1] + v->z * mat->m[2][2];
	ft_memcpy(v, &res, sizeof(t_vec3));
}

void				vec3_matrix_apply(t_vec3 *vec, t_matrix *mx, t_matrix *my)
{
	apply_matrix(vec, mx);
	apply_matrix(vec, my);
}

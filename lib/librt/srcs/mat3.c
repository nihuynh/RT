/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:52:18 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/03/15 19:52:21 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

t_matrix	matrix_mult(const t_matrix *lhs, const t_matrix *rhs)
{
	int			i;
	int			j;
	t_matrix	res;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			res.m[i][j] = lhs->m[i][0] * rhs->m[0][j]
						+ lhs->m[i][1] * rhs->m[1][j]
						+ lhs->m[i][2] * rhs->m[2][j];
		}
	}
	return (res);
}

t_vec3		get_column(t_matrix m, int column)
{
	return (t_vec3){
			m.m[0][column],
			m.m[1][column],
			m.m[2][column]};
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:05:31 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/19 20:56:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "ftio.h"

void				print_matrix(t_matrix *mat_x, t_matrix *mat_y)
{
	char *format;

	format = "Matrix :\nx : %f, %f ,%f\ny : %f, %f, %f\nz : %f, %f, %f\n";
	ft_printf(format,
			mat_x->m[0][0], mat_x->m[0][1], mat_x->m[0][2],
			mat_x->m[1][0], mat_x->m[1][1], mat_x->m[1][2],
			mat_x->m[2][0], mat_x->m[2][1], mat_x->m[2][2]);
	ft_printf(format,
			mat_y->m[0][0], mat_y->m[0][1], mat_y->m[0][2],
			mat_y->m[1][0], mat_y->m[1][1], mat_y->m[1][2],
			mat_y->m[2][0], mat_y->m[2][1], mat_y->m[2][2]);
}

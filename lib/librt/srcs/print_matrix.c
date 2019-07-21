/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:05:31 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/21 19:23:31 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "ftio.h"

void				print_matrix(t_matrix *mat)
{
	char *format;

	format = "%s%.2f, %.2f, %.2f\n\t\t%.2f, %.2f, %.2f\n\t\t%.2f, %.2f, %.2f\n";
	ft_printf(format, "Matrix:  x       y      z\n\t\t",
			mat->m[0][0], mat->m[0][1], mat->m[0][2],
			mat->m[1][0], mat->m[1][1], mat->m[1][2],
			mat->m[2][0], mat->m[2][1], mat->m[2][2]);
}

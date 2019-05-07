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
#include "stdio.h"

void				print_matrix(t_matrix *mat)
{
	char *format;

	format = "Matrix:  x       y      z\n\t\t% .2f, % .2f, % .2f\n\t\t% .2f, % .2f, % .2f\n\t\t% .2f, % .2f, % .2f\n";
	printf(format,
			mat->m[0][0], mat->m[0][1], mat->m[0][2],
			mat->m[1][0], mat->m[1][1], mat->m[1][2],
			mat->m[2][0], mat->m[2][1], mat->m[2][2]);
}

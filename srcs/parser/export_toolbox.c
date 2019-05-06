/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_toolbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 17:57:38 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/06 17:58:54 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include <stdio.h>

void
	export_material(int fd, t_material *mat)
{
	dprintf(fd, "\t\ttexture(none)");
	dprintf(fd, "\t\tcolor(%f %f %f)\n", mat->color.r, mat->color.g, mat->color.b);
}

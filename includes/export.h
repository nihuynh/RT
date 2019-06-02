/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:41:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/03 00:23:04 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

#include "t_data.h"

/*
** Functions Expose :
*/

int		export_scene(t_data *app, char *filename);

void	plane_export(int fd, void *shape);
void	sphere_export(int fd, void *shape);
void	cone_export(int fd, void *shape);
void	cylinder_export(int fd, void *shape);
void	csg_export(int fd, void *shape);
void	export_material(int fd, t_material *mat);

/*
** Functions Needed :
*/

char	*get_obj_str(int type);

#endif


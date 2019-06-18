/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:41:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/18 04:13:48 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "t_data.h"

/*
** Functions Expose :
*/

int		export_scene(t_data *app, char *filename);
void	export_animation(int fd, t_data *app);
void	plane_export(int fd, void *shape);
void	sphere_export(int fd, void *shape);
void	cone_export(int fd, void *shape);
void	cylinder_export(int fd, void *shape);
void	csg_export(int fd, void *shape);
void	export_material(int fd, t_material *mat);

/*
** Functions Needed :
*/

void	export_tvec3(int fd, char *name, t_vec3 vector);
void	export_color(int fd, char *name, t_color color);
char	*get_obj_str(int type);

#endif

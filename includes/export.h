/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 02:41:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/01 22:22:16 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include <SDL.h>

/*
** Functions Expose :
*/

void	plane_export(int fd, void *shape);
void	sphere_export(int fd, void *shape);
void	cone_export(int fd, void *shape);
void	cylinder_export(int fd, void *shape);
void	csg_export(int fd, void *shape);
void	cube_export(int fd, void *shape);
void	tore_export(int fd, void *shape);
void	export_material(int fd, t_material *mat);
void	set_win_title(SDL_Window *win, char *filename);

/*
** Functions Needed :
*/

void	export_tvec3(int fd, char *name, t_vec3 vector);
void	export_color(int fd, char *name, t_color color);
char	*get_obj_str(int type);

#endif

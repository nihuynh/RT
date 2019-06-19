/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_scene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 00:10:23 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/19 01:47:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SCENE_H
# define T_SCENE_H

# include "ftlist.h"

typedef struct	s_scene
{
	t_list		*lst_obj;
	t_list		*lst_light;
	t_list		*lst_anim;
	t_list		*lst_anim_light;
	int			nb_objs[5];
	int			nb_light;
}				t_scene;

typedef struct	s_scene_name
{
	char		*name;
	char		*dir;
}				t_scene_name;

#endif

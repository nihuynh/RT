/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:19:59 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/12 01:46:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATE_H
# define ANIMATE_H

# include "rtstruct.h"

typedef struct s_anim	t_anim;

struct s_anim
{
	int		type;
	t_obj	*obj;
	t_pt3	*pos;
	t_pt3	origin;
	void	*res;
	void	(*anim_obj)(t_anim*);
	void	(*ui_anim)(t_anim*, int);
	t_anim	*next;
};

typedef struct s_rotate
{
	t_vec3	dir;
	float	speed;
}			t_rotate;

typedef struct s_translate
{
	t_vec3	dir;
	float	speed;
}			t_translate;

typedef struct s_orbit
{
	t_obj	*obj_center;
	t_pt3	center;
	t_vec3	axis;
	float	deg;
}			t_orbit;

void	anim_translate(t_anim *anim);
void	anim_orbit(t_anim *anim);
void	anim_set(t_anim *anim, int type);
t_pt3	*get_pos(t_obj *obj);
void	ui_orbit(t_anim *anim, int n);
void	ui_translate(t_anim *anim, int n);
void	anim_free(t_anim *anim);

#endif

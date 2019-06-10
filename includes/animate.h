/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:19:59 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/10 22:01:52 by sklepper         ###   ########.fr       */
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
	void	*res;
	void	(*anim_obj)(t_anim*);
	void	(*ui_anim)(t_anim*);
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
	t_obj	*center;
	float	deg;
}			t_orbit;

void	anim_translate(t_anim *anim);
void	anim_set(t_anim *anim, int type);
t_pt3	*get_pos(t_obj *obj);
void	ui_translate(t_anim *anim);
void	anim_reset(t_anim *anim);

#endif

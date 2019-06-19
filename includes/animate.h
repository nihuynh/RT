/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:19:59 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 01:30:44 by sklepper         ###   ########.fr       */
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
	t_light	*light;
	t_pt3	*pos;
	t_vec3	*x;
	t_vec3	*n;
	t_vec3	*z;
	t_pt3	origin;
	t_vec3	x_save;
	t_vec3	n_save;
	t_vec3	z_save;
	void	*res;
	void	(*anim_obj)(t_anim*);
	void	(*ui_anim)(t_anim*, int);
	void	(*export)(int, t_anim*);
	void	(*parse)(void*, void*);
	t_anim	*next;
};

typedef struct s_rotate
{
	t_vec3	axis;
	float	deg;
}			t_rotate;

typedef struct s_translate
{
	t_vec3	dir;
	float	speed;
}			t_translate;

typedef struct s_orbit
{
	t_obj	*obj_center;
	t_vec3	axis;
	float	deg;
}			t_orbit;

void	anim_translate(t_anim *anim);
void	anim_orbit(t_anim *anim);
void	anim_rotate(t_anim *anim);
void	anim_set(t_anim *anim, int type);
void	ui_orbit(t_anim *anim, int n);
void	ui_translate(t_anim *anim, int n);
void	ui_rotate(t_anim *anim, int n);
void	anim_free(t_anim *anim);
void	export_rotate(int fd, t_anim *anim);
void	export_orbit(int fd, t_anim *anim);
void	export_translate(int fd, t_anim *anim);
void	parse_rotate(void *parse, void *res);
void	parse_translate(void *parse, void *res);
void	parse_orbit(void *parse, void *res);
void	anim_list(t_anim *anim, char *str);
void	anim_add_camera(t_cam *cam);

#endif

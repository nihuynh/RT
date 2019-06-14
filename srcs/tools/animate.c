/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:05:07 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/14 06:12:44 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "rt.h"
#include "animate.h"
#include "librt.h"
#include "config.h"
#include "librt.h"
#include <SDL.h>

void	animate_branch(void *res)
{
	t_anim	*anim;

	anim = res;
	if (anim->anim_obj)
		anim->anim_obj(anim);
	if (anim->next)
		animate_branch(anim->next);
}

void	animate(t_data *app)
{
	t_list	*lst;

	lst = app->scene.lst_anim;
	while (lst)
	{
		animate_branch(lst->content);
		lst = lst->next;
	}
	app->gui.animated_frames += 1;
	app->sdl->sub_sample = 1;
	app->sdl->partial_render = false;
	app->sdl->needs_render = true;
	SDL_Delay(50);
}

void	anim_translate(t_anim *anim)
{
	t_translate	*translate;
	t_vec3		result;

	translate = anim->res;
	result = translate->dir;
	vec3_scalar(&result, translate->speed);
	vec3_add(anim->obj->pos, anim->obj->pos, &result);
}

void	anim_orbit(t_anim *anim)
{
	t_orbit		*orbit;
	t_vec3		vec;
	t_matrix	mat;
	t_pt3		*center;

	orbit = anim->res;
	center = orbit->obj_center->pos;
	vec3_sub(&vec, anim->obj->pos, center);
	mat = mat_orbit(orbit->axis, orbit->deg);
	apply_matrix(&vec, &mat);
	vec3_add(anim->obj->pos, center, &vec);
}

void	anim_rotate(t_anim *anim)
{
	t_rotate	*rotate;
	t_matrix	mat;

	rotate = anim->res;
	mat = mat_orbit(rotate->axis, rotate->deg);
	if (anim->obj->n)
	{
		apply_matrix(anim->obj->n, &mat);
		vec3_normalize(anim->obj->n);
	}
	if (anim->obj->x)
	{
		apply_matrix(anim->obj->x, &mat);
		vec3_normalize(anim->obj->x);
	}
	if (anim->obj->z)
	{
		apply_matrix(anim->obj->z, &mat);
		vec3_normalize(anim->obj->z);
	}
}

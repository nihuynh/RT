/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:05:07 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/25 21:36:32 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "rt.h"
#include "animate.h"
#include "librt.h"
#include "config.h"
#include "libft.h"
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
	if (app->gui.record)
		record_frame(app);
	if (app->gui.frame_limit)
	{
		if (app->gui.animated_frames == 0)
			app->gui.frames_render_time = ft_curr_usec();
		if (app->gui.animated_frames >= app->gui.frame_limit)
		{
			app->gui.animate = false;
			app->gui.frames_render_time = (ft_curr_usec()
				- app->gui.frames_render_time) / 1000;
			return ;
		}
	}
	while (lst)
	{
		animate_branch(lst->content);
		lst = lst->next;
	}
	lst = app->scene.lst_anim_light;
	while (lst)
	{
		animate_branch(lst->content);
		lst = lst->next;
	}
	if (app->cam.anim)
		animate_branch(app->cam.anim);
	app->gui.animated_frames += 1;
	app->sdl->sub_sample = 1;
	app->sdl->partial_render = false;
	app->sdl->needs_render = true;
}

void	anim_translate(t_anim *anim)
{
	t_translate	*translate;
	t_vec3		result;

	translate = anim->res;
	result = translate->dir;
	vec3_scalar(&result, translate->speed);
	vec3_add(anim->pos, anim->pos, &result);
}

void	anim_orbit(t_anim *anim)
{
	t_orbit		*orbit;
	t_vec3		vec;
	t_matrix	mat;
	t_pt3		*center;

	orbit = anim->res;
	center = orbit->obj_center->pos;
	vec3_sub(&vec, anim->pos, center);
	mat = mat_orbit(orbit->axis, orbit->deg);
	apply_matrix(&vec, &mat);
	vec3_add(anim->pos, center, &vec);
}

void	anim_rotate(t_anim *anim)
{
	t_rotate	*rotate;
	t_matrix	mat;

	rotate = anim->res;
	mat = mat_orbit(rotate->axis, rotate->deg);
	if (anim->n)
	{
		apply_matrix(anim->n, &mat);
		vec3_normalize(anim->n);
	}
	if (anim->x)
	{
		apply_matrix(anim->x, &mat);
		vec3_normalize(anim->x);
	}
	if (anim->z)
	{
		apply_matrix(anim->z, &mat);
		vec3_normalize(anim->z);
	}
}

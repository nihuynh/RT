/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_anim_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:56:43 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/18 17:23:37 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "librt.h"
#include "ftstring.h"
#include "ftio.h"
#include "t_data.h"

void
	ui_translate(t_anim *anim, int n)
{
	t_translate	*trans;
	t_translate	tmp;
	char		*str;

	trans = anim->res;
	tmp = *trans;
	if (!(str = ft_strjoini("Normal (X Y Z) ", n)))
		ft_error(__func__, __LINE__);
	if (igSliderFloat3(str, &tmp.dir.x, -1, 1, "%g", 1))
		trans->dir = tmp.dir;
	free(str);
	igSameLine(0, 0);
	if (!(str = ft_strjoini("Normalize ", n)))
		ft_error(__func__, __LINE__);
	if (igButton(str, (ImVec2){0, 0}))
		vec3_normalize(&trans->dir);
	free(str);
	if (!(str = ft_strjoini("Speed ", n)))
		ft_error(__func__, __LINE__);
	if (igDragFloat(str, &tmp.speed, 1, 0, 1000, "%g", 1))
		trans->speed = tmp.speed;
	free(str);
}

static inline void
	ui_orbit_obj_list(t_data *app, t_orbit *orbit, char *str)
{
	t_list		*current;
	t_obj		*selected;
	t_obj		*tmp;
	bool		is_selected;

	current = app->scene.lst_obj;
	selected = orbit->obj_center;
	tmp = current->content;
	if (igBeginCombo(str, selected->name, 0))
	{
		while (current)
		{
			is_selected = (ft_strcmp(selected->name, tmp->name) == 0);
			if (igSelectable(tmp->name, is_selected, 0, (ImVec2){0, 0}))
				orbit->obj_center = tmp;
			if (is_selected)
				igSetItemDefaultFocus();
			current = current->next;
			if (current)
				tmp = current->content;
		}
		igEndCombo();
	}
}

static inline void
	ui_orbit_obj(t_orbit *orbit, int n)
{
	char	*str;
	t_data	*app;

	app = NULL;
	app = get_app(app);
	if (!app->scene.lst_obj)
		return ;
	if (orbit->obj_center == NULL)
		orbit->obj_center = app->scene.lst_obj->content;
	if (!(str = ft_strjoini("Center Object ", n)))
		ft_error(__func__, __LINE__);
	ui_orbit_obj_list(app, orbit, str);
	free(str);
}

static inline void
	ui_orbit_pos(t_orbit *orbit, int n)
{
	char	*str;
	t_data	*app;
	t_pt3	tmp;

	app = NULL;
	app = get_app(app);
	tmp = orbit->center;
	if (!(str = ft_strjoini("Center (X Y Z) ", n)))
		ft_error(__func__, __LINE__);
	if (igInputFloat3(str, &tmp.x, "%g", 0))
		orbit->center = tmp;
	free(str);
}

void
	ui_orbit(t_anim *anim, int n)
{
	t_orbit	*orbit;
	t_orbit	tmp;
	char	*str;

	orbit = anim->res;
	tmp = *orbit;
	if (anim->type == 2)
		ui_orbit_obj(orbit, n);
	else if (anim->type == 3)
		ui_orbit_pos(orbit, n);
	if (!(str = ft_strjoini("Axis (X Y Z) ", n)))
		ft_error(__func__, __LINE__);
	if (igSliderFloat3(str, &tmp.axis.x, -1, 1, "%g", 1))
		orbit->axis = tmp.axis;
	free(str);
	igSameLine(0, 0);
	if (!(str = ft_strjoini("Normalize ", n)))
		ft_error(__func__, __LINE__);
	if (igButton(str, (ImVec2){0, 0}))
		vec3_normalize(&orbit->axis);
	free(str);
	if (!(str = ft_strjoini("Speed ", n)))
		ft_error(__func__, __LINE__);
	if (igDragFloat(str, &tmp.deg, 1, -360, 360, "%g", 1))
		orbit->deg = tmp.deg;
	free(str);
}

void
	ui_rotate(t_anim *anim, int n)
{
	t_rotate	*rotate;
	t_rotate	tmp;
	char		*str;

	rotate = anim->res;
	tmp = *rotate;
	if (!(str = ft_strjoini("Axis (X Y Z) ", n)))
		ft_error(__func__, __LINE__);
	if (igSliderFloat3(str, &tmp.axis.x, -1, 1, "%g", 1))
		rotate->axis = tmp.axis;
	free(str);
	igSameLine(0, 0);
	if (!(str = ft_strjoini("Normalize ", n)))
		ft_error(__func__, __LINE__);
	if (igButton(str, (ImVec2){0, 0}))
		vec3_normalize(&rotate->axis);
	free(str);
	if (!(str = ft_strjoini("Speed ", n)))
		ft_error(__func__, __LINE__);
	if (igDragFloat(str, &tmp.deg, 1, -360, 360, "%g", 1))
		rotate->deg = tmp.deg;
	free(str);
}

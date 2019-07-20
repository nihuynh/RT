/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_anim_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:56:43 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/20 21:05:13 by sklepper         ###   ########.fr       */
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

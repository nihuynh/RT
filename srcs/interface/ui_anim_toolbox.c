/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_anim_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:56:43 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/10 17:41:57 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "librt.h"

void	ui_translate(t_anim *anim)
{
	t_translate	*trans;
	t_translate	tmp;

	trans = anim->res;
	tmp = *trans;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.dir.x, -1, 1, "%g", 1))
		trans->dir = tmp.dir;
	igSameLine(0, 0);
	if (igButton("Normalize", (ImVec2){0, 0}))
		vec3_normalize(&trans->dir);
	if (igDragFloat("Speed", &tmp.speed, 1, 0, 1000, "%g", 1))
		trans->speed = tmp.speed;
}

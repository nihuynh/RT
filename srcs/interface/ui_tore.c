/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_tore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 21:11:12 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/20 21:15:52 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "interface.h"
#include "config.h"
#include "librt.h"

void
	ui_tore(void *app_v, void *res)
{
	t_tore	*tore;
	t_tore	tmp;

	(void)app_v;
	tore = res;
	tmp = *tore;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		tore->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		tore->n = tmp.n;
	if (igSliderFloat3("X (X Y Z)", &tmp.x.x, -1, 1, "%g", 1))
		tore->x = tmp.x;
	if (igSliderFloat3("Z (X Y Z)", &tmp.z.x, -1, 1, "%g", 1))
		tore->z = tmp.z;
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&tore->n);
		vec3_normalize(&tore->x);
		vec3_normalize(&tore->z);
	}
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		tore->size = tmp.size;
	if (igInputFloat("Radius", &tmp.radius, 0, 0, "%g", 0))
		tore->radius = tmp.radius;
}

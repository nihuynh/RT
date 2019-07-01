/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cluster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 04:01:19 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/01 20:16:32 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cluster.h"
#include "interface.h"
#include "librt.h"

void	ui_cluster_tore(t_cluster *cluster)
{
	t_cluster	tmp;

	tmp = *cluster;
	if (igInputFloat3("Position (X Y Z)", &tmp.pos.x, "%g", 0))
		cluster->pos = tmp.pos;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		cluster->n = tmp.n;
	igSameLine(0, 10);
	if (igButton("Normalize", (ImVec2){0, 0}))
		vec3_normalize(&cluster->n);
	if (igDragFloat("Radius Tore", &tmp.radius_tore, 1, 0, 10000, "%g", 1))
		cluster->radius_tore = tmp.radius_tore;
	if (igDragFloat("Radius Spheres", &tmp.radius_spheres, 1, 0, 10000, "%g", 1))
		cluster->radius_spheres = tmp.radius_spheres;
	if (igDragInt("Object Number", &tmp.nb_obj, 1, 0, 80, "%d"))
		cluster->nb_obj = tmp.nb_obj;
}

void	ui_cluster(t_cluster *cluster)
{
	if (cluster->type == 0)
		ui_cluster_tore(cluster);
}

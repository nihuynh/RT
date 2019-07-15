/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cluster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 03:46:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/15 19:27:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "t_cluster.h"
#include "librt.h"
#include "interface.h"
#include "parse.h"

void	new_cluster_tore(t_data *app, t_cluster cluster)
{
	t_matrix	mat;
	t_vec3		x;
	t_vec3		z;
	t_sphere	*sphere;

	mat = mat_orbit(cluster.n, (float)(360.0f / (float)cluster.nb_obj));
	create_orthobasis_from_y_axis(cluster.n, &x, &z);
	vec3_scalar(&x, cluster.size_cluster);
	while (cluster.nb_obj > 0)
	{
		new_obj(app, get_obj_type("sphere"));
		sphere = app->gui.obj_set->shape;
		sphere->radius = cluster.radius_spheres;
		vec3_add(&sphere->origin, &cluster.pos, &x);
		apply_matrix(&x, &mat);
		cluster.nb_obj--;
	}
}

void	new_cluster_rand_cube(t_data *app, t_cluster cluster)
{
	(void)app;
	(void)cluster;
}

void	new_cluster(t_data *app, int type)
{
	if (type == 0)
		new_cluster_tore(app, app->gui.cluster);
	if (type == 1)
		new_cluster_rand_cube(app, app->gui.cluster);
}

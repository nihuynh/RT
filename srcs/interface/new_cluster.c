/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cluster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 03:46:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/20 19:08:00 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "t_cluster.h"
#include "librt.h"
#include "interface.h"
#include "parse.h"
#include <stdlib.h>
#include <time.h>

static inline void
	new_cluster_tore(t_data *app, t_cluster cluster)
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

static inline float
	rand_float(float max, float offset, int scale)
{
	return (((float)(rand() % scale) / (float)scale) * max + offset);
}

static inline void
	new_cluster_rand_cube(t_data *app, t_cluster clstr)
{
	t_sphere	*sphere;

	srand(time(NULL));
	while (clstr.nb_obj > 0)
	{
		new_obj(app, get_obj_type("sphere"));
		sphere = app->gui.obj_set->shape;
		sphere->radius = rand_float(clstr.radius_spheres, 1, 10000);
		sphere->origin.x = rand_float(clstr.size_cluster, clstr.pos.x, 10000);
		sphere->origin.y = rand_float(clstr.size_cluster, clstr.pos.y, 10000);
		sphere->origin.z = rand_float(clstr.size_cluster, clstr.pos.z, 10000);
		clstr.nb_obj--;
	}
}

void
	new_cluster(t_data *app, int type)
{
	if (type == 0)
		new_cluster_tore(app, app->gui.cluster);
	else if (type == 1)
		new_cluster_rand_cube(app, app->gui.cluster);
}

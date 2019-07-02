/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cluster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 03:50:44 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/02 22:41:02 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CLUSTER_H
# define T_CLUSTER_H

# include "rtstruct.h"

typedef struct	s_cluster
{
	int			type;
	int			nb_obj;
	float		radius_tore;
	float		radius_spheres;
	t_pt3		pos;
	t_vec3		n;
}				t_cluster;

#endif

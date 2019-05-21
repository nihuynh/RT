/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:22:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/21 03:16:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftbtree.h"
#include "rtstruct.h"

void			inter_csg(t_inter *data, t_obj *node)
{
	// Do stuff
	(void)data;
	(void)node;
}

/*
** Useless for csg because it's not the primitives :
*/

void			normal_csg(t_inter *inter)
{
	// Do stuff
	(void)inter;
}

t_vec3			get_csg_uv(t_inter *inter)
{
	t_vec3 tmp;

	tmp = inter->obj->get_uv(inter);
	return (tmp);
}

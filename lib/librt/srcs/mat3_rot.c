/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 04:51:01 by nihuynh           #+#    #+#             */
/*   Updated: 2019/02/27 17:15:04 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmath.h"
#include "ftmem.h"

static inline void	mat_special(t_matrix *mat, t_vec3 *vf)
{
	mat->m[0][0] = 1;
	mat->m[0][1] = 0;
	mat->m[0][2] = 0;
	mat->m[1][0] = 0;
	mat->m[1][1] = 0;
	mat->m[2][0] = 0;
	mat->m[2][2] = 0;
	if (vf->y > 0)
	{
		mat->m[1][2] = -1;
		mat->m[2][1] = 1;
	}
	else
	{
		mat->m[1][2] = 1;
		mat->m[2][1] = -1;
	}
}

static inline void	mat_unitaire(t_matrix *mat)
{
	mat->m[0][0] = 1;
	mat->m[0][1] = 0;
	mat->m[0][2] = 0;
	mat->m[1][0] = 0;
	mat->m[1][1] = 1;
	mat->m[1][2] = 0;
	mat->m[2][0] = 0;
	mat->m[2][1] = 0;
	mat->m[2][2] = 1;
}

static inline void	rot_x(t_matrix *mat, t_vec3 *vi, t_vec3 *vf)
{
	t_vec3	axis;
	float	datcos;
	float	datsin;
	t_vec3	tmp;

	ft_memcpy(&tmp, vf, sizeof(t_vec3));
	ft_bzero(mat, sizeof(t_matrix));
	vec3_normalize(&tmp);
	tmp.z = (tmp.z > 0) ? -tmp.z : tmp.z;
	tmp.x = (tmp.x > 0) ? -tmp.x : tmp.x;
	tmp.z = (tmp.z < tmp.x) ? tmp.z : tmp.x;
	tmp.z = (tmp.z == 0) ? -1 : tmp.z;
	tmp.x = 0;
	vec3_normalize(&tmp);
	datcos = vec3_dot(vi, &tmp);
	vec3_cross(vi, &tmp, &axis);
	datsin = vec3_mag(&axis);
	if (vf->y < 0)
		datsin = -datsin;
	mat->m[0][0] = 1;
	mat->m[1][1] = datcos;
	mat->m[1][2] = -datsin;
	mat->m[2][1] = datsin;
	mat->m[2][2] = datcos;
}

static inline void	rot_y(t_matrix *mat, t_vec3 *vi, t_vec3 *vf)
{
	t_vec3		axis;
	float		datcos;
	float		datsin;
	t_vec3		tmp;

	ft_memcpy(&tmp, vf, sizeof(t_vec3));
	tmp.y = 0;
	vec3_normalize(&tmp);
	datcos = vec3_dot(vi, &tmp);
	vec3_cross(vi, &tmp, &axis);
	datsin = vec3_mag(&axis);
	mat->m[0][0] = axis.x * axis.x * (1 - datcos) + datcos;
	mat->m[0][1] = axis.x * axis.y * (1 - datcos) - axis.z * datsin;
	mat->m[0][2] = axis.x * axis.z * (1 - datcos) + axis.y * datsin;
	mat->m[1][0] = 0;
	mat->m[1][1] = 1;
	mat->m[1][2] = 0;
	mat->m[2][0] = axis.z * axis.x * (1 - datcos) - axis.y * datsin;
	mat->m[2][1] = axis.z * axis.y * (1 - datcos) + axis.x * datsin;
	mat->m[2][2] = axis.z * axis.z * (1 - datcos) + datcos;
}

void				mat3_rot(t_matrix *mat_x, t_matrix *mat_y,
										t_vec3 *vi, t_cam *cam)
{
	if (cam->dir.x == 0 && cam->dir.z == 0 && cam->dir.y != 0)
	{
		mat_special(mat_x, &cam->dir);
		mat_unitaire(mat_y);
	}
	else
	{
		rot_x(mat_x, vi, &cam->dir);
		rot_y(mat_y, vi, &cam->dir);
	}
}

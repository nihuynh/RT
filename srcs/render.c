/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/12 17:39:53 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include "librt.h"
#include "libft.h"

static inline void
	cam_ray(t_data *data, t_ray *res, float x, float y)
{
	double	fovt;
	double	r;
	t_pt3	p;
	t_vec3	n;

	r = WIDTH / (double)HEIGHT;
	fovt = tan(FOV * M_PI / 360);
	p.x = (float)((2 * x / WIDTH - 1) * fovt * r) + data->cam.pos.x;
	p.y = (float)((1 - 2 * y / HEIGHT) * fovt) + data->cam.pos.y;
	p.z = data->cam.pos.z - 1;
	vec3_find(&data->cam.pos, &p, &n);
	vec3_normalize(&n);
	vec3_matrix_apply(&n, &data->matrix_camera[0], &data->matrix_camera[1]);
	vec3_normalize(&n);
	ray_new(res, &data->cam.pos, &n);
}

void
	init_render(t_data *data)
{
	int		len;
	t_vec3	vi;

	len = HEIGHT * WIDTH;
	vec3_new(&vi, 0, 0, -1);
	if (!(data->core = ft_memalloc(len * sizeof(t_inter))))
		exit_safe(data);
	mat3_rot(&data->matrix_camera[0], &data->matrix_camera[1], &vi, &data->cam);
	if (DEBUG)
		print_matrix(&data->matrix_camera[0], &data->matrix_camera[1]);
	data->sdl.key_map = &key_mapping;
	data->sdl.mouse_map = &mouse_mapping;
}

void
	cast_primary(t_data *data, t_inter *inter)
{
	t_list	*lst;
	t_obj	*obj;

	lst = data->lst_obj;
	while (lst != NULL)
	{
		obj = lst->content;
		if (obj != NULL && obj->f_inter != NULL)
			obj->f_inter(inter, obj);
		lst = lst->next;
	}
}

void
	cast_light_primary(t_data *data, t_inter *inter)
{
	t_list	*lst;
	t_obj	*obj;

	lst = data->lst_obj;
	while (lst != NULL)
	{
		obj = lst->content;
		if (obj != NULL && obj->f_inter != NULL)
			obj->f_inter(inter, obj);
		if (inter->obj != NULL)
			return ;
		lst = lst->next;
	}
}

int	recursive_cast(t_data *data, t_ray *rene, int depth);

static inline void
	deflect_cast(t_data *data, t_inter *inter, int depth)
{
	t_color	primary;
	t_ray	absorbed;

	if (!(NO_DEFLECT) && inter->obj->material.deflect_idx > 0)
	{
		itocolor(&primary, recursive_cast(data, &inter->deflected, depth + 1));
		color_scalar(&primary, inter->obj->material.deflect_idx);
		color_add(&inter->color, &primary);
	}
	if (!(NO_ABSORB) && inter->obj->material.absorb_idx > 0)
	{
		inter_setrefract(inter, &absorbed);
		itocolor(&primary, recursive_cast(data, &absorbed, depth + 1));
		color_scalar(&primary, inter->obj->material.absorb_idx);
		color_add(&inter->color, &primary);
	}
}

int
	recursive_cast(t_data *data, t_ray *rene, int depth)
{
	t_inter	inter;
	t_color	primary;

	inter_set(&inter, rene);
	cast_primary(data, &inter);
	if (inter.obj == NULL)
		return (BACK_COLOR);
	color_cpy(&primary, &inter.color);
	color_scalar(&primary, AMB_LIGHT);
	if (data->lst_light == NULL || NO_LIGHT)
		return (colortoi(&inter.color));
	inter.find_normal(&inter);
	cast_shadow(data, &inter);
	color_scalar(&inter.color, 1.0f - AMB_LIGHT);
	color_add(&inter.color, &primary);
	if (depth < DEPTH_MAX)
		deflect_cast(data, &inter, depth);
	return (colortoi(&inter.color));
}

int __attribute__((hot))
	process_pixel(int x, int y, void *arg)
{
	t_data	*data;
	t_ray	rene;

	data = arg;
	cam_ray(data, &rene, x + 0.5, y + 0.5);
	return(recursive_cast(data, &rene, 0));
}

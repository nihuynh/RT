/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/20 03:13:39 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include "librt.h"
#include "libft.h"

SIVOID	cam_ray(t_data *data, t_ray *res, int x, int y)
{
	double	fovt;
	double	r;
	t_pt3	p;
	t_vec3	n;

	r = WIDTH / (double)HEIGHT;
	fovt = tan(FOV * M_PI / 360);
	p.x = (float)(((2 * ((x + 0.5) / WIDTH) - 1) * fovt * r)) + data->cam.pos.x;
	p.y = (float)(((1 - 2 * ((y + 0.5) / HEIGHT) * fovt))) + data->cam.pos.y;
	p.z = data->cam.pos.z - 1;
	vec3_find(&data->cam.pos, &p, &n);
	vec3_normalize(&n);
	vec3_matrix_apply(&n, &data->matrix_camera[0], &data->matrix_camera[1]);
	vec3_normalize(&n);
	ray_new(res, &data->cam.pos, &n);
}

void	init_render(t_data *data)
{
	int		len;
	t_vec3	vi;

	len = HEIGHT * WIDTH;
	vec3_new(&vi, 0, 0, -1);
	if (!(data->core = ft_memalloc(len * sizeof(t_inter))))
		ft_error(__func__, __LINE__);
	mat3_rot(&data->matrix_camera[0], &data->matrix_camera[1], &vi, &data->cam);
	if (DEBUG)
		print_matrix(&data->matrix_camera[0], &data->matrix_camera[1]);
}

void	cast_primary(t_data *data, t_inter *inter)
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

int		process_pixel(int x, int y, void *arg)
{
	t_data	*data;
	t_inter	*inter;
	t_ray	rene;
	t_color	primary;

	data = arg;
	inter = &data->core[y * WIDTH + x];
	cam_ray(data, &rene, x, y);
	inter_set(inter, &rene);
	cast_primary(data, inter);
	if (inter->obj == NULL)
		return (BACK_COLOR);
	color_cpy(&primary, &inter->color);
	color_scalar(&primary, AMB_LIGHT);
	if (data->lst_light == NULL || NO_LIGHT)
		return (colortoi(&inter->color));
	inter->find_normal(inter);
	cast_shadow(data, inter);
	color_scalar(&inter->color, 1.0f - AMB_LIGHT);
	color_add(&inter->color, &primary);
	return (colortoi(&inter->color));
}

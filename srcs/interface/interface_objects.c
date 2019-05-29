/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:32:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/29 19:16:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"

void
	ui_light(t_light *light)
{
	t_pt3			origin_tmp;
	t_color			color_tmp;

	origin_tmp = light->origin;
	if (igInputFloat3("Position (X Y Z)", &origin_tmp.x, "%g", 0))
		light->origin = origin_tmp;
	igInputFloat("Intensity", &light->intensity, 0, 0, "%g", 0);
	color_tmp = light->color;
	if (igColorEdit3("Color", &color_tmp.r, 0))
		light->color = color_tmp;
}

static inline void
	uv_mapping_details(t_uv_mapping *uv_mapping)
{
	t_vec2	uv;

	uv = uv_mapping->scale;
	if (igSliderFloat2("UV scale", &uv.x, 0, 10, "%.2g", 10))
		uv_mapping->scale = uv;
	uv = uv_mapping->offset;
	if (igSliderFloat2("UV offset", &uv.x, -1, 1, "%.2g", 1))
		uv_mapping->offset = uv;
	if (igRadioButtonBool("Repeat", uv_mapping->repeat == true))
		uv_mapping->repeat = true;
	if (igRadioButtonBool("Clamp", uv_mapping->repeat == false))
		uv_mapping->repeat = false;
}

static inline void
	material_details(t_material *mat)
{
	t_color	color_tmp;

	color_tmp = mat->color_diffuse;
	if (igColorEdit3("Object Color", &color_tmp.r, 0))
		mat->color_diffuse = color_tmp;
	color_tmp = mat->color_tex;
	if (igColorEdit3("Color of the pattern", &color_tmp.r, 0))
		mat->color_tex = color_tmp;
	color_tmp = mat->color_specular;
	if (igColorEdit3("Specular Color", &color_tmp.r, 0))
		mat->color_specular = color_tmp;
	igDragFloat("Specular Index", &mat->spec_idx, 0.01, 0, 1, "%g", 1);
	igDragFloat("Specular Power", &mat->spec_power, 0.1, 0, 1000, "%g", 1);
	color_tmp = mat->reflection_color;
	if (igColorEdit3("Reflection Color", &color_tmp.r, 0))
		mat->reflection_color = color_tmp;
	igDragFloat("Refraction Index", &mat->refraction_idx, 0.01, 0, 2, "%g", 1);
	color_tmp = mat->refraction_color;
	if (igColorEdit3("Refraction Color", &color_tmp.r, 0))
		mat->refraction_color = color_tmp;
	uv_mapping_details(&mat->uv_mapping);
}

static inline void
	material(t_data *app, t_obj *obj)
{
	material_list(app->lst_mat, obj);
	texture_list(app->lst_tex, obj);
	igText("Material Details");
	material_details(&obj->material);
}

void
	object(t_data *app, t_obj *obj)
{
	obj->f_gui(app, obj->shape);
	material(app, obj);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_objects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:32:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/14 20:51:39 by sklepper         ###   ########.fr       */
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
	edit_color_mat(&mat->color_diffuse, "Object Color", mat);
	edit_color_mat(&mat->color_tex, "Color of the pattern", mat);
	if (igDragFloat("Specular Index", &mat->spec_idx, 0.01, 0, 1, "%g", 1))
		mat->name = "custom";
	if (igDragFloat("Specular Power", &mat->spec_power, 0.1, 0, 1000, "%g", 1))
		mat->name = "custom";
	edit_color_mat(&mat->reflection_color, "Reflection Color", mat);
	edit_color_mat(&mat->color_specular, "Specular Color", mat);
	if (igDragFloat("Refraction Index", &mat->refraction_idx, 0.01, 0, 2, "%g", 1))
		mat->name = "custom";
	edit_color_mat(&mat->refraction_color, "Refraction Color", mat);
}

static inline void
	material(t_data *app, t_obj *obj)
{
	material_list(app->lst_mat, obj);
	if (load_selected_tex("Texture", obj->material.tex->name, app->lst_tex, &obj->material.tex))
		obj->material.name = "custom";
	if (load_selected_tex("Normal Map", obj->material.normal_map->name, app->lst_tex, &obj->material.normal_map))
		obj->material.name = "custom";
	if (load_selected_tex("Specular Map", obj->material.spec_map->name, app->lst_tex, &obj->material.spec_map))
		obj->material.name = "custom";
	igText("Material Details");
	material_details(&obj->material);
	uv_mapping_details(&obj->material.uv_mapping);
}

void
	ui_object(t_data *app, t_obj *obj)
{
	char buff[20];

	if (obj->animated == false)
		if (igButton("Add To Animation List", (ImVec2){0, 0}))
			anim_add(app, obj);
	ft_strlcpy(buff, obj->name, sizeof(buff));
	if (igInputText("Name", buff, sizeof(buff),
		ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
	{
		if (ft_strlen(buff) > 0)
		{
			free(obj->name);
			if (!(obj->name = ft_strdup(buff)))
				ft_error(__func__, __LINE__);
		}
	}
	obj->f_gui(app, obj->shape);
	material(app, obj);
}

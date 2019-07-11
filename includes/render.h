/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:50:27 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/11 12:45:57 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "rtstruct.h"
# include "color.h"
# include "t_data.h"

/*
** Render :
*/

# define DIFFUSE	0
# define SPECULAR	1

# define REFLECT	0
# define REFRACT	1

t_shading		get_shading_data(t_inter *inter);
void			render_gui(void *arg);
void			light_intensity(t_inter *inter, t_color *color, t_ray *ray);
void			cast_shadow(t_data *app, t_inter *inter);
t_color			get_lighting(t_shading s, t_scene scene, t_settings *setng);
void			cast_primary(t_list *obj_list, t_inter *inter);
t_color			recursive_cast(t_scene scene, t_settings s, t_ray r, int depth);
void			set_direction(t_cam *cam, t_vec3 direction);
void			cam_ray(t_data *app, t_ray *res, float x, float y);
t_color			cast_light_primary(t_list *obj_list, t_inter *inter,
	float dist_light);
t_vec3			compute_shading_normal(t_material mat, t_vec3 uv, t_vec3 geo_n);
t_color			get_sky_color(t_scene scene, t_settings settings, t_ray ray);
float			get_distance_attenuation(float distance);
void			add_specular_light(t_color *specular, t_shading shading,
	bool no_specular);
void			add_diffuse_light(t_color *diffuse, t_shading shading,
	bool no_diffuse);

void			update_camera(t_cam *cam, bool *needs_render);

/*
** Textures :
*/

typedef struct	s_tex_proced
{
	char		*name;
	t_color		(*f_texture)(t_material *, t_texture *, t_vec3);
}				t_tex_proced;

t_color			texture_checkers(t_material *mat, t_texture *tex, t_vec3 uv);
t_color			texture_strips(t_material *mat, t_texture *tex, t_vec3 uv);
t_color			texture_wave(t_material *mat, t_texture *tex, t_vec3 uv);
t_color			texture_perlin(t_material *mat, t_texture *tex, t_vec3 uv);
t_color			texture_wood(t_material *mat, t_texture *tex, t_vec3 uv);
t_color			texture_marble(t_material *mat, t_texture *tex, t_vec3 uv);
t_color			texture_cloud(t_material *mat, t_texture *tex, t_vec3 uv);
t_color			sample(t_material *material, t_texture *tex, t_vec3 uv);

/*
** Perlin :
*/

float			noise(float x, float y, float z);
float			perlin(t_vec3 uv, int octaves, float persistence);

/*
** Post-process :
*/
t_color			anti_aliasing(t_color col_prim, t_data *app, int x, int y);
t_color			sepia(t_color in);
t_color			grayscale(t_color in);
t_color			cartoon(t_color in);
t_color			negative(t_color in);

#endif

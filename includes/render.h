/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:50:27 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/25 14:56:41 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "rtstruct.h"
#include "color.h"

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

float			noise(float x,  float y,  float z);
float			perlin(t_vec3 uv, int octaves, float persistence);

/*
** Post-process :
*/

t_color			sepia(t_color in);
t_color			grayscale(t_color in);
t_color			cartoon(t_color in);
t_color			negative(t_color in);

#endif

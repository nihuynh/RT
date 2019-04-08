/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 05:12:37 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/19 15:59:04 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include "librt.h"

# define ERR_PARSE_CONTENT	"ERROR :	Unknown object			at line : "

# define ERR_PARSE_VECTOR	"ERROR :	parsing of the Vector	at line : "
# define ERR_PARSE_FLOAT	"ERROR :	parsing of the Float	at line : "
# define ERR_PARSE_COLOR	"ERROR :	parsing of the Color 	at line : "
# define ERR_PARSE_STRN		"ERROR :		NULL string		 	at line : "

# define ERR_P_CLOSE_PAR	"ERROR :	Missing parenthese		at line : "
# define ERR_P_BRACKET		"ERROR :	Missing bracket 		at line : "
# define ERR_P_KEY			"ERROR :	Missing key				at line : "

# define ERR_PARSE_SET_SP	"ERROR :	Set-up of the sphere	at line : "
# define ERR_PARSE_SET_CY	"ERROR :	Set-up of the cylinder	at line : "
# define ERR_PARSE_SET_PL	"ERROR :	Set-up of the plan		at line : "
# define ERR_PARSE_SET_CO	"ERROR :	Set-up of the cone		at line : "
# define ERR_PARSE_SET_LI	"ERROR :	Set-up of the light		at line : "
# define ERR_FILE			"ERROR :	File is too small to be valid"

/*
** Getters :
*/

void			ft_error_wmsg(char *str, int line, char *endl);
void			parse_color(t_color *color, char *str, int line, char *key);
void			parse_vector(t_vec3 *vec, char *str, int line, char *key);
void			parse_fval(float *val, char *str, int line, const char *key);
void			parse_limit(float *l_x, float * l_y, char *str, int line);
void			parse_texture(t_plane *plane, char *str, int line);

/*
** Setters :
*/

void			cone_set(void *cone, char **greed, int i);
void			cylinder_set(void *cylinder, char **greed, int i);
void			plane_set(void *plane, char **greed, int i);
void			sphere_set(void *sphere, char **greed, int i);
void			light_set(t_light *light, char **greed, int i);

/*
** Structs :
*/

typedef struct	s_parse
{
	char		*printout;
	size_t		content_size;
	void		(*setter) (void*, char **, int);
	size_t		line_offset;
}				t_parse;

#endif

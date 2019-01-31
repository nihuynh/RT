/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 05:12:37 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 17:24:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include "librt.h"

# define ERR_PARSE_CONTENT	"ERROR :	Unknown object			at line : "

# define ERR_PARSE_NORMAL	"ERROR :	parsing of the Normal	at line : "
# define ERR_PARSE_ORIGIN	"ERROR :	parsing of the Origin	at line : "
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
void			parse_color(t_color *color, char *str, int line);
void			parse_origin(t_pt3 *origin, char *str, int line);
void			parse_normal(t_vec3 *normal, char *str, int line);
void			parse_fval(float *val, char *str, int line, const char *key);

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

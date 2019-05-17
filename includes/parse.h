/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 05:12:37 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/17 18:30:49 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include "librt.h"
# include "rt.h"

# define ERR_P_CONTENT		"ERROR :	Unknown object			at line : "

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
** Structs :
*/

typedef struct	s_parse
{
	char		*printout;
	size_t		content_size;
	void		(*setter) (void*, char **, int);
	void		(*export) (int, void*);
	size_t		line_offset;
}				t_parse;

typedef struct	s_objset
{
	void		(*f_inter) (t_inter*, t_obj*);
	void		(*f_gui) (void*);
	void		(*find_normal) (t_inter*);
	t_vec3		(*get_uv) (t_inter*);
}				t_objset;

typedef struct	s_built
{
	void		(*setter) (void*, char **, int);
}				t_built;
/*
** New object
*/

void			sphere_new(void *res, char **greed, int i);
void			plane_new(void *res, char **greed, int i);
void			cylinder_new(void *res, char **greed, int i);
void			cone_new(void *res, char **greed, int i);

/*
** Getters :
*/

int				matcmp(void *content, void *key);
int				texcmp(void *content, void *key);
char			*check_key(char *str, int line, const char *key, char *err);
void			ft_error_wmsg(char *str, int line, char *endl);
void			parse_color(t_color *color, char **lines, int idx, char *key);
void			parse_fval(float *val, char **lines, int idx, const char *key);
void			parse_vector(t_vec3 *vec, char **lines, int idx, char *key);
void			parse_limit(float *l_x, float *l_y, char **lines, int line_idx);
t_texture		*parse_texture(t_list **lst_tex, char **lines, int line_idx);
void			open_textures(t_data *app);

/*
** Setters :
*/

void			obj_set(t_obj *obj, int type, void *shape);
void			init_parse_cfg(int type, t_parse *config);
void			cone_set(void *cone, char **greed, int i);
void			cylinder_set(void *cylinder, char **greed, int i);
void			plane_set(void *plane, char **greed, int i);
void			sphere_set(void *sphere, char **greed, int i);
void			light_set(t_light *light, char **greed, int i);

/*
** Export :
*/

void			plane_export(int fd, void *shape);
void			sphere_export(int fd, void *shape);
void			cone_export(int fd, void *shape);
void			cylinder_export(int fd, void *shape);
void			export_material(int fd, t_material *mat);


#endif

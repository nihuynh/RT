/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 05:12:37 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/20 14:02:55 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include "rtstruct.h"
# include "data_struct.h"

# define ERR_P_CAMERA		"Err : camera is missing"
# define ERR_P_CONTENT		"Err : content is missing"
# define ERR_UNKNWD_OBJ		"Err : Unknown object"
# define ERR_UNKNWD_MAT		"Err : Unknown material"

# define ERR_PARSE_VECTOR	"Err : [Vector]	Wrong number of args"
# define ERR_PARSE_FLOAT	"Err : [Float]	Wrong number of args"
# define ERR_PARSE_COLOR	"Err : [Color]	Wrong number of args"
# define ERR_PARSE_LIMIT	"Err : [Limit]	Wrong number of args"
# define ERR_PARSE_STRN		"Err : NULL string"
# define ERR_PARSE_OUTR		"Err : line_idx out of range"

# define ERR_P_CLOSE_PAR	"Err : Missing parenthese"
# define ERR_P_BRACKET_CLSE	"Err : Missing closing bracket"
# define ERR_P_BRACKET_OPEN	"Err : Missing opening bracket"
# define ERR_P_KEY			"Err : Missing key"

# define ERR_PARSE_SET_SP	"Err : *sphere		is null"
# define ERR_PARSE_SET_CY	"Err : *cylinder	is null"
# define ERR_PARSE_SET_PL	"Err : *plan		is null"
# define ERR_PARSE_SET_CO	"Err : *cone		is null"
# define ERR_PARSE_SET_LI	"Err : *light		is null"
# define ERR_PARSE_SET_CSG	"Err : *csg			is null"
# define ERR_FILE			"Err : File is too small to be valid"

/*
** Parsing structs :
*/

typedef struct s_parse_txt	t_parse_txt;

typedef struct	s_parse
{
	char		*printout;
	size_t		content_size;
	void		(*setter) (void*, t_parse_txt*);
	void		(*export) (int, void*);
}				t_parse;

struct			s_parse_txt
{
	char		**greed;
	int			line_idx;
	int			line_max;
	short		is_pop;
	const char	*err_func;
	const char	*err_file;
	int			err_at_line;
	t_data		*app;
	char		*(*get_curr_line) (t_parse_txt*);
	char		*(*pop_line) (t_parse_txt*);
	void		(*err_set) (t_parse_txt*, const char[], int, const char[]);
	void		(*err_exit) (char *, t_parse_txt*);
};

typedef struct	s_objset
{
	void		(*f_inter) (t_inter*, t_obj*);
	void		(*f_gui) (void*);
	void		(*find_normal) (t_inter*);
	t_vec3		(*get_uv) (t_inter*);
}				t_objset;

typedef struct	s_built
{
	void		(*setter) (void*);
}				t_built;

/*
** Parser :
*/

int				load_parse_txt(t_parse_txt *s_f, t_data *app, char *filename);
void			check_opening_bracket(t_parse_txt *scene_file);
void			check_closing_bracket(t_parse_txt *scene_file);

void			create_obj(t_obj *obj, t_parse_txt *scene_file, int type);
void			parse_light(t_parse_txt *scene_file);
void			parse_shape(t_parse_txt *scene_file, int type);

void			init_parse_cfg(int type, t_parse *config);
void			obj_set(t_obj *obj, int type, void *shape);

void			parse_color(t_color *color, char *key, t_parse_txt *scene_file);
void			parse_fval(float *val, char *key, t_parse_txt *scene_file);
void			parse_vector(t_vec3 *vec, char *key, t_parse_txt *scene_file);
void			parse_limit(float *l_x, float *l_y, t_parse_txt *scene_file);

/*
** New object
*/

void			sphere_new(void *res);
void			plane_new(void *res);
void			cylinder_new(void *res);
void			cone_new(void *res);

/*
** list of material & textures :
*/

int				matcmp(void *content, void *key);
int				texcmp(void *content, void *key);
char			*load_texture(t_texture *tex);
void			open_textures(t_data *app);

/*
** Getters :
*/

char			*get_obj_str(int type);
int				get_obj_type(char *obj_type);
char			*get_args_key_require(t_parse_txt *scene_file, const char *key);

/*
** Setters :
*/

void			light_set(t_light *light, t_parse_txt *scene_file);
void			cone_set(void *cone, t_parse_txt *scene_file);
void			cylinder_set(void *cylinder, t_parse_txt *scene_file);
void			plane_set(void *plane, t_parse_txt *scene_file);
void			sphere_set(void *sphere, t_parse_txt *scene_file);
void			csg_set(void *root, t_parse_txt *scene_file);

/*
** Export :
*/

void			plane_export(int fd, void *shape);
void			sphere_export(int fd, void *shape);
void			cone_export(int fd, void *shape);
void			cylinder_export(int fd, void *shape);
void			csg_export(int fd, void *shape);
void			export_material(int fd, t_material *mat);

/*
** CSG :
*/

void			inter_csg(t_inter *data, t_obj *node);
void			ui_csg(void *res);
void			normal_csg(t_inter *inter);
t_vec3			get_csg_uv(t_inter *inter);

#endif

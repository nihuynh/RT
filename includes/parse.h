/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 05:12:37 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/26 22:41:25 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include "rtstruct.h"
# include "t_data.h"

# define ERR_P_CAMERA		"Err : camera is missing"
# define ERR_P_CONTENT		"Err : content is missing"
# define ERR_UNKNWD_OBJ		"Err : Unknown object"
# define ERR_UNKNWD_MAT		"Err : Unknown material"
# define ERR_UNKNWD_OBJ_A	"Err : Unknown object in animation list"
# define ERR_UNKNWD_MOTION	"Err : Unknown motion in animation list"
# define ERR_MISSING_MOTION	"Err : Missing motion in animation list"

# define ERR_PARSE_VEC3		"Err : [Vec3]	Wrong number of args"
# define ERR_PARSE_FLOAT	"Err : [Float]	Wrong number of args"
# define ERR_PARSE_COLOR	"Err : [Color]	Wrong number of args"
# define ERR_PARSE_VEC2		"Err : [Vec2]	Wrong number of args"
# define ERR_OP_EQUAL_OBJ	"Err : [Csg]	sizeof(t_obj) == sizeof(t_csg_op)"
# define ERR_PARSE_STRN		"Err : line		is NULL"
# define ERR_GREED_NULL		"Err : greed	is NULL"
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

# define CSV_MATERIAL_COLUMN_COUNT 17

/*
** Parsing structs :
*/

typedef struct s_parse_txt	t_parse_txt;

typedef struct	s_parse
{
	char		*printout;
	size_t		content_size;
	void		(*setter) (t_obj*, void*, t_parse_txt*);
	void		(*export) (int, void*);
}				t_parse;

struct			s_parse_txt
{
	int			line_idx;
	int			line_max;
	char		**greed;
	char		*filename;
	t_data		*app;
	const char	*err_func;
	const char	*err_file;
	int			err_at_line;
	bool		is_pop;
	bool		exit_on_err;
};

void			err_set(t_parse_txt *scene_file, const char err_func[],
					int line_in_code, const char err_file[]);
void			err_exit(char *err_msg, t_parse_txt *scene_file);
char			*pop_line(t_parse_txt *scene_file);
char			*get_curr_line(t_parse_txt *scene_file);

typedef struct	s_objset
{
	void		(*f_inter) (t_inter*, t_obj*);
	void		(*f_gui) (void*, void*);
	void		(*find_normal) (t_inter*);
	t_vec3		(*get_uv) (t_inter*);
}				t_objset;

typedef struct	s_built
{
	void		(*setter) (t_obj*, void*);
}				t_built;

/*
** Parser :
*/

void			init_parse_cfg(int type, t_parse *config);
int				load_parse_txt(t_parse_txt *s_f, t_data *app, char *filename);
void			check_opening_bracket(t_parse_txt *scene_file);
void			check_closing_bracket(t_parse_txt *scene_file);

void			create_obj_from_txt(t_obj *obj, t_parse_txt *scene_f, int type);
void			parse_light(t_parse_txt *scene_file);
void			parse_shape(t_parse_txt *scene_file, int type);
void			parse_anim(t_parse_txt *scene_file);
void			parse_motion(t_parse_txt *scene_file, t_anim *anim);

t_color			parse_color(char *key, t_parse_txt *scene_file);
float			parse_fval(char *key, t_parse_txt *scene_file);
t_vec3			parse_vector(char *key, t_parse_txt *scene_file);
t_vec2			parse_vec2(char *key, t_parse_txt *scene_file);
char			*parse_str(t_parse_txt *scene_file, char *key);
int				parse_int(char *key, t_parse_txt *scene_file);

/*
** New object
*/

void			sphere_new(t_obj *obj, void *res);
void			plane_new(t_obj *obj, void *res);
void			cylinder_new(t_obj *obj, void *res);
void			cone_new(t_obj *obj, void *res);
char			*name_obj(int type, int *nb);

/*
** list of material & textures :
*/

int				matcmp(void *content, void *key);
int				texcmp(void *content, void *key);
int				obj_cmp_key(void *content, void *key);
int				light_cmp_key(void *content, void *key);
void			load_texture(t_texture *tex);
void			open_textures(t_data *app);

/*
** Getters :
*/

int				get_obj_type(char *obj_type);
char			*get_args_key_require(t_parse_txt *scene_file, const char *key);
char			*get_args_after_key(t_parse_txt *scene_file, const char *key);

/*
** Setters :
*/

void			obj_set(t_obj *obj, int type);
void			light_set(t_light *light, t_parse_txt *scene_file);
void			cone_set(t_obj *obj, void *cone, t_parse_txt *scene_file);
void			cylinder_set(t_obj *obj, void *cylinder, t_parse_txt *scene_fi);
void			plane_set(t_obj *obj, void *plane, t_parse_txt *scene_file);
void			sphere_set(t_obj *obj, void *sphere, t_parse_txt *scene_file);
void			csg_set(t_obj *obj, void *root, t_parse_txt *scene_file);
void			set_min_max_corner(t_cube *cube);
void			cube_set(t_obj *obj, void *root, t_parse_txt *scene_file);
void			tore_set(t_obj *obj, void *root, t_parse_txt *scene_file);

/*
** CSG :
*/

int				csg_is_op(t_parse_txt *scene_file);

#endif

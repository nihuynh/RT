/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:04:12 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/15 19:33:08 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "tools.h"
#include "parse.h"
#include "libft.h"
#include <unistd.h>

static inline t_texture
	*load_texture_csv(t_data *app, char *tex_name)
{
	t_texture *dst;

	if (!(dst = ft_lstgetelt(app->lst_tex, &texcmp, tex_name)))
		dst = ft_lstgetelt(app->lst_tex, &texcmp, "none");
	load_texture(dst);
	return (dst);
}

static inline t_material
	split_to_mat(t_data *app, char **split)
{
	t_material	mat;

	ft_bzero(&mat, sizeof(t_material));
	if (!(mat.name = ft_strdup(split[0])))
		ft_error(__func__, __LINE__);
	mat.color_diffuse = itocolor(ft_atoi_base(split[1], 16));
	mat.color_specular = itocolor(ft_atoi_base(split[2], 16));
	mat.color_tex = itocolor(ft_atoi_base(split[3], 16));
	mat.spec_idx = ft_atof(split[4]);
	mat.spec_power = ft_atof(split[5]);
	mat.refraction_color = itocolor(ft_atoi_base(split[6], 16));
	mat.reflection_color = itocolor(ft_atoi_base(split[7], 16));
	mat.refraction_idx = ft_atof(split[8]);
	mat.uv_mapping.scale.x = ft_atof(split[9]);
	mat.uv_mapping.scale.y = ft_atof(split[10]);
	mat.uv_mapping.offset.x = ft_atof(split[11]);
	mat.uv_mapping.offset.y = ft_atof(split[12]);
	mat.uv_mapping.repeat = ft_atoi(split[13]);
	mat.tex = load_texture_csv(app, split[14]);
	mat.normal_map = load_texture_csv(app, split[15]);
	mat.spec_map = load_texture_csv(app, split[16]);
	return (mat);
}

void
	parse_material_csv(t_data *app, char *csv_file)
{
	int			fd;
	char		*line;
	char		**split;
	char		*abs_path __attribute__((cleanup(ft_strdel)));
	t_material	node;

	if (!(abs_path = ft_strjoin(app->option.path, csv_file)))
		ft_error(__func__, __LINE__);
	fd = ft_fopen_read(abs_path);
	(ft_gnl(fd, &line, "\n") > 0) ? ft_strdel(&line) : exit_safe(EXIT_FAILURE);
	while (ft_gnl(fd, &line, "\n") > 0)
	{
		if (!(split = ft_strsplit(line, ',')))
			ft_error(__func__, __LINE__);
		if (ft_tablen(split) != CSV_MATERIAL_COLUMN_COUNT)
			ft_error(__func__, __LINE__);
		node = split_to_mat(app, split);
		ft_lstpushnew(&app->lst_mat, &node, sizeof(t_material));
		ft_tabdel(split);
		ft_strdel(&line);
	}
	close(fd);
	ft_lstsort(&app->lst_mat, &mat_cmp);
	if (ft_lstlen(app->lst_mat) == 0)
		exit_safe(EXIT_FAILURE);
}

int
	csg_is_op(t_parse_txt *scene_file)
{
	if (ft_strstr(get_curr_line(scene_file), INTER_STR) != NULL)
		return (INTER);
	if (ft_strstr(get_curr_line(scene_file), NOT_STR) != NULL)
		return (NOT);
	if (ft_strstr(get_curr_line(scene_file), UNION_STR) != NULL)
		return (UNION);
	return (0);
}

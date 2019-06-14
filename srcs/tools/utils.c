/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:04:12 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/14 04:27:01 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
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
	t_material	node;

	fd = ft_fopen_read(csv_file);
	if (ft_gnl(fd, &line, "\n") > 0)
		ft_strdel(&line);
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
}

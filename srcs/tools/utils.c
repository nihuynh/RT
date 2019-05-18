/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:04:12 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/18 03:49:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"
#include <unistd.h>

int
	matcmp(void *content, void *key)
{
	t_material	*mat;
	char		*ckey;

	mat = content;
	ckey = key;
	return (!ft_strncasecmp(mat->name, ckey, ft_strlen(mat->name)));
}

/*
** @brief			Verify if a line is containing the proper value and key.
**
** @param str 		String to check
** @param line		Current line of parsing
** @param key		Parameter to find
** @param err		Error to send if the parameter is not found
** @return char*	A pointer to the beginning of the value for the parameter
*/

char
	*check_key(char *str, int line, const char *key, char *err)
{
	static char buffer[128];

	if (!(str = ft_strstr(str, key)))
	{
		snprintf(buffer, 128, "Missing key: \"%s\" at line ", key);
		ft_parse_err(__func__, __LINE__, buffer, line, str);
	}
	str += ft_strlen(key);
	if (!*str)
		ft_parse_err(__func__, __LINE__, err, line, str);
	if (ft_strrchr(str, ')') == NULL)
		ft_parse_err(__func__, __LINE__, ERR_P_CLOSE_PAR, line, str);
	return (str);
}

static inline void
	split_to_mat(t_data *data, char **split, t_material *mat)
{
	ft_bzero(mat, sizeof(t_material));
	if (!(mat->name = ft_strdup(split[0])))
		ft_error(__func__, __LINE__);
	if (!(mat->tex = ft_lstgetelt(data->lst_tex, &texcmp, split[0])))
		mat->tex = ft_lstgetelt(data->lst_tex, &texcmp, "none");
	mat->color_diffuse = itocolor(ft_atoi_base(split[1], 16));
	mat->color_specular = itocolor(ft_atoi_base(split[2], 16));
	mat->color_tex = itocolor(ft_atoi_base(split[3], 16));
	mat->spec_idx = ft_atof(split[4]);
	mat->spec_power = ft_atof(split[5]);
	mat->refraction_color = itocolor(ft_atoi_base(split[6], 16));
	mat->reflection_color = itocolor(ft_atoi_base(split[7], 16));
	mat->refraction_idx = ft_atof(split[8]);
}

void
	parse_material_csv(t_data *data, char *csv_file)
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
		if (ft_tablen(split) != 9)
			ft_error(__func__, __LINE__);
		split_to_mat(data, split, &node);
		ft_lstpushnew(&data->lst_mat, &node, sizeof(t_material));
		ft_tabdel(split);
		ft_strdel(&line);
	}
	close(fd);
}

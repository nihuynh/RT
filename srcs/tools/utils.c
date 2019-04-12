/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:04:12 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/12 20:12:17 by nihuynh          ###   ########.fr       */
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

/**
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
	if (!(str = ft_strstr(str, key)))
		ft_error_wmsg(ERR_P_KEY, line, str);
	str += ft_strlen(key);
	if (!*str)
		ft_error_wmsg(err, line, str);
	if (ft_strrchr(str, ')') == NULL)
		ft_error_wmsg(ERR_P_CLOSE_PAR, line, str);
	return (str);
}

static inline void
	split_to_mat(char **split, t_material *mat)
{
	if (!(mat->name = ft_strdup(split[0])))
		ft_error(__func__, __LINE__);
	itocolor(&mat->color_ambient, ft_atoi_base(split[1], 16));
	itocolor(&mat->color_diffuse, ft_atoi_base(split[2], 16));
	itocolor(&mat->color_specular, ft_atoi_base(split[3], 16));
	itocolor(&mat->self_light, ft_atoi_base(split[4], 16));
	mat->spec_idx = ft_atof(split[5]);
	mat->spec_power = ft_atof(split[6]);
	mat->absorb_idx = ft_atof(split[7]);
	mat->deflect_idx = ft_atof(split[8]);
}

void
	parse_material_csv(t_data *data, char *csv_file)
{
	int			fd;
	char		*line;
	char		**split;
	t_material	node;
	t_list		*lst_node;

	fd = ft_fopen_read(csv_file);
	if (ft_gnl(fd, &line, "\n") > 0)
		ft_strdel(&line);
	while (ft_gnl(fd, &line, "\n") > 0)
	{
		if (!(split = ft_strsplit(line, ',')))
			ft_error(__func__, __LINE__);
		if (ft_tablen(split) != 9)
			ft_error(__func__, __LINE__);
		split_to_mat(split, &node);
		if (!(lst_node = ft_lstnew(&node, sizeof(t_material))))
			ft_error(__func__, __LINE__);
		ft_lstadd(&data->lst_mat, lst_node);
		lst_node = NULL;
		ft_tabdel(split);
		ft_strdel(&line);
	}
	close(fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 23:29:11 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/19 04:08:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "config.h"
#include "parse.h"
#include "lifetime.h"
#include <unistd.h>

static inline char
	*safe_line(t_parse_txt *scene_file)
{
	scene_file->is_pop = 0;
	if (!(ft_btw(scene_file->line_idx, 0, scene_file->line_max)))
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit("line_idx out of range", scene_file);
	}
	if (!(scene_file->greed[scene_file->line_idx]))
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit("Str is null", scene_file);
	}
	return (scene_file->greed[scene_file->line_idx]);
}

static inline char
	*pop_line(t_parse_txt *scene_file)
{
	char *res;

	res = scene_file->get_curr_line(scene_file);
	scene_file->is_pop = 1;
	scene_file->line_idx++;
	return (res);
}

static inline void
	err_exit(char *err_msg, t_parse_txt *scene_file)
{
	t_data *app;

	app = get_app(NULL);
	scene_file->line_idx -= scene_file->is_pop;
	ft_printf("%s\nPARSE_TXT : [line :%d]%s\n%s : %s (%s:%d)",
		err_msg, scene_file->line_idx, scene_file->greed[scene_file->line_idx],
		"Error in the function", scene_file->err_func, scene_file->err_file,
		scene_file->err_at_line);
	ft_tabdel(scene_file->greed);
	exit_safe(app);
}

static inline void
	err_set(t_parse_txt *scene_file, const char err_func[],
		int line_in_code, const char err_file[])
{
	scene_file->err_file = err_file;
	scene_file->err_func = err_func;
	scene_file->err_at_line = line_in_code;
}


int
	load_parse_txt(t_parse_txt *scene_file, char *filename)
{
	int		fd;
	size_t	size_greed;

	ft_bzero(scene_file, sizeof(t_parse_txt));
	scene_file->get_curr_line = &safe_line;
	scene_file->pop_line = &pop_line;
	scene_file->err_set = &err_set;
	scene_file->err_exit = &err_exit;
	if ((scene_file->line_max = ft_line_count(filename)) < 9)
		return (EXIT_FAILURE);
	size_greed = sizeof(char *) * (scene_file->line_max + 1);
	if (!(scene_file->greed = ft_memalloc(size_greed)))
		return (EXIT_FAILURE);
	fd = ft_fopen_read(filename);
	while (ft_gnl(fd, &scene_file->greed[scene_file->line_idx], "\n") > 0)
		scene_file->line_idx++;
	close(fd);
	scene_file->line_idx = 0;
	return (EXIT_SUCCESS);
}

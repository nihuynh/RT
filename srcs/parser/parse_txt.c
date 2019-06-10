/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 23:29:11 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/10 04:56:49 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"
#include "parse.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>

/**
** @brief Check if the line_idx is in range and return the curr_line.
**
** @param scene_file	: data in txt to parse
** @return char*		: curr_line
*/

char
	*get_curr_line(t_parse_txt *scene_file)
{
	if (!(scene_file->greed))
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_GREED_NULL, scene_file);
	}
	scene_file->is_pop = 0;
	if (!(ft_btw(scene_file->line_idx, 0, scene_file->line_max)))
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_OUTR, scene_file);
	}
	if (!(scene_file->greed[scene_file->line_idx]))
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_STRN, scene_file);
	}
	return (scene_file->greed[scene_file->line_idx]);
}

/**
** @brief Return the curr_line and move line_idx to the next line.
**
** @param scene_file	: data in txt to parse
** @return char*		: curr_line before the increment of line_idx
*/

char
	*pop_line(t_parse_txt *scene_file)
{
	char *res;

	res = get_curr_line(scene_file);
	scene_file->is_pop = 1;
	scene_file->line_idx++;
	return (res);
}

/**
** @brief Print the exit message and exit after cleaning the data allocated.
**
** @param err_msg		: message to explain the error.
** @param scene_file	: data in txt to parse
*/

void
	err_exit(char *err_msg, t_parse_txt *scene_file)
{
	scene_file->line_idx -= scene_file->is_pop;
	if (scene_file->line_idx < scene_file->line_max && scene_file->greed)
	{
		ft_printf("%s\nPARSE_TXT : \"%s\" (%s:%d)\n%s%s (%s:%d)\n",
			err_msg, get_curr_line(scene_file),
			scene_file->filename, scene_file->line_idx + 1,
			"Error in the function : ", scene_file->err_func,
			scene_file->err_file, scene_file->err_at_line);
	}
	else
		ft_printf("%s\nError in the function : %s (%s:%d)\n",
			err_msg, scene_file->err_func, scene_file->err_file,
			scene_file->err_at_line);
	ft_tabdel(scene_file->greed);
	if (scene_file->exit_on_err)
		exit_safe(errno);
}

/**
** @brief Save data that produce the exit.
**
** @param scene_file	: data in txt to parse
** @param err_func		: function where the error occure
** @param line_in_code	: line where the error occure
** @param err_file		: file where the error occure
*/

void
	err_set(t_parse_txt *scene_file, const char err_func[],
		int line_in_code, const char err_file[])
{
	scene_file->err_file = err_file;
	scene_file->err_func = err_func;
	scene_file->err_at_line = line_in_code;
}

/**
** @brief	: Load a file into the t_parse_txt & bind the hooks and t_data app
**
** @param scene_file	: data in txt to parse
** @param app			: link to the data
** @param filename		: file to load
** @return int			: status of the function
*/

int
	load_parse_txt(t_parse_txt *scene_file, t_data *app, char *filename)
{
	int		fd;
	size_t	size_greed;

	ft_bzero(scene_file, sizeof(t_parse_txt));
	scene_file->app = app;
	scene_file->filename = filename;
	scene_file->exit_on_err = true;
	scene_file->line_max = ft_line_count(filename);
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

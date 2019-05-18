/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:53:33 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/18 03:20:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "libui.h"
#include "parse.h"

void
	ft_error_wmsg(char *msg, int line, char *endl)
{
	ft_printf("%s%d\n Parser endl : %s", msg, line, endl);
	ft_error(__func__, __LINE__);
}

void
	ft_parse_err(const char function[], int line, char *msg, int line_idx, char *endl)
{
	ft_printf("%s%d\n Parser endl : %s", msg, line_idx, endl);
	ft_error(function, line);
}

void
	exit_safe(t_data *data)
{
	free_lst(data);
	SDL_GL_DeleteContext(data->gui.gl_context);
	exit_sdl(&data->sdl);
}

void
	parsing_error(char *error_msg,
		t_parse_txt *scene_file, const char func[], int line)
{
	t_data *app;

	app = get_app(NULL);
	ft_parse_err(func, line, error_msg, scene_file->line_idx,
		scene_file->greed[scene_file->line_idx]);
	ft_tabdel(scene_file->greed);
	exit_safe(app);
}

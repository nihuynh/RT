/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:53:33 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/17 06:37:45 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "libui.h"

void
	ft_error_wmsg(char *str, int line, char *endl)
{
	ft_printf("%s%d\n Parser endl : %s", str, line, endl);
	ft_error(__func__, __LINE__);
}

void
	exit_safe(t_data *data)
{
	free_lst(data);
	SDL_GL_DeleteContext(data->gui.gl_context);
	exit_sdl(&data->sdl);
}

void
	parsing_error(int line, char *error, t_data *data, char **greed)
{
	line++;
	ft_error_wmsg(error, line, greed[line]);
	ft_tabdel(greed);
	exit_safe(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:14:02 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/17 06:21:56 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "interface.h"
#include <fcntl.h>
#include <unistd.h>

bool	check_file(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (false);
	close(fd);
	return (true);
}

void	reload(t_data *app, char *filename)
{
	free_scene(app);
	if (!(app->arg = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	if (reader(filename, app) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	default_settings(&app->settings);
	hook_cam_to_gui(app);
	init_gui(&app->gui, app);
	change_window_title(app->sdl.win, app);
	app->sdl.needs_render = true;
}

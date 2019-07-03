/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 03:28:01 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/03 17:34:23 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "t_data.h"
#include "interface.h"

bool
	check_file(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (false);
	close(fd);
	return (true);
}

void
	reload_scene(t_data *app, char *filename)
{
	char *tmp;

	if (ft_strcmp(filename, "scenes/") == 0)
	{
		ft_strlcpy(app->gui.err_msg, "Can't reload an unsaved scene.",
			sizeof(app->gui.err_msg));
		app->gui.err_open = true;
		return ;
	}
	if (!(tmp = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	load_scene(app, tmp);
	free(tmp);
}

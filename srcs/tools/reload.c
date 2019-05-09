/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:14:02 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/09 15:28:11 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <fcntl.h>

bool	check_file(char *filename)
{
	if (open(filename, O_RDONLY) == -1)
		return (false);
	return (true);
}

void	free_reload(t_data *app)
{
	free(app->arg);
	if (app->scene.lst_obj)
		ft_lstdel(&app->scene.lst_obj, &del_obj);
	if (app->scene.lst_light)
		ft_lstdel(&app->scene.lst_light, &del_obj);
	if (app->lst_mat)
		ft_lstdel(&app->lst_mat, &del_mat);
	if (app->lst_tex)
		ft_lstdel(&app->lst_tex, &del_obj);
}

void	reload(t_data *app, char *filename)
{
	free_reload(app);
	app->arg = ft_strdup(filename);
	if (reader(filename, app) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	init_settings(&app->settings);
	init_render(app);
	change_window_title(app->sdl.win, app);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 03:30:09 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/14 06:03:08 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_unit_test.h"

int	ut_export_load_scene(char *scene_path, t_data *const_app)
{
	t_data	local_app;
	char	*export_path;

	if (!(export_path = ft_strndup(scene_path, ft_strlen(scene_path - 3))))
		return (EXIT_FAILURE);
	if (!(export_path = ft_strjoinfree(export_path, "_export.rt")))
		return (EXIT_FAILURE);
	ft_bzero(&local_app, sizeof(t_data));
	local_app.lst_mat = const_app->lst_mat;
	local_app.lst_tex = const_app->lst_tex;
	if (reader_no_exit(scene_path, &local_app))
		return (EXIT_FAILURE);
	if (export_scene(&local_app, export_path))
		return (EXIT_FAILURE);
	free_scene(&local_app);
	if (reader_no_exit(export_path, &local_app))
		return (EXIT_FAILURE);
	ft_strdel(&export_path);
	return (EXIT_SUCCESS);
}

int	export_test_suite(t_data *const_data)
{
	bool res;

	res = ut_export_load_scene("scenes/fig1.rt", const_data);
	return (res);
}

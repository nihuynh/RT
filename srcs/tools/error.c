/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:53:33 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/09 15:01:44 by sklepper         ###   ########.fr       */
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
	del_obj(void *content, size_t content_size)
{
	t_obj *obj;

	obj = content;
	if (sizeof(t_obj) == sizeof(t_light))
		ft_error(__func__, __LINE__);
	if (content_size == sizeof(t_obj))
		free(obj->shape);
	free(obj);
}

void
	del_mat(void *content, size_t content_size)
{
	t_material *mat;

	(void)content_size;
	mat = content;
	free(mat->name);
	free(mat);
}

void
	exit_safe(t_data *data)
{
	free(data->arg);
	if (data->scene.lst_obj)
		ft_lstdel(&data->scene.lst_obj, &del_obj);
	if (data->scene.lst_light)
		ft_lstdel(&data->scene.lst_light, &del_obj);
	if (data->lst_mat)
		ft_lstdel(&data->lst_mat, &del_mat);
	if (data->lst_tex)
		ft_lstdel(&data->lst_tex, &del_obj);
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

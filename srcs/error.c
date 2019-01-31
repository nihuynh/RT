/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:53:33 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/20 00:31:44 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "libui.h"

void	ft_error_wmsg(char *str, int line, char *endl)
{
	ft_printf("%s%d\n Parser endl : %s", str, line, endl);
	ft_error(__func__, __LINE__);
}

SIVOID	del_obj(void *content, size_t content_size)
{
	t_obj *obj;

	obj = content;
	if (sizeof(t_obj) == sizeof(t_light))
		ft_error(__func__, __LINE__);
	if (content_size == sizeof(t_obj))
		free(obj->shape);
	free(obj);
}

void	exit_safe(t_data *data)
{
	data->stage = 1;
	if (data->lst_obj)
		ft_lstdel(&data->lst_obj, &del_obj);
	if (data->lst_light)
		ft_lstdel(&data->lst_light, &del_obj);
	if (data->core)
		free(data->core);
	exit_sdl(&data->sdl);
	exit(0);
}

void	parsing_error(int line, char *error, t_data *data, char **greed)
{
	line++;
	ft_error_wmsg(error, line, greed[line]);
	ft_tabdel(greed);
	exit_safe(data);
}

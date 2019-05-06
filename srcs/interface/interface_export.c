/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:28:02 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/06 19:21:51 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "interface.h"
#include "libft.h"

void	export_window(t_data *app)
{
	char buff[30];

	ft_strcpy(buff, app->gui.scene_name);
	igBegin("Export Scene", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	if (igInputText("Filename", buff, 30, ImGuiInputTextFlags_EnterReturnsTrue, NULL, NULL))
	{
		export_scene(app, buff);
		app->gui.export_open = false;
	}
	igEnd();
}

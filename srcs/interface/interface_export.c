/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:28:02 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/06 18:59:19 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "interface.h"

void	export_window(t_data *app)
{
	char buff[25];

	(void)app;
	igBegin("Export Scene", NULL, 0);
	if (igInputText("Filename", buff, 25, 0, NULL, NULL))
		export_scene(app, buff);
	igEnd();
}

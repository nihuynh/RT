/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:16:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/03/14 18:48:57 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"

void	update(void *arg)
{
	t_data *app;

	app = arg;
	update_camera(&app->cam, &app->sdl.isrender);
}

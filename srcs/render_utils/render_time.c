/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:32:58 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/13 16:29:19 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	push_render_time(t_sdl *sdl, long new_frame)
{
	int i;

	i = -1;
	while (++i < 24)
		sdl->render_time[i] = sdl->render_time[i + 1];
	sdl->render_time[i] = (float)new_frame / 1000;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/13 00:07:11 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

# include "rt.h"
# include <SDL.h>

# define FLAGS1	ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
# define FLAGS2	ImGuiWindowFlags_AlwaysAutoResize
# define FLAGS3	ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse
# define RENDER_FLAGS FLAGS1 | FLAGS2 | FLAGS3

void	window_scene(t_data *app);
void	icolortogui(int src, float dest[3]);
void	guicolortoi(float src[3], int *dest);
void	colortogui(t_color src, float dest[3]);
void	guitocolor(float src[3], t_color *dest);

#endif

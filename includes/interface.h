/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/12 20:17:43 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

# include "rt.h"
# include <SDL_video.h>
# include <SDL.h>
# include <OpenGL/gl.h>
# include "cimgui.h"
# define FLAGS1	ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar
# define FLAGS2	ImGuiWindowFlags_AlwaysAutoResize
# define FLAGS3	ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse
# define RENDER_FLAGS FLAGS1 | FLAGS2 | FLAGS3
# include "imgui_impl_sdl.h"
# include "imgui_impl_opengl2.h"
# include "libft.h"
typedef struct SDL_Window SDL_Window;

void	window_scene(t_data *app);

#endif

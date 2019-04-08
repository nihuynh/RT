/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:22:04 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/01 19:13:29 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "cimgui.h"

void	interface()
{
	igBegin("dev", NULL, ImGuiWindowFlags_None);
}

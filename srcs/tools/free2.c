/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:40:23 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/11 00:49:46 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include "stdlib.h"

void
	del_anim(void *content, size_t content_size)
{
	t_anim *anim;

	(void)content_size;
	anim = content;
	anim_free(anim);
	free(anim);
	anim = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:40:23 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 05:14:11 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include "stdlib.h"

void
	del_anim(void *content, size_t content_size)
{
	t_anim	*anim;

	(void)content_size;
	anim = content;
	if (anim->obj)
		anim->obj->anim = NULL;
	if (anim->light)
		anim->light->anim = NULL;
	if (anim->next)
		del_anim(anim->next, 0);
	anim_free(anim);
	free(anim);
	anim = NULL;
}

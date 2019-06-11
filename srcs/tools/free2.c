/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:40:23 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/11 16:00:19 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include "stdlib.h"

void
	del_anim(void *content, size_t content_size)
{
	t_anim	*anim;
	t_obj	*obj;

	(void)content_size;
	anim = content;
	obj = anim->obj;
	obj->animated = false;
	if (anim->next)
		del_anim(anim->next, 0);
	anim_free(anim);
	free(anim);
	anim = NULL;
}

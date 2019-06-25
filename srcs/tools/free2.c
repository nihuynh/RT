/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:40:23 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/25 23:01:52 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include <stdlib.h>

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

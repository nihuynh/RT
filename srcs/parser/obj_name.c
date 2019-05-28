/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:34:56 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/28 14:42:53 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*name_obj(const char *type, int *nb)
{
	char	*tmp;
	char	*name;

	if (!(tmp = ft_itoa(*nb)))
		ft_error(__func__, __LINE__);
	if (!(name = ft_strjoin(type, tmp)))
		ft_error(__func__, __LINE__);
	free(tmp);
	*nb += 1;
	return (name);
}

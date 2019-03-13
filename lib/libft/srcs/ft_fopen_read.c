/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fopen_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:38:14 by nihuynh           #+#    #+#             */
/*   Updated: 2018/08/20 15:22:18 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include <fcntl.h>

int	ft_fopen_read(char *file_name)
{
	int	fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_error(__func__, __LINE__);
	return (fd);
}

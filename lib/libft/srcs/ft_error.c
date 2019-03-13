/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 14:18:39 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/15 23:18:13 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftio.h"
#include <string.h>
#include <stdlib.h>
#include <sys/errno.h>

/*
** @ft_error
** This will abort the program an give valuable intel on why and where
** @param function (__func__)
** @param line (__LINE__)
*/

void	ft_error(const char function[], int line)
{
	ft_printf("Error during %s (at line : %d) => %s\n",\
			function, line, strerror(errno));
	exit(errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:09:18 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMATH_H
# define FTMATH_H

int		ft_abs(int value);
float	ft_absf(float value);
int		ft_btw(int value, int a, int b);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_clamp(int value, int low, int high);
float	ft_clampf(float value, float low, float high);

#endif

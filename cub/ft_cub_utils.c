/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 23:58:14 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:35:47 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_header.h"

float			ft_radian(float angle)
{
	return ((float)(angle * M_PI / 180));
}

float			ft_distance(float x, float y)
{
	return (sqrt(powf(x - g_p.axis.x, 2) + powf(y - g_p.axis.y, 2)));
}

float			ft_norm_angle(float angle)
{
	if (angle >= ft_radian(360.0F))
		angle -= ft_radian(360.0F);
	else if (angle <= ft_radian(0.0F))
		angle += ft_radian(360.0F);
	return (angle);
}

unsigned int	ft_color_s(t_color color)
{
	return ((color.r * 256 * 256) + (color.g * 256) + color.b);
}

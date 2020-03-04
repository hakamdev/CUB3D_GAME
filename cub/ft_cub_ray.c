/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:59:58 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:35:40 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_header.h"

static void			ft_init_ray(t_ray *ray)
{
	if (ray != NULL)
	{
		ray->length = 0;
		ray->w_hit.x = 0;
		ray->w_hit.y = 0;
		ray->hit_hor = 0;
		ray->hit_ver = 0;
		ray->r_down = (ray->angle > 0 && ray->angle < M_PI);
		ray->r_up = !ray->r_down;
		ray->r_right = ((ray->angle < 0.5 * M_PI) || (ray->angle > 1.5 * M_PI));
		ray->r_left = !ray->r_right;
	}
}

static t_ray_data	ft_horizontal(t_ray *ray)
{
	t_ray_data	hor;

	hor.len = 1000000000;
	hor.inter.y = floorf(g_p.axis.y / (float)TILE_SIZE) * (float)TILE_SIZE;
	hor.inter.y += (ray->r_down ? (float)TILE_SIZE : 0.0F);
	hor.inter.x = g_p.axis.x + (hor.inter.y - g_p.axis.y) / tanf(ray->angle);
	hor.step.y = (float)TILE_SIZE;
	hor.step.y *= (ray->r_up ? -1.0F : 1.0F);
	hor.step.x = (float)TILE_SIZE / tanf(ray->angle);
	hor.step.x *= (ray->r_left && hor.step.x > 0.0F) ? -1.0F : 1.0F;
	hor.step.x *= (ray->r_right && hor.step.x < 0.0F) ? -1.0F : 1.0F;
	hor.hit.x = hor.inter.x;
	hor.hit.y = hor.inter.y;
	while (hor.hit.y >= 0.0F && hor.hit.y < (float)g_data.m_dimens.h
		&& hor.hit.x >= 0.0F && hor.hit.x < (float)g_data.m_dimens.w)
	{
		if (ft_is_wall(hor.hit.x, ray->r_up ? hor.hit.y - 1 : hor.hit.y))
		{
			hor.len = ft_distance(hor.hit.x, hor.hit.y);
			break ;
		}
		hor.hit.x += hor.step.x;
		hor.hit.y += hor.step.y;
	}
	return (hor);
}

static t_ray_data	ft_vertical(t_ray *ray)
{
	t_ray_data	ver;

	ver.len = 1000000000;
	ver.inter.x = floorf(g_p.axis.x / (float)TILE_SIZE) * (float)TILE_SIZE;
	ver.inter.x += (ray->r_right ? (float)TILE_SIZE : 0.0F);
	ver.inter.y = g_p.axis.y + (ver.inter.x - g_p.axis.x) * tanf(ray->angle);
	ver.step.x = (float)TILE_SIZE;
	ver.step.x *= (ray->r_left ? -1.0F : 1.0F);
	ver.step.y = (float)TILE_SIZE * tanf(ray->angle);
	ver.step.y *= (ray->r_up && ver.step.y > 0.0F) ? -1.0F : 1.0F;
	ver.step.y *= (ray->r_down && ver.step.y < 0.0F) ? -1.0F : 1.0F;
	ver.hit.x = ver.inter.x;
	ver.hit.y = ver.inter.y;
	while (ver.hit.y >= 0.0F && ver.hit.y < (float)g_data.m_dimens.h
		&& ver.hit.x >= 0.0F && ver.hit.x < (float)g_data.m_dimens.w)
	{
		if (ft_is_wall(ray->r_left ? ver.hit.x - 1 : ver.hit.x, ver.hit.y))
		{
			ver.len = ft_distance(ver.hit.x, ver.hit.y);
			break ;
		}
		ver.hit.x += ver.step.x;
		ver.hit.y += ver.step.y;
	}
	return (ver);
}

static void			ft_setup_ray(t_ray *ray)
{
	t_ray_data	hor;
	t_ray_data	ver;

	ft_init_ray(ray);
	hor = ft_horizontal(ray);
	ver = ft_vertical(ray);
	if (ver.len > hor.len)
	{
		ray->length = hor.len;
		ray->hit_hor = 1;
		ray->hit_ver = 0;
		ray->w_hit.x = hor.hit.x;
		ray->w_hit.y = hor.hit.y;
	}
	else
	{
		ray->length = ver.len;
		ray->hit_ver = 1;
		ray->hit_hor = 0;
		ray->w_hit.x = ver.hit.x;
		ray->w_hit.y = ver.hit.y;
	}
}

void				ft_rays(float x, float y, float angle)
{
	int		i;
	float	ang;

	i = 0;
	ang = angle - ft_radian((float)(FOV / 2));
	while (i < g_data.dimens.w)
	{
		g_rays[i].angle = ft_norm_angle(ang);
		ft_setup_ray(&g_rays[i]);
		ang += ft_radian(g_data.ray_step);
		++i;
	}
}

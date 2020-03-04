/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:00:00 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:35:50 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_header.h"

int				ft_is_wall(float x, float y)
{
	int		i;
	int		j;

	i = floorf(y / (float)TILE_SIZE);
	j = floorf(x / (float)TILE_SIZE);
	return (g_data.map[i][j] == '1');
}

/*** WALL ***/

void			ft_draw_walls(void)
{
	int			i;
	int			j;
	t_wall_data	wall;

	wall.pp_dist = ((float)g_data.dimens.w / 2.0F) / tanf(ft_radian((FOV / 2)));
	i = 0;
	while (i < g_data.dimens.w)
	{
		wall.corr_len = g_rays[i].length * cosf(g_rays[i].angle - g_p.rot_ang);
		wall.hieght = (float)TILE_SIZE / wall.corr_len * (float)wall.pp_dist;
		wall.top = ((float)g_data.dimens.h / 2.0F) - (wall.hieght / 2.0F);
		wall.top = wall.top < 0 ? 0 : wall.top;
		wall.bottom = ((float)g_data.dimens.h / 2.0F) + (wall.hieght / 2.0F);
		wall.bottom = wall.bottom > g_data.dimens.h ? g_data.dimens.h : wall.bottom;
		j = 0;
		while (j < wall.top)
			g_data_3d[(j++ * g_data.dimens.w) + i] = ft_color_s(g_data.ciel);
		j = wall.bottom;
		while (j < g_data.dimens.h)
			g_data_3d[(j++ * g_data.dimens.w) + i] = ft_color_s(g_data.floor);
		ft_wall(wall.top, wall.bottom, wall.hieght, i);
		++i;
	}
	mlx_put_image_to_window(g_mlx, g_win, g_img_3d, 0, 0);
}

void			ft_wall(int w_top, int w_bottom, int w_height, int index)
{
	int j;
	int offset_x;
	int offset_y;
	int	color;

	if (g_rays[index].hit_ver)
		offset_x = (int)g_rays[index].w_hit.y % TILE_SIZE;
	else
		offset_x = (int)g_rays[index].w_hit.x % TILE_SIZE;
	j = w_top;
	while (j < w_bottom)
	{
		offset_y = (j + ((w_height / 2) - (g_data.dimens.h / 2))) *
			((float)g_dimd[0].h / (float)w_height);
		if (g_rays[index].hit_hor && g_rays[index].r_up)
			color = g_data_n[(offset_y * g_dimd[0].h) + offset_x];
		else if (g_rays[index].hit_hor && g_rays[index].r_down)
			color = g_data_s[(offset_y * g_dimd[0].h) + offset_x];
		else if (g_rays[index].hit_ver && g_rays[index].r_left)
			color = g_data_w[(offset_y * g_dimd[0].h) + offset_x];
		else if (g_rays[index].hit_ver && g_rays[index].r_right)
			color = g_data_e[(offset_y * g_dimd[0].h) + offset_x];
		g_data_3d[(j * g_data.dimens.w) + index] = color;
		++j;
	}
}
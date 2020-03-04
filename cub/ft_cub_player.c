/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:59:53 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:35:37 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_header.h"

static void		ft_player_axis(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_data.rows)
	{
		j = 0;
		while (j < g_data.cols)
		{
			if (g_data.map[i][j] == 'N' || g_data.map[i][j] == 'W'
				|| g_data.map[i][j] == 'S' || g_data.map[i][j] == 'E')
			{
				g_p.axis.x = j * TILE_SIZE + (TILE_SIZE / 2);
				g_p.axis.y = i * TILE_SIZE + (TILE_SIZE / 2);
				if (g_data.map[i][j] == 'N')
					g_p.rot_ang = ft_radian(270);
				else if (g_data.map[i][j] == 'W')
					g_p.rot_ang = ft_radian(180);
				else if (g_data.map[i][j] == 'S')
					g_p.rot_ang = ft_radian(90);
				else if (g_data.map[i][j] == 'E')
					g_p.rot_ang = ft_radian(0);
			}
			j++;
		}
		i++;
	}
}

void			ft_init_all(void)
{
	ft_player_axis();
	g_is_pressed = 0;
	g_p.turn_direct = 0;
	g_p.move_direct = 0;
	g_p.move_speed = (float)INIT_MOVE_SPD;
	g_p.rot_speed = ft_radian((float)INIT_ROT_SPD);
	g_p.side_ang = ft_radian(0);
	g_img_n = mlx_xpm_file_to_image(g_mlx, g_data.xpm_n, &g_dimd[0].w,
									&g_dimd[0].h);
	g_data_n = (int *)mlx_get_data_addr(g_img_n, &g_imgd[2].bits_per_pixel, &g_imgd[2].size_line, &g_imgd[2].endian);
	g_img_s = mlx_xpm_file_to_image(g_mlx, g_data.xpm_s,  &g_dimd[1].w,
									&g_dimd[1].h);
	g_data_s = (int *)mlx_get_data_addr(g_img_s, &g_imgd[10].bits_per_pixel, &g_imgd[3].size_line, &g_imgd[3].endian);
	g_img_w = mlx_xpm_file_to_image(g_mlx, g_data.xpm_w, &g_dimd[2].w,
									&g_dimd[2].h);
	g_data_w = (int *)mlx_get_data_addr(g_img_w, &g_imgd[4].bits_per_pixel, &g_imgd[4].size_line, &g_imgd[4].endian);
	g_img_e = mlx_xpm_file_to_image(g_mlx, g_data.xpm_e,  &g_dimd[3].w,
									&g_dimd[3].h);
	g_data_e = (int *)mlx_get_data_addr(g_img_e, &g_imgd[5].bits_per_pixel, &g_imgd[5].size_line, &g_imgd[5].endian);
	ft_rays(g_p.axis.x, g_p.axis.y, g_p.rot_ang);
	ft_draw_walls();
}

void			ft_update_all(void)
{
	t_axis	next;

	next.x = g_p.axis.x + g_p.move_speed * g_p.move_direct * cosf(g_p.rot_ang + g_p.side_ang);
	next.y = g_p.axis.y + g_p.move_speed * g_p.move_direct * sinf(g_p.rot_ang + g_p.side_ang);
	g_p.rot_ang = ft_norm_angle((g_p.rot_ang + g_p.rot_speed * g_p.turn_direct));
	if (!ft_is_wall(next.x, g_p.axis.y))
		g_p.axis.x = next.x;
	if (!ft_is_wall(g_p.axis.x, next.y))
		g_p.axis.y = next.y;
	if (g_p.move_direct || g_p.turn_direct || g_is_pressed)
	{
		ft_rays(g_p.axis.x, g_p.axis.y, g_p.rot_ang);
		ft_draw_walls();
	}
}

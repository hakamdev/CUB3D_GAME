/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:00:09 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:35:34 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_header.h"

void	ft_read_all(fd)
{
	char	*line;

	g_data.cols = 0;
	g_data.rows = 0;
	g_data.map = (char **)malloc(sizeof(char *) * 100);
	while (get_next_line(fd, &line) > 0)
	{
		ft_process_line(line);
		free(line);
	}
	ft_process_line(line);
	free(line);
	g_data.m_dimens.w = g_data.cols * TILE_SIZE;
	g_data.m_dimens.h = g_data.rows * TILE_SIZE;
	g_data.ray_step = (float)FOV / (float)g_data.dimens.w;
	g_rays = malloc(sizeof(t_ray) * g_data.dimens.w);
}

int main(int ac, char **av)
{
	int		fd;

	g_fname = av[1];
	if (!g_fname)
		return (1);
	fd = open(g_fname, O_RDONLY);
	ft_read_all(fd);
	close(fd);
	g_mlx = mlx_init();
	g_win = mlx_new_window(g_mlx, g_data.dimens.w, g_data.dimens.h, GAME_TITLE);
	g_img_3d = mlx_new_image(g_mlx, g_data.dimens.w, g_data.dimens.h);
	g_data_3d = (int *)mlx_get_data_addr(g_img_3d, &g_imgd[1].bits_per_pixel, &g_imgd[1].size_line, &g_imgd[1].endian);
	ft_init_all();
	mlx_hook(g_win, 2, 0, ft_key_pressed, NULL);
	mlx_hook(g_win, 3, 0, ft_key_released, NULL);
	mlx_loop_hook(g_mlx, ft_update, NULL);
	mlx_loop(g_mlx);
	return (0);
}

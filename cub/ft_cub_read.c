/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:38:46 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:35:43 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_header.h"

static void	ft_read_map(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (g_data.cols == 0)
	while (line[i])
	{
		if (line[i] != ' ')
			g_data.cols++;
		i++;
	}
	i = 0;
	g_data.map[g_data.rows] = (char *)malloc(sizeof(char) * g_data.cols + 1);
	while (line[i])
	{
		if (line[i] != ' ')
			g_data.map[g_data.rows][j++] = line[i];
		i++;
	}
	g_data.map[g_data.rows][j] = '\0';
	g_data.rows++;
}

static void	ft_read_resolution(char *line)
{
	char	**fragments;
	int		i;

	i = 0;
	fragments = ft_split(line, ' ');
	g_data.dimens.w = ft_atoi(fragments[1]) <= 2560 ? ft_atoi(fragments[1]) : 2560;
	g_data.dimens.h = ft_atoi(fragments[2]) <= 1395 ? ft_atoi(fragments[2]) : 1395;
	while (fragments[i] != NULL)
		free(fragments[i++]);
	free(fragments);
}

static void	ft_read_xpm(char *line, char **which)
{
	char	**fragments;
	int		i;

	i = 0;
	fragments = ft_split(line, ' ');
	*which = ft_strdup(fragments[1]);
	while (fragments[i] != NULL)
		free(fragments[i++]);
	free(fragments);
}

static void	ft_read_color(char *line, t_color *color)
{
	char	**fragments;
	int		i;

	i = 0;
	while (!(*line >= '0' && *line <= '9'))
		line++;
	fragments = ft_split(line, ',');
	(*color).r = ft_atoi(fragments[0]);
	(*color).g = ft_atoi(fragments[1]);
	(*color).b = ft_atoi(fragments[2]);
	while (fragments[i] != NULL)
		free(fragments[i++]);
	free(fragments);
}

void		ft_process_line(char *line)
{
	if (ft_strnstr(line, "R", 1))
		ft_read_resolution(line);
	else if (ft_strnstr(line, "NO", 2))
		ft_read_xpm(line, &g_data.xpm_n);
	else if (ft_strnstr(line, "SO", 2))
		ft_read_xpm(line, &g_data.xpm_s);
	else if (ft_strnstr(line, "WE", 2))
		ft_read_xpm(line, &g_data.xpm_w);
	else if (ft_strnstr(line, "EA", 2))
		ft_read_xpm(line, &g_data.xpm_e);
	else if (ft_strnstr(line, "S", 1))
		ft_read_xpm(line, &g_data.xpm_sprite);
	else if (ft_strnstr(line, "F", 1))
		ft_read_color(line, &g_data.floor);
	else if (ft_strnstr(line, "C", 1))
		ft_read_color(line, &g_data.ciel);
	else if (ft_strnstr(line, "1 ", 2))
		ft_read_map(line);
}
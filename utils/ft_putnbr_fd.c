/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:54:15 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:36:15 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_header.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nn;

	nn = n;
	if (nn < 0)
	{
		nn *= -1;
		c = '-';
		write(fd, &c, 1);
	}
	if (nn >= 0 && nn <= 9)
	{
		c = nn + 48;
		write(fd, &c, 1);
	}
	if (nn > 9)
	{
		ft_putnbr_fd(nn / 10, fd);
		ft_putnbr_fd(nn % 10, fd);
	}
}

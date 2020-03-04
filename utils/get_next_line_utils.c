/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:25:21 by ehakam            #+#    #+#             */
/*   Updated: 2020/03/04 22:34:56 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

void	ft_free(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

char	*ft_strsub(char **s, unsigned int start, size_t n)
{
	char			*ss;
	unsigned int	lens;
	unsigned int	i;

	i = 0;
	if (*s == NULL)
		EXIT(NULL);
	lens = ft_strlen(*s);
	if (start > lens)
		n = 0;
	if (!(ss = (char *)malloc(n + 1)))
		EXIT(NULL);
	while (i < n && start < lens)
		*(ss + i++) = *(*s + start++);
	*(ss + i) = CNULL;
	EXIT(ss);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ss;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	if (!s1 && s2)
	{
		ss = ft_strdup(s2);
		EXIT(ss);
	}
	i = -1;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ss = malloc(len1 + len2 + 1)))
		EXIT(NULL);
	while (++i < len1)
		*(ss + i) = *((char *)(s1 + i));
	while (j < len2)
		*(ss + i++) = *((char *)(s2 + j++));
	*(ss + i) = CNULL;
	ft_free(&s1);
	EXIT(ss);
}

char	*ft_strdup(const char *s)
{
	char	*ss;
	size_t	lens;
	size_t	i;

	i = 0;
	lens = ft_strlen(s);
	if (!(ss = (char *)malloc(lens + 1)))
		EXIT(NULL);
	while (i < lens)
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = CNULL;
	EXIT(ss);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (*(s + i))
		i++;
	EXIT(i);
}

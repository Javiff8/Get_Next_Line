/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javferna <javferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:18:32 by javferna          #+#    #+#             */
/*   Updated: 2021/10/18 12:34:44 by javferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin_gnl(char *temp, char *buf)
{
	char	*new_temp;
	int		i;
	int		j;

	if (!temp && !buf)
		return (NULL);
	new_temp = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(buf) + 1));
	if (!new_temp)
		return (NULL);
	i = -1;
	while (temp[++i])
		new_temp[i] = temp[i];
	j = 0;
	while (buf[j])
		new_temp[i++] = buf[j++];
	new_temp[i] = '\0';
	free(temp);
	return (new_temp);
}

static char	*ft_substr_gnl(char const *s, int start, int len)
{
	char	*substr;
	int		i;

	if (start > len)
		return (NULL);
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

static char	*ft_fill_result(char **temp)
{
	int		pos;
	int		len;
	char	*ret;
	char	*aux;

	if (!*temp)
		return (NULL);
	if (!**temp)
	{
		free(*temp);
		*temp = NULL;
		return (NULL);
	}
	aux = *temp;
	len = ft_strlen(*temp);
	pos = ft_strchr(*temp, '\n') - *temp;
	if (pos < 0)
		pos = len;
	ret = ft_substr_gnl(*temp, 0, pos + 1);
	*temp = ft_substr_gnl(*temp, pos + 1, len);
	free(aux);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*temp[MAX_FD];
	char		*buf;
	int			r;

	if (BUFFER_SIZE < 1 || (fd < 0 && fd > MAX_FD))
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	r = 1;
	while (r && (!temp[fd] || !ft_strchr(temp[fd], '\n')))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
			break ;
		buf[r] = '\0';
		if (!temp[fd])
			temp[fd] = ft_strdup(buf);
		else
			temp[fd] = ft_strjoin_gnl(temp[fd], buf);
	}
	free(buf);
	return (ft_fill_result(&temp[fd]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:07:44 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/15 10:00:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"

void	update_line(char **str)
{
	char	*tmp;

	tmp = *str;
	while (*tmp && *tmp != '\n')
		tmp++;
	if (*tmp == '\n' && *(tmp + 1))
	{
		tmp = ft_strdup(++tmp);
		if (!tmp)
			return (free(*str), (void)(*str = NULL));
	}
	else
		tmp = NULL;
	free(*str);
	*str = tmp;
}

char	*create_line(char *str)
{
	char	*extracted_line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i = i + 1 * (str[i] == '\n');
	extracted_line = (char *)malloc(i + 1);
	if (!extracted_line)
		return (free(str), str = NULL);
	i = 0;
	while (str[i])
	{
		extracted_line[i] = str[i];
		if (str[i++] == '\n')
			break ;
	}
	extracted_line[i] = '\0';
	return (extracted_line);
}

void	read_line(int fd, char **str)
{
	char	*buffer;
	char	*nl;
	int		rd;

	nl = NULL;
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(*str), (void)(*str = NULL));
	while (!nl)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
		{
			free(buffer);
			buffer = NULL;
			return ;
		}
		buffer[rd] = '\0';
		nl = ft_strchr(buffer, '\n');
		*str = ft_strjoin(*str, buffer);
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0
		|| BUFFER_SIZE > 2147483647 || read(fd, NULL, 0) < 0)
		return (free(str), str = NULL);
	if (!str || !ft_strchr(str, '\n'))
		read_line(fd, &str);
	if (!str)
		return (NULL);
	line = create_line(str);
	if (!line)
		return (str = NULL);
	update_line(&str);
	return (line);
}

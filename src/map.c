/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:18:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 16:28:13 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	set_map_dim(t_map *map)
{
	int		h;
	int		w;

	h = -1;
	while (map->content[++h])
	{
		w = (int)ft_strlen(map->content[h]);
		if (map->content[h + 1])
			if (w != (int)ft_strlen(map->content[h + 1]))
				return (NOT_VALID);
	}
	if (h == w)
		return (NOT_VALID);
	map->height = h;
	map->width = w;
	return (VALID);
}

static char	*get_map(char *path)
{
	char	*line;
	char	*content;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		raise_error(NULL, errno);
	content = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '1' || !ft_strpbrk(line, "01ECP\n"))
			return (free(line), free(content), NULL);
		content = ft_strjoin(content, line);
		free(line);
		if (!content)
			raise_error(NULL, ENOMEM);
	}
	close(fd);
	return (content);
}

t_map	*init_map(char *path)
{
	char	*content;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		raise_error(NULL, errno);
	content = get_map(path);
	if (!content)
	{
		free(map);
		raise_error("Extra characters are included in the map", 0);
	}
	map->content = ft_split(content, '\n');
	if (!map->content)
		(raise_error(NULL, ENOMEM));
	map->content_copy = ft_split(content, '\n');
	if (!map->content_copy)
		(free(content), free(map->content), raise_error(NULL, ENOMEM));
	free(content);
	if (!set_map_dim(map))
		raise_error("Invalid map dimensions", errno);
	map->collects = 0;
	map->exit.x = 0;
	map->exit.y = 0;
	return (map);
}

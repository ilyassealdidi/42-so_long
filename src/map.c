/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:18:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/20 17:59:28 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * @brief Sets the dimensions of the map.
 * 
 * This function calculates the height and width of the map based on the content.
 * 
 * @param map A pointer to the map structure.
 * @return Returns 1 if the map dimensions are successfully set, returns 0 if
 * the map is invalid.
 */
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
	map->height = h;
	map->width = w;
	return (VALID);
}

/**
 * @brief Retrieves the map content from a file descriptor.
 * 
 * This function reads the lines from the file descriptor `fd` and concatenates
 * them into a single string `content`. The lines are validated to ensure
 * they only contain valid characters ('0', '1', 'E', 'C', 'P', '\n')
 * and start with '1'. If any invalid line is encountered, the function
 * frees the allocated memory and returns NULL.
 * 
 * @param fd The file descriptor to read from.
 * @return A pointer to the map content string if successful, NULL otherwise.
 */
static char	*get_map(int fd)
{
	char	*line;
	char	*content;
	int		len;

	content = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '1' || ft_strspn(line, "01ECP\n") != ft_strlen(line))
			return (free(line), free(content), NULL);
		content = ft_strjoin(content, line);
		free(line);
		if (!content)
			raise_error(NULL, ENOMEM, NULL);
	}
	close(fd);
	if (!content)
		return (NULL);
	len = ft_strlen(content);
	if (!len || content[len - 1] != '1')
		return (NULL);
	return (content);
}

/**
 * Initializes a map structure by allocating memory and setting its content.
 * 
 * @param fd The file descriptor of the map file.
 * @return A pointer to the initialized map structure.
 */
t_map	*init_map(int fd)
{
	char	*content;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		raise_error(NULL, errno, NULL);
	content = get_map(fd);
	if (!content)
	{
		free(map);
		raise_error("Empty file or Extra characters included", 0, NULL);
	}
	map->content = ft_split(content, '\n');
	if (!map->content)
		(free(map), free(content), raise_error(NULL, errno, NULL));
	free(content);
	if (!set_map_dim(map))
		(free_array(map->content), free(map),
			raise_error("Invalid map dimensions", 0, NULL));
	map->collects = 0;
	set_point(&map->exit, 0, 0);
	return (map);
}

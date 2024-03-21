/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:41:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/20 01:59:30 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * Sets the coordinates of a point.
 *
 * @param p The point to set the coordinates for.
 * @param x The x-coordinate value.
 * @param y The y-coordinate value.
 */
void	set_point(t_point *p, int x, int y)
{
	p->x = x;
	p->y = y;
}

/**
 * This function opens a file specified by the given path and returns
 * the file descriptor.
 * It also performs a check on the file extension to ensure it is a ".ber" file.
 *
 * @param path The path of the file to be opened.
 * @return The file descriptor of the opened file, or -1 if an error occurs.
 */
int	is_valid_file(char *path)
{
	int		fd;
	int		len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".ber", 4))
		raise_error("Allowed extension: *.ber", 0, NULL);
	fd = open(path, O_RDONLY);
	return (fd * (fd != -1));
}

/**
 * Recursively performs flood fill algorithm on a map starting from
 * position (i, j). Replaces all connected cells with '1' until it reaches
 * the boundary or an obstacle ('1').
 *
 * @param map The map represented as a 2D array of characters.
 * @param i The row index of the starting position.
 * @param j The column index of the starting position.
 */
void	flood_fill(char **map, int i, int j)
{
	if (map[i][j] == 'E' || map[i][j] == 'N')
		map[i][j] = '1';
	if (map[i][j] != '1')
	{
		map[i][j] = '1';
		flood_fill(map, i - 1, j);
		flood_fill(map, i, j + 1);
		flood_fill(map, i + 1, j);
		flood_fill(map, i, j - 1);
	}
}

/**
 * Frees a dynamically allocated array of strings.
 * 
 * @param arr The array of strings to be freed.
 */
void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (1)
	{
		free(arr[++i]);
		if (!arr[i])
			break ;
	}
	free(arr);
}

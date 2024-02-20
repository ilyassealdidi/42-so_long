/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:41:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 14:36:48 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	mr_propre(t_object *obj)
{
	int	i;

	i = -1;
	while (++i < obj->map->height)
	{
		free(obj->map->content[i]);
		free(obj->map->content_copy[i]);
	}
	free(obj->map->content);
	free(obj->map->content_copy);
	free(obj->map);
	free(obj->player);
	exit(1);
}

void	flood_fill(char	**map, int i, int j)
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

void	raise_error(char *msg, int err)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd(strerror(err), 2);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:41:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/11 11:25:10 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	destroy_object(t_object *obj)
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
	//mlx_destroy_window(obj->mlx, obj->win);
}

int	exiter(t_object *obj)
{
	destroy_object(obj);
	exit(0);
	return (0);
}

void	flood_fill(char	**map, int i, int j)
{
	if (map[i][j] == 'E')
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

void	raise_error(char *msg, int err, t_object *obj)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (err)
		ft_putstr_fd(strerror(err), 2);
	if (obj)
		destroy_object(obj);
	exit(1);
}

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

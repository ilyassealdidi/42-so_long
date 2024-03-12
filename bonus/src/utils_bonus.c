/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:41:38 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/12 11:57:59 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	set_point(t_point *p, int x, int y)
{
	p->x = x;
	p->y = y;
}

static void	destroy_object(t_object *obj)
{
	free_array(obj->map->content);
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

void	raise_error(char *msg, int err, t_object *obj)
{
	ft_printf("Error\n");
	if (msg)
		ft_printf("%s", msg);
	if (err)
		ft_printf("%s", strerror(err));
	if (obj)
		destroy_object(obj);
	exit(1);
}

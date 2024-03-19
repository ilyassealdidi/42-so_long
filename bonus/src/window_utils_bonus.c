/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:23:22 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/19 18:13:45 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"
#include <time.h>

// void	draw_line(t_object *obj)
// {
// 	int	i;
// 	while ();
// }

// void	opening_animation(t_object *obj)
// {
	
// }

static void	render_coin(t_object *obj, void *img)
{
	char	**map;
	int		x;
	int		y;

	map = obj->map->content;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'C')
			{
				mlx_put_image_to_window(obj->mlx, obj->win, img, x * BLOCK_SIZE,
					y * BLOCK_SIZE);
			}
		}
	}
}

int	coin_animation(t_object *obj)
{
	char			path[23];
	void			*img;
	int				var;
	static clock_t	time;
	static int		i;

	if (!obj->map->collects)
		return (0);
	if (clock() - time >= 8000)
	{
		i = i * (i != 15);
		ft_strlcpy(path, "bonus/textures/c__.xpm", 23);
		path[16] = (i / 10) + 48;
		path[17] = (i % 10) + 48;
		img = mlx_xpm_file_to_image(obj->mlx, path, &var, &var);
		if (!img)
			raise_error(NULL, errno, obj);
		render_coin(obj, img);
		mlx_destroy_image(obj->mlx, img);
		time = clock();
		i++;
	}
	return (0);
}

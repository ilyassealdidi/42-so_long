/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:23:22 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/20 14:05:29 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * Renders the coins on the game window.
 * 
 * @param obj The object containing the game information.
 * @param img The image of the coin.
 */
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

/**
 * Performs a coin animation for a given object.
 * 
 * @param obj The object for which the coin animation is performed.
 * @return Returns 0 if the coin animation is successfully performed.
 */
int	coin_animation(t_object *obj)
{
	char			path[35];
	void			*img;
	int				var;
	static clock_t	time;
	static int		i;

	if (!obj->map->collects)
		return (0);
	if (time == 0 || clock() - time >= 10000)
	{
		i = i * (i != 15);
		ft_strlcpy(path, "bonus/textures/collectible/c__.xpm", 35);
		path[28] = (i / 10) + 48;
		path[29] = (i % 10) + 48;
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

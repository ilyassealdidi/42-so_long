/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:14:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/20 14:37:14 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	*get_image(void *mlx, char c)
{
	void	*img;
	char	*path;
	int		_0;

	if (c == '1')
		path = IMG_WALL;
	else if (c == '0')
		path = IMG_SPACE;
	else if (c == 'P')
		path = IMG_PLAYER;
	else if (c == 'C')
		path = IMG_COLLECTIBLE;
	else
		path = IMG_EXIT;
	img = mlx_xpm_file_to_image(mlx, path, &_0, &_0);
	if (!img)
		raise_error(NULL, errno);
	return (img);
}

void	render_map(t_object *obj)
{
	void	*img;
	char	**map;
	int		x;
	int		y;

	map = obj->map->content;
	y = -1;
	mlx_clear_window(obj->mlx, obj->win);
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			img = get_image(obj->mlx, map[y][x]);
			mlx_put_image_to_window(obj->mlx, obj->win, img,
				x * BLOCK_SIZE, y * BLOCK_SIZE);
			mlx_destroy_image(obj->mlx, img);
		}
	}
}

void	load_window(t_object	*obj)
{
	obj->mlx = mlx_init();
	if (!obj->mlx)
		return (mr_propre(obj), (void)0);
	obj->win = mlx_new_window(obj->mlx, obj->map->width * BLOCK_SIZE,
			obj->map->height * BLOCK_SIZE, WINDOW_TITLE);
	if (!obj->win)
		return (mr_propre(obj), (void)0);
	render_map(obj);
	mlx_hook(obj->win, ON_KEYDOWN, 0, keydown_handler, obj);
	mlx_hook(obj->win, ON_DESTROY, 0, mr_propre, obj);
	mlx_loop(obj->mlx);
}

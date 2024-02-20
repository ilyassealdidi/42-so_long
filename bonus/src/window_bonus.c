/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:14:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 14:55:09 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"


void	print_moves(t_object *obj)
{
	char	*str;
	char	*num;
	int		i;
	int		j;

	i = -1;
	while (++i < 255)
	{
		j = -1;
		while (++j < BLOCK_SIZE)
			mlx_pixel_put(obj->mlx, obj->win, i, j, i << 24);
	}
	num = ft_itoa(obj->player->moves);
	if (!num)
		return (exit(1));
	str = ft_strdup("Number of moves : ");
	if (!str)
		return (exit(1));
	str = ft_strjoin(str, num);
	if (!str)
		return (exit(1));
	mlx_string_put(obj->mlx, obj->win, 5, 5, 0xFFFFFFFF, str);
	free(num);
	free(str);
}

static void	*get_image(void *mlx, char c, int x, int y)
{
	void	*img;
	char	*path;
	int		_0;

	if (c == '1')
		path = IMG_WALL;
	else if (c == '0')
		path = IMG_SPACE;
	else if (c == 'P')
		path = IMG_PLAYER_RIGHT;
	else if (c == 'C')
		path = IMG_COLLECTIBLE;
	else if (c == 'N')
		path = IMG_ENEMY;
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
			img = get_image(obj->mlx, map[y][x],
					x * BLOCK_SIZE, y * BLOCK_SIZE);
			mlx_put_image_to_window(obj->mlx, obj->win, img,
				x * BLOCK_SIZE, y * BLOCK_SIZE);
			mlx_destroy_image(obj->mlx, img);
		}
	}
	print_moves(obj);
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
	mlx_hook(obj->win, ON_DESTROY, 0, mr_propre, obj);
	mlx_hook(obj->win, ON_KEYDOWN, 1, keydown_handler, obj);
	mlx_loop(obj->mlx);
}

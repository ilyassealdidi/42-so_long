/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:14:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/12 12:48:24 by ialdidi          ###   ########.fr       */
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
		return (raise_error(0, errno, obj));
	str = ft_strjoin("Number of moves : ", num);
	if (!str)
		return (raise_error(0, errno, obj));
	mlx_string_put(obj->mlx, obj->win, 5, 5, 0xFFFFFFFF, str);
	free(num);
	free(str);
}

static void	*get_image(t_object *obj, char c)
{
	void	*img;
	char	*path;
	int		var;

	path = (char *)malloc(20);
	if (path)
		raise_error(NULL, errno, obj);
	if (c == '1')
		path = IMG_WALL;
	else if (c == '0')
		path = IMG_SPACE;
	else if (c == 'P')
		path = ft_strlcat(path, );
	else if (c == 'C')
		path = IMG_COLLECTIBLE;
	else if (c == 'N')
		path = IMG_ENEMY;
	else
		path = IMG_EXIT;
	img = mlx_xpm_file_to_image(obj->mlx, path, &var, &var);
	if (!img)
		raise_error(NULL, errno, obj);
	return (img);
}

static void	render_map(t_object *obj)
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

static int	keydown_handler(int key, t_object *obj)
{
	t_point	next_pos;

	obj->keycode = key;
	if (ft_strchr("\001\002\015\065", key))
	{
		if (key == ESC_KEY)
			exiter(obj);
		set_point(&next_pos, -1 * (key == A_KEY) + (key == D_KEY),
			-1 * (key == W_KEY) + (key == S_KEY));
		if (move_player(obj, next_pos))
			render_map(obj);
	}
	return (0);
}

void	load_window(t_object	*obj)
{
	obj->mlx = mlx_init();
	if (!obj->mlx)
		raise_error(0, ENOMEM, obj);
	obj->win = mlx_new_window(obj->mlx, obj->map->width * BLOCK_SIZE,
			obj->map->height * BLOCK_SIZE, WINDOW_TITLE);
	if (!obj->win)
		raise_error(0, ENOMEM, obj);
	render_map(obj);
	mlx_hook(obj->win, ON_KEYDOWN, 0, keydown_handler, obj);
	mlx_hook(obj->win, ON_DESTROY, 0, exiter, obj);
	mlx_loop(obj->mlx);
}

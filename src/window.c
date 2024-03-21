/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:14:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/20 17:21:21 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * Retrieves the image corresponding to the given character.
 *
 * @param obj The object containing the mlx instance.
 * @param c The character representing the type of image to retrieve.
 * @return A pointer to the image.
 */
static void	*get_image(t_object *obj, char c)
{
	void	*img;
	char	*path;
	int		var;

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
	img = mlx_xpm_file_to_image(obj->mlx, path, &var, &var);
	if (!img)
		raise_error(NULL, errno, obj);
	return (img);
}

/**
 * Renders the map on the window.
 * 
 * @param obj The object containing the map and window information.
 */
static void	render_map(t_object *obj)
{
	void	*img;
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
			img = get_image(obj, map[y][x]);
			mlx_put_image_to_window(obj->mlx, obj->win, img,
				x * BLOCK_SIZE, y * BLOCK_SIZE);
			mlx_destroy_image(obj->mlx, img);
		}
	}
}

/**
 * Handles keydown events and performs corresponding actions.
 * 
 * @param key The key code of the pressed key.
 * @param obj A pointer to the t_object structure.
 * @return 0 indicating success.
 */
static int	keydown_handler(int key, t_object *obj)
{
	t_point	next_pos;

	if (ft_strchr("\001\002\015\065", key))
	{
		if (key == ESC_KEY)
			exiter(obj);
		next_pos.x = -1 * (key == A_KEY) + (key == D_KEY);
		next_pos.y = -1 * (key == W_KEY) + (key == S_KEY);
		if (move_player(obj, next_pos))
			render_map(obj);
	}
	return (0);
}

/**
 * Loads the window and initializes the necessary components,
 * Sets up the event handlers, and calls the render_map
 * function to display the map on the window
 * 
 * @param obj The object containing the necessary data for window initialization.
 */
void	load_window(t_object *obj)
{
	obj->mlx = mlx_init();
	if (!obj->mlx)
		raise_error(0, errno, obj);
	obj->win = mlx_new_window(obj->mlx, obj->map->width * BLOCK_SIZE,
			obj->map->height * BLOCK_SIZE, WINDOW_TITLE);
	if (!obj->win)
		raise_error(0, errno, obj);
	render_map(obj);
	mlx_hook(obj->win, ON_KEYDOWN, 0, keydown_handler, obj);
	mlx_hook(obj->win, ON_DESTROY, 0, exiter, obj);
	mlx_loop(obj->mlx);
}

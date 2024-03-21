/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:14:00 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/20 17:04:23 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * @brief Prints the moves on the window.
 * 
 * This function is responsible for printing the number of moves on the window.
 * It fills the window with a color gradient and displays the moves as text.
 * 
 * @param obj A pointer to the object structure.
 */
static void	print_moves(t_object *obj)
{
	char	*str;
	char	*num;
	int		i;
	int		j;

	i = -1;
	while (++i < 130)
	{
		j = -1;
		while (++j < BLOCK_SIZE)
			mlx_pixel_put(obj->mlx, obj->win, i, j, i << 25);
	}
	num = ft_itoa(obj->player->moves);
	if (!num)
		return (raise_error(0, errno, obj));
	str = ft_strdup("Moves: ");
	if (!str)
		return (free(num), raise_error(0, errno, obj));
	str = ft_strjoin(str, num);
	if (!str)
		return (free(num), raise_error(0, errno, obj));
	mlx_string_put(obj->mlx, obj->win, 5, 5, 0xFFFFFFFF, str);
	free(num);
	free(str);
}

/**
 * Retrieves the image corresponding to the given character and direction.
 * 
 * @param obj The object containing the mlx instance.
 * @param c The character representing the object in the game map.
 * @param direction The direction of the player.
 * @return A pointer to the image corresponding to the character, 
 * or NULL if no image is found.
 */
static void	*get_image(t_object *obj, char c, int direction)
{
	void	*img;
	int		var;

	if (c == '1')
		img = IMG_WALL;
	else if (c == '0')
		img = IMG_SPACE;
	else if (c == 'P' && direction == W_KEY)
		img = IMG_PLAYER_W;
	else if (c == 'P' && direction == A_KEY)
		img = IMG_PLAYER_A;
	else if (c == 'P' && direction == S_KEY)
		img = IMG_PLAYER_S;
	else if (c == 'P' && direction == D_KEY)
		img = IMG_PLAYER_D;
	else if (c == 'N')
		img = IMG_ENEMY;
	else if (c == 'E')
		img = IMG_EXIT;
	else
		return (NULL);
	img = mlx_xpm_file_to_image(obj->mlx, (char *)img, &var, &var);
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
			img = get_image(obj, map[y][x], obj->keycode);
			if (img)
			{
				mlx_put_image_to_window(obj->mlx, obj->win, img,
					x * BLOCK_SIZE, y * BLOCK_SIZE);
				mlx_destroy_image(obj->mlx, img);
			}
		}
	}
	print_moves(obj);
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

	obj->keycode = key;
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
void	load_window(t_object	*obj)
{
	obj->mlx = mlx_init();
	if (!obj->mlx)
		raise_error(0, errno, obj);
	obj->win = mlx_new_window(obj->mlx, obj->map->width * BLOCK_SIZE,
			obj->map->height * BLOCK_SIZE, WINDOW_TITLE);
	if (!obj->win)
		raise_error(0, errno, obj);
	render_map(obj);
	mlx_hook(obj->win, ON_KEYDOWN, 1, keydown_handler, obj);
	mlx_hook(obj->win, ON_DESTROY, 0, exiter, obj);
	mlx_loop_hook(obj->mlx, coin_animation, obj);
	mlx_loop(obj->mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:33:50 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/20 02:38:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * Initializes the player object with the given coordinates.
 * 
 * @param obj The object containing the player.
 * @param x The x-coordinate of the player's position.
 * @param y The y-coordinate of the player's position.
 */
static void	init_player(t_object *obj, int x, int y)
{
	t_player	*p;

	p = (t_player *)malloc(sizeof(t_player));
	if (!p)
		return (raise_error(NULL, errno, obj));
	set_point(&p->position, x, y);
	p->moves = 0;
	obj->player = p;
}

/**
 * Checks if a block in the map is valid.
 * 
 * @param obj The object containing the map and player information.
 * @param i The row index of the block.
 * @param j The column index of the block.
 * @return 1 if the block is valid, 0 otherwise.
 */
static int	is_valid_block(t_object *obj, int i, int j)
{
	char		block;

	block = obj->map->content[i][j];
	if ((i == 0 || i == obj->map->height - 1
			|| j == 0 || j == obj->map->width - 1) && block != '1')
		return (NOT_VALID);
	if (block == 'P' && !obj->player)
		init_player(obj, j, i);
	else if (block == 'C')
		obj->map->collects++;
	else if (block == 'E' && !obj->map->exit.x)
		set_point(&obj->map->exit, i, j);
	else if (block == 'N')
		obj->map->enemies++;
	else if (block == 'E' || block == 'P')
		return (NOT_VALID);
	return (VALID);
}

/**
 * @brief Initializes the items in the game object.
 * 
 * This function iterates over the map content and checks if each block is valid.
 * If any block is not valid, it returns the NOT_VALID constant.
 * 
 * @param obj The game object.
 * @return Returns NOT_VALID if any block is not valid or if some elements are
 * duplicated or missed, otherwise returns 1.
 */
static int	init_items(t_object	*obj)
{
	int		i;
	int		j;

	i = -1;
	while (obj->map->content[++i])
	{
		j = -1;
		while (obj->map->content[i][++j])
		{
			if (!is_valid_block(obj, i, j))
				return (NOT_VALID);
		}
	}
	return (obj->player && obj->map->exit.x && obj->map->collects
		&& obj->map->enemies);
}

/**
 * @brief Floods the map with a fill algorithm to check whether
 * the Exit and Collectibles are reachable.
 * 
 * @param obj A pointer to a structure of type `t_object` representing
 * the game object.
 * @return Returns 0 if there are 'E' or 'C' characters in the map, 1 otherwise.
 */
static int	flood_map(t_object	*obj)
{
	int		i;
	char	**map;
	char	*line;

	map = (char **)malloc(sizeof(char *) * (obj->map->height + 1));
	if (!map)
		raise_error(NULL, errno, obj);
	i = -1;
	while (obj->map->content[++i])
	{
		line = ft_strdup(obj->map->content[i]);
		if (!line)
			(free_array(map), raise_error(NULL, errno, obj));
		map[i] = line;
		map[i + 1] = NULL;
	}
	flood_fill(map, obj->player->position.y, obj->player->position.x);
	i = -1;
	while (++i < obj->map->height)
	{
		if (ft_strpbrk(map[i], "EC"))
			return (free_array(map), 0);
	}
	return (free_array(map), 1);
}

/**
 * Parses the map file and initializes the game object.
 *
 * This function checks whether the given path parameter is a valid file and
 * initializes the necessary elements of the game object, including the player
 * and the map.
 *
 * @param obj The game object to be initialized.
 * @param path The path to the map file.
 */
void	parse(t_object *obj, char *path)
{
	int	fd;

	fd = is_valid_file(path);
	if (!fd)
		raise_error(0, errno, NULL);
	obj->map = init_map(fd);
	if (!init_items(obj) || !flood_map(obj))
		raise_error("Invalid map!!", 0, obj);
}

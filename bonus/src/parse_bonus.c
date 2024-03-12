/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:33:50 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/12 12:39:57 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"


static void	init_player(t_object *obj, int x, int y)
{
	t_player	*p;

	p = (t_player *)malloc(sizeof(t_player));
	if (!p)
		return (raise_error(NULL, errno, obj));
	set_point(&p->last_position, x, y);
	p->moves = 0;
	obj->player = p;
}

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
	else if (block == 'E' || block == 'P')
		return (NOT_VALID);
	return (VALID);
}

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
	return (obj->player && obj->map->exit.x && obj->map->collects);
}

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
		if (ft_strpbrk(map[i], "ECN"))
			return (free_array(map), 0);
	}
	return (free_array(map), 1);
}

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

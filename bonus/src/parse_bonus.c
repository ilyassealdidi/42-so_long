/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:33:50 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 14:37:41 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"


static void	init_player(t_object *obj, int x, int y)
{
	t_player	*p;

	p = (t_player *)malloc(sizeof(t_player));
	if (!p)
		return (raise_error(NULL, errno));
	p->position.x = x;
	p->position.y = y;
	p->moves = 0;
	obj->player = p;
}

static int	is_valid_block(t_object *obj, int i, int j)
{
	char		block;
	static int	exit;

	block = obj->map->content[i][j];
	if ((i == 0 || i == obj->map->height - 1
			|| j == 0 || j == obj->map->width - 1)
		&& block != '1')
		return (NOT_VALID);
	if (block == 'P' && !obj->player)
		init_player(obj, j, i);
	else if (block == 'C')
		obj->map->collects++;
	else if (block == 'E' && !obj->map->exit.x)
	{
		obj->map->exit.x = i;
		obj->map->exit.y = j;
	}
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

	flood_fill(obj->map->content_copy,
		obj->player->position.y, obj->player->position.x);
	i = -1;
	while (++i < obj->map->height)
	{
		if (ft_strpbrk(obj->map->content_copy[i], "ECN"))
			return (0);
	}
	return (1);
}

void	parse(t_object *obj, char *path)
{
	obj->map = init_map(path);
	if (!init_items(obj))
	{
		mr_propre(obj);
		raise_error("Invalid map!!", 0);
	}
	if (!flood_map(obj))
	{
		mr_propre(obj);
		raise_error("The player won't be able to reach some postions!!", 0);	
	}
}

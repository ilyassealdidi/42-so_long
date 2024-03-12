/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:39:52 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/12 12:41:18 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	is_movable(t_object *obj, char c)
{
	t_player	*p;

	p = obj->player;
	if (c == 'C')
		obj->map->collects--;
	else if ((c == 'E' && !obj->map->collects) || c == 'N')
		return (1);
	else if (c != '0')
		return (0);
	obj->map->content[p->position.y][p->position.x] = '0';
	return (1);
}

int	move_player(t_object *obj, t_point pos)
{
	t_player	*p;
	char		**map;

	p = obj->player;
	map = obj->map->content;
	if (is_movable(obj, map[p->position.y + pos.y][p->position.x + pos.x]))
	{
		//set_point(&p->last_position, p->position.x, p->position.y);
		set_point(&p->position, p->position.x + pos.x, p->position.y + pos.y);
		ft_printf("%d Moves\n", ++p->moves);
		if (map[p->position.y][p->position.x] == 'E')
		{
			ft_printf("%s", VICTORY_MESSAGE);
			exiter(obj);
		}
		if (map[p->position.y][p->position.x] == 'N')
		{
			ft_printf("%s", LOSS_MESSAGE);
			exiter(obj);
		}
		map[p->position.y][p->position.x] = 'P';
		return (1);
	}
	return (0);
}

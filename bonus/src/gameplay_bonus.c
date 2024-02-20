/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:39:52 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 14:43:34 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

t_object	*g_obj;

static int	check_next_block(char c)
{
	t_player	*p;

	p = g_obj->player;
	if (c == 'C')
		g_obj->map->collects--;
	else if (c == 'E' && !g_obj->map->collects)
	{
		ft_putstr_fd(VICTORY_MESSAGE, 1);
		exit(0);
	}
	else if (c == 'N')
	{
		ft_putstr_fd(LOSS_MESSAGE, 1);
		mr_propre(g_obj);
	}
	else if (c != '0')
		return (0);
	g_obj->map->content[p->position.y][p->position.x] = '0';
	return (1);
}

static void	move_player(char *pos)
{
	t_player	*p;
	char		**map;

	p = g_obj->player;
	map = g_obj->map->content;
	if (check_next_block(map[p->position.y - pos[1]][p->position.x + pos[0]]))
	{
		p->position.x += pos[0];
		p->position.y -= pos[1];
		g_obj->map->content[p->position.y][p->position.x] = 'P';
		ft_putnbr_fd(++p->moves, 1);
		ft_putstr_fd(" Move(s)\n", 1);
		render_map(g_obj);
	}
}

int	keydown_handler(int key, t_object *object)
{
	char	new_pos[2];

	g_obj = object;
	if (key == ESC_KEY)
		mr_propre(g_obj);
	else if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY)
	{
		if (key == A_KEY)
			new_pos[0] = -1;
		else if (key == S_KEY)
			new_pos[1] = -1;
		else if (key == D_KEY)
			new_pos[0] = 1;
		else
			new_pos[1] = 1;
		move_player(new_pos);
	}
	return (0);
}

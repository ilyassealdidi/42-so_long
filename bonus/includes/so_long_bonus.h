/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:39:15 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 14:12:54 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <mlx.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"
# include "dictionnary_bonus.h"

enum	e_keys
{
	A_KEY,
	S_KEY,
	D_KEY,
	W_KEY = 13,
	ESC_KEY = 53,
};

enum	e_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_DESTROY = 17
};

typedef struct s_point
{
	unsigned int	x;
	unsigned int	y;
}	t_point;

typedef struct s_map
{
	char			*path;
	char			**content;
	char			**content_copy;
	unsigned int	height;
	unsigned int	width;
	unsigned int	collects;
	t_point			exit;
}	t_map;

typedef struct s_player
{
	t_point			position;
	unsigned int	moves;
}	t_player;

typedef struct s_object
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
}	t_object;

void	flood_fill(char	**map, int i, int j);
void	raise_error(char *msg, int err);
int		mr_propre(t_object *obj);
t_map	*init_map(char *path);
void	parse(t_object *object, char *path);
void	load_window(t_object	*obj);
void	render_map(t_object *obj);
int		keydown_handler(int keycode, t_object *object);

#endif

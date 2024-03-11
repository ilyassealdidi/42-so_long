/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:39:15 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/11 14:34:35 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"
# include "dictionnary.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char			**content;
	char			**content_copy;
	int				height;
	int				width;
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

/* Utils */
void	flood_fill(char	**map, int i, int j);
void	raise_error(char *msg, int err, t_object *obj);
int		exiter(t_object *obj);
int		is_valid_file(char *filename);

/* Parsing */
void	parse(t_object *object, char *path);
/* Map */
t_map	*init_map(int fd);
/* Graphics */
void	load_window(t_object	*obj);
/* Gameplay */
int		move_player(t_object *obj, t_point pos);

#endif
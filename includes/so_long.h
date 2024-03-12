/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:39:15 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/12 11:25:02 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <errno.h>
# include <fcntl.h>
# include "../helpers/libft/libft.h"
# include "../helpers/ft_printf/includes/libftprintf.h"
# include "dictionnary.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char			**content;
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
char	*get_next_line(int fd);
void	free_array(char **arr);
void	set_point(t_point *p, int x, int y);
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
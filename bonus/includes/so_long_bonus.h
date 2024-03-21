/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:39:15 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/21 12:07:51 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <mlx.h>
# include <errno.h>
# include <time.h>
# include <fcntl.h>
# include "dictionnary_bonus.h"
# include "../../lib/libft/libft.h"
# include "../../lib/ft_printf/includes/libftprintf.h"

/**
 * @struct t_point
 * @brief Represents a point in a 2D coordinate system.
 */
typedef struct s_point
{
	int	x; /**< The x-coordinate of the point. */
	int	y; /**< The y-coordinate of the point. */
}	t_point;

/**
 * @struct t_map
 * @brief Represents a map in the game.
 *
 * The `t_map` structure contains information about the map,
 * including its content,
 * height, width, number of collects, and the exit point.
 */
typedef struct s_map
{
	char			**content;		/**< The content of the map. */
	int				height;			/**< The height of the map. */
	int				width;			/**< The width of the map. */
	unsigned int	collects;		/**< The number of collects in the map. */
	unsigned int	enemies;		/**< The number of enemies in the map. */
	t_point			exit;			/**< The exit point of the map. */
}	t_map;

/**
 * @struct t_player
 * @brief Represents a player in the game.
 *
 * The `t_player` structure holds information about the player's
 * position and the number of moves made.
 */
typedef struct s_player
{
	t_point			position;	/**< The position of the player. */
	unsigned int	moves;		/**< The number of moves made by the player. */
}	t_player;

/**
 * @struct s_object
 * @brief Represents an object in the game.
 * 
 * This structure holds the necessary information for an object in the game,
 * including the MLX context, window, map, and player.
 */
typedef struct s_object
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	*player;
	int			keycode;
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
int		coin_animation(t_object *obj);
/* Gameplay */
int		move_player(t_object *obj, t_point pos);

#endif

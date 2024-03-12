/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:11 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/12 14:08:04 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONNARY_H
# define DICTIONNARY_H

# define WINDOW_TITLE "Sooo loooooong!"
# define VICTORY_MESSAGE "Congratulations!!"
# define LOSS_MESSAGE "Game over!!"

# define IMG_SPACE "textures/SPACE.xpm"
# define IMG_WALL "textures/WALL.xpm"
# define IMG_PLAYER "textures/PLAYER.xpm"
# define IMG_COLLECTIBLE "textures/COLLECTIBLE.xpm"
# define IMG_EXIT "textures/EXIT.xpm"
# define IMG_PLAYER_W "textures/PLAYER_W.xpm"
# define IMG_PLAYER_A "textures/PLAYER_A.xpm"
# define IMG_PLAYER_S "textures/PLAYER_S.xpm"
# define IMG_PLAYER_D "textures/PLAYER_D.xpm"
# define IMG_ENEMY "textures/ENEMY.xpm"

# define BLOCK_SIZE 32

# define VALID 1
# define NOT_VALID 0

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

#endif

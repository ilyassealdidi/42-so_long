/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:11 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/11 13:49:48 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONNARY_H
# define DICTIONNARY_H

# define WINDOW_TITLE "Sooo loooooong!"
# define WIN_MESSAGE "Congratulations!!"

# define IMG_SPACE "textures/SPACE.xpm"
# define IMG_WALL "textures/WALL.xpm"
# define IMG_PLAYER "textures/PLAYER.xpm"
# define IMG_COLLECTIBLE "textures/COLLECTIBLE.xpm"
# define IMG_EXIT "textures/EXIT.xpm"

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

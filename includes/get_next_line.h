/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:08:22 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/15 10:01:31 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	2000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*create_line(char *str);
void	read_line(int fd, char **str);
void	update_line(char **str);
char	*get_next_line(int fd);

#endif
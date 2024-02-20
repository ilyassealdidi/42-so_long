/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:25:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 16:26:50 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	is_valid_file(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".ber", 4))
		return (NOT_VALID);
	return (ft_strlen(ext) == 4);
}



int	main(int argc, char **av)
{
	t_object	obj;

	if (argc != 2)
		raise_error("Invalid format, try: [./program] [map_filename]", 0);
	if (!is_valid_file(av[1]))
		raise_error("Allowed extension: *.ber", 0);
	parse(&obj, av[1]);
	load_window(&obj);
}


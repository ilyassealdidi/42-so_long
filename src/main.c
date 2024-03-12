/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:25:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/12 11:41:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (1)
	{
		free(arr[++i]);
		if (!arr[i])
			break ;
	}
	free(arr);
}

int	is_valid_file(char *path)
{
	int		fd;
	int		len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".ber", 4))
		raise_error("Allowed extension: *.ber", 0, NULL);
	fd = open(path, O_RDONLY);
	return (fd * (fd != -1));
}

int	main(int argc, char **av)
{
	t_object	obj;

	if (argc != 2)
		raise_error("Invalid format, try: [./program] [map_filename]", 0, NULL);
	parse(&obj, av[1]);
	load_window(&obj);
}

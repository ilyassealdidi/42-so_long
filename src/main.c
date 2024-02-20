/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:25:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/02/19 16:10:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	f(void)
{
	system("leaks so_long");
}

int	main(int argc, char **av)
{
	t_object	obj;

	atexit(f);
	if (argc != 2)
		raise_error("Invalid format, try: [./program] [map_filename]", 0);
	if (!is_valid_file(av[1]))
		raise_error("Allowed extension: *.ber", 0);
	parse(&obj, av[1]);
	load_window(&obj);
}


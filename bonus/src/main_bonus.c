/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:25:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/03/20 16:00:03 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * Initializes the game object.
 * 
 * @return A pointer to the newly created object.
 */
static t_object	*object_init(void)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		raise_error(0, errno, NULL);
	obj->map = NULL;
	obj->player = NULL;
	obj->mlx = NULL;
	obj->win = NULL;
	obj->keycode = S_KEY;
	return (obj);
}

/**
 * @brief Destroys an object and frees the allocated memory.
 * 
 * This function frees the memory allocated for the object's map, player,
 * and the window created using MLX library.
 * 
 * @param obj The object to be destroyed.
 */
void	destroy_object(t_object *obj)
{
	free_array(obj->map->content);
	free(obj->map);
	free(obj->player);
	if (obj->win)
		mlx_destroy_window(obj->mlx, obj->win);
}

/**
 * @brief Exits the program and cleans up the object.
 *
 * This function destroys the given object and exits the program
 * with a status code of 0.
 *
 * @param obj The object to be destroyed.
 * @return Always returns 0.
 */
int	exiter(t_object *obj)
{
	destroy_object(obj);
	exit(0);
	return (0);
}

/**
 * Function to raise an error and exit the program.
 *
 * @param msg The error message to be displayed.
 * @param err The error code.
 * @param obj The object to be destroyed (optional).
 */
void	raise_error(char *msg, int err, t_object *obj)
{
	ft_printf("Error\n");
	if (msg)
		ft_printf("%s", msg);
	if (err)
		ft_printf("%s", strerror(err));
	if (obj)
		destroy_object(obj);
	exit(1);
}

int	main(int argc, char **av)
{
	t_object	*obj;

	if (argc != 2)
		raise_error("Invalid format, try: [./program] [map_filename]", 0, NULL);
	obj = object_init();
	parse(obj, av[1]);
	load_window(obj);
}

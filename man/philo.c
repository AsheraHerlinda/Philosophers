/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asherlin <asherlin@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 04:00:00 by asherlin          #+#    #+#             */
/*   Updated: 2022/06/23 12:56:29 by asherlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_data *data);

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (error_msg("Incorrect nums of arguments", 0));
	data = (t_data *) malloc (sizeof (t_data));
	if (!data)
		return (error_msg("data malloc error", errno));
	if ((data_init(data, &philos, argc, argv) == -1))
	{
		free_all(data, &philos);
		return (-1);
	}
	if ((simulation(data, philos) == -1))
	{
		free_all(data, &philos);
		return (-1);
	}
	free_all(data, &philos);
	return (0);
}

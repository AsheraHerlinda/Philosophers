/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asherlin <asherlin@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 04:00:00 by asherlin          #+#    #+#             */
/*   Updated: 2022/05/28 14:20:39 by asherlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_data *data);

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (error_msg("Incorrect nums of arguments", 0));
	data = (t_data *) malloc (sizeof (t_data));
	if (!data)
		return (error_msg("data malloc error", errno));
	if ((data_init(data, argc, argv) == -1))
	{
		free_data(data, NULL, 0);
		return (-1);
	}
	simulation(data);
	checker(data);
	free_data(data, NULL, errno);
	return (0);
}

void	checker(t_data *data)
{
	int	i = 0;

	printf("%d\n", data->n_phils);
	printf("%d\n", data->n_forks);
	printf("%d\n", data->t_die);
	printf("%d\n", data->t_eat);
	printf("%d\n", data->t_sleep);
	printf("%d\n\n", data->must_eat);
	while (i < data->n_phils)
	{
		printf("%d\n", data->philos[i].posit);
		i++;
	}
}
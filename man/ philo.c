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

int	main(int argc, char argv)
{
	t_data	*data;

	if (argc < 5 || argv > 6)
		if ((error_msg("Incorrect nums of arguments", 0) == -1))
			return (-1);
	if ((data_init(data)) == -1)
		return (-1);		
	return (0);
}

static t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (!data)
		if ((error_msg("data malloc error", 0) == -1))
			return (-1);
	
}
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

static int	data_init(t_data **data, int argc, char **argv);
static int	ft_atoi(const char *nptr);

int	main(int argc, char argv)
{
	t_data	*data;

	if (argc < 5 || argv > 6)
		return (error_msg("Incorrect nums of arguments", 0));
	if ((data_init(&data)) == -1)
		free_data(data, NULL, 0);		
	return (0);
}

static int	data_init(t_data **data, int argc, char **argv)
{
	t_data	*tmp;

	tmp = (t_data *) malloc (sizeof (t_data));
	if (!tmp)
		return (error_msg("data malloc error", errnum));
	data->n_phils = ft_atoi(argv[1]);
	data->n_forks = data->n_phils;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->must_eat = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (data->n_phils == -1 || data->n_phils > 250 || data->t_die == -1 || \
		data->t_eat== -1 || data->t_sleep == -1 || data->must_eat == -1)
		return (error_msg("invalid args", 0));
	data->philos = NULL;
	data->m_forks = NULL;
	data->m_printf = NULL;
	data->t_begin = 0;
	data->checker = NULL;
	return (1);
}

static int	ft_atoi(const char *s)
{
	long int	i;
	int			max;
	int			res;

	i = 0;
	max = 2147483647;
	res = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || \
			s[i] == '\f' || s[i] == '\v' || s[i] == ' ')
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			return (-1);
		i++;
	}
	while (48 <= s[i] && s[i] <= 57)
	{
		res = (res * 10) + (s[i] - '0');
		if (res > max)
			return (-1);
		i++;
	}
	if (s[i] != '\0')
		return (-1);
	return ((int)res);
}

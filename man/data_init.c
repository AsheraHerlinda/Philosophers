/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asherlin <asherlin@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 04:00:00 by asherlin          #+#    #+#             */
/*   Updated: 2022/06/23 12:56:29 by asherlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	mutex_init(t_data *data);
static int	philos_init(t_data *data, t_philo **philos);
static int	ft_atoi(const char *nptr);

int	data_init(t_data *data, t_philo **philos, int argc, char **argv)
{
	data->n_phils = ft_atoi(argv[1]);
	data->n_forks = data->n_phils;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->must_eat = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->m_forks = NULL;
	if (data->n_phils <= 0 || data->n_phils > 200 || data->t_die == -1 || \
		data->t_eat == -1 || data->t_sleep == -1 || data->must_eat == -1)
		return (error_msg("invalid args", 0));
	data->t_begin = 0;
	data->monitoring = 0;
	data->finish = 0;
	if (mutex_init(data) == -1 || philos_init(data, philos) == -1)
		return (-1);
	return (0);
}

static int	ft_atoi(const char *s)
{
	int			i;
	int			max;
	long int	res;

	i = 0;
	max = 2147483647;
	res = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || \
			s[i] == '\f' || s[i] == '\v' || s[i] == ' ' || s[i] == '+')
		i++;
	if (s[i] == '-')
		return (-1);
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

static int	mutex_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->m_printf, NULL))
		return (error_msg("mutex_printf_init_error", errno));
	data->m_forks = (t_mutex *)malloc(sizeof(t_mutex) * data->n_forks);
	if (!data->m_forks)
		return (error_msg("mutex_forks_malloc_error", errno));
	i = 0;
	while (i < data->n_forks)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL))
			return (error_msg("mutex_forks_init_error", errno));
		i++;
	}
	return (0);
}

static int	philos_init(t_data *data, t_philo **philos)
{
	int		i;
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo) * data->n_phils);
	if (!tmp)
		return (error_msg("philos_malloc_error", errno));
	i = 0;
	while (i < data->n_phils)
	{
		tmp[i].posit = i + 1;
		tmp[i].eat_cnt = 0;
		tmp[i].t_last_eat = 0;
		if (i == 0)
		{
			tmp[i].left_fork = &data->m_forks[data->n_phils - 1];
			tmp[i].right_fork = &data->m_forks[i];
		}
		else
		{
			tmp[i].left_fork = &data->m_forks[i - 1];
			tmp[i].right_fork = &data->m_forks[i];
		}
		tmp[i].data = data;
		i++;
	}
	*philos = tmp;
	return (0);
}

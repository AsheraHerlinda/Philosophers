/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asherlin <asherlin@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 04:00:00 by asherlin          #+#    #+#             */
/*   Updated: 2022/06/23 12:56:29 by asherlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*actions(void *philo);
void	*monitoring(void *philo);
void	print_action(t_philo *philo, char *str);
void	execution(t_data *data, long long t);

int	simulation(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->t_begin = get_time();
	while (i < data->n_phils)
	{
		philos[i].t_last_eat = get_time();
		if (pthread_create(&philos[i].philo_pth, NULL, &actions, &philos[i]))
			return (error_msg("philo pth_crt error", errno));
		pthread_detach(philos[i].philo_pth);
		usleep(50);
		i++;
	}
	if (pthread_create(&data->monitoring, NULL, &monitoring, philos))
		return (error_msg("monitor pth_crt error", errno));
	if (pthread_join(data->monitoring, NULL))
		return (error_msg("monitor join error", errno));
	i = 0;
	while (i < data->n_forks)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->m_printf);
	return (0);
}

void	*actions(void *philo)
{
	t_philo	*pers;

	pers = (t_philo *)philo;
	while (!pers->data->finish)
	{
		print_action(pers, "thinking");
		pthread_mutex_lock(pers->left_fork);
		print_action(pers, "left fork");
		pthread_mutex_lock(pers->right_fork);
		print_action(pers, "right fork");
		print_action(pers, "eating");
		execution(pers->data, pers->data->t_eat);
		pers->t_last_eat = get_time();
		pthread_mutex_unlock(pers->right_fork);
		pthread_mutex_unlock(pers->left_fork);
		if (!pers->data->finish)
			pers->eat_cnt++;
		print_action(pers, "sleeping");
		execution(pers->data, pers->data->t_sleep);
	}
	return (0);
}

void	*monitoring(void *philo)
{
	t_philo	*p;
	int		i;
	int		all_ate;

	p = (t_philo *)philo;
	while (!p->data->finish)
	{
		all_ate = 0;
		i = 0;
		while (i < p->data->n_phils)
		{
			if (get_time() - p[i].t_last_eat > p->data->t_die)
			{
				print_action(&p[i], "died");
				p->data->finish = 1;
				break ;
			}
			if (p->data->must_eat > 0 && p[i].eat_cnt >= p->data->must_eat)
				all_ate++;
			i++;
		}
		if (all_ate == p->data->n_phils)
			p->data->finish = 1;
	}
	return (0);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->m_printf);
	if (!philo->data->finish)
		printf("%lld %d %s\n", get_time() - philo->data->t_begin, \
					philo->posit, str);
	pthread_mutex_unlock(&philo->data->m_printf);
}

void	execution(t_data *data, long long t)
{
	long long	curr_t;

	curr_t = get_time();
	while (!data->finish)
	{
		if ((get_time() - curr_t) >= t)
			break ;
		usleep(500);
	}
}

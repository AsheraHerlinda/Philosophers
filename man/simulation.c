#include "../inc/philo.h"

void	*eating(void *philo);
void	*monitoring(void *data);

int	simulation(t_data *data)
{
	int	i;

	i = 0;
	data->t_begin = get_time();
	while (i < data->n_phils)
	{
		data->philos[i].t_last_eat = get_time();
		if (pthread_create(data->philos[i].philo_pth, NULL, &eating, \
			&data->philos[i]))
			return (error_msg("philo pth_crt error", errno));
		pthread_detach(data->philos[i].philo_pth);
		usleep(50);
		i++;
	}
	if (pthread_create(data->checker, NULL, &monitoring, data))
		return (error_msg("monitor pth_crt error", errno));
	if (pthread_join(data->checker, NULL))
		return (error_msg("monitor join error", errno));
	i = 0;
	while (i < data->n_forks)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->m_printf);
}

void	*eating(void *philo)
{

}

void	*monitoring(void *data)
{
	
}
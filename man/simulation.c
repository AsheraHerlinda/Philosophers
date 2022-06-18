#include "../inc/philo.h"

void	*eating(void *philo);

int	simulation(t_data *data)
{
	int i;

	i = 0;
	data->t_begin = get_time();
	while (i < data->n_phils)
	{
		data->philos[i].t_last_eat = get_time();
		if (pthread_create(data->philos[i].philo_pth, NULL, &eating, &data->philos[i]))
			return (error_msg("philo pht_crt error", errno));
		pthread_detach(data->philos[i].philo_pth);
		usleep(50);
	}
}

void	*eating(void *philo)
{

}
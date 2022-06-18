#include "../inc/philo.h"

static int	mutex_init(t_data *data);
static int	philos_init(t_data *data);
static int	ft_atoi(const char *nptr);

int	data_init(t_data *data, int argc, char **argv)
{
	data->n_phils = ft_atoi(argv[1]);
	data->n_forks = data->n_phils;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->must_eat = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->philos = NULL;
	data->m_forks = NULL;
	if (data->n_phils == -1 || data->n_phils > 200 || data->t_die == -1 || \
		data->t_eat == -1 || data->t_sleep == -1 || data->must_eat == -1)
		return (error_msg("invalid args", 0));
	data->t_begin = 0;
	data->checker = NULL;
	if (mutex_init(data) == -1 || philos_init(data) == -1)
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

static int	philos_init(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_phils);
	if (!data->philos)
		return (error_msg("philos_malloc_error", errno));
	i = 0;
	while (i < data->n_phils)
	{
		data->philos[i].posit = i + 1;
		data->philos[i].eat_cnt = 0;
		data->philos[i].t_last_eat = 0;
		if (i == 0)
		{
			data->philos[i].left_fork = &data->m_forks[data->n_phils - 1];
			data->philos[i].right_fork = &data->m_forks[i];
		}
		else
		{
			data->philos[i].left_fork = &data->m_forks[i - 1];
			data->philos[i].right_fork = &data->m_forks[i];
		}
		i++;
	}
	return (0);
}

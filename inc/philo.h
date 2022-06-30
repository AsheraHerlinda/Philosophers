/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asherlin <asherlin@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 04:00:00 by asherlin          #+#    #+#             */
/*   Updated: 2022/06/23 12:55:38 by asherlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	int				n_phils;
	int				n_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	t_mutex			*m_forks;
	t_mutex			m_printf;
	long long int	t_begin;
	pthread_t		monitoring;
	int				finish;
}	t_data;

typedef struct s_philo
{
	int				posit;
	int				eat_cnt;
	long long int	t_last_eat;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	pthread_t		philo_pth;
	t_data			*data;
}	t_philo;

int			data_init(t_data *data, t_philo **philos, int argc, char **argv);
int			simulation(t_data *data, t_philo *philos);

long long	get_time(void);
int			error_msg(char *errmsg, int errnum);
void		free_all(t_data *data, t_philo **philos);

#endif
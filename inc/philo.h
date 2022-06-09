/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asherlin <asherlin@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 04:00:00 by asherlin          #+#    #+#             */
/*   Updated: 2022/05/26 22:10:46 by asherlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t mutex;

typedef struct s_philo
{
	int				posit;
	int				eat_cnt;
	long long int	t_last_eat;
	mutex			*left_fork;
	mutex			*right_fork;
	pthread_t		philo_pth;		
}	t_philo;

typedef struct s_data
{
	int				n_phils;
	int				n_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	t_philo			**philos;
	mutex			*m_forks;
	mutex			m_printf;
	long long int	t_begin;
	pthread_t		checker;
}	t_data;

int		error_msg(char *errmsg, int errnum);
void	free_data(t_data *data, char *errmsg, int errnum);

#endif
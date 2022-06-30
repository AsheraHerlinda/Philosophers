/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_programm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asherlin <asherlin@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 04:00:00 by asherlin          #+#    #+#             */
/*   Updated: 2022/06/23 12:56:29 by asherlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static void	free_arr(t_philo **arr);
static void	ft_putendl_fd(char *s, int fd);
static void	ft_putstr_fd(char *s, int fd);

int	error_msg(char *errmsg, int errnum)
{
	if (errmsg != 0 || errnum != 0)
		ft_putendl_fd("Error", 2);
	if (errmsg != 0)
		ft_putstr_fd(errmsg, 2);
	if (errmsg != 0 && errnum != 0)
		ft_putstr_fd(": ", 2);
	if (errnum != 0)
		ft_putstr_fd(strerror(errnum), 2);
	if (errmsg != 0 || errnum != 0)
	{
		ft_putendl_fd("", 2);
		return (-1);
	}
	return (0);
}

void	free_all(t_data *data, t_philo **philos)
{
	(void) philos;
	// int	i;

	// i = 0;
	// while (i < data->n_phils)
	// {
	// 	free(philos[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < data->n_phils)
	// 	free(data->m_forks[i++]);
	// free(philos);
	free(data);
}

// static void	free_arr(t_philo **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }

static void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
	return ;
}

static void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:09:11 by asajid            #+#    #+#             */
/*   Updated: 2023/10/19 15:29:17 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	check_overflow(t_data *data)
{
	if (data->philo_num < 1 || data->philo_num > 200 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (-1);
	if (data->max_eat_num == 0 || data->max_eat_num < -1)
		return (-1);
	return (0);
}

int	check_error(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (-1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf(" Invalid Arguments ");
				return (-1);
			}
			return (0);
		}
	}
	return (0);
}

int	check_philo_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->phil_mutex->death_mutex);
	if (philo->value->dead_philo == 1)
	{
		pthread_mutex_unlock(&philo->phil_mutex->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->phil_mutex->death_mutex);
	return (0);
}

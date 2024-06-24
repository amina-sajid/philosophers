/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajid <asajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:12:54 by asajid            #+#    #+#             */
/*   Updated: 2023/10/19 17:01:08 by asajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
	return (0);
}

int	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_destroy(&data->data_mutex->mutex[i]) != 0)
			return (1);
		if (pthread_mutex_destroy(&data->data_mutex->fork_mutex[i]) != 0)
			return (1);
		if (pthread_mutex_destroy(&data->data_mutex->sign_mutex[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->data_mutex->death_mutex) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->data_mutex->last_meal_mutex) != 0)
		return (1);
	if (pthread_mutex_destroy(&data->data_mutex->print_mutex) != 0)
		return (1);
	return (0);
}

void	free_data(t_data *data, t_mutex *mutex)
{
	ft_destroy_mutex(data);
	free_mut(mutex);
	free(data->greedy_state);
	free(data->fork_state);
	free(data->philo);
	free(data);
}

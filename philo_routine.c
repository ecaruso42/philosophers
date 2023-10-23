/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:34:55 by ecaruso           #+#    #+#             */
/*   Updated: 2023/10/23 19:33:16 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
void	*routine(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	philo->time_left = philo->env->time_to_die + get_time();
}

int	play(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->number_of_philosophers)
	{
		if (pthread_create(&env->table[i].philo, NULL, &routine, (
					void *)&env->table[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < env->number_of_philosophers)
	{
		if (pthread_join(env->table[i].philo, NULL))
			return (1);
		i++;
	}
	free(env->table);
	return (0);
}

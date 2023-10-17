/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:41:41 by ecaruso           #+#    #+#             */
/*   Updated: 2023/10/17 21:53:33 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philo(t_env *env, int i)
{
	env->table[i].id = i;
	env->table[i].is_alive = 1;
	env->table[i].is_eating = 0;
	env->table[i].eat_count = 0;
}

int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	init(t_env *env, int argc, char **argv)
{
	int	i;
	
	env->number_of_philosophers = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	//origin_time_missing;
	if (argc == 6)
		env->max_eat = ft_atoi(argv[5]);
	else
		env->max_eat = -1;
	env->table = (t_philo *)malloc(sizeof(t_philo)
			* env->number_of_philosophers);
	if(pthread_mutex_init(&env->lock, NULL))
		return(1);
	i = 0;
	while (i < env->number_of_philosophers)
	{
		if(init_philo(env, i))
			return (1);
		i++;
	}
	return (0);
}

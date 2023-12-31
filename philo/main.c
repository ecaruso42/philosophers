/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:23:39 by ecaruso           #+#    #+#             */
/*   Updated: 2023/11/06 12:31:59 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	message(t_philo *philo, char *str)
{
	u_int64_t	time;

	time = get_time() - philo->env->start_time;
	if (philo->is_alive || philo->env->number_of_philosophers == 1)
		printf("%lu %d %s\n", time, philo->id + 1, str);
}

void	case_one(t_env *env)
{
	message(&env->table[0], FORK);
	my_usleep(env->time_to_die);
	env->table[0].is_alive = 0;
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	num;
	int	i;

	neg = 1;
	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10;
		num += (str[i] - 48);
		i++;
	}
	num *= neg;
	return (num);
}

int	ft_exit(t_env *env, int status)
{
	int	i;

	i = 0;
	while (i < env->number_of_philosophers)
	{
		pthread_mutex_destroy(&env->table[i].fork);
		i++;
	}
	pthread_mutex_destroy(&env->lock);
	return (status);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 5 || argc > 6)
	{
		printf("ERROR: Argoument count not valid\n");
		return (1);
	}
	if (check_input(argv))
		return (1);
	if (init(&env, argc, argv))
	{
		return (ft_exit(&env, 1));
		free(env.table);
	}
	if (play(&env))
		return (ft_exit(&env, 1));
	return (ft_exit(&env, 0));
}

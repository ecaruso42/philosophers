/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:24:48 by ecaruso           #+#    #+#             */
/*   Updated: 2023/11/07 21:52:44 by ecaruso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# include <semaphore.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

struct	s_env;

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				is_alive;
	int				is_eating;
	int				eat_count;
	int				next_fork;
	u_int64_t		time_left;
	pthread_t		supervisor;
	struct s_env	*env;
}t_philo;

typedef struct s_env
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pid_t			pid[200];
	sem_t			*sem_dead;
	sem_t			*sem_eat;
	u_int64_t		start_time;
	pthread_mutex_t	lock;
	t_philo			philo;
}t_env;

int			play(t_env *env, int philo_id);
int			check_input(char **argv);
int			init(t_env *env, int argc, char **argv);
int			ft_atoi(const char *str);
u_int64_t	get_time(void);
void		my_usleep(int ms);
void		message(t_philo *philo, char *str);
void		case_one(t_env *env);

#endif
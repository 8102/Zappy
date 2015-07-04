/*
** misc.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:36:38 2015 Emmanuel Chambon
** Last update Fri Jul  3 18:18:40 2015 Hugo Prenat
*/

#pragma once
#ifndef _MISC_H_
# define _MISC_H_

# include <stdbool.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <errno.h>
# include <sys/types.h>
# include <stdarg.h>
# include <math.h>
# include <getopt.h>

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BOLDBLACK	"\033[1m\033[30m"
# define BOLDRED	"\033[1m\033[31m"
# define BOLDGREEN	"\033[1m\033[32m"
# define BOLDYELLOW	"\033[1m\033[33m"
# define BOLDBLUE	"\033[1m\033[34m"
# define BOLDMAGENTA	"\033[1m\033[35m"
# define BOLDCYAN	"\033[1m\033[36m"
# define BOLDWHITE	"\033[1m\033[37m"

void		error(char *);
char		*epur_str(char *);
char		*str_replace(char *, char, char);
t_case		*getCaseFromCoord(size_t x, size_t y, t_case *);
char		*transform_int(int);

#endif /* !_MISC_H_ */

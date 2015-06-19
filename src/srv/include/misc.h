/*
** misc.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:36:38 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:53:26 2015 Emmanuel Chambon
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

void		error(char *);
char		*epur_str(char *);
char		*str_replace(char *, char, char);

#endif /* !_MISC_H_ */

/*
** timespec_add.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Fri Jul  3 05:57:46 2015 Emmanuel Chambon
** Last update Fri Jul  3 05:57:57 2015 Emmanuel Chambon
*/

#include "zappy.h"

void            timespec_add_usec(struct timespec *time,
				  unsigned long long int usec, bool reset)
{
  assert(time != NULL);
  timespec_add_timespec(time, timespec_convert(usec), reset);
}

void            timespec_add_timespec(struct timespec *one,
				      struct timespec *two, bool reset)
{
  assert(one != NULL && two != NULL);
  if (reset)
    timespec_update(one);
  one->tv_sec += two->tv_sec;
  one->tv_nsec += two->tv_nsec;
}

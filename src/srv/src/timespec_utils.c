/*
** timespec_utils.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Fri Jul  3 05:56:50 2015 Emmanuel Chambon
** Last update Fri Jul  3 06:08:57 2015 Emmanuel Chambon
*/

#include "zappy.h"

struct timespec		*timespec_now()
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  timespec_update(time);
  return (time);
}

struct timespec		*timespec_init(struct timespec *base)
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  if (!base)
    timespec_update(time);
  else
    {
      time->tv_sec = base->tv_sec;
      time->tv_nsec = base->tv_nsec;
    }
  return (time);
}

void			timespec_update(struct timespec *time)
{
  assert(time != NULL);
#if defined(_POSIX_C_SOURCE)
  if (clock_gettime(CLOCK_BOOTTIME, time))
    error("clock_gettime");
#else
  if (!timespec_get(time, TIME_UTC))
    error("timespec_get");
#endif
}

void			timespec_release(struct timespec *t)
{
  assert(t != NULL);
  free(t);
}

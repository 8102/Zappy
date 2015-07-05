/*
** timelib.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jul  2 21:53:04 2015 Emmanuel Chambon
** Last update Sun Jul  5 01:31:48 2015 Emmanuel Chambon
*/

#include "zappy.h"

struct timespec		*timespec_usec_to_timespec(unsigned long long int t)
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  time->tv_sec = (time_t)(t / 1000000);
  time->tv_nsec = (t % 1000000) * 100;
  return (time);
}

struct timespec		*timespec_time_to_timespec_ptr(time_t *t)
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  time->tv_sec = *t;
  time->tv_nsec = 0;
  return (time);
}

struct timespec		*timespec_time_to_timespec_cp(time_t t)
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  time->tv_sec = t;
  time->tv_nsec = 0;
  return (time);
}

struct timespec		*timespec_tm_to_timespec_cp(struct tm t)
{
  return (timespec_time_to_timespec_cp(mktime(&t)));
}

struct timespec		*timespec_tm_to_timespec_ptr(struct tm *t)
{
  return (timespec_time_to_timespec_cp(mktime(t)));
}

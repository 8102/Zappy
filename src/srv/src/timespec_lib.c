/*
** timelib.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jul  2 21:53:04 2015 Emmanuel Chambon
** Last update Fri Jul  3 04:18:29 2015 Emmanuel Chambon
*/

#include "zappy.h"

struct timespec *timespec_now()
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  timespec_update(time);
  return (time);
}

struct timespec	*timespec_init(struct timespec *base)
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

void		timespec_update(struct timespec *time)
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

void		timespec_add_usec(struct timespec *time, unsigned long long int usec, bool reset)
{
  assert(time != NULL);
  timespec_add_timespec(time, timespec_convert(usec), reset);
}

void		timespec_add_timespec(struct timespec *one, struct timespec *two, bool reset)
{
  assert(one != NULL && two != NULL);
  if (reset)
    timespec_update(one);
  one->tv_sec += two->tv_sec;
  one->tv_nsec += two->tv_nsec;
}

void		timespec_sub_usec(struct timespec *time, unsigned long long int usec, bool reset)
{
  assert(time != NULL);
  timespec_sub_timespec(time, timespec_convert(usec), reset);
}

void		timespec_sub_timespec(struct timespec *one, struct timespec *two, bool reset)
{
  assert(one != NULL && two != NULL);
  if (reset)
    timespec_update(one);
  one->tv_sec -= two->tv_sec;
  one->tv_nsec -= two->tv_nsec;
}

bool		timespec_is_lower(struct timespec *one, struct timespec *two)
{
  assert(one != NULL && two != NULL);
  return ((one->tv_sec <= two->tv_sec && one->tv_nsec < two->tv_nsec) ?
	  true : false);
}

bool		timespec_is_greater(struct timespec *one, struct timespec *two)
{
  assert(one != NULL && two != NULL);
  return ((one->tv_sec >= two->tv_sec && one->tv_nsec > two->tv_nsec) ?
	  true : false);
}

bool		timespec_is_equal(struct timespec *one, struct timespec *two)
{
  assert(one != NULL && two != NULL);
  return ((one->tv_sec == two->tv_sec && one->tv_nsec == two->tv_nsec) ?
	  true : false);
}

struct timespec	*timespec_usec_to_timespec(unsigned long long int t)
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  time->tv_sec = (time_t)(t / 1000000);
  time->tv_nsec = (t % 1000000) * 100;
  return (time);
}

struct timespec	*timespec_time_to_timespec_ptr(time_t *t)
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  time->tv_sec = *t;
  time->tv_nsec = 0;
  return (time);
}

struct timespec	*timespec_time_to_timespec_cp(time_t t)
{
  struct timespec	*time;

  if (!(time = malloc(sizeof(struct timespec))))
    error("malloc");
  time->tv_sec = t;
  time->tv_nsec = 0;
  return (time);
}

struct timespec	*timespec_tm_to_timespec_cp(struct tm t)
{
  return (timespec_time_to_timespec_cp(mktime(&t)));
}

struct timespec	*timespec_tm_to_timespec_ptr(struct tm *t)
{
  return (timespec_time_to_timespec_cp(mktime(t)));
}

void		timespec_release(struct timespec *t)
{
  assert(t != NULL);
  free(t);
}

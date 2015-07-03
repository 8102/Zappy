/*
** timespec_cmp.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Fri Jul  3 05:58:31 2015 Emmanuel Chambon
** Last update Fri Jul  3 06:08:18 2015 Emmanuel Chambon
*/

#include "zappy.h"

bool		timespec_is_lower(struct timespec *one, struct timespec *two)
{
  assert(one != NULL && two != NULL);
  if (one->tv_sec < two->tv_sec)
    return (true);
  else if ((one->tv_sec == two->tv_sec && one->tv_nsec < two->tv_nsec))
    return (true);
  return (false);
}

bool		timespec_is_greater(struct timespec *one, struct timespec *two)
{
  assert(one != NULL && two != NULL);
  if (one->tv_sec > two->tv_sec)
    return (true);
  else if ((one->tv_sec == two->tv_sec && one->tv_nsec > two->tv_nsec))
    return (true);
  return (false);
}

bool		timespec_is_equal(struct timespec *one, struct timespec *two)
{
  assert(one != NULL && two != NULL);
  return ((one->tv_sec == two->tv_sec && one->tv_nsec == two->tv_nsec) ?
	  true : false);
}

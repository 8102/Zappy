/*
** zappy_init.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Fri Jul  3 06:00:12 2015 Emmanuel Chambon
** Last update Sat Jul  4 00:01:24 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		release_delays(t_master *content)
{
  for (int i = 0; content->time.delays[i]; i++)
    timespec_release(content->time.delays[i]);
  timespec_release(content->time.timeout);
  timespec_release(content->time.io_now);
  timespec_release(content->time.pl_now);
}

void		set_timeout(t_master *content)
{
  double	x;

  x = (1 / (double)(content->delay)) * 1000000;
  content->time.timeout = timespec_convert((ull)x);
  content->time.io_now = timespec_now();
  content->time.pl_now = timespec_now();
}

void		set_delays(t_master *content)
{
  double	x;
  double	y;
  double	z;

  x = (7 / (double)(content->delay)) * 1000000;
  y = (300 / (double)(content->delay)) * 1000000;
  z = (42 / (double)(content->delay)) * 1000000;
  content->time.delays[AVANCE] = timespec_convert((ull)x);
  content->time.delays[DROITE] = timespec_convert((ull)x);
  content->time.delays[GAUCHE] = timespec_convert((ull)x);
  content->time.delays[VOIR] = timespec_convert((ull)x);
  content->time.delays[INVENTAIRE] = timespec_convert((ull)x);
  content->time.delays[PREND] = timespec_convert((ull)x);
  content->time.delays[POSE] = timespec_convert((ull)x);
  content->time.delays[EXPULSE] = timespec_convert((ull)x);
  content->time.delays[BROADCAST] = timespec_convert((ull)x);
  content->time.delays[INCANTATION] = timespec_convert((ull)y);
  content->time.delays[FORK] = timespec_convert((ull)z);
  content->time.delays[11] = NULL;
}

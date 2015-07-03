/*
** zappy_init.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Fri Jul  3 06:00:12 2015 Emmanuel Chambon
** Last update Fri Jul  3 06:11:10 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		release_delays(t_master *content)
{
  for (int i = 0; content->delays[i]; i++)
    timespec_release(content->delays[i]);
  timespec_release(content->timeout);
}

void		set_timeout(t_master *content)
{
  double	x;

  x = (1 / (double)(content->delay)) * 1000000;
  content->timeout = timespec_convert((ull)x);
}

void		set_delays(t_master *content)
{
  double	x;
  double	y;
  double	z;

  x = (7 / (double)(content->delay)) * 1000000;
  y = (300 / (double)(content->delay)) * 1000000;
  z = (42 / (double)(content->delay)) * 1000000;
  content->delays[AVANCE] = timespec_convert((ull)x);
  content->delays[DROITE] = timespec_convert((ull)x);
  content->delays[GAUCHE] = timespec_convert((ull)x);
  content->delays[VOIR] = timespec_convert((ull)x);
  content->delays[INVENTAIRE] = timespec_convert((ull)x);
  content->delays[PREND] = timespec_convert((ull)x);
  content->delays[POSE] = timespec_convert((ull)x);
  content->delays[EXPULSE] = timespec_convert((ull)x);
  content->delays[BROADCAST] = timespec_convert((ull)x);
  content->delays[INCANTATION] = timespec_convert((ull)y);
  content->delays[FORK] = timespec_convert((ull)z);
  content->delays[11] = NULL;
}

/*
** zappy.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 20:14:21 2015 Emmanuel Chambon
** Last update Tue Jun 16 20:19:37 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		init_zappy(t_all *content)
{
  char  *port = "3031"; // Hard coded for now


  init_server(&(content->server), port);
}

void		release_zappy(t_all *content)
{
  release_server(&(content->server));
}

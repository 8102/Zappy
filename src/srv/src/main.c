/*
** main.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:16:36 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:50:36 2015 Emmanuel Chambon
*/

#include "zappy.h"

int		main(int ac, char **av)
{
  t_master	content;

  if (init_zappy(&content, ac, av) == -1)
    return (-1);
  idle_server(&content);
  release_zappy(&content);
  return (0);
}

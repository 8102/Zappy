/*
** main.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:16:36 2015 Emmanuel Chambon
** Last update Wed Jun 17 17:58:52 2015 Hugo Prenat
*/

#include "zappy.h"

int	main(int ac, char **av)
{
  t_all	content;

  if (init_zappy(&content, ac, av) == -1)
    return (-1);
  idle_server(&content.server);
  release_zappy(&content);
  return (0);
}

/*
** main.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:16:36 2015 Emmanuel Chambon
** Last update Tue Jun 16 20:21:08 2015 Emmanuel Chambon
*/

#include "zappy.h"

int	main(int __attribute((unused))ac, char __attribute((unused))**av)
{
  t_all	content;	// I prefer declaring a strut and pass its pointer
                        // everywhere (if you have a problem with that call me...)
  init_zappy(&content);
  idle_server(&content.server);
  release_zappy(&content);
  return (0);
}

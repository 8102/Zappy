/*
** misc.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:59:24 2015 Emmanuel Chambon
** Last update Tue Jun 16 12:03:34 2015 Emmanuel Chambon
*/

#include "zappy.h"

void            error(char *error)
{
  perror(error);
  exit(EXIT_FAILURE);
}

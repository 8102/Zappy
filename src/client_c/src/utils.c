/*
** utils.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:56:34 2015 TommyStarK
** Last update Sun Jul  5 03:05:26 2015 Emmanuel Chambon
*/

#include "client.h"

void		error(char *error)
{
  perror(error);
  exit(EXIT_FAILURE);
}

void		ssend(int socket, char *msg, ...)
{
  va_list	args;

  va_start(args, msg);
  if (!(vdprintf(socket, msg, args)))
    error("dprintf");
  va_end(args);
}

int 		get_array_size(char **array)
{
  int		i;

  i = 0;
  if (!array || !(*array))
    return (i);
  while (array[i])
    ++i;
  return (i);
}

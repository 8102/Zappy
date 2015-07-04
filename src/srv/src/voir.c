/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sat Jul  4 22:26:10 2015 Hugo Prenat
*/

#include "zappy.h"

void	voir(char UNUSED*params,
	     t_client *client,
	     t_master *content)
{
  char	*ret;
  char	*str;

  timespec_add(client->clock, content->time.delays[VOIR], true);
  str = first_case(content, client);
  // There
  if (!(ret = malloc(sizeof(*str) * (strlen(str) + 3))))
    return ;
  strcpy(ret, str);
  strcat(ret, "}\n");
  ssend(client->socket, ret);
  free(str);
  free(ret);
}

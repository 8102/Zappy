/*
** time.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Thu Jul  2 15:35:30 2015 Hugo Prenat
** Last update Sat Jul  4 01:10:35 2015 Emmanuel Chambon
*/

#include "zappy.h"

void	sgt(char UNUSED*params,
	    t_client *client,
	    t_master *content)
{
  ssend(client->socket, "sgt %d\n", content->delay);
}

void	sst(char *params,
	    t_client UNUSED*client,
	    t_master *content)
{
  int	newT;

  if (!params || !params[0])
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  newT = atoi(params);
  ssend(client->socket, "sgt %d\n", newT);
  content->delay = newT;
  set_timeout(content);
  set_delays(content);
}

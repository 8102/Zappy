/*
** client_handler.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jun 18 14:42:29 2015 Emmanuel Chambon
** Last update Thu Jul  2 19:12:46 2015 Emmanuel Chambon
*/

#include "zappy.h"

t_client	*get_client(int socket, t_client **clients)
{
  t_client	*tmp;

  for (tmp = *clients; tmp; tmp = tmp->next)
    if (tmp->socket == socket)
      return (tmp);
  return (NULL);
}

void		input_interpret(t_client *client, t_master *content)
{
  char		*input;
  int		i;

  input = cb_read(client->buffer);
  printf("[%s]\n", input);
  for (i = 0; i < MAX_CMD - 1; i++)
    {
      if (!client->trigger[AUTH])
  	continue ;
      if (!(strncmp(content->server.cmd[i],
		    input, strlen(content->server.cmd[i]))))
	{
	  content->server.cmd_handler[i](epur_str(strchr(input, ' ')),
					 client, content);
	  break ;
	}
    }
  if (i == MAX_CMD - 1 && !client->trigger[AUTH])
    select_team(input, client, content);
  else if (i == MAX_CMD - 1)
    ssend(client->socket, "ko\n");
  free(input);
}

void		handle_io(char *tmp, t_client *client, t_master *content)
{
  rb_write(client->recv, tmp);
  if (rb_at(client->recv, -1) == '\n')
    {
      rb_delete_last(client->recv);
      if (!cb_available(client->buffer))
	rb_reset(client->recv);
      else
	{
	  cb_write(client->buffer, epur_str(str_replace(rb_read(client->recv),
	  						'\n', '\0')), false);
	  input_interpret(client, content);
	}
    }
}

void		handle_io_connection(t_client *client, t_master *content)
{
  char		tmp[RB_SIZE];
  int		rc;
  int		i;
  int		x;

  if (!client)
    return ;
  memset(tmp, 0, RB_SIZE);
  if ((rc = recv(client->socket, tmp, RB_SIZE, 0)) > 0)
    {
      if (!strchr(tmp, (int)'\n'))
	rb_write(client->recv, tmp);
      else {
	x = -1;
	for (i = 0; tmp[i]; i++)
	  if (tmp[i] == '\n')
	    {
	      handle_io(strndup(&tmp[x + 1], i - x), client, content);
	      x = i;
	    }
      }
    }
  else
    remove_connection(client, content, rc);
}

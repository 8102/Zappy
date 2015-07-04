/*
** win.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Sat Jul  4 02:12:44 2015 Emmanuel Chambon
** Last update Sat Jul  4 02:14:12 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		team_win(t_team *team, t_master *content)
{
  ssend_graphics(content, "seg %s\n", team->name);
  g_run = false;
}

void		reset_leveled(t_master *content)
{
  for (t_team *tmp = content->teams; tmp; tmp = tmp->next)
    tmp->leveled_pl = 0;
}

void		check_leveled(t_master *content)
{
  for (t_team *tmp = content->teams; tmp; tmp = tmp->next)
    if (tmp->leveled_pl == PLAYERS_REQ_WIN)
      team_win(tmp, content);
}

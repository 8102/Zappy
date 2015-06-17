/*
** server_init.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:26:31 2015 Emmanuel Chambon
** Last update Thu Jun 18 01:34:27 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		set_commands(t_server *serv)
{
  serv->cmd[0] = "avance";
  serv->cmd[1] = "droite";
  serv->cmd[2] = "gauche";
  serv->cmd[3] = "voir";
  serv->cmd[4] = "inventaire";
  serv->cmd[5] = "prend";
  serv->cmd[6] = "pose";
  serv->cmd[7] = "expulse";
  serv->cmd[8] = "broadcast";
  serv->cmd[9] = "incantation";
  serv->cmd[10] = "fork";
  serv->cmd[11] = "connect_nbr";
  serv->cmd[12] = NULL;
}

void		set_commands_handlers(t_server *serv)
{
  serv->cmd_handler[0] = &avance;
  serv->cmd_handler[1] = &droite;
  serv->cmd_handler[2] = &gauche;
  serv->cmd_handler[3] = &voir;
  serv->cmd_handler[4] = &inventaire;
  serv->cmd_handler[5] = &prend;
  serv->cmd_handler[6] = &pose;
  serv->cmd_handler[7] = &expulse;
  serv->cmd_handler[8] = &broadcast;
  serv->cmd_handler[9] = &incantation;
  serv->cmd_handler[10] = &_fork;
  serv->cmd_handler[11] = &connect_nbr;
  serv->cmd_handler[12] = NULL;
}

void		set_commands_checkers(t_server *serv)
{
  serv->param_checker[0] = NULL;
  serv->param_checker[1] = NULL;
  serv->param_checker[2] = NULL;
  serv->param_checker[3] = NULL;
  serv->param_checker[4] = NULL;
  serv->param_checker[5] = NULL;
  serv->param_checker[6] = NULL;
  serv->param_checker[7] = NULL;
  serv->param_checker[8] = NULL;
  serv->param_checker[9] = NULL;
  serv->param_checker[10] = NULL;
  serv->param_checker[11] = NULL;
  serv->param_checker[12] = NULL;
}

void		set_handler(t_server *serv)
{
  set_commands(serv);
  set_commands_handlers(serv);
  set_commands_checkers(serv);
}

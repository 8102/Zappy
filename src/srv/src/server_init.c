/*
** server_init.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:26:31 2015 Emmanuel Chambon
** Last update Fri Jul  3 01:37:43 2015 Emmanuel Chambon
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
  serv->cmd[12] = "msz";
  serv->cmd[13] = "bct";
  serv->cmd[14] = "mct";
  serv->cmd[15] = "tna";
  serv->cmd[16] = "ppo";
  serv->cmd[17] = "plv";
  serv->cmd[18] = "pin";
  serv->cmd[19] = "sgt";
  serv->cmd[20] = "sst";
  serv->cmd[21] = "GRAPHIC";
  serv->cmd[22] = NULL;
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
  serv->cmd_handler[12] = &msz;
  serv->cmd_handler[13] = &bct;
  serv->cmd_handler[14] = &mct;
  serv->cmd_handler[15] = &tna;
  serv->cmd_handler[16] = &ppo;
  serv->cmd_handler[17] = &plv;
  serv->cmd_handler[18] = &pin;
  serv->cmd_handler[19] = &sgt;
  serv->cmd_handler[20] = &sst;
  serv->cmd_handler[21] = &graphic;
  serv->cmd_handler[22] = NULL;
}

void		set_handler(t_server *serv)
{
  set_commands(serv);
  set_commands_handlers(serv);
}

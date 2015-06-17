/*
** init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 17 18:04:44 2015 Hugo Prenat
** Last update Wed Jun 17 21:20:14 2015 Hugo Prenat
*/

#include "zappy.h"

size_t		size_team(t_team *teams)
{
  size_t	i;

  i = 0;
  if (teams[0].slot == -1)
    return (0);
  while (teams[i].slot != -1)
    i++;
  return (i);
}

int		add_one_team(char *team, t_all *content)
{
  t_team	*old;
  size_t	i;

  i = 0;
  old = content->teams;
  if ((content->teams = malloc(sizeof(*content->teams) *
			       (size_team(old) + 2))) == NULL)
    return (-1);
  while (i != size_team(old))
    {
      content->teams[i].name = old[i].name;
      content->teams[i].slot = old[i].slot;
      i++;
    }
  content->teams[i].name = team;
  content->teams[i].slot = content->max_clients;
  content->teams[i + 1].slot = -1;
  free(old);
  return (0);
}

int	add_team(char **av, int ac, t_all *content)
{
  int	i;

  i = optind - 1;
  while(i < ac)
    {
      if (av[i][0] == '-')
	{
	  optind = i - 1;
	  return (0);
	}
      add_one_team(av[i], content);
      i++;
    }
  return (0);
}

int	check_param(int ac, char **av, t_all *content)
{
  int	opt;
  int	ret;

  ret = 0;
  while ((opt = getopt(ac, av, "p:x:y:c:t:n:")) != -1)
    {
      if (opt == '?')
	ret = -1;
      if (opt == 'p')
	content->port = optarg;
      if (opt == 'x')
	content->width = atoi(optarg);
      if (opt == 'y')
	content->height = atoi(optarg);
      if (opt == 'c')
	content->max_clients = atoi(optarg);
      if (opt == 't')
	content->delay = atoi(optarg);
      if (opt == 'n')
	ret = add_team(av, ac, content);
    }
  if (ac < 13)
    ret = -1;
  return (ret);
}

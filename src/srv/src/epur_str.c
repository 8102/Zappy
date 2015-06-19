/*
** epur_str.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jun 18 19:29:47 2015 Emmanuel Chambon
** Last update Thu Jun 18 19:32:19 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		clean_string(char *str)
{
  int		i;
  int		j;

  i = -1;
  j = 0;
  while (str[++i])
    {
      if (str[i] != ' ' && str[i] != '\t')
        {
          str[j] = str[i];
          j++;
	  if (str[i + 1] == ' ' || str[i + 1] == '\t')
	    {
	      str[j] = ' ';
	      j++;
	    }
	}
    }
  str[j] = '\0';
  if (str[j - 1] == ' ')
    str[j - 1] = '\0';
}

int		no_char(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] > 20 && str[i] < 127)
	return (1);
      i++;
    }
  return (0);
}

char            *epur_str(char *str)
{
  if (!str)
    return (NULL);
  if (!no_char(str))
    str[0] = 0;
  else
    clean_string(str);
  return (str);
}

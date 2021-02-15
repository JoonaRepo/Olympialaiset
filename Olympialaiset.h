#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
	char name[20];
	int g;
	int s;
	int b;
} Country;

typedef struct 								// A global variable to store the current command type e.g. 'A', 'M', 'L' and arguments
{
	char type;
	char *name;
	int g;
	int s;
	int b;
} Command;

int read_command (char *cmd, Country *list) /*Reads and parses user-given command. 
											Returns 0 if unsuccessful otherwise returns 1.*/
{
	char *cmd_alpha = toupper(cmd[0]);

	char *name;
	char *namestart = name;
	for (int i = 0, int alpha = 0; cmd[i]; i++)
	{
		if (!alpha && isalpha(cmd[i+1]))
		{
			alpha = 1;
		}

		if (alpha && !isalpha(cmd[i+1]))
		{
			alpha = 0;
		}

		else
		{
			*name = cmd[i];
			name++;
		}
	}
	name++;
	*name = '\0';
	name = namestart;

	int par1;
	int par2;
	int par3;

	switch (cmd_alpha)
	{
		case 'A' : 							// Calls function append()
		{

		}
		case 'M' : 							// Calls function update_medals()
		{
			
		}
		case 'L' : 							// Calls function print_table()
		{
			
		}
		case 'W' : 							//
		{
			
		}
		case 'O' : 							//
		{
			
		}
		case 'Q' : 							//
		{
			
		}

		default :
		return 0;
	}
}

Country* init() //Mallocs and initializes a list of countries. Returns a pointer to the start of the list.
{
	struct *Country list = malloc(sizeof(Country));
	list[0].name = '\0';
	return list;
}

Country* append(Country *list, char *name) //Appends a new country to the end of the list.
{
	int listlen = sizeof(list)/sizeof(list[0]);
	list = realloc(listlen + 1, sizeof(Country));
	strncpy(name, list[listlen - 2].name, 20);
	return list;
}

Country* update_medals(Country *list, char *name, int g, int s, int b)
{
	int listindex = -1;
	for (int i = 0; list[i].name != '\0'; i++)
	{
		if (strcmp(list[i].name, name) == 0)
		{
			listindex = i;
		}
	}
	
	if (listindex <= 0)
	{
		list[i].g += g;
		list[i].s += s;
		list.[i].b += b;
	}

	else
	{
	/*ERROMESSAGE*/
	}
	return list;
}

void order(Country *list) //Järjestää listan suurimmasta pienimpään mitalien mukaan. kulta -> hopea -> pronssi
{
	char *temp_n[21];
	int temp_g, temp_s, temp_b;
	for (int i = 0; list[i].name != '\0'; i++)
	{
		strcpy(temp_n, list[i].name);
			temp_g = list[i].g;
			temp_s = list[i].s;
			temp_b = list[i].b;
		for (int j = i; list[j].name != '\0'; j++)
		{
			if (list[j].g > temp_g)
			{
				list[i] = list[j];
				strcpy(list[j].name, temp_n),
				list[j].g = temp_g;
				list[j].s = temp_s;
				list[j].b = temp_b;
			}

			else if (list[j].g == temp_g)
			{
				if (list[j].s > temp_s)
				{
					list[i] = list[j];
					strcpy(list[j].name, temp_n),
					list[j].g = temp_g;
					list[j].s = temp_s;
					list[j].b = temp_b;
				}

				else if
				{
					else if (list[j].g == temp_g)
					{
						if (list[j].b > temp_b)
						{
							list[i] = list[j];
							strcpy(list[j].name, temp_n),
							list[j].g = temp_g;
							list[j].s = temp_s;
							list[j].b = temp_b;
						}
					}
				}
			}
		}
	}
}

void print_table(Country *list) //Tulostaa taulukon tiedot: Maan nimelle varattu 20 merkkiä tilaa
{
	Order(list);
	Printf("Maa                 Kulta Hopea Pronssi\n");
	for (int i = 0; list[i].name != '\0')
	{
		printf("%s");
		for (int j = 20 - strlen(list[i].name); j > 0; i--) //Täytetään maan nimen tulostuksen perään välilyöntejä, jotta tilaa on käytetty 20 merkkiä
		{
			printf(" ");
		}
		printf(" %5d%5d%5d\n", g, s, b);
	}
}


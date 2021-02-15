#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
	char name[21];
	int g;
	int s;
	int b;
} Country;

Country* init() 			//Mallocs and initializes a list of countries. Returns a pointer to the start of the list.
{
	Country *list = malloc(sizeof(Country));
	list[0].name[0] = '\0';
	return list;
}

void order(Country *list) 	//Sorts the list of countries according to the number of medals from gold to silver to bronze.
{							//Most medals is first.
	char temp_n[21];
	int temp_g = 0;
	int temp_s = 0;
	int temp_b = 0;
	int temp_index = 0;
	for (int i = 0; list[i].name[0] != '\0'; i++)
	{
		strcpy(temp_n, list[i].name);				//Setting up temporary values 
		temp_g = list[i].g;
		temp_s = list[i].s;
		temp_b = list[i].b;
		for (int j = i; list[j].name[0] != '\0'; j++)  //Searching through the list from item i forward.
		{											//Comparing list item i to list item j
			if (list[j].g > temp_g)             	//Comparing gold medals
			{
				strcpy(temp_n, list[j].name);
				temp_g = list[j].g;
				temp_s = list[j].s;
				temp_b = list[j].b;
				temp_index = j;
			}
			else if (list[j].g == temp_g)			//Comparing silver medals
			{
				if (list[j].s > temp_s)
				{
					strcpy(temp_n, list[j].name);
					temp_g = list[j].g;
					temp_s = list[j].s;
					temp_b = list[j].b;
					temp_index = j;
				}
				else if (list[j].s == temp_s)		//Comparing bronze medals
				{
					if (list[j].b > temp_b)
					{
						strcpy(temp_n, list[j].name);
						temp_g = list[j].g;
						temp_s = list[j].s;
						temp_b = list[j].b;
						temp_index = j;
					}
				}
			}
		}

		if (strcmp(temp_n, list[i].name) != 0)		//If a higher value list item was found code is executed.
		{
			strcpy(list[temp_index].name, list[i].name);
			list[temp_index].g = list[i].g;
			list[temp_index].s = list[i].s;
			list[temp_index].b = list[i].b;
			strcpy(list[i].name, temp_n);
			list[i].g = temp_g;
			list[i].s = temp_s;
			list[i].b = temp_b;
		}
	}
}

Country* append(Country *list, const char *name) //Appends a new country to the end of the list.
{
	int listlen = 1;
	for (int i = 0; list[i].name[0] != '\0'; i++)
	{
		listlen++;
	}

	list = realloc(list, (listlen + 1) * sizeof(Country));
	
	list[listlen].name[0] = '\0';
	if (strlen(name) > 20) 
	{
		strncpy(list[listlen - 1].name, name, 20);
		list[listlen - 1].name[20] = '\0';
	}
	else strcpy(list[listlen - 1].name, name);
	list[listlen - 1].g = 0;
	list[listlen - 1].s = 0;
	list[listlen - 1].b = 0;

	printf("%s appended succesfully.\n", name);
	return list;
}

Country* update_medals(Country *list, char *name, int g, int s, int b)
{
	for (int i = 0; list[i].name[0] != '\0'; i++)
	{
		if (strcmp(list[i].name, name) == 0)
		{
			list[i].g += g;
			list[i].s += s;
			list[i].b += b;
			printf("Medals updated! %s holds: %d Golds %d Silvers %d Bronzes.\n", list[i].name, list[i].g, list[i].s, list[i].b);
			return list;
		}
	}
	
	printf("Country was not found.\nNo medals updated.\n");
	return list;
}

void print_table(Country *list) //Prints the table of countries. Only the first 20 chars of the name are printed.
{
	order(list);
	printf("\n%-21s%-7s%-7s%-7s\n", "Country", "Gold", "Silver", "Bronze");
	for (int i = 0; list[i].name[0] != '\0'; i++)
	{
		printf("%-21s%-7d%-7d%-7d\n", list[i].name, list[i].g, list[i].s, list[i].b);
	}
}

void output_list(Country *list, char *filename)
{
	int listlen = 0;
	for (int i = 0; list[i].name[0] != '\0'; i++)
	{
		listlen++;
	}
	if (listlen <= 0)
	{
		printf("No countries in memory. File writing unsuccessful.\n");
		return;
	}
	char *fname = malloc((strlen(filename) + 5) * sizeof(char));
	fname = strcpy(fname, filename);
	fname = strcat(fname, ".txt");
	FILE *file = fopen(fname, "w");
	order(list);
	fprintf(file, "%-21s%-7s%-7s%-7s\r\n", "Country", "Gold", "Silver", "Bronze");
	for (int i = 0; list[i].name[0] != '\0'; i++)
	{
		fprintf(file, "%-21s%-7d%-7d%-7d\r\n", list[i].name, list[i].g, list[i].s, list[i].b);
	}
	fclose(file);
	free(fname);
	printf("Table written: %s.txt\n", filename);
}

Country* input_list(Country *list, char *filename)
{
	char *fname = malloc((strlen(filename) + 5) * sizeof(char));
	fname = strcpy(fname, filename);
	fname = strcat(fname, ".txt");
	FILE *file = fopen(fname, "r");
	if (file != NULL)
	{
		free(list);
		Country *countries = init();
		fseek(file, 0, SEEK_END);
		long flen = ftell(file) + 1;
		rewind(file);
		char *row = malloc(flen * sizeof(char));
		int g, s, b;
		char *name = malloc(21 * sizeof(char));
		
		fgets(row, flen, file); 					//Skipping the header-row

		while(fgets(row, flen, file) != NULL)
		{
			sscanf(row, "%s %d %d %d", name, &g, &s, &b);
			countries = append(countries, name);
			countries = update_medals(countries, name, g, s, b);
			printf("\n");
		}
		sscanf(row, "%s %d %d %d", name, &g, &s, &b);

		fclose(file);
		free(fname);
		free(row);
		free(name);
		printf("Table loaded!");
		return countries;
	}
	else
	{
		printf("Error in reading file: %s(.txt)\n", filename);
		free(fname);
		return list;
	}
}

int main() 
{

	Country *countries = init();
	char cmd;
	char *str = malloc(51 * sizeof(char));
	char *name = malloc(21 * sizeof(char));
	int g, s, b, scanret;

	printf("\n\nEnter a command: (Press H for help)\n");
	while(fgets(str, 28, stdin)) {
		switch(toupper(str[0])) 
		{
			case 'A':									// Calls function append(Country *list, char *name)
				scanret = sscanf(str, "%c %20s", &cmd, name);
				if (scanret == 2) countries = append(countries, name);
				else printf("Check format!: 'A' 'name of the country'\n");
				break;	

			case 'M' : 									// Calls function update_medals(Country *list, char *name, int g, int s, int b)	
				scanret = sscanf(str, "%c %20s %d %d %d", &cmd, name, &g, &s, &b);
				if (scanret == 5) countries = update_medals(countries, name, g, s, b);
				else printf("Check format!: 'M' 'name of the country' 'gold medals' 'silver medals' 'bronze medals'\n");
				break;

			case 'L' : 									// Calls function print_table(Country *list)
				print_table(countries);
				break;
			case 'W' : 									// Calls function output_list(Country *list, char *filename)
				scanret = sscanf(str, "%c %20s", &cmd, name);
				if (scanret == 2) output_list(countries, name);
				else printf("Check format!: 'W' 'filename' (no file extension)");
				break;
			case 'O' : 									// Calls function input_list(Country *list, char *filename)
				scanret = sscanf(str, "%c %20s", &cmd, name);
				if (scanret == 2) countries = input_list(countries, name);
				else printf("Check format!: 'O' 'filename' (no file extension)");
				break;
			case 'Q' : 									// Frees allocated memory and exits the software
				free(countries);
				free(str);
				free(name);
				exit(0);
			case 'H' :									// Prints a list of commands and their descriptions
				printf("---------------------------------------------------------------------------------------------------------------------------------------\n\n"
						"List of commands (format):\n"
						"'A' (command) (name of the country)\n"
						"	= Appends a new country to the end of the list. Only the first 20 characters of the name are used. All medals are set to 0.\n\n"
						"'M' (command) (name of the country (max 20 char)) (golds) (silvers) (bronzes)\n"
						"	= Updates the amount of medals for a country. Medals can be added with '+' and reduced with '-'.\n\n"
						"'L' (command)\n"
						"	= Prints out the current list in decreasing order of medals\n\n"
						"'W' (command) (filename)\n"
						"	= Writes a .txt file with a specified filename (file extension doesn't need to be specified).\n"
						"	  The file is formatted like the printed table.\n\n"
						"'O' (command) (filename)\n"
						"	= Replaces the current list with a list read from a file with specified filename (file extension doesn't need to be specified).\n"
						"	  The file must follow the same format as the files written by this software.\n\n"
						"'Q' (command)\n"
						"	= Exits the program.\n\n"
						"---------------------------------------------------------------------------------------------------------------------------------------\n");
				break;
		}
		printf("\nEnter a command: \n");
	}

	return 0;
}

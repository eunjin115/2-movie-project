#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#pragma warning(disable:4996)

typedef struct movie {
	int serial ;
	int year;
	int runtime;
	char* title;
	char* genre;
    char* director;
	char* actor;
	struct movie* next;
}movie;
 typedef struct director {
    int serial;
    char* director;
	char* sex;
	int birth;
    char* title;
    struct director* next;
}director;
 typedef struct actor {
   int serial;
   char* actor;
   char* sex;
   char* birth;
   char* title;
   struct actor* next;

}actor;
 typedef struct list {
	 movie* p;
	 movie* movie;
	 director* director;
	 actor* actor;
 }List;

void input_command(char *, char *, char *);
void search(char *);
void print(char *,List* list);
void add(char *,List* list);
void update(char *);
void delete(char *);
void sort(char *);
void save(char *);
void func(int);

int main(void)
{
	List* list = (List*)malloc(sizeof(List));
	list->movie = NULL;
	char * input = (char *)malloc(sizeof(char) * 30);
	char * command = (char *)malloc(sizeof(char) * 7);
	char * options = (char *)malloc(sizeof(char) * 20);
	*input = '\0';
	*command = '\0';
	*options = '\0';
	printf(">>Welcome to My Movie<< \n");
	printf("File Loading.....\n");
	printf("You can use add, update, search, sort, save, end commands. \n");
	printf("(movie) ");
	signal(2, func);
	while (1){
		input_command(input, command, options);
		if (!strcmp(command, "search"))
		{
			printf("do search\n");
			search(options);
			printf("(movie) ");
		}
		else if (!strcmp(command, "print"))
		{
			printf("do print\n");
			print(options,list);
			printf("(movie) ");
		}
		else if (!strcmp(command, "add"))
		{
			printf("do add\n");
			add(options, list);
			printf("(movie) ");
			/*int a;
			a = get_length(list);*/
		}
		else if (!strcmp(command, "update"))
		{
			printf("do update\n");
			update(options);
			printf("(movie) ");
		}
		else if (!strcmp(command, "delete"))
		{
			printf("do delete\n");
			delete(options);
			printf("(movie) ");
		}
		else if (!strcmp(command, "sort"))
		{
			printf("do sort\n");
			sort(options);
			printf("(movie) ");
		}
		else if (!strcmp(command, "save"))
		{
			printf("do save\n");
			save(options);
			printf("(movie) ");
		}
		else if (!strcmp(command, "end"))
		{
			break;
		}
		/*else if (!strcmp(command, ""))
		{
			printf("");
			continue;
		}
		else
		{
			printf("command not found.\n");
		}*/
		//printf("p-command : %p\n", command);
		*input = '\0';
		*command = '\0';
		*options = '\0';
	}
	free(input);
	free(command);
	free(options);
	return 0;
}
void func(int c) {
	char a;
	printf("Get Interrupt Signal.\n");
	printf("Do you want to exit myMOVIE program? (Y/N)");
	scanf("%c",&a);
	if (a == 'Y') {
		exit(1);
	}
	return;
}
void input_command(char * input, char * command, char * options)
{
	scanf("%[^\n]", input);
	getchar();
	sscanf(input, "%[^ ]%*[ ]%[^\0]", command, options);
	/*printf("input : ==%s==\n", input);
	printf("command : ==%s==\n", command);
	printf("options : ==%s==\n", options);
	printf("strlen(command)+1 : %d\n", strlen(command) + 1);
	printf("strlen(options)+1 : %d\n", strlen(options) + 1);
	*/
}
void print(char * options,List* list)
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * arg = (char *)malloc(sizeof(char) * 4);
	int num = -1;
	*arg = '\0';

	sscanf(options, "%[amd]%*[ ]%d", arg, &num);

	/*printf("arg : ==%s==\n", arg);
	for (int i = 0; i < strlen(arg); i++)
	{
		printf("*(arg + %d) : ==%c==\n", i, *(arg + i));
	}
	printf("num : %d\n", num);
	printf("strlen(arg)+1 : %d\n", strlen(arg) + 1);
	*/
	if (!strcmp(arg, ""))
	{
		printf("input arg\n");
		free(arg);
		return;
	}
	else if (!strcmp(arg, "m")) {
		printf("%s, ", list->p->title);
		printf("%s \n", list->p->genre);
		printf("D : %s \n", list->p->director);
		while (list->p->next != NULL) {
			printf("%s, ", list->p->next->title);
			printf("%s \n", list->p->next->genre);
			printf("D : %s \n", list->p->next->director);
			list->p = list->p->next;
		}
		printf("%s, ", list->p->title);
		printf("%s \n", list->p->genre);
		printf("D : %s \n", list->p->director);
		return;
	}
	/*if (num < 0)
	{
		printf("input num\n");
		free(arg);
		return;
	}*/

	free(arg);
	printf("end print\n");
}
void search(char * options)
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * op = (char *)malloc(sizeof(char) * 4);
	char * string = (char *)malloc(sizeof(char) * 20);
	*op = '\0';
	*string = '\0';

	sscanf(options, "-%[amd]%*[ ]%[^\0]", op, string);

	printf("op : ==%s==\n", op);
	for (int i = 0; i < strlen(op); i++)
	{
		printf("*(op + %d) : ==%c==\n", i, *(op + i));
	}
	for (int i = 0; i < strlen(string); i++)
	{
		printf("*(string + %d) : ==%c==\n", i, *(string + i));
	}
	printf("strlen(op)+1 : %d\n", strlen(op) + 1);
	printf("strlen(string)+1 : %d\n", strlen(string) + 1);

	if (!strcmp(op, ""))
	{
		printf("input op\n");
		free(op);
		free(string);
		return;
	}
	if (!strcmp(string, ""))
	{
		printf("input string\n");
		free(op);
		free(string);
		return;
	}

	free(op);
	free(string);
	printf("end search\n");
}
void add(char * options, List* list)
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * arg = (char *)malloc(sizeof(char) * 4);
	*arg = '\0';

	sscanf(options, "%[amd]", arg);

	/*printf("arg : ==%s==\n", arg);
	for (int i = 0; i < strlen(arg); i++)
	{
		printf("*(arg + %d) : ==%c==\n", i, *(arg + i));
	}
	printf("strlen(arg)+1 : %d\n", strlen(arg) + 1);

	if (!strcmp(arg, ""))
	{
		printf("input op\n");
		free(arg);
		return;
	}*/
	if (!strcmp(options,"m")) {
		FILE *fp;
		//int i = 1;
		fp = fopen("movie_list", "a+w");
		if (list->movie == NULL) {
			list->movie = (movie*)malloc(sizeof(movie));
			//list->movie->serial = i;
			list->movie->title = (char*)malloc(sizeof(char) * 40);
			printf("title > ");
			gets(list->movie->title);
			fprintf(fp, "%s:", list->movie->title);
			list->movie->genre = (char*)malloc(sizeof(char) * 15);
			printf("genre > ");
			gets(list->movie->genre);
			fprintf(fp, "%s:", list->movie->genre);
			list->movie->director = (char*)malloc(sizeof(char) * 40);
			printf("director > ");
			gets(list->movie->director);
			fprintf(fp, "%s:", list->movie->director);
			printf("year > ");
			scanf("%d", &list->movie->year);
			fprintf(fp, "%d:", list->movie->year);
			printf("runtime > ");
			scanf("%d", &list->movie->runtime);
			fprintf(fp, "%d \n", list->movie->runtime);
			list->movie->next = NULL;
			list->p = list->movie;
			//i++;
			fclose(fp);
			return;
		}
		else {
			//list->movie->serial = i;
			list->movie->next = (movie*)malloc(sizeof(movie));
			list->movie->next->title = (char*)malloc(sizeof(char) * 40);
			printf("title > ");
			gets(list->movie->next->title);
			fprintf(fp, "%s:", list->movie->next->title);
			list->movie->next->genre = (char*)malloc(sizeof(char) * 15);
			printf("genre > ");
			gets(list->movie->next->genre);
			printf("%s \n", list->movie->next->genre);
			fprintf(fp, "%s:", list->movie->next->genre);
			list->movie->next->director = (char*)malloc(sizeof(char) * 40);
			printf("director > ");
			gets(list->movie->next->director);
			fprintf(fp, "%s:", list->movie->next->director);
			printf("year > ");
			scanf("%d", &list->movie->next->year);
			fprintf(fp, "%d:", list->movie->next->year);
			printf("runtime > ");
			scanf("%d", &list->movie->next->runtime);
			fprintf(fp, "%d \n", list->movie->next->runtime);
			list->movie->next->next = NULL;
			list->movie = list->movie->next;
			//i++;
			fclose(fp);
			return;
		}
			}
		/*else if (!strcmp(options, "d")) {
		list->director = (director*)malloc(sizeof(director*));
		list->director->director = (char*)malloc(sizeof(char) * 40);
		printf("director > ");
		gets(list->movie->director);
		list->director->sex = (char*)malloc(sizeof(char) * 3);
		printf("sex > ");
		scanf("%c",list->director->sex);
		printf("birth > ");
		scanf("%d", &list->director->birth);
		//printf(" > "); title 연결리스트
		
	}*/

	free(arg);
	printf("end add\n");
}
void writeFile(FILE* fp) {

}
void update(char * options)
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * arg = (char *)malloc(sizeof(char) * 4);
	char * op = (char *)malloc(sizeof(char) * 7);
	int num = 0;
	*arg = '\0';
	*op = '\0';

	sscanf(options, "%[amd]%*[ ]%[tgdyransbm]%*[ ]%d", arg, op, &num);

	printf("arg : ==%s==\n", arg);
	for (int i = 0; i < strlen(arg); i++)
	{
		printf("*(arg + %d) : ==%c==\n", i, *(arg + i));
	}
	printf("op : ==%s==\n", op);
	for (int i = 0; i < strlen(op); i++)
	{
		printf("*(op + %d) : ==%c==\n", i, *(op + i));
	}
	printf("num : %d\n", num);
	printf("strlen(arg)+1 : %d\n", strlen(arg) + 1);
	printf("strlen(op)+1 : %d\n", strlen(op) + 1);

	if (!strcmp(arg, ""))
	{
		printf("input arg\n");
		free(arg);
		free(op);
		return;
	}
	if (!strcmp(op, ""))
	{
		printf("input op\n");
		free(arg);
		free(op);
		return;
	}
	free(arg);
	free(op);
	printf("end update\n");
}
void delete(char * options)
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * arg = (char *)malloc(sizeof(char) * 4);
	int num = -1;
	*arg = '\0';

	sscanf(options, "%[amd]%*[ ]%d", arg, &num);

	printf("arg : ==%s==\n", arg);
	for (int i = 0; i < strlen(arg); i++)
	{
		printf("*(arg + %d) : ==%c==\n", i, *(arg + i));
	}
	printf("num : %d\n", num);
	printf("strlen(arg)+1 : %d\n", strlen(arg) + 1);

	if (!strcmp(arg, ""))
	{
		printf("input arg\n");
		free(arg);
		return;
	}
	if (num < 0)
	{
		printf("input num\n");
		free(arg);
		return;
	}

	free(arg);
	printf("end delete\n");
}
void sort(char * options)
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * arg = (char *)malloc(sizeof(char) * 4);
	char * op = (char *)malloc(sizeof(char) * 7);
	char * op_f = (char *)malloc(sizeof(char) * 2);
	char * file_name = (char *)malloc(sizeof(char) * 20);
	*arg = '\0';
	*op = '\0';
	*op_f = '\0';
	*file_name = '\0';

	sscanf(options, "%[amd]%*[ ]%[tgdyransbm]%*[ ]-%[f]%*[ ]%[^\0]", arg, op, op_f, file_name);

	printf("arg : ==%s==\n", arg);
	for (int i = 0; i < strlen(arg); i++)
	{
		printf("*(arg + %d) : ==%c==\n", i, *(arg + i));
	}
	printf("op : ==%s==\n", op);
	for (int i = 0; i < strlen(op); i++)
	{
		printf("*(op + %d) : ==%c==\n", i, *(op + i));
	}
	printf("op_f : ==%s==\n", op_f);
	printf("file_name : ==%s==\n", file_name);
	printf("strlen(arg)+1 : %d\n", strlen(arg) + 1);
	printf("strlen(op)+1 : %d\n", strlen(op) + 1);
	printf("strlen(op_f)+1 : %d\n", strlen(op_f) + 1);
	printf("strlen(file_name)+1 : %d\n", strlen(file_name) + 1);

	if (!strcmp(arg, ""))
	{
		printf("input arg\n");
		free(arg);
		free(op);
		free(op_f);
		free(file_name);
		return;
	}
	if (!strcmp(op, ""))
	{
		printf("input op\n");
		free(arg);
		free(op);
		free(op_f);
		free(file_name);
		return;
	}
	if (!strcmp(op_f, ""))
	{
		// -f 옵션 사용하지 않음
		printf("no use op_f\n");
	}
	else
	{
		// -f 옵션 사용
		printf("use op_f\n");
		if (!strcmp(file_name, ""))
		{
			printf("input file_name\n");
			free(arg);
			free(op);
			free(op_f);
			free(file_name);
			return;
		}
	}

	free(arg);
	free(op);
	free(op_f);
	free(file_name);
	printf("end sort\n");
}
void save(char * options)
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * arg = (char *)malloc(sizeof(char) * 4);
	char * op = (char *)malloc(sizeof(char) * 7);
	char * op_f = (char *)malloc(sizeof(char) * 2);
	char * file_name = (char *)malloc(sizeof(char) * 20);
	*arg = '\0';
	*op = '\0';
	*op_f = '\0';
	*file_name = '\0';

	sscanf(options, "%[amd]%*[ ]%[tgdyransbm]%*[ ]-%[f]%*[ ]%[^\0]", arg, op, op_f, file_name);

	printf("arg : ==%s==\n", arg);
	for (int i = 0; i < strlen(arg); i++)
	{
		printf("*(arg + %d) : ==%c==\n", i, *(arg + i));
	}
	printf("op : ==%s==\n", op);
	for (int i = 0; i < strlen(op); i++)
	{
		printf("*(op + %d) : ==%c==\n", i, *(op + i));
	}
	printf("op_f : ==%s==\n", op_f);
	printf("file_name : ==%s==\n", file_name);
	printf("strlen(arg)+1 : %d\n", strlen(arg) + 1);
	printf("strlen(op)+1 : %d\n", strlen(op) + 1);
	printf("strlen(op_f)+1 : %d\n", strlen(op_f) + 1);
	printf("strlen(file_name)+1 : %d\n", strlen(file_name) + 1);

	if (!strcmp(arg, ""))
	{
		printf("input arg\n");
		free(arg);
		free(op);
		free(op_f);
		free(file_name);
		return;
	}
	if (!strcmp(op, ""))
	{
		printf("input op\n");
		free(arg);
		free(op);
		free(op_f);
		free(file_name);
		return;
	}
	if (!strcmp(op_f, ""))
	{
		// -f 옵션 사용하지 않음
		printf("no use op_f\n");
	}
	else
	{
		// -f 옵션 사용
		printf("use op_f\n");
		if (!strcmp(file_name, ""))
		{
			printf("input file_name\n");
			free(arg);
			free(op);
			free(op_f);
			free(file_name);
			return;
		} 
	}

	free(arg);
	free(op);
	free(op_f);
	free(file_name);
	printf("end save\n");
}

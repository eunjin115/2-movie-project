#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define EMPTY -1
#define MAX_LEN 30
#define FULL (MAX_LEN-1)
typedef struct stack
{
        char * s;
        int top;
} stack;
static stack s;
void reset() {
        s.top = EMPTY;
}
void push(char c) {
        s.top++;
        *(s.s + s.top) = c;
}
char pop(void) {
        return *(s.s +s.top--);
}
bool empty(void) {
        return (s.top == EMPTY);
}
bool full(void) {
        return (s.top == FULL);
}
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
	char* birth;
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
	 director* q;
	 actor* actor;
	 actor* r;
 }List;

void input_command(char *, char *, char *);
void search(char *, List *);
void print(char *,List* list);
void add(char *,List* list);
void update(char *);
void delete(char *);
void sort(char *);
void save(char *);
void func(int);
void file_loading(List *);

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
	file_loading(list);
	printf("You can use add, update, search, sort, save, end commands. \n");
	signal(2, func);
	while (1){
		printf("(movie) ");
		input_command(input, command, options);
		if (!strcmp(command, "search"))
		{
			search(options);
		}
		else if (!strcmp(command, "print"))
		{
			print(options,list);
		}
		else if (!strcmp(command, "add"))
		{
			add(options, list);
			/*int a;
			a = get_length(list);*/
		}
		else if (!strcmp(command, "update"))
		{
			update(options);
		}
		else if (!strcmp(command, "delete"))
		{
			delete(options);
		}
		else if (!strcmp(command, "sort"))
		{
			sort(options);
		}
		else if (!strcmp(command, "save"))
		{
			save(options);
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
void func(int c) { //신호처리함수
	char a;
	printf("Get Interrupt Signal.\n");
	printf("Do you want to exit myMOVIE program? (Y/N)");
	scanf("%c",&a);
	if (a == 'Y') {
		exit(1);
	}
	return;
}
void input_command(char * input, char * command, char * options)//command와options구분하는함수
{
	scanf("%[^\n]", input);
	getchar();
	sscanf(input, "%[^ ]%*[ ]%[^\0]", command, options);
}
void print(char * options,List* list) //print함수
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

	free(arg);
	printf("end print\n");
}
void search(char * options, List * list)
{
        if (!strcmp(options, "")) // 옵션이 입력되지 않은 경우 오류처리
        {
                printf("input options\n");
                return;
        }

        char * op = (char *)malloc(sizeof(char)*4);
        char * string = (char *)malloc(sizeof(char)*MAX_LEN);
        *op = '\0';
        *string = '\0';

        sscanf(options, "-%[amd]%*[ ]%[^\0]", op, string);

        if (!strcmp(op, "")) //부적절한 옵션인 경우 오류처리
        {
                printf("input op\n");
                free(op);
                free(string);
                return;
        }
        if (!strcmp(string, "")) //부적절한 옵션인 경우 오류처리
        {
                printf("input string\n");
                free(op);
                free(string);
                return;
        }
        char * comp_str = (char *)malloc(sizeof(char)*MAX_LEN);

        for (int l = 0; l < strlen(op); l++)
        {
                if (*(op+l) == 'a')
                {
                        for (int i = 0; i < strlen(string); i++)
                        {
                                if (*(string + i) == '?') //메타문자 ?사용시 아스키코드값을 일일이 비교하여 검색
				{
                                        for (int j = 32; j < 127; j++)
                                        {
                                                while (list -> actor -> next != NULL)
                                                {
                                                        *(string + i) = j;
                                                        if (!strcmp(string, list->actor->actor))
                                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                                        if (!strcmp(string, list->actor->sex))
                                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                                        if (!strcmp(string, list->actor->birth))
                                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                                        if (!strcmp(string, list->actor->title))
                                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                                }
                                        }
                                }
                        }
                        if (*(string + strlen(string)-1) == '*')//메타문자 *이 문자열 뒤에 있는 경우
                        {
                                sscanf(string, "%[^*]", comp_str);
                                // strncmp 이용 리스트 전체의 내용과 comp_str 비교
                                while (list->actor->next != NULL)
                                {
                                        if (!strncmp(comp_str, list->actor->actor, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        if (!strncmp(comp_str, list->actor->birth, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        if (!strncmp(comp_str, list->actor->sex, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        if (!strncmp(comp_str, list->actor->title, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        list -> actor = list->actor ->next;
                                }
                        }
                        else if (*string == '*') //메타문자 *이 문자열 앞에 있는 경우
                        {
                                char * r_comp_str = (char *)malloc(sizeof(char)*MAX_LEN);
                                char * r_list = (char *)malloc(sizeof(char)*MAX_LEN);
                                s.s = (char *)malloc(sizeof(char)*MAX_LEN);
                                reset();
                                sscanf(string, "*%[^\0]", comp_str); //스택을 이용하여 비교할 문자열 string을 뒤집음
                                reset();
                                for (int i = 0; i < strlen(comp_str); i++)
                                {
                                        if (!full())
                                                push(*(comp_str + i));
                                }
                                for (int j = 0; !empty(); j++)
                                {
                                        *(r_comp_str + j) = pop();
                                }
                                // 리스트 내용을 뒤집어 r_list 만든 후 strncmp 이용 r_list 내용과 r_comp_str 비교
                                while (list->actor->next != NULL)
                                {
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->actor->actor + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->actor->birth + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->actor->sex + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->actor->title + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        list -> actor = list->actor ->next;
                                }
                                free(r_comp_str);
                                free(r_list);
                        }
                        else //메타문자가 없는 경우 그대로 검색
                        {
                                while (list->actor->next != NULL)
                                {
                                        if (!strcmp(string, list->actor->actor))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        if (!strcmp(string, list->actor->birth))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        if (!strcmp(string, list->actor->sex))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        if (!strcmp(string, list->actor->title))
                                                printf("%d:%s:%s:%s:%s\n", list->actor->serial, list->actor->actor, list->actor->sex, list->actor->birth, list->actor->title);
                                        list -> actor = list->actor ->next;
                                }
                        }
                }
                if (*(op+l) == 'd')
                {
                        for (int i = 0; i < strlen(string); i++)
                        {
                                if (*(string + i) == '?')
                                {
                                        for (int j = 32; j < 127; j++)
                                        {
                                                while (list -> director -> next != NULL)
                                                {
                                                        *(string + i) = j;
                                                        if (!strcmp(string, list->director->director))
                                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                                        if (!strcmp(string, list->director->sex))
                                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                                        if (!strcmp(string, list->director->birth))
                                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                                        if (!strcmp(string, list->director->title))
                                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                                }
                                        }
                                }
                        }
                        if (*(string + strlen(string)-1) == '*')
                        {
                                sscanf(string, "%[^*]", comp_str);
                                // strncmp 이용 리스트 전체의 내용과 comp_str 비교
                                while (list->director->next != NULL)
                                {
                                        if (!strncmp(comp_str, list->director->director, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strncmp(comp_str, list->director->birth, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strncmp(comp_str, list->director->sex, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strncmp(comp_str, list->director->title, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        list -> director = list->director ->next;
                                }
                        }
                        else if (*string == '*')
                        {
                                char * r_comp_str = (char *)malloc(sizeof(char)*MAX_LEN);
                                char * r_list = (char *)malloc(sizeof(char)*MAX_LEN);
                                s.s = (char *)malloc(sizeof(char)*MAX_LEN);
                                reset();
                                sscanf(string, "*%[^\0]", comp_str);
                                reset();
                                for (int i = 0; i < strlen(comp_str); i++)
                                {
                                        if (!full())
                                                push(*(comp_str + i));
                                }
                                for (int j = 0; !empty(); j++)
                                {
                                        *(r_comp_str + j) = pop();
                                }
                                // 리스트 내용 역전해 r_list 만든 후 strncmp 이용 r_list 내용과 r_comp_str 비교
                                while (list->actor->next != NULL)
                                {
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->director->director + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->director->birth + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->actor->sex + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->director->title + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        list -> director = list->director ->next;
                                }
                                free(r_comp_str);
                                free(r_list);
                        }
                        else
                        {
                                while (list->director->next != NULL)
                                {
                                        if (!strcmp(string, list->director->director))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strcmp(string, list->director->birth))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strcmp(string, list->director->sex))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strcmp(string, list->director->title))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        list -> director = list->director ->next;
                                }
                        }
                }
                if (*(op+l) == 'm')
                {
                        for (int i = 0; i < strlen(string); i++)
                        {
                                if (*(string + i) == '?')
                                {
                                        for (int j = 32; j < 127; j++)
                                        {
                                                while (list -> movie -> next != NULL)
                                                {
                                                        *(string + i) = j;
                                                        if (!strcmp(string, list->movie->title))
                                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                                        if (!strcmp(string, list->movie->genre))
                                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                                        if (!strcmp(string, list->movie->director))
                                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                                        if (!strcmp(string, list->movie->actor))
                                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                                }
                                        }
                                }
                        }
                        if (*(string + strlen(string)-1) == '*')
                        {
                                sscanf(string, "%[^*]", comp_str);
                                // strncmp 이용 리스트 전체의 내용과 comp_str 비교
                                while (list->movie->next != NULL)
                                {
                                        if (!strncmp(comp_str, list->movie->title, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        if (!strncmp(comp_str, list->movie->genre, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        if (!strncmp(comp_str, list->movie->director, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        if (!strncmp(comp_str, list->movie->actor, sizeof(comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        list -> movie = list->movie ->next;
                                }
                        }
                        else if (*string == '*')
                        {
                                char * r_comp_str = (char *)malloc(sizeof(char)*MAX_LEN);
                                char * r_list = (char *)malloc(sizeof(char)*MAX_LEN);
                                s.s = (char *)malloc(sizeof(char)*MAX_LEN);
                                reset();
                                sscanf(string, "*%[^\0]", comp_str);
                                reset();
                                for (int i = 0; i < strlen(comp_str); i++)
                                {
                                        if (!full())
                                                push(*(comp_str + i));
                                }
                                for (int j = 0; !empty(); j++)
                                {
                                        *(r_comp_str + j) = pop();
                                }
                                // 리스트 내용 역전해 r_list 만든 후 strncmp 이용 r_list 내용과 r_comp_str 비교
                                while (list->movie->next != NULL)
                                {
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->movie->title + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->movie->genre + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->movie->director + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        reset();
                                        for (int i = 0; i < strlen(comp_str); i++)
                                        {
                                                if (!full())
                                                        push(*(list->movie->director + i));
                                        }
                                        for (int j = 0; !empty(); j++)
                                        {
                                                *(r_list + j) = pop();
                                        }
                                        if (!strncmp(r_comp_str, r_list, sizeof(r_comp_str)))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        list -> movie = list->movie ->next;
                                }
                                free(r_comp_str);
                                free(r_list);
                        }
                        else
                        {
                                while (list->director->next != NULL)
                                {
                                        if (!strcmp(string, list->movie->title))
                                                printf("%d:%s:%s:%s:%s\n", list->movie->serial, list->movie->title, list->movie->genre, list->movie->director, list->movie->actor);
                                        if (!strcmp(string, list->movie->genre))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strcmp(string, list->movie->director))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        if (!strcmp(string, list->movie->actor))
                                                printf("%d:%s:%s:%s:%s\n", list->director->serial, list->director->director, list->director->sex, list->director->birth, list->director->title);
                                        list -> director = list->director ->next;
                                }
                        }
                }
        }
        free(comp_str);
        free(op);
        free(string);
}
void add(char * options, List* list)//add함수
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}

	char * arg = (char *)malloc(sizeof(char) * 4);
	*arg = '\0';

	sscanf(options, "%[amd]", arg); //옵션으로 amd중 하나를읽어들임

	if (!strcmp(options,"m")) {
		FILE *fp;
		//int i = 1;
		fp = fopen("movie_list", "a+w");//movie_list파일을 열어 정보들을 저장함
		if (list->movie == NULL) { //NULL을포인트하는 처음의 영화구조체를 if문에서 영화에 관한 정보를받고 이후 영화구조체에 저장할정보들을else문에서입력받음
			list->movie = (movie*)malloc(sizeof(movie));
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
			fclose(fp);
			return;
		}
		else {
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
			list->movie = list->movie->next;// 현재 영화구조체가 다음 영화구조체를 참조할 수 있게함
			fclose(fp);
			return;
		}
		else if (!strcmp(options, "d")) //add d
		{
			 FILE* dp;
        		 dp =fopen("direcor_list","a+w");//director_list파일을 열어 감독에 관한 정보들을 입력받는다
	         if(list->director == NULL)
		 {
	         list->director = (director*)malloc(sizeof(director));
	         list->director->director = (char*)malloc(sizeof(char) * 40);
	         printf("director > ");
	         gets(list->director->director);
 		 fprintf(dp,"%s:",list->director->director);
 	         list->director->sex = (char*)malloc(sizeof(char) * 3);
	         printf("sex > ");
	         scanf("%c",list->director->sex);
	         fprintf(dp,"%c:",list->director->sex);
	         printf("birth > ");
	         scanf("%d", &list->director->birth);
	         getchar();	
	         fprintf(dp,"%d:",list->director->birth);
	         printf("title > ");
 	         scanf("%[^\n]",list->director->title);
        	 getchar();
 	         fprintf(dp,"%s:",list->director->title);
	         list->director->next = NULL;
	         list->q = list->director;
        	 fclose(dp);
		 }
	         else{
             		list->director->next=(director*)malloc(sizeof(director));//현재 감독구조체가 다음 감독구조체를 참조하기 위한 동적할당
         	        list->director->next->director = (char*)malloc(sizeof(char)*20);
      		        printf("director > ");
  	                gets(list->director->next->director);
 	                fprintf(dp,"%s:",list->director->next->director);
	                list->director->next->sex = (char*)malloc(sizeof(char)*5);
	                printf("sex > ");
     		        scanf("%c",list->director->next->sex);
           	        getchar();
      		        printf("%s",list->director->next->sex);
     		        fprintf(dp,"%c:",list->director->next->sex);
       		        printf("birth > ");
      		        scanf("%d",&list->director->next->birth);
      		        fprintf(dp,"%d:",list->director->next->birth);
  	                printf("title > ");
	                scanf("%[^\n]",list->director->next->title);
     		        getchar();
	                fprintf(dp,"%s:",list->director->next->title);
    	                list->director->next->next = NULL;
         	        list->director = list->director->next;//현재 감독구조체가 다음 감독구조체를 참조할 수 있게함
             		fclose(dp);
             		return;
        	       }
      		}

    else if (!strcmp(options,"a")) //add a
    {
        FILE *ap;
        ap=fopen("actor_list","a+w");//actor_list파일을 열어 actor에 관한 정보를 입력받는다
    if(list->actor == NULL)
        {
        list->actor=(actor*)malloc(sizeof(actor));
        list->actor->actor=(char*)malloc(sizeof(char)*20);
        list->actor->next=(actor*)malloc(sizeof(actor));
        printf("actor > ");
        scanf("%[^\n]",list->actor->actor);
        getchar();
        fprintf(ap,"%s:",list->actor->actor);
        printf("sex > ");
        scanf("%c", list->actor->sex);
        getchar();
        fprintf(ap,"%c:",list->actor->sex);
        printf("birth > ");
        scanf("%d", &list->actor->birth);
        getchar();
        fprintf(ap,"%d:",list->actor->birth);
        printf("title > ");
        scanf("%[^\n]", list->actor->title);
        getchar();
        fprintf(ap,"%s:",list->actor->title);
        list->actor->next = NULL;
        list->r = list->actor;
        }
        else
        {
            list->actor->next=(actor*)malloc(sizeof(actor));
            list->actor->next->actor=(char*)malloc(sizeof(char)*20);
            printf("actor > ");
            scanf("%[^\n]",list->actor->next->actor);
            getchar();
            fprintf(ap,"%s:",list->actor->next->actor);
            printf("sex > ");
            scanf("%[^\n]",list->actor->next->sex);
            getchar();
            fprintf(ap,"%c:",list->actor->next->sex);
            printf("birth > ");
        	scanf("%d",&list->actor->next->birth);
            fprintf(ap,"%d:",list->actor->next->birth);
            printf("title > ");
            scanf("%[^\n]", list->actor->next->title);
            getchar();
            fprintf(ap,"%s:",list->actor->next->title);
            list->actor->next->next = NULL;
            list->actor = list->actor->next;//배우구조체가 다음의 배우구조체를 참조하게함
            fclose(ap);
            return;
          }

    }
      free(arg);
      free(list);
      free(movie);
      free(actor);
      free(director);
      printf("end add\n");
 }
	
	}

	free(arg);
	printf("end add\n");
}
void writeFile(FILE* fp) {

}
void update(char * options)//update함수
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

	sscanf(options, "%[amd]%*[ ]%[tgdyransbm]%*[ ]%d", arg, op, &num);//command와option,숫자 읽어  각각 arg op num에저장함

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
void delete(char * options)//delete함수
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

	if (strcmp(arg, "m")) {
		list->movie = (movie *)malloc(sizeof(movie));
		FILE *mf = fopen("movie_log", "r");
		if (fscanf(mf, "%d", &list->movie->serial) == num) {

		}
		else
			printf("  No such record\n");
		fclose(mf);
	}
	else if (strcmp(arg, "d")) {
		list->director = (director *)malloc(sizeof(director));
		FILE *df = fopen("director_log", "r");
		if (fscanf(df, "%d", &list->director->serial) == num) {

		}
		else
			printf("  No such record\n");
		fclose(df);
	}
	else if (strcmp(arg, "a")) {
		list->actor = (actor *)malloc(sizeof(actor));
		FILE *af = fopen("actor_log", "r");
		if (fscanf(af, "%d", &list->actor->serial) == num) {

		}
		else
			printf("  No such record\n");
		fclose(af);
	}
	
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
void sort(char * options)//sort함수
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
void save(char * options)//save함수
{
	if (!strcmp(options, ""))
	{
		printf("input options\n");
		return;
	}
	
FILE *mp, *dp, *ap;
	mp = fopen("movie_list", "w");
	dp = fopen("director_list", "w");
	ap = fopen("actor_list", "w");
	
	char * arg = (char *)malloc(sizeof(char) * 4);
	char * op = (char *)malloc(sizeof(char) * 7);
	char * op_f = (char *)malloc(sizeof(char) * 2);
	char * file_name = (char *)malloc(sizeof(char) * 20);
	*arg = '\0';
	*op = '\0';
	*op_f = '\0';
	*file_name = '\0';

	sscanf(options, "%[amd]%*[ ]%[tgdyransbm]%*[ ]-%[f]%*[ ]%[^\0]", arg, op, op_f, file_name);

	if (strcmp(arg, "m")){
		if (strcmp(op, "t")) 
			fprintf(mp, "%s", movie->title);
		else if (strcmp(op, "g")) 
			fprintf(mp, "%s", movie->genre);
		else if (strcmp(op, "d")) 
			fprintf(mp, "%s", movie->director);
		else if (strcmp(op, "y")) 
			fprintf(mp, "%d", movie->year);
		else if (strcmp(op, "r")) 
			fprintf(mp, "%d", movie->runtime);
		else if (strcmp(op, "a")) 
			fprintf(mp, "%s", movie->actor);
	}
	fclose(mp);

	else if (strcmp(arg, "d")) {
		if (strcmp(op, "n") 
			fprintf(dp, "%s", director->name);
		else if (strcmp(op, "s")) 
			fprintf(dp, "%s", director->sex);
		else if (strcmp(op, "b")) 
			fprintf(dp, "%d", director->birth);
		else if (strcmp(op, "m")) 
			fprintf(dp, "%s", director->movie);
	}
	fclose(dp);

	else if (strcmp(arg, "a")) {
		if (strcmp(op, "n")) 
			fprintf(ap, "%s", actor->name);
		else if (strcmp(op, "s"))
			fprintf(ap, "%s", actor->sex);
		else if (strcmp(op, "b"))
			fprintf(ap, "%d", actor->birth);
		else if (strcmp(op, "m"))
			fprintf(ap, "%s", actor->movie);
	}
	fclose(ap);
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
void file_loading(List * list)
{
        movie * l_movie = (movie *)malloc(sizeof(movie));
        movie * head_m = (movie *)malloc(sizeof(movie));

        director * l_director = (director *)malloc(sizeof(director));
        director * head_d = l_director;

        actor * l_actor = (actor *)malloc(sizeof(actor));
        actor * head_a = l_actor;

        list -> movie = (movie *)malloc(sizeof(movie));
        list -> movie = l_movie;
        list -> director = (director *)malloc(sizeof(director));
        list -> director = l_director;
        list -> actor = (actor *)malloc(sizeof(actor));;
        list -> actor = l_actor;

        FILE * mlog_file, * alog_file, * dlog_file;

        printf("File loading......\n");
        mlog_file = fopen("movie_log", "r");
        if (mlog_file == NULL)
        {
                printf("no movie_log file\n");
                return;
        }
        rewind(mlog_file);
        char * m_command = (char *)malloc(sizeof(char)*10);
        char * m_options = (char *)malloc(sizeof(char)*90);
        int m_serial_number = 0;
        char * m_title = (char *)malloc(sizeof(char)*10);
        char * m_genre = (char *)malloc(sizeof(char)*10);
        char * m_director = (char *)malloc(sizeof(char)*10);
        char * m_year = (char *)malloc(sizeof(char)*10);
        char * m_time = (char *)malloc(sizeof(char)*10);
        char * m_actors = (char *)malloc(sizeof(char)*50);
        do
        {
                *m_command = '\0';
                m_serial_number = 0;
                *m_title = '\0';
                *m_genre = '\0';
                *m_director = '\0';
                *m_year = '\0';
                *m_time = '\0';
                *m_actors = '\0';
                fscanf(mlog_file, "%[^:]:%d:%[^\n\0]", m_command, &m_serial_number, m_options);

                if (!strcmp(m_command, "add"))
                {
                        sscanf(m_options, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^\n\0]", m_title, m_genre, m_director, m_year, m_time, m_actors);
                        if (list->movie == NULL)
                        {
                                list->movie -> serial = m_serial_number;
                                list->movie -> title = (char *)malloc(sizeof(char)*10);
                                list->movie -> title = m_title;
                                list->movie -> genre = (char *)malloc(sizeof(char)*10);
                                list->movie -> genre = m_genre;
                                list->movie -> director = (char *)malloc(sizeof(char)*10);
                                list->movie -> director = m_director;
                                list->movie -> actor = (char *)malloc(sizeof(char)*50);
                                list->movie -> actor = m_actors;
                                list->movie -> next = NULL;
                                head_m = list->movie;
                        }
                        else
                        {
                                list->movie -> next = (movie *)malloc(sizeof(movie));
                                list->movie -> serial = m_serial_number;
                                list->movie -> title = (char *)malloc(sizeof(char)*10);
                                list->movie -> title = m_title;
                                list->movie -> genre = (char *)malloc(sizeof(char)*10);
                                list->movie -> genre = m_genre;
                                list->movie -> director = (char *)malloc(sizeof(char)*10);
                                list->movie -> director = m_director;
                                list->movie -> actor = (char *)malloc(sizeof(char)*50);
                                list->movie -> actor = m_actors;
                                list->movie -> next -> next = NULL;
                                list->movie = list->movie -> next;
                        }
                }
                else if (!strcmp(m_command, "update"))
                {
                        sscanf(m_options, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^\n\0]", m_title, m_genre, m_director, m_year, m_time, m_actors);
                        while (list->movie->serial == m_serial_number)
                                list->movie = list->movie -> next;
                        if (m_title != "=")
                                list->movie -> title = m_title;
                        if (m_genre != "=")
                                list->movie -> genre = m_genre;
                        if (m_director != "=")
                                list->movie -> director = m_director;
                        if (m_actors != "=")
                                list->movie -> actor = m_actors;
                }
                else if (!strcmp(m_command, "delete"))
                {
                        l_movie = l_movie -> next -> next;
                }
                else break;
        }while (getc(mlog_file) == '\n');
        fclose(mlog_file);
        free(m_command);
        free(m_options);
        free(m_title);
        free(m_genre);
        free(m_director);
        free(m_year);
        free(m_time);
        free(m_actors);

        dlog_file = fopen("director_log", "r");
        if (dlog_file == NULL)
        {
                printf("no director_log file\n");
                return;
        }
        rewind(dlog_file);
        char * d_command = (char *)malloc(sizeof(char)*10);
        char * d_options = (char *)malloc(sizeof(char)*90);
        int d_serial_number = 0;
        char * d_name = (char *)malloc(sizeof(char)*10);
        char * d_sex = (char *)malloc(sizeof(char)*10);
        char * d_birth = (char *)malloc(sizeof(char)*10);
        char * d_best_movie = (char *)malloc(sizeof(char)*50);
        do
        {
                *d_command = '\0';
                d_serial_number = 0;
                *d_name = '\0';
                *d_sex = '\0';
                *d_birth = '\0';
                *d_best_movie = '\0';
                fscanf(dlog_file, "%[^:]:%d:%[^\n\0]", d_command, &d_serial_number, d_options);

                if (!strcmp(d_command, "add"))
                {
                        sscanf(d_options, "%[^:]:%[^:]:%[^:]:%[^\n\0]", d_name, d_sex, d_birth, d_best_movie);
                        if (list->director == NULL)
                        {
                                list->director -> serial = d_serial_number;
                                list->director -> director = (char *)malloc(sizeof(char)*10);
                                list->director -> director = d_name;
                                list->director -> sex = (char *)malloc(sizeof(char)*10);
                                list->director -> sex = d_sex;
                                list->director -> birth = (char *)malloc(sizeof(char)*10);
                                list->director -> birth = d_birth;
                                list->director -> title = (char *)malloc(sizeof(char)*50);
                                list->director -> title = d_best_movie;
                                list->director -> next = NULL;
                                head_d = list->director;
                        }
                        else
                        {
                                list->director -> next = (director *)malloc(sizeof(director));
                                list->director -> serial = d_serial_number;
                                list->director -> director = (char *)malloc(sizeof(char)*10);
                                list->director -> director = d_name;
                                list->director -> sex = (char *)malloc(sizeof(char)*10);
                                list->director -> sex = d_sex;
                                list->director -> birth = (char *)malloc(sizeof(char)*10);
                                list->director -> birth = d_birth;
                                list->director -> title = (char *)malloc(sizeof(char)*50);
                                list->director -> title = d_best_movie;
                                list->director -> next -> next = NULL;
                                list->director = list->director -> next;
                        }
                }
                else if (!strcmp(m_command, "update"))
                {
                        sscanf(d_options, "%[^:]:%[^:]:%[^:]:%[^\n\0]", d_name, d_sex, d_birth, d_best_movie);

                        while (list->director->serial == d_serial_number)
                                list->director = list->director -> next;
                        if (d_name != "=")
                                list->director -> director = d_name;
                        if (d_sex != "=")
                                list->director -> sex = d_sex;
                        if (d_birth != "=")
                                list->director -> birth = d_birth;
                        if (d_best_movie != "=")
                                list->director -> title = d_best_movie;
                }
                else if (!strcmp(m_command, "delete"))
                {
                        list->director = list->director -> next -> next;
                }
                else break;
        }while (getc(dlog_file) == '\n');
        fclose(dlog_file);
        free(d_command);
        free(d_options);
        free(d_name);
        free(d_sex);
        free(d_birth);
        free(d_best_movie);

        alog_file = fopen("actor_log", "r");
        if (alog_file == NULL)
        {
                printf("no actor_log file\n");
                return;
        }
        rewind(alog_file);
        char * a_command = (char *)malloc(sizeof(char)*10);
        char * a_options = (char *)malloc(sizeof(char)*90);
        int a_serial_number = 0;
        char * a_name = (char *)malloc(sizeof(char)*10);
        char * a_sex = (char *)malloc(sizeof(char)*10);
        char * a_birth = (char *)malloc(sizeof(char)*10);
        char * a_best_movie = (char *)malloc(sizeof(char)*50);
        do
        {
                *a_command = '\0';
                a_serial_number = 0;
                *a_name = '\0';
                *a_sex = '\0';
                *a_birth = '\0';
                *a_best_movie = '\0';
                fscanf(alog_file, "%[^:]:%d:%[^\n\0]", a_command, &a_serial_number, a_options);

                if (!strcmp(a_command, "add"))
                {
                        sscanf(a_options, "%[^:]:%[^:]:%[^:]:%[^\n\0]", a_name, a_sex, a_birth, a_best_movie);
                        if (list->actor == NULL)
                        {
                                list->actor -> serial = a_serial_number;
                                list->actor -> actor = (char *)malloc(sizeof(char)*10);
                                list->actor -> actor = a_name;
                                list->actor -> sex = (char *)malloc(sizeof(char)*10);
                                list->actor -> sex = a_sex;
                                list->actor -> birth = (char *)malloc(sizeof(char)*10);
                                list->actor -> birth = a_birth;
                                list->actor -> title = (char *)malloc(sizeof(char)*50);
                                list->actor -> title = a_best_movie;
                                list->actor -> next = NULL;
                                head_a = list -> actor;
                        }
                        else
                        {
                                list->actor -> next = (actor *)malloc(sizeof(actor));
                                list->actor -> serial = a_serial_number;
                                list->actor -> actor = (char *)malloc(sizeof(char)*10);
                                list->actor -> actor = a_name;
                                list->actor -> sex = (char *)malloc(sizeof(char)*10);
                                list->actor -> sex = a_sex;
                                list->actor -> birth = (char *)malloc(sizeof(char)*10);
                                list->actor -> birth = a_birth;
                                list->actor -> title = (char *)malloc(sizeof(char)*50);
                                list->actor -> title = a_best_movie;
                                list->actor -> next -> next = NULL;
                                list->actor = list->actor -> next;
                        }
                }
                else if (!strcmp(a_command, "update"))
                {
                        sscanf(a_options, "%[^:]:%[^:]:%[^:]:%[^\n\0]", a_name, a_sex, a_birth, a_best_movie);

                        while (list->actor->serial == a_serial_number)
                                list->actor = list->actor -> next;
                        if (a_name != "=")
                                list->actor -> actor = a_name;
                        if (a_sex != "=")
                                list->actor -> sex = a_sex;
                        if (a_name != "=")
                                list->actor -> birth = a_birth;
                        if (m_actors != "=")
                                list->actor -> title = a_best_movie;
                }
                else if (!strcmp(a_command, "delete"))
                {
                        list->actor = list->actor -> next -> next;
                }
                else break;
        }while (getc(alog_file) == '\n');
        fclose(alog_file);
        free(a_command);
        free(a_options);
        free(a_name);
        free(a_sex);
        free(a_birth);
        free(a_best_movie);

        free(list->actor);
        free(list->director);
        free(list->movie);
        free(l_actor);
        free(l_director);
        free(l_movie);
        free(list);
}


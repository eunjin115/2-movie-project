#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct movie {
	int serial;
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
	movie* movie;
	director* director;
	actor* actor;
}List;
void add(char o,List *list) {
	if (o == 'm') {
		//add m일 경우
		list->movie = (movie*)malloc(sizeof(movie));
	}
	else if (o == 'd') {
		//add d 일 경우
	}
	else if (o == 'a') {
		//add a일경우
	}
}

int main() {
	List* list = (List*)malloc(sizeof(List));
	char* cmd;
	char c,a;
	cmd = (char *)malloc(sizeof(char) * 20);
	printf(">>Welcome to My Movie<< \n");
	printf("File Loading.....\n");
	printf("You can use add, update, search, sort, save, end commands. \n");
	while (1) {
		printf("(movie)");
		scanf("%s",cmd);
		c=getchar();
		a = getchar();
		if (!strcmp(cmd,"add")) {
			add(a, list);
			continue;
		}
		else if (!strcmp(cmd,"update")) {
			update(a, list);
			continue;
		}
		else if (!strcmp(cmd,"delete")) {
			Delete(a, list);
			continue;
		}
		else if (!strcmp(cmd,"search")) {
			search(a, list);
			continue;
		}
		else if (!strcmp(cmd,"sort")) {
			sort(a, list);
			continue;
		}
		else if (!strcmp(cmd,"save")) {
			printf("save");
			continue;
		else if (!strcmp(cmd,"end")) {
			printf("end");

		}
	}
}

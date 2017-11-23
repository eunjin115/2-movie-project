#include <stdio.h>
#include <stdlib.h>

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
int main() {

}
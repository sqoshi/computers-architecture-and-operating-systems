#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct {
	int size;
	int** m1;
	int** m2;
	int** res;
} matrices;

//fill >0 random  values and calloc 
//fill = 0 just calloc - empty mat
int** alloc_matrix(int size, int fill) {

	srand(time(NULL));

	int** matrix = calloc(size, sizeof(int*));

	for (int i = 0; i < size; i++) {
		matrix[i] = calloc(size, sizeof(int));
		if (fill > 0) {
			for (int j = 0; j < size; j++) matrix[i][j] = rand() % fill;
		}
	}

	return matrix;
}

//mutex lock changes on concrete row
pthread_mutex_t mutex;
int curr_row = 0;

void* mult(void* vargp) {
	matrices* m = (matrices*) vargp;

	while (curr_row < m->size){

		pthread_mutex_lock(&mutex);
		int row = curr_row;
		curr_row++;
		pthread_mutex_unlock(&mutex);

		for (int i = 0; i < m->size; i++) {
			for (int j = 0; j < m->size; j++) {
				m->res[row][i] |= (m->m1[row][j] && m->m2[j][i]);
				if(m->res[row][i]==1) break;//bc if once its 1 rest no matter 
			}
		}
	}

	pthread_exit(0);
}

void* printer(matrices m){
//print m2 up + space
        int size,row, columns;
	size = m.size;
//space
        for (int row=0; row<size; row++){
                for(int columns=0; columns<size; columns++)
                        printf("  ");
                printf(" | ");
//m2
        for(int columns=0; columns<size; columns++)
                printf("\x1b[38;5;226m%d \x1b[0m",m.m2[row][columns]);
        printf("\n");
        }
// --
        for(int columns=0; columns<2*size+1; columns++)
                printf("--");
        printf("\n");
//m1+res
        for (int row=0; row<size; row++){
// m1
        for(int columns=0; columns<size; columns++)
                        printf("\x1b[38;5;81m%d \x1b[0m",m.m1[row][columns]);
        printf(" | ");
// res
        for(int columns=0; columns<size; columns++)
                printf("\x1b[38;5;2m%d \x1b[0m", m.res[row][columns]);
        printf("\n");
        }
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("need args: [size] [#threads]\n");
		return 1;
	}
	int size = atoi(argv[1]);
	int tnum = atoi(argv[2]);

	matrices m;

	m.size = size;
	m.m1 = alloc_matrix(size, 2);
	m.m2 = alloc_matrix(size, 2);
	m.res = alloc_matrix(size, 0);

	pthread_mutex_init(&mutex, NULL);
	pthread_t threadIds[tnum];

	for (int i = 0; i < tnum; i++) {
		printf("[thread %d starting] ", i);
		pthread_create(&threadIds[i], NULL, &mult, &m);
	}printf("\n");

	for (int i = 0; i < tnum; i++) {
		pthread_join(threadIds[i], NULL);
		printf("[thread %d finished] ", i);
	}printf("\n");

	pthread_mutex_destroy(&mutex);
	printf("mutex-destroy, exit\n");
	printer(m);
return 0;
}



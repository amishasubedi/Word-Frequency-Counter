#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

 typedef struct {
	char word[101];
	int freq;
} array ;

int compare(const void *f1, const void *f2){
	array *a = (array *)f1;
	array *b = (array *)f2;
	return (b->freq - a->freq);
}

char *countFrequency(char *fileName){
	
	int counter = 0;
	int isUnique;
	FILE *file;
	char buff[10000000];

	file = fopen(fileName, "rb");

	if (!file){
		printf("File does not exist\n");
	}
	
	else {
		while ( (fscanf(file, "%s", buff)) != EOF) {
			isUnique = -1;

			// String comparison - to check if the word is already in the array
		
			for (int i = 0; i < counter; i++){
				if (strcmp(words[i].word, buff) == 0){
					isUnique = i;
				}
			}
			// string not found in array
			if (isUnique == -1){
				strcpy(words[counter].word, buff);
				words[counter].frequency = 1;
				counter++;
			}

			// Increase frequency of new words
			else {
				words[isUnique].frequency++;
			}	

            // Re-allocate memory for the array
			words = realloc(words, (sizeof(*words) + counter) * sizeof(array));	
		}
	}	
	

}



int main(int argc, char *argv[]){

    if (argc == 1) {
        printf("file does not exist\n")
    }
	
	// Declare threads and default attributes
	pthread_t threads[argc-1];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// Run all threads 
	for (int i = 1; i < argc; i++){
		char* arguments = (char*)malloc(sizeof(argv[i])+1);
		arguments = argv[i];
		
        // new thread each time 
		pthread_create(&threads[i], &attr, (void*) countFrequency, (void*) arguments);
	}
	for (i = 1; i < argc; i++){

		// prevent memory leaks
		pthread_join(threads[i], NULL);
	}

	return 0;
}



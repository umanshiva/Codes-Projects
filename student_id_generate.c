#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(int arr[], int n) {
    srand(time(NULL));

    for (int i = n - 1; i > 0; i--) {
        int j = 53*rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

int main() {
    int n = 10000000; 
    int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
        //printf("%d\n",arr[i]);
    }

    shuffle(arr, n);

    /*for (int i = 0; i < n; i++) {
        printf("%d\n",arr[i]);
    }*/

    int selectedNumbers[1100];
    for (int i = 0; i < 1100; i++) {
        selectedNumbers[i] = arr[i];
    }

    FILE *outputFile = fopen("student_id.txt", "w");

    for (int i = 0; i < 1100; i++) {
        fprintf(outputFile, "%d\n", selectedNumbers[i]);
    }

    fclose(outputFile);
    free(arr);

    return 0;
}

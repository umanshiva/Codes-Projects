#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE1 1013
#define SIZE2 2017

struct Hash_table1{
    int table[SIZE1];
};

struct Hash_table2{
    int table[SIZE2];
};

int hash_fun1(int k, int i){
    return (k % SIZE1 + i*(1 + k % (SIZE1 - 1))) % SIZE1;
}

int hash_fun2(int k, int i){
    return (k % SIZE2 + i*(1 + k % (SIZE2 - 1))) % SIZE2;
}

struct Hash_table1* generate_hash_table1(){
    struct Hash_table1* hash_table = (struct Hash_table1*)malloc(sizeof(struct Hash_table1));
    for(int i = 0 ; i < SIZE1; i ++){
        hash_table->table[i] = 0;
    }
    return hash_table;
}

struct Hash_table2* generate_hash_table2(){
    struct Hash_table2* hash_table = (struct Hash_table2*)malloc(sizeof(struct Hash_table2));
    for(int i = 0 ; i < SIZE2; i ++){
        hash_table->table[i] = 0;
    }
    return hash_table;
}


void hash_insert1(struct Hash_table1* htable,int k){
    int i = 0;
    while(i != SIZE1){
        int j;
        j = hash_fun1(k,i);
        
        if(htable->table[j] == 0 || htable->table[j] == -1){
            htable->table[j] = k;
            break;
        }
        else{
            i++;
        }
    }
}

void hash_insert2(struct Hash_table2* htable,int k){
    int i = 0;
    while(i != SIZE2){
        int j;
        j = hash_fun2(k,i);
        
        if(htable->table[j] == 0 || htable->table[j] == -1){
            htable->table[j] = k;
            break;
        }
        else{
            i++;
        }
    }
}

int hash_search1(struct Hash_table1* htable, int k){
    int i = 0;
    int probes = 0; // Initialize probe count
    int j = hash_fun1(k,i);
    probes++;
    while (i < SIZE1 || htable->table[j] != 0) {
        if(i >= SIZE1){
            break;
        }
        if (htable->table[j] == k) {
            return probes; // Key found; return probe count
        }
        j = hash_fun1(k, i);
        probes++; // Increment probe count for this iteration

        i++;
    }
    return probes;
}

int hash_search2(struct Hash_table2* htable, int k){
    int i = 0;
    int probes = 0;
    int j = hash_fun2(k, i);
    probes++;
    while (i < SIZE2 || htable->table[j] != 0) {
        if(i >= SIZE2){
            break;
        }

        if (htable->table[j] == k) {
            return probes; 
        }

        j = hash_fun2(k, i);
        probes++; 

        i++;
    }
    return probes;
}


void hash_delete1(struct Hash_table1* htable,int k){
    int i = 0;
    int j = hash_fun1(k, i);
    while (i < SIZE1 || htable->table[j] != 0) {
        if(i >= SIZE1){
            break;
        }

        if (htable->table[j] == k) {
            htable->table[j] = -1;
            return; // Exit the function after the item is deleted
        }

        j = hash_fun1(k, i);
        i++;
    }
}

void hash_delete2(struct Hash_table2* htable,int k){
    int i = 0;
    int j = hash_fun2(k, i);
    while (i < SIZE2 || htable->table[j] != 0) {
        if(i >= SIZE2){
            break;
        }

        if (htable->table[j] == k) {
            htable->table[j] = -1;
            return; // Exit the function after the item is deleted
        }

        int j = hash_fun2(k, i);
        i++;
    }
}

void shuffle(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


int main(){
    int students[1100];
    int k;
    int index = 0;
    FILE* f = fopen("student_id.txt", "r");
    while(fscanf(f, "%d", &k) != EOF){
        students[index] = k;
        index ++;
    }
    fclose(f);

    int students1[1000];
    int students2[100];

    for(int i = 0; i < 1100; i ++){
        if(i < 1000){
            students1[i] = students[i];
           // printf("%d\n",students1[i]);
        }
        else{
            students2[i - 1000] = students[i];
        }
    }


    struct Hash_table1* H1 = generate_hash_table1();

    int probes1[100];

    for(int i = 0; i < 1000; i ++){
        hash_insert1(H1,students1[i]);
    }

    /*for(int i = 0; i < SIZE1; i ++){
        printf("%d\n",H1->table[i]);
    }*/

    srand(time(NULL));
    int random_students[200];

    shuffle(students1, 1000);

    for(int i = 0; i < 200; i ++){
        random_students[i] = students1[i];
    }
    
    for(int i = 0; i < 100; i++){
        probes1[i] = hash_search1(H1,random_students[i]);
    }

    for(int i = 0; i < 100; i++){
        hash_delete1(H1,random_students[i]);
    }

    int total_probes1 = 0;

    for(int i = 0; i < 100; i ++){
        total_probes1 += probes1[i];
    }

    printf("%d\n",total_probes1);

    for(int i = 0; i < 100; i++){
        probes1[i] = hash_search1(H1,random_students[i + 100]);
    }

    int total_probes2 = 0;
    for(int i = 0; i < 100; i ++){
        total_probes2 += probes1[i];
    }

    printf("%d\n",total_probes2);

    for(int i = 0; i < 100; i++){
        probes1[i] = hash_search1(H1,students2[i]);
    }

    int total_probes3 = 0;
    for(int i = 0; i < 100; i ++){
        total_probes3 += probes1[i];
    }

    printf("%d\n",total_probes3);



    struct Hash_table2* H2 = generate_hash_table2();

    int probes2[100];

    for(int i = 0; i < 1000; i ++){
        hash_insert2(H2,students[i]);
    }

    /*for(int i = 0; i < SIZE2; i ++){
        printf("%d\n",H2->table[i]);
    }*/
    
    for(int i = 0; i < 100; i++){
        probes2[i] = hash_search2(H2,random_students[i]);
       // printf("%d\n",probes2[i]);
    }

    for(int i = 0; i < 100; i++){
        hash_delete2(H2,random_students[i]);
    }

    int total_probes4 = 0;
    for(int i = 0; i < 100; i ++){
        total_probes4 += probes2[i];
    }

    printf("%d\n",total_probes4);

    for(int i = 0; i < 100; i++){
        probes2[i] = hash_search2(H2,random_students[i + 100]);
    }

    int total_probes5 = 0;
    for(int i = 0; i < 100; i ++){
        total_probes5 += probes2[i];
    }

    printf("%d\n",total_probes5);

    for(int i = 0; i < 100; i++){
        probes2[i] = hash_search2(H2,students2[i]);
    }

    int total_probes6 = 0;
    for(int i = 0; i < 100; i ++){
        total_probes6 += probes2[i];
    }

    printf("%d\n",total_probes6);

}
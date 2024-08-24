#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 500

int hash_fun(int key){
   return key % SIZE; 
}


struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int height;
};

struct Hash_table{
    struct Node* table[SIZE];
};


struct Node* search(struct Node* x,int k){
    if(x == NULL || k == x->data){
        return x;
    }
    if(x->data < k){
        return search(x->right,k);
    }
    else{
        return search(x->left,k);
    }
}

int height(struct Node* x){
    if(x != NULL){
        return x->height;
    }
    return 0;
}

int max(int x,int y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}

void recompute_height(struct Node* x){
    while(x != NULL){
        x->height = max(height(x->left),height(x->right)) + 1;
        x = x->parent;
    }
}

void preorder(struct Node* root){
    if (root != NULL) { 
        printf("%d(%d)", root->data,root->height); 
        preorder(root->left); 
        preorder(root->right); 
    }
}

struct Node* left_rot(struct Node* x){
    if((x) == NULL || (x)->right == NULL){
        return x;
    }

    struct Node* y = (x)->right;
    struct Node* leftsubT = y->left;

    y->left = x;
    y->parent = (x)->parent;
    
    if((x)->parent != NULL){
        if(((x)->parent)->left == x){
            ((x)->parent)->left = y;
        }
        else{
            ((x)->parent)->right = y;
        }
    }
    (x)->parent = y;
    (x)->right = leftsubT;
    
    if(leftsubT != NULL){
        leftsubT->parent = x;
    }
    
    (x)->height = max(height((x)->right),height((x)->left)) + 1;
    y->height = max(height(y->right),height(y->left)) + 1;

    return y;
}

struct Node* right_rot(struct Node* x){
    if(x == NULL || (x)->left == NULL){
        return x;
    }

    struct Node* y = (x)->left;
    struct Node* rightsubT = y->right;

    y->right = x;
    y->parent = (x)->parent;

    if((x)->parent != NULL){
        if(((x)->parent)->left == x){
            ((x)->parent)->left = y;
        }
        else{
            ((x)->parent)->right = y;
        }
    }

    (x)->parent = y;
    (x)->left = rightsubT;

    if(rightsubT != NULL){
        rightsubT->parent = x;
    }
    
    (x)->height = max(height((x)->right),height((x)->left)) + 1;
    y->height = max(height(y->right),height(y->left)) + 1;

    return y;
}

void rebalanceAVL(struct Node* x){
    while((x) != NULL){
        if(abs(height((x)->left) - height((x)->right)) > 1){
            if(height((x)->left) > height((x)->right)){
                if((x)->left != NULL){
                    struct Node* y = (x)->left;
                    if(height(y->left) > height(y->right)){
                        x = right_rot(x);
                    }
                    else{
                        y = left_rot(y);
                       // (x)->left = y;
                        x = right_rot(x);
                    }
                }
            }
            else{
                if((x)->right != NULL){
                    struct Node* y = (x)->right;
                    if(height(y->left) > height(y->right)){
                       y = right_rot(y);
                    //   (x)->right = y;
                       x = left_rot(x);
                    }
                    else{
                        x = left_rot(x);
                    }   
                }
            }
        }
        (x)->height = max(height((x)->left),height((x)->right)) + 1;
        x = (x)->parent;
    }
}

void Insert(struct Node* root,struct Node* node){
    struct Node* y = NULL;
    struct Node* x = root;
    while (x != NULL){
        y = x;
        if((node)->data < x->data){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    (node)->parent = y;
    if((node)->data < y->data){
        y->left = (node);
    }
    else{
        y->right = (node);
    }
    recompute_height(y);
    rebalanceAVL(y);
}

void Transplant(struct Node** root,struct Node** u, struct Node** v){
    if((*u)->parent == NULL){
        *root = *v;
    }
    else if((*u) == (((*u)->parent)->left)){
        (((*u)->parent)->left) = *v;
    }
    else{
        (((*u)->parent)->right) = *v;
    }
    if((*v) != NULL){
        (*v)->parent = (*u)->parent;
    }
}

struct Node* Tree_min(struct Node** root){
    struct Node* x = *root;
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

void Delete(struct Node** root, struct Node** z){
    if((*z)->left == NULL && (*z)->right == NULL){
        struct Node* x = (*z)->parent;
        if((*z) == x->left){
            x->left = NULL;
        }
        else{
            x->right = NULL;
        }
        recompute_height(x);
        rebalanceAVL(x);
        free(*z);
    }
    else if((*z)->left == NULL && (*z)->right != NULL){
        struct Node* x = (*z)->parent;
        Transplant(root,z,&((*z)->right));
        recompute_height(x);
        rebalanceAVL(x);
        free(*z);
    }
    else if((*z)->right == NULL && (*z)->left != NULL){
        struct Node* x = (*z)->parent;
        Transplant(root,z,&((*z)->left));
        recompute_height(x);
        rebalanceAVL(x);
        free(*z);
    }
    else{
        struct Node* y = Tree_min(&((*z)->right));
        struct Node* x = (*z)->parent;
        if(y->parent != (*z)){
            Transplant(root,&y,&(y->right));
            y->right = (*z)->right;
            (y->right)->parent = y;
        }
        Transplant(root,z,&y);
        y->left = (*z)->left;
        (y->left)->parent = y;
        recompute_height(y);
        rebalanceAVL(x);
        free(*z);
    }
}

struct Hash_table* generate_hash_table(){
    struct Hash_table* hash_table = (struct Hash_table*)malloc(sizeof(struct Hash_table));
    for(int i = 0 ; i < SIZE; i ++){
        hash_table->table[i] = NULL;
    }
    return hash_table;
}

void chained_hash_insert(struct Hash_table* htable, int k){
    int index = hash_fun(k);
    if(htable->table[index] == NULL){
        struct Node* root = (struct Node*)malloc(sizeof(struct Node));
        root->data = k;
        root->left = root->right = root->parent = NULL;
        root->height = 1;
        htable->table[index] = root;
    }
    else{
        struct Node* root = htable->table[index];
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->data = k;
        node->left = node->right = node->parent = NULL;
        node->height = 1;
        Insert(root, node);
    }
}

struct Node* chained_hash_search(struct Hash_table* htable, int k){
    int index = hash_fun(k);
    struct Node* root = htable->table[index];
    return search(root, k);
}

void chained_hash_delete(struct Hash_table* htable, int k){
    struct Node* z = chained_hash_search(htable, k);
    if(z != NULL){
        int index = hash_fun(k);
        struct Node* root = htable->table[index];
        Delete(&root, &z);
        return ;
    }
    return ;
}


int main(){
    int students[1000];
    int k;
    int index = 0;
    FILE* f = fopen("student_id.txt", "r");
    while(fscanf(f, "%d", &k) != EOF && index < 1000){
        students[index] = k;
        index ++;
    }
    fclose(f);

    struct Hash_table* H = generate_hash_table();

    for(int i = 0; i < 1000; i ++){
        chained_hash_insert(H, students[i]);
    }

    for(int i = 0; i < SIZE; i++){
        if(H->table[i] == NULL){
            continue;
        }
        preorder(H->table[i]);
        puts("");
    }    
}
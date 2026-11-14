#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char word[50];
    struct Node* left;
    struct Node* right;
    int height ;
} Node;

int size = 0;


void inOrder( Node* root );
Node* newNode(char* txt);
Node* insert( Node* root , char* txt);
Node* search(Node* root , char* txt);
Node* DictionaryToTree(Node* root);

Node* searchForPre(Node* root , char* txt , Node* Pre);
Node* searchForSuc(Node* root , char* txt, Node* Succ);
Node* successorNode(Node* current , Node* root);
Node* predecessorNode(Node* current , Node* root);
Node* findMin(Node* root);
Node* findMax(Node* root);

Node* leftRotation(Node* x);
Node* rightRotation(Node* x);
int balanceFactor(Node* root);
int height(Node* root);
int max1(int a , int b);


Node* rootMain;
int main(){
    rootMain = newNode("mango");
    rootMain = DictionaryToTree(rootMain);
    char line[100];
    printf("===== AVL TREE DICTIONARY =====\n");
    printf("\e[0;92m>> Dictinary Loaded Successfully . . .\e[0m\n");
    printf(">> Tree Height : \e[4;34m%d\e[0m \n" , height(rootMain));
    printf(">> Size : \e[4;34m%d\e[0m \n" , size);
    printf("==============================\n");
    printf("Enter A Sentence: ");
    fgets(line,100,stdin);
    
    char* buff = strtok(line," ");
    while(buff != NULL){
        buff[strcspn(buff, "\n")] = '\0';
        printf("\e[0;94m>>\e[0m %s " , buff);
        search(rootMain , buff);
        buff = strtok(NULL," ");
    }
}

Node* newNode(char* txt){
    Node* n = malloc(sizeof(Node));
    if(n == NULL){
        return NULL;
    }
    strcpy(n->word,txt);
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

Node* insert( Node* root , char* txt){
    if(root == NULL){
        root = newNode(txt);
    }else if( strcmp( txt , root->word ) > 0 ){
        root->right = insert(root->right,txt);
    }else if( strcmp(txt , root->word) < 0 ){
        root->left = insert(root->left,txt);
    }else{
        return root;
    }
    root->height = 1 + max1( height(root->left) , height(root->right) );

    int balFac = balanceFactor(root);

    if(balFac > 1 && strcmp(txt,root->left->word) < 0){
        return rightRotation(root);
    }else if(balFac > 1 && strcmp(txt,root->left->word) > 0){
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }else if(balFac < -1 && strcmp(txt,root->right->word) > 0){
        return leftRotation(root);
    }else if(balFac < -1 && strcmp(txt,root->right->word) < 0){
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}


Node* leftRotation(Node* x){
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max1(height(x->left),height(x->right));
    y->height = 1 + max1(height(y->left),height(y->right));
    return y;
}

Node* rightRotation(Node* x){
    Node* y = x->left;
    Node* T2 = y->right;
    y->right = x;
    x->left = T2;
    x->height = 1 + max1(height(x->left),height(x->right));
    y->height = 1 + max1(height(y->left),height(y->right));
    return y;
}


void inOrder( Node* root ){
    if(root != NULL){
        inOrder(root->left);
        printf("%s ",root->word);
        inOrder(root->right);
    }
}

int height(Node* root){
    if(root == NULL){
        return 0;
    }else{
        return root->height;
    }
}

int max1(int a , int b){
    if(a > b){
        return a;
    }else if(b >= a){
        return b;
    }
}

Node* DictionaryToTree(Node* root){
    FILE* dict = fopen("Dictionary.txt","r");
    if(dict == NULL){
        printf("Cannot Open File . . . ");
        return root;
    }
    char buff[50];
    while(fscanf(dict,"%s",buff) == 1){
        root = insert(root,buff);
        size++;
    }
    return root;
}


int balanceFactor(Node* root){
    if(root == NULL){
        return 0;
    }else{
        return height(root->left) - height(root->right);
    }
}


// 3amaltohom global variables flexable 2ktar

Node* last;
Node* succc;
Node* preee;

Node* search(Node* root , char* txt){
    if(root == NULL){
        succc = successorNode( last , rootMain );
        preee = predecessorNode( last, rootMain );
        printf("\e\t[0;31m- INCORRECT\e[0m , %s - %s - %s \n" , last->word , succc->word , preee->word);
        return NULL;
    }
    // da part (A) : 25r node before not exisit
    last = root;
    if( strcmp(txt,root->word) > 0 ){
        return search(root->right,txt);
    }else if( strcmp(txt,root->word) < 0 ){
        return search(root->left,txt);
    }else if( strcmp(txt,root->word) == 0){
        printf("\e[0;32m- CORRECT\e[0m\n");
        return root;
    }
}


Node* findMin(Node* root){
    if(root == NULL){
        return NULL;
    }else if(root->left != NULL){
        return findMin(root->left);
    }else{
        return root;
    }
}

Node* searchForSuc(Node* root , char* txt ,Node* Succ){
    if(root == NULL){
        return Succ;
    }else if( strcmp(txt,root->word) > 0 ){
        return searchForSuc(root->right,txt,Succ);
    }else if( strcmp(txt,root->word) < 0 ){
        return searchForSuc(root->left,txt,root);
    }else if( strcmp(txt,root->word) == 0){
        return Succ;
    }
}


Node* successorNode(Node* current , Node* root){
    Node* temp;
    if(current->right != NULL){
        temp = findMin(current->right);
    }else{
        temp = searchForSuc(root , current->word , NULL );
    }
    return temp;
}


Node* findMax(Node* root){
    if(root == NULL){
        return NULL;
    }else if(root->right != NULL ){
        root = findMax(root->right);
    }else{
        return root;
    }
}

Node* predecessorNode(Node* current , Node* root){
    Node* temp;
    if(current->left != NULL){
        temp = findMax(current->left);
    }else{
        temp = searchForPre(root, current->word , NULL);
    }
    return temp;
}

Node* searchForPre(Node* root , char* txt , Node* Pre){
    if(root == NULL){
        return Pre;
    }else if(strcmp(root->word,txt) < 0){
        return searchForPre(root->right , txt,root);
    }else if(strcmp(root->word,txt) > 0){
        return searchForPre(root->left , txt ,Pre);
    }else{
        return Pre;
    }
}
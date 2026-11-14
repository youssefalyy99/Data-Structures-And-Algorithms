#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node{
    float data;
    struct Node* next;
} Node;

typedef struct{
    Node *top;
    Node *start;
} Stack;

// FUNCTION PROTOTYPES

// PART 1 <STACK USING LINKED LISTS>
Stack* initialize();
Node* newnode();
void push(Stack* s, float value);
float pop(Stack* s);
void display(Stack *s);
int isEmpty(Stack* s);
float peek(Stack* s);

// PART 2 < INFIX TO POSTFIX >
Stack* infixToPostfix(char* infix);
int prior(char x);

// PART 3 < POSTFIX EVALUATION >
float evaluatePostfix( Stack* postfix );

int main(){
    char line[100];
    printf("\033[32m===== Expression Evaluation Assignment =====\033[0m\n");
    printf(">> Input (Infix) : ");
    fgets(line,100,stdin);
    Stack* st = initialize();
    st = infixToPostfix(line);
    evaluatePostfix(st);
    return 0;
}


// PART 1 FUNCTIONS
Stack* initialize(){
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    s->start = NULL;
    return s;
}
Node* newnode(){
    Node* n = (Node*)malloc(sizeof(Node));
    n->next = NULL;
    return n;
}
void push(Stack* s, float value){
    Node* n = newnode();
    if(s->start == NULL){
        s->start = n;
        s->top = n;
        n->data = value;
        n->next = NULL;
    }else{
        s->top->next = n;
        s->top = n;
        n->data = value;
        n->next = NULL;
    }
}
float pop(Stack* s){
    if(s->start == NULL){
        return -1;
    }else if(s->start->next == NULL){
        float x = s->start->data;
        s->start = NULL;
        s->top = NULL;
        return x;
    }else{
        Node* temp = s->start;
        float x = s->top->data;
        while(temp->next != s->top){
            temp = temp->next;
        }
        s->top = temp;
        temp->next = NULL;
        return x;
    }
}
void display(Stack *s){
    Node* temp = s->start;
    while(temp != NULL){
        if(temp->data == '*' || temp->data == '%' || temp->data == '^' || temp->data == '+' || temp->data == '-' || temp->data == '(' || temp->data == ')' || temp->data == '/'){
            printf("%c ",(char)temp->data);
        }else{
            printf("%0.2f ",temp->data);
        }
        temp = temp->next;
    }
}

int isEmpty(Stack* s){
    if(s->start == NULL){
        return 1;
    }
    return 0;
}

float peek(Stack* s){
    return s->top->data;
}

// PART 2 FUNCTIONS
Stack* infixToPostfix(char* infix){
    Stack* final = initialize();
    Stack* buffer = initialize();
    char* tok = strtok(infix," ");
    
    // TOK WHILE LOOP
    while(tok != NULL){
        float num = atof(tok);
        if( num < 0 ){
            push(final,num);
            tok = strtok(NULL," ");
            continue;
        }
        if(*tok == '*' || *tok == '%' || *tok == '^' || *tok == '+' || *tok == '-' || *tok == '(' || *tok == ')' || *tok == '/'){
            if(*tok != ')'){
                // CHECK IF EMPTY
                    if(isEmpty(buffer)){ 
                        push(buffer,(float)*tok);
                    }else{ // ELSE CHECK PRIORITY

                        //IF HIGHTER PRIORITY PUSH IT
                        if( prior((float)*tok) > prior(peek(buffer)) ){
                            push(buffer,(float)*tok);
                        }else{
                            // ELSE POP ALL UNTILL A SMALLER PRIORITY APPEAR
                            while( !isEmpty(buffer) && prior(peek(buffer)) >= prior((float)*tok) && peek(buffer) != '('){
                                push(final,pop(buffer));
                            }
                            push(buffer,(float)*tok);
                        }
                    }
            }else if(*tok == ')'){
                // IF CLOSED PARENTHSIS POP ALL UNTILL OPEN PARENTHSIS
                while(peek(buffer) != '(' && !isEmpty(buffer)){
                    push(final,pop(buffer));
                }
                pop(buffer);
            }
        }else{
            push(final,num);
        }
        // GET NEXT CHAR
        tok = strtok(NULL," ");
    }
    
    // IF BUFFER STILL HAVE ANYTHING EMPTY IT
    while(!isEmpty(buffer)){
        push(final,pop(buffer));
    }

    printf("\033[34mFinal Postfix Expression : \033[0m");
    display(final);

    return final;
}



int prior(char x){
    if(x == '^'){
        return 3;
    }else if( x == '*' || x == '/' || x == '%'){
        return 2;
    }else if(x == '-' || x == '+'){
        return 1;
    }
}

// PART 3 FUNCTIONS

float evaluatePostfix( Stack* postfix ){
    Node* temp = postfix->start;
    Stack* buff = initialize();
    float num1 , num2 , value;

    while(temp != NULL){
        if(temp->data == '*' || temp->data == '%' || temp->data == '^' || temp->data == '+' || temp->data == '-' || temp->data == '/'){
            if(temp->data != '^'){
                num2 = pop(buff);
                num1 = pop(buff);
                if(temp->data == '*'){
                    value = num1 * num2;
                }else if(temp->data == '%'){
                    value = (int)num1 % (int)num2;
                }else if(temp->data == '+'){
                    value = num1 + num2;
                }else if(temp->data == '-'){
                    value = num1 - num2;
                }else if(temp->data == '/'){
                    value = num1 / num2;
                }
                push(buff,value);
            }else if(temp->data == '^'){
                num2 = pop(buff);
                num1 = pop(buff);
                value = pow(num1,num2);
                push(buff,value);
            }
        }else{
            push(buff,temp->data);
        }
        temp = temp->next;
    }

    printf("\n\033[34mFinal Value :\033[0m %0.2f " , pop(buff));
}
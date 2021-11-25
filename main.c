#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

char stack[20];
int posisiAtas = -1;

void showNIM(char *x);


void push(char x);
char pop();

int is_operator(char symbol);
int pangkatOperator(char x);
void infixToPostfix(char infix[], char postfix[]);
void reverse(char array[]);
void infixToPrefix (char infix[] , char prefix[]);

int main(int argc, char const *argv[])
{
    if(argc > 1){
        int panjangStringNIM = strlen(argv[1]);
        char NIM[panjangStringNIM];
        strcpy(NIM, argv[1]);

        char infix[20];
        strcpy(infix, argv[2]);  
          
        // postfix
        printf("POSTFIX ANSWER\n");
        showNIM(NIM);
        printf(" = ");

        
        
        char postfix[20];
        infixToPostfix(infix, postfix);
        printf("%s\n",postfix);
        

        //PREFIX
        printf("\nPREFIX ANSWER\n");
        showNIM(NIM);
        printf(" = ");
        char prefix[20];
        infixToPrefix(infix, prefix);
        printf("%s\n",prefix);

    }
    else{
        printf("FORMAT INPUTAN SALAH!!! FORMAT : ./file SDnim INFIX_EXPRESSION\n");
    }
    return 0;
}



void showNIM(char *x){
    for(int i = 2; i <= strlen(x)-1 ; i++){
        printf("%c", *(x+i));
    }
}

void push(char x){
    stack[++posisiAtas] = x;
}
char pop(){
    if (posisiAtas == -1)
    {
        return 0;
    }else{
        return stack[posisiAtas--];
    }
}

int is_operator(char symbol)
{
	if(symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}
int pangkatOperator(char x){
    if(x == '('){
        return 0;
    }if (x == '*' || x == '/')
    {
        return 2;
    }if (x == '+' || x == '-')
    {
        return 1;
    }if (x == '^')
    {
        return 3;
    }
    else{
        return 0;
    }
}
void infixToPostfix(char infix[], char postfix[]){
    
    int j = 0;
    char x;
    for (int i = 0; i < strlen(infix); i++)
    {   
        if (infix[i] == '(')
        {
            push(infix[i]);
        }
        else if (isdigit(infix[i]) || isalpha(infix[i]))
        {
            postfix[j] = infix[i];
            j++;
        }
        
        
        else if(is_operator(infix[i]) == 1)
        {
            x=pop(); //x = isi stack paling atas
			while(pangkatOperator(x)>= pangkatOperator(infix[i]))
			{
				postfix[j] = x;  // masukkan x ke belakang postfix                
				j++;
				x = pop();                       
			}
			push(x); // masukkan nilai x ke dalam stack lagi
			
			push(infix[i]);  
        }
        else if(infix[i] == ')')         
		{
			x = pop();       //x = isi stack paling atas            
			while(x != '(')                
			{
				postfix[j] = x;
				j++;
				x = pop();
			}
		}
    }
    while (posisiAtas != -1)
    {
        postfix[j] = pop();
        j++;
    }
    
    
}

void reverse(char array[]) 
{
	int i,j;
	char temp[100];
	for (i=strlen(array)-1,j=0;i+1!=0;--i,++j) {
        if (array[i] == '(')
        {
            array[i] = ')';
        }else if (array[i] == ')')
        {
            array[i] = '(';
        }
        
		temp[j]=array[i];
	}
	temp[j]='\0';
	strcpy(array,temp);
	
}

void infixToPrefix (char infix[] , char prefix[]){
    reverse(infix);
    infixToPostfix(infix, prefix);
    reverse(prefix);
}

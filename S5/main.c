#include <stdio.h>

// Implementing a menu using pointers to functions

void option1(void* something){
    printf("option1\n");
    int number = *(int*)something;
    printf("%d\n",number);
}

void option2(void* something){
    printf("option2\n");
    int number = *(int*)something;
    printf("%d\n",number);
}


int main() {
    printf("Hello, World!\n");

    void (*menu[])(void*) = {option1, option2};
    int option = 0;;
    do{
        printf("Enter choice: \n1 for Option 1\n2 for Option 2\n");
        scanf("%d",&option);
        if(option > 2 || option < 1) {
            if(option == 3)
                break;
            printf("error, try again\n");
            continue;
        }
        (*menu[option-1])(&option);
    }while(option != 3);

    printf("Bye!\n");
    return 0;
}
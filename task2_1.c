#include <stdio.h>

int verrou = 0; //peut etre volatile

int acquire_lock(int *lock){
    asm("movl   %1, %%eax;"
        "xchgl  %%eax, %[lock];" 
        : "=r" (*lock)
        : [lock] "r" (*lock)
        : "%eax"
        );
    /*if(*lock){
        aquire_lock(&verrou);
    }*/
    printf("Valeur de lock est %d\n", *lock);

}

int release_lock(){

}

int test_and_set(int *lock){ //que faire le xchg dans l assembly les reste est fait en dehors 

    /*asm("acquire_lock:"
        "   movl $1, %%eax;"
        "   xchgl %%eax, %[lock];"
        "   cmpl $0, %%eax;"
        "   jne aquire_lock;"
        "   ret"
        "release_lock:"
        "   movl $0, %%eax;"
        "   xchgl %%eax, %[lock];"
        "   ret"
        : "=a" (*lock)
        : [lock] "r" (*lock)
        );*/
}

void enter_SC(){
    while(test_and_set(&verrou)){
        printf("Hello World!\n");
    }
}


int main(){
    verrou = 0;

    acquire_lock(&verrou);

    return 0;
}

#include <stdio.h>


void main(){
    int var = 20;
    int *pont; // $*$ so serve para avisar ao compilador que é um ponteiro
    pont = &var; //aqui ele vai estar pegando o endereço de var, nesse momento o pont aponta para o endereco de var

    printf("imprimindo var %d\n", var);
    printf("imprimindo pont %d\n", *pont);  //quando voce poe o operador * na frente do ponteiro, ele vai passar o valor que ele esta guardando no endereço que ele aponta

}
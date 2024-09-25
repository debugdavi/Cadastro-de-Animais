 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <termios.h>
 // Define as setas do teclado
 #define UP_ARROW 65
 #define DOWN_ARROW 66
 #define ENTER 10
 void disableBufferedInput() {
 struct termios t;
 tcgetattr(STDIN_FILENO, &t);
 t.c_lflag &= ~(ICANON | ECHO);  // Desativa entrada canônica e eco
 tcsetattr(STDIN_FILENO, TCSANOW, &t);
 }
 void enableBufferedInput() {
 struct termios t;
 tcgetattr(STDIN_FILENO, &t);
 t.c_lflag |= ICANON | ECHO;  // Ativa entrada canônica e eco
 tcsetattr(STDIN_FILENO, TCSANOW, &t);
 }
 void printMenu(int selected) {
 system("clear");  // Limpa a tela
 printf("Use as setas para navegar e Enter para selecionar:\n\n");
 printf(selected == 0 ? " -> " : "    ");
 printf("1. Opção 1\n");
 printf(selected == 1 ? " -> " : "    ");
printf("2. Opção 2\n");
 printf(selected == 2 ? " -> " : "    ");
 printf("3. Opção 3\n");
 }
 int main() {
 int selected = 0;
 char key;
 disableBufferedInput();  // Desativa o buffer de entrada
 while (1) {
 printMenu(selected);
 key = getchar();  // Lê o caractere
 if (key == '\e') {  // Se a tecla for uma sequência de escape
 getchar();        
// Ignora o caractere '['
 switch(getchar()) {
 case UP_ARROW:
 if (selected > 0) selected--;
 break;
 case DOWN_ARROW:
 if (selected < 2) selected++;
 break;
 }
 } else if (key == ENTER) {
 break;  // Sai do loop se a tecla Enter for pressionada
 }
 }
 enableBufferedInput();  // Reativa o buffer de entrada
 printf("\nVocê selecionou a Opção %d\n", selected + 1);
 return 0;
 }
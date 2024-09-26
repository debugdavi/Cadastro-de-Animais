#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define DATA 12
#define MAX 10
#define TAM_MAX 80

#define UP_ARROW 65
#define DOWN_ARROW 66
#define ENTER 10

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define PINK "\033[95m"

#define BRIGHT_BLACK  "\033[90m"
#define BRIGHT_RED    "\033[91m" 
#define BRIGHT_GREEN  "\033[92m"  
#define BRIGHT_YELLOW "\033[93m" 
#define BRIGHT_BLUE   "\033[94m" 
#define BRIGHT_MAGENTA "\033[95m" 
#define BRIGHT_CYAN   "\033[96m"  
#define BRIGHT_WHITE  "\033[97m"  

#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"
#define RESET "\033[0m"

int ultimo_id = 5;

typedef struct Alergias {
    char descricao[50];
} Alergias;

typedef struct Vacinas {
    char nome[30];
    char dataapl[DATA];
    char datavec[DATA];
} Vacinas;

typedef struct Animal {
    int id;
    char tutor[40];
    char contato[30];
    char nomeanimal[20];
    int idade;
    char cor[50];
    char sexo[12]; 
    char especie[30];
    Alergias alergia[MAX];
    Vacinas vac[MAX];
} Animal;

void disableBufferedInput() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enableBufferedInput() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void aguardarTecla() {       //FUNÇÃO CRIADA PARA LISTAGEM COM ENTRADA
    disableBufferedInput();
    printf("\nPressione qualquer tecla para voltar ao menu principal...");
    while (getchar() != '\n');
    getchar();
    enableBufferedInput();
}

void aguardarTeclaSemInte() {  //FUNÇÃO CRIADA PARA LISTAGEM SEM ENTRADA
    disableBufferedInput();
    printf("\nPressione qualquer tecla para voltar ao menu principal...");
    getchar();
    enableBufferedInput();
}

void limparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int comprimentoReal(const char* str) {
    int comprimento = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '\033') { 
            while (str[i] != 'm' && str[i] != '\0') {
                i++;  
            }
        } else if ((unsigned char)str[i] >= 0xF0) {  
            comprimento += 2;  
            i += 3; 
        } else if ((unsigned char)str[i] >= 0xC0) { 
            comprimento += 1; 
            i += 1;  
        } else {
            comprimento++;
        }
        i++;
    }

    return comprimento;
}

void imprimirTitulo(const char* titulo) {
    int largura_terminal = TAM_MAX; 
    int largura_titulo = comprimentoReal(titulo);
    int espacos = (largura_terminal - largura_titulo) / 2;

    printf("╔");
    for (int i = 0; i < largura_terminal - 2; i++) {
        printf("═");
    }
    printf("╗\n");

    printf(" ");
    for (int i = 0; i < espacos - 1; i++) {
        printf(" ");
    }
    printf("%s", titulo);
    for (int i = 0; i < espacos - 1 + (largura_terminal - largura_titulo) % 2; i++) {
        printf(" ");
    }
    printf(" \n");

    printf("╚");
    for (int i = 0; i < largura_terminal - 2; i++) {
        printf("═");
    }
    printf("╝\n");
}

void printMenu(int selected) {
    limparTerminal();
    imprimirTitulo(BG_CYAN "🐾 Cadastro de Animais 🐾" RESET);
    printf("Use as setas para navegar e Enter para selecionar:\n\n");

    printf(selected == 0 ? " -> " : "    ");
    printf("📃 Fazer cadastro\n");
    
    printf(selected == 1 ? " -> " : "    ");
    printf("📂 Mostrar dados\n");
    
    printf(selected == 2 ? " -> " : "    ");
    printf("📝 Atualizar dados\n");
    
    printf(selected == 3 ? " -> " : "    ");
    printf("❌ Deletar dados\n");
    
    printf(selected == 4 ? " -> " : "    ");
    printf("💊 Listar alergias\n");
    
    printf(selected == 5 ? " -> " : "    ");
    printf("💉 Listar vacinas\n");

    printf(selected == 6 ? " -> " : "    ");
    printf("⛔ Sair\n");
}

void cadastrarAnimal(Animal *animal) {
    ultimo_id++;
    animal->id = ultimo_id;
    int quant;

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);

    printf(GREEN "🠊 Qual o nome do tutor?" RESET "\n");
    scanf(" %[^\n]", animal->tutor);
    printf("\n");

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "🠊 Telefone para contato:" RESET "\n");
    scanf(" %[^\n]", animal->contato);
    printf("\n");

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "🠊 Qual o nome do animal?" RESET "\n");
    scanf(" %[^\n]", animal->nomeanimal);
    printf("\n");

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "🠊 Qual a idade do animal? Apenas números. Exemplo: 3" RESET "\n");
    scanf(" %d", &animal->idade);
    printf("\n");


    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "🠊 Qual a cor do animal?" RESET "\n");
    scanf(" %[^\n]", animal->cor);
    printf("\n");

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "🠊 Qual o sexo do animal?" RESET "\n");
    scanf(" %[^\n]", animal->sexo);
    printf("\n");


    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "🠊 Qual a espécie do animal?" RESET "\n");
    scanf(" %[^\n]", animal->especie);
    printf("\n");

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "🠊 Quantas alergias o seu bichinho tem? Até 10." RESET "\n");
    scanf("%d", &quant);

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    if (quant != 0) {
        for (int i = 0; i < quant; i++) {
            printf(GREEN "%d° alergia" RESET "\n", i + 1);
            printf(GREEN "Descrição da alergia" RESET "\n");
            scanf(" %[^\n]", animal->alergia[i].descricao);
            printf("\n");
            printf("\n");
        }
    }

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    printf(GREEN "Quantas vacinas o seu bichinho tomou? Até 10." RESET "\n");
    scanf("%d", &quant);

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    if (quant != 0) {
        for (int i = 0; i < quant; i++) {
            printf(GREEN "%d° vacina" RESET "\n", i + 1);
            printf(GREEN "Nome da vacina" RESET "\n");
            scanf(" %[^\n]", animal->vac[i].nome);
            printf(GREEN "Data da aplicação" RESET "\n");
            scanf(" %[^\n]", animal->vac[i].dataapl);
            printf(GREEN "Data do vencimento" RESET "\n");
            scanf(" %[^\n]", animal->vac[i].datavec);
            printf("\n");
            printf("\n");
        }
    }

    limparTerminal();
    imprimirTitulo(BG_GREEN "🐶 CADASTRAR ANIMAIS 😺" RESET);
    aguardarTecla();
}

void listarAnimais(Animal *animais, int totalAnimais) {
    limparTerminal();
    imprimirTitulo(BG_BRIGHT_MAGENTA "📂 LISTAR ANIMAIS CADASTRADOS 📂" RESET);

    if (totalAnimais == 0) {
        printf(RED "Nenhum animal cadastrado.\n" RESET);
        aguardarTeclaSemInte();
        return;
    }

    printf("════════════════════════════════════════════════════════════════════════════════\n");
    printf(CYAN "  %-4s | %-14s │ %-14s │ %-14s │ %-14s \n" RESET, "ID", "Nome", "Tutor", "Especie", "Cor");
    printf("════════════════════════════════════════════════════════════════════════════════\n");

    for (int i = 0; i < totalAnimais; i++) {
        if (i % 2 == 0) {
            printf(MAGENTA);
        } else {
            printf(BLUE);
        }

        printf(" %-4d | %-14s │ %-14s │ %-14s │ %-14s  \n" RESET,
            animais[i].id,
            animais[i].nomeanimal,
            animais[i].tutor,
            animais[i].especie,
            animais[i].cor);
    }

    printf("════════════════════════════════════════════════════════════════════════════════\n");

    aguardarTeclaSemInte();
}

void atualizarCadastro(Animal *animais, int totalAnimais) {
    char nome[20];
    int encontrado = 0;
    int escolha;
    int continuar = 1;

    limparTerminal();
    imprimirTitulo(BG_BRIGHT_RED "📝 ATUALIZAR DADOS 📝" RESET);

    printf(BRIGHT_RED "Digite o nome do animal que deseja atualizar: " RESET);
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalAnimais; i++) {
        if (strcmp(animais[i].nomeanimal, nome) == 0) {
            encontrado = 1;
            while (continuar) {
                limparTerminal();
                imprimirTitulo(BG_BRIGHT_RED "📝 ATUALIZAR DADOS 📝" RESET);

                printf("1. Tutor           : %s\n", animais[i].tutor);
                printf("2. Contato         : %s\n", animais[i].contato);
                printf("3. Nome do Animal  : %s\n", animais[i].nomeanimal);
                printf("4. Idade           : %d\n", animais[i].idade);
                printf("5. Cor             : %s\n", animais[i].cor);
                printf("6. Sexo            : %s\n", animais[i].sexo);
                printf("7. Espécie         : %s\n", animais[i].especie);

                printf("8. Alergias:\n");
                for (int j = 0; j < MAX; j++) {
                    if (strlen(animais[i].alergia[j].descricao) > 0) {
                        printf("   %d. %s\n\n", j + 1, animais[i].alergia[j].descricao);
                    }
                }

                printf("9. Vacinas:\n");
                for (int j = 0; j < MAX; j++) {
                    if (strlen(animais[i].vac[j].nome) > 0) {
                        printf("   %d. Nome: %s\n   Data de Aplicação : %s\n   Data de Vencimento: %s\n\n", j + 1, animais[i].vac[j].nome, animais[i].vac[j].dataapl, animais[i].vac[j].datavec);
                    }
                }

                printf("0. Voltar ao Menu Principal\n\n");
                printf(BRIGHT_RED "Escolha uma opção para atualizar: " RESET);
                scanf("%d", &escolha);

                limparTerminal();
                imprimirTitulo(BG_BRIGHT_RED "📝 ATUALIZAR DADOS 📝" RESET);

                switch (escolha) {
                    case 1:
                        printf(BRIGHT_RED "Tutor: " RESET);
                        scanf(" %[^\n]", animais[i].tutor);
                        break;
                    case 2:
                        printf(BRIGHT_RED "Contato: " RESET);
                        scanf(" %[^\n]", animais[i].contato);
                        break;
                    case 3:
                        printf(BRIGHT_RED "Nome do Animal: " RESET);
                        scanf(" %[^\n]", animais[i].nomeanimal);
                        break;
                    case 4:
                        printf(BRIGHT_RED "Idade: " RESET);
                        scanf(" %d", &animais[i].idade);
                        break;
                    case 5:
                        printf(BRIGHT_RED "Cor: " RESET);
                        scanf(" %[^\n]", animais[i].cor);
                        break;
                    case 6:
                        printf(BRIGHT_RED "Sexo: " RESET);
                        scanf(" %[^\n]", animais[i].sexo);
                        break;
                    case 7:
                        printf(BRIGHT_RED "Espécie: " RESET);
                        scanf(" %[^\n]", animais[i].especie);
                        break;
                    case 8: {
                        int quant;
                        printf(BRIGHT_RED "Quantas alergias deseja atualizar? Até 10." RESET "\n");
                        scanf("%d", &quant);

                        if (quant > 0) {
                            for (int j = 0; j < quant; j++) {
                                limparTerminal();
                                imprimirTitulo(BG_BRIGHT_RED "📝 ATUALIZAR DADOS 📝" RESET);

                                printf(BRIGHT_RED "%d° alergia" RESET "\n" , j + 1);
                                printf(BRIGHT_RED "Descrição da alergia: " RESET);
                                scanf(" %[^\n]", animais[i].alergia[j].descricao);
                            }
                            for (int j = quant; j < MAX; j++) {
                                animais[i].alergia[j].descricao[0] = '\0';
                            }
                        }
                        break;
                    }
                    case 9: {
                        int quant;
                        printf(BRIGHT_RED "Quantas vacinas deseja atualizar? Até 10." RESET "\n");
                        scanf("%d", &quant);
                        if (quant > 0) {
                            for (int j = 0; j < quant; j++) {
                                limparTerminal();
                                imprimirTitulo(BRIGHT_RED "📝 ATUALIZAR DADOS 📝" RESET);

                                printf(BRIGHT_RED "%d° vacina" RESET "\n", j + 1);
                                printf(BRIGHT_RED "Nome da vacina: " RESET);
                                scanf(" %[^\n]", animais[i].vac[j].nome);
                                printf(BRIGHT_RED "Data da aplicação: " RESET);
                                scanf(" %[^\n]", animais[i].vac[j].dataapl);
                                printf(BRIGHT_RED "Data do vencimento: " RESET);
                                scanf(" %[^\n]", animais[i].vac[j].datavec);
                            }
                            for (int j = quant; j < MAX; j++) {
                                animais[i].vac[j].nome[0] = '\0';
                                animais[i].vac[j].dataapl[0] = '\0';
                                animais[i].vac[j].datavec[0] = '\0';
                            }
                        }
                        break;
                    }
                    case 0:
                        continuar = 0;
                        break;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                }
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Animal não encontrado.\n");
    }

    aguardarTecla();
}

void deletarCadastro(Animal *animais, int *totalAnimais) {
    char nome[20];
    int encontrado = 0;

    limparTerminal();
    imprimirTitulo(BG_RED "❌ DELETAR DADOS ❌" RESET);

    printf(RED "🠊 Digite o nome do animal que deseja deletar" RESET "\n");
    if (scanf(" %[^\n]", nome) != 1) {
        printf(RED "Erro na leitura do nome." RESET "\n");
        aguardarTecla();
        return;
    }

    limparTerminal();
    imprimirTitulo(BG_RED "❌ DELETAR DADOS ❌" RESET);

    for (int i = 0; i < *totalAnimais; i++) {
        if (strcmp(animais[i].nomeanimal, nome) == 0) {
            for (int j = i; j < *totalAnimais - 1; j++) {
                animais[j] = animais[j + 1];
            }
            (*totalAnimais)--;
            encontrado = 1;
            printf(RED "Animal deletado com sucesso." RESET "\n");
            aguardarTecla();
            break;
        }
    }

    if (!encontrado) {
        printf(RED "Animal não encontrado." RESET "\n");
        aguardarTecla(); 
    }
}

void listarAlergias(Animal *animais, int totalAnimais) {
    char nome[20];
    int encontrado = 0;
    limparTerminal();
    imprimirTitulo(BG_BRIGHT_BLUE "💊 LISTAR ALERGIAS 💊" RESET);

    printf(BRIGHT_BLUE "Digite o nome do animal para listar alergias: " RESET);
    scanf(" %[^\n]", nome);

    limparTerminal();
    imprimirTitulo(BG_BRIGHT_BLUE "💊 LISTAR ALERGIAS 💊" RESET);
    for (int i = 0; i < totalAnimais; i++) {
        if (strcmp(animais[i].nomeanimal, nome) == 0) {
            printf(BRIGHT_BLUE "Alergias de %s:" RESET "\n", animais[i].nomeanimal);
            printf("════════════════════════════════════════════════════════════════════════════════\n");

            int alergiasExibidas = 0;
            for (int j = 0; j < MAX; j++) {
                if (strlen(animais[i].alergia[j].descricao) > 0) {
                    if (alergiasExibidas % 2 == 0) {
                        printf(MAGENTA);
                    } else {
                        printf(BLUE);
                    }

                    printf("  %-18s \n" RESET, animais[i].alergia[j].descricao);
                    alergiasExibidas++;
                }
            }

            if (alergiasExibidas == 0) {
                printf("   Nenhuma alergia cadastrada.\n\n");
            }

            printf("════════════════════════════════════════════════════════════════════════════════\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf(RED "Animal não encontrado.\n" RESET);
    }

    aguardarTecla();
}

/*void listarAlergias(Animal *animais, int totalAnimais) {
    char nome[20];
    int encontrado = 0;
    limparTerminal();
    imprimirTitulo(BG_BRIGHT_BLUE "💊 LISTAR ALERGIAS 💊" RESET);

    printf(BRIGHT_BLUE "Digite o nome do animal para listar alergias: " RESET);
    scanf(" %[^\n]", nome);

    limparTerminal();
    imprimirTitulo(BG_BRIGHT_BLUE "💊 LISTAR ALERGIAS 💊" RESET);
    for (int i = 0; i < totalAnimais; i++) {
        if (strcmp(animais[i].nomeanimal, nome) == 0) {
            printf(BRIGHT_BLUE "Alergias de %s:" RESET "\n", animais[i].nomeanimal);
            printf("════════════════════════════════════════════════════════════════════════════════\n");

            for (int j = 0; j < MAX && strlen(animais[i].alergia[j].descricao) > 0; j++) {
                if (j % 2 == 0) {
                    printf(MAGENTA);
                } else {
                    printf(BLUE);
                }

                printf("  %-18s \n" RESET, animais[i].alergia[j].descricao);
            }

            printf("════════════════════════════════════════════════════════════════════════════════\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf(RED "Animal não encontrado.\n" RESET);
    }

    aguardarTecla();
}*/

void listarVacinas(Animal *animais, int totalAnimais) {
    int id;
    int encontrado = 0;
    limparTerminal();
    imprimirTitulo(BG_MAGENTA "💉 MOSTRAR VACINAS 💉" RESET);

    printf(MAGENTA "Digite o id do animal para listar vacinas: " RESET);
    scanf(" %d", &id);

    limparTerminal();
    imprimirTitulo(BG_MAGENTA "💉 MOSTRAR VACINAS 💉" RESET);
    for (int i = 0; i < totalAnimais; i++) {
        if (animais[i].id == id) {
            printf(MAGENTA "Vacinas de %s:" RESET "\n", animais[i].nomeanimal);
            printf("════════════════════════════════════════════════════════════════════════════════\n");
            printf(MAGENTA "  %-18s │ %-18s │ %-18s \n" RESET, "Nome", "Aplicacao", "Vencimento");
            printf("════════════════════════════════════════════════════════════════════════════════\n");

            int vacinasExibidas = 0;
            for (int j = 0; j < MAX; j++) {
                if (strlen(animais[i].vac[j].nome) > 0) {
                    if (vacinasExibidas % 2 == 0) {
                        printf(BRIGHT_BLUE);
                    } else {
                        printf(BLUE);
                    }

                    printf("  %-18s │ %-18s │ %-18s \n" RESET,
                        animais[i].vac[j].nome, animais[i].vac[j].dataapl, animais[i].vac[j].datavec);
                    vacinasExibidas++;
                }
            }

            if (vacinasExibidas == 0) {
                printf("   Nenhuma vacina cadastrada.\n\n");
            }

            printf("════════════════════════════════════════════════════════════════════════════════\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf(RED "Animal não encontrado.\n" RESET);
    }

    aguardarTecla();
}

void inicializarAnimais(Animal animais[]){
    animais[0].id = 1;
    strcpy(animais[0].tutor, "Davi Lucas");
    strcpy(animais[0].contato, "(88) 98765-4321");
    strcpy(animais[0].nomeanimal, "Emilia");
    animais[0].idade = 5;
    strcpy(animais[0].cor, "Rajada verde");
    strcpy(animais[0].sexo, "Femea");
    strcpy(animais[0].especie, "Gato domestico");
    strcpy(animais[0].alergia[0].descricao, "Pulga");
    strcpy(animais[0].vac[0].nome, "Raiva");
    strcpy(animais[0].vac[0].dataapl, "10/01/2023");
    strcpy(animais[0].vac[0].datavec, "10/01/2024");

    animais[1].id = 2;
    strcpy(animais[1].tutor, "Joyce Vieira");
    strcpy(animais[1].contato, "(88) 99876-5432");
    strcpy(animais[1].nomeanimal, "Tuko Jr");
    animais[1].idade = 3;
    strcpy(animais[1].cor, "Preto");
    strcpy(animais[1].sexo, "Macho");
    strcpy(animais[1].especie, "Gato domestico");
    strcpy(animais[1].alergia[0].descricao, "Poeira");
    strcpy(animais[1].vac[0].nome, "V5");
    strcpy(animais[1].vac[0].dataapl, "15/02/2023");
    strcpy(animais[1].vac[0].datavec, "15/02/2024");

    animais[2].id = 3;
    strcpy(animais[2].tutor, "William Mendes");
    strcpy(animais[2].contato, "(88) 91234-5678");
    strcpy(animais[2].nomeanimal, "Jade");
    animais[2].idade = 7;
    strcpy(animais[2].cor, "Preto");
    strcpy(animais[2].sexo, "Femea");
    strcpy(animais[2].especie, "Pinsher");
    strcpy(animais[2].alergia[0].descricao, "Acaro");
    strcpy(animais[2].vac[0].nome, "Leptospirose");
    strcpy(animais[2].vac[0].dataapl, "05/03/2023");
    strcpy(animais[2].vac[0].datavec, "05/03/2024");


    animais[3].id = 4;
    strcpy(animais[3].tutor, "Luidy Farias");
    strcpy(animais[3].contato, "(88) 95678-1234");
    strcpy(animais[3].nomeanimal, "Lady");
    animais[3].idade = 2;
    strcpy(animais[3].cor, "Preta");
    strcpy(animais[3].sexo, "Femea");
    strcpy(animais[3].especie, "Salsicha");
    strcpy(animais[3].alergia[0].descricao, "Feno");
    strcpy(animais[3].vac[0].nome, "Mixomatose");
    strcpy(animais[3].vac[0].dataapl, "20/04/2023");
    strcpy(animais[3].vac[0].datavec, "20/04/2024");

    animais[4].id = 5;
    strcpy(animais[4].tutor, "Joyce Vieira");
    strcpy(animais[4].contato, "(88) 99876-5432");
    strcpy(animais[4].nomeanimal, "Louis");
    animais[4].idade = 4;
    strcpy(animais[4].cor, "Cinza");
    strcpy(animais[4].sexo, "Macho");
    strcpy(animais[4].especie, "Gato domestico");
    strcpy(animais[4].alergia[0].descricao, "Poeira");
    strcpy(animais[4].vac[0].nome, "Polivalente");
    strcpy(animais[4].vac[0].dataapl, "30/05/2023");
    strcpy(animais[4].vac[0].datavec, "30/05/2024");
}

int main() {
    Animal animais[MAX];
    inicializarAnimais(animais);
    int totalAnimais = 5;
    int selected = 0;
    char key;


    while (1) {
        printMenu(selected);
        disableBufferedInput();
        key = getchar();
        enableBufferedInput();

        if (key == '\033') {
            getchar(); 
            switch(getchar()) { 
                case UP_ARROW:
                    selected = (selected == 0) ? 6 : selected - 1;
                    break;
                case DOWN_ARROW:
                    selected = (selected == 6) ? 0 : selected + 1;
                    break;
            }
        } else if (key == ENTER) {
            switch (selected) {
                case 0:
                    cadastrarAnimal(&animais[totalAnimais]);
                    totalAnimais++;
                    break;
                case 1:
                    listarAnimais(animais, totalAnimais);
                    break;
                case 2:
                    atualizarCadastro(animais, totalAnimais);
                    break;
                case 3:
                    deletarCadastro(animais, &totalAnimais);
                    break;
                case 4:
                    listarAlergias(animais, totalAnimais);
                    break;
                case 5:
                    listarVacinas(animais, totalAnimais);
                    break;
                case 6: 
                    exit(0);
                    break;
            }
        }
    }
}

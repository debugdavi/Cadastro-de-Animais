#include <stdio.h>

typedef struct Alergias{
    char descricao[50];
}Alergias;

typedef struct Vacinas{
    char nome[50];
    char dataapl[12];
    char datavec[12];
}Vacinas;

typedef struct HistoricoMed{
    char nomedoenc[20];
    char tratamento[300];
    char dataalta[12];
}HistoricoMed;

typedef struct Animal{
    char tutor[40];
    char cpf[15];
    char contato[15];
    char nomeanimal[20];
    //char id[15];
    int idade;              //considerar tratar por meses também, usando float. Se menor que 1
    char datadenas[12];
    char cor[50];
    char sexo[12];          //os meses serao representados por 0.1, 0.3, 0.6
    char especie[30];
    float peso;
    Alergias alergia[10];
    Vacinas vac[10];
    HistoricoMed his[10];
    char statusatend[20];   // Nao atendido / Em tratamento / Alta
    char ultvisita[12];
}Animal;

void cadastrarAnimal(Animal *animal){
    int quant;

    printf("Qual o nome do tutor?\n");
    scanf(" %s", animal->tutor);
    printf("Qual o cpf do tutor?\n");
    scanf(" %s", animal->cpf);
    printf("Telefone para contato:\n");
    scanf(" %s", animal->contato);
    printf("Qual a idade do animal? Apenas números. Exemplo: 3\n");
    scanf(" %d", &animal->idade);
    printf("Qual a data de nascimento do animal? Exemplo: 01/01/2001\n");
    scanf(" %s", animal->datadenas);
    printf("Qual a cor animal?\n");
    scanf(" %s", animal->cor);
    printf("Qual o sexo do animal?\n");
    scanf(" %s", animal->sexo);
    printf("Qual a especie do animal?\n");
    scanf(" %s", animal->especie);
    printf("Qual o peso do animal? Apenas números. Exemplo: 12.5\n");
    scanf(" %f", &animal->peso);
    printf("Qual a especie do animal?\n");
    scanf(" %s", animal->especie);

    printf("\n\nQuantas alergias o seu bichinho tem?\n");
    scanf("%d", &quant);
    if(quant != 0){
        for(int i = 0; i < quant; i++){
            printf("%d° alergia\n", i + 1);
            printf("Descrição da alergia: ");
            scanf(" %s", animal->alergia[i].descricao);
        }
    }

    printf("\n\nQuantas vacinas o seu bichinho tomou?\n");
    scanf("%d", &quant);
    if(quant != 0){
        for(int i = 0; i < quant; i++){
            printf("%d° vacina\n", i + 1);
            printf("Nome da vacina: ");
            scanf(" %s", animal->vac[i].nome);
            printf("Data da aplicação: ");
            scanf(" %s", animal->vac[i].dataapl);
            printf("Data do vencimento: ");
            scanf(" %s", animal->vac[i].datavec);
        }
    }

    printf("\n\nQuantas doenças o seu bichinho já pegou?\n");
    scanf("%d", &quant);
    if(quant != 0){
        for(int i = 0; i < quant; i++){
            printf("%d° doença\n", i + 1);
            printf("Nome da doença: ");
            scanf(" %s", animal->his[i].nomedoenc);
            printf("Descreva o tratamento: ");
            scanf(" %s", animal->his[i].tratamento);
            printf("Data do vencimento: ");
            scanf(" %s", animal->his[i].dataalta);
        }
    }

    printf("\nQual o seu status de atendimento?\nResponda com 'Não atendido', 'Em tratamento' ou 'Alta' ");
    scanf(" %s", animal->statusatend);
    printf("Qual a última vísita na clínica? Exemplo: 01/01/2001");
    scanf(" %s", animal->ultvisita);
}

void imprimeInfo(){
    printf("Seja bem-vind@ ao nosso sistema, ele é responsável\n");
    printf("pela manipulação e armazenamento de dados relacio-\n");
    printf("nados aos animais :).\n\n");
}

void imprimeMenu(){
    printf("Que operação você desejaria fazer?\n");
    printf("1. Fazer cadastro\n");
    printf("2. Mostrar cadastro\n");
    printf("3. Atualizar cadastro\n");
    printf("4. Excluir cadastro\n\n");
    printf("OBS: Para sair, digite '0'\n\n");
}

void main(){
    Animal animais[5];
    Animal *opanimal;
    opanimal = animais;

    int escolhe = -1;

    imprimeInfo();

    while(1){
        imprimeMenu();
        scanf("%d", &escolhe);
        if(escolhe == 0){
            break;
        }
        switch(escolhe){
            case 1: 
                    cadastrarAnimal(opanimal);
                    opanimal++;
                    break;
            default:
                    printf("Opção inválida. Tente novamente!");
        }
    }
}
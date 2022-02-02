/*
===============================================Programa Portal SIGA IPLEIRIA===================================================
Projeto Avaliação Fundamentos da Progrmação

Escola | IPL-ESTG
Curso  | Programação de Sistemas de Informação
Ano    | 1º
Data   | 04/01/2022

Programado por | Rodrigo Luís         nº2211919
               | Filipe Marques       nº2211921
===============================================================================================================================
*/


//-----------INCLUDES--------------
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


//--------- CONSTANTES -----------
#define MAX_NOME_ESTUDANTE 50
#define MAX_VETOR_ESTUDANTES 120
#define MIN_NUMERO_ESTUDANTE 1000000
#define MAX_NUMERO_ESTUDANTE 9999999

#define MAX_NOME_ESCOLA 50
#define MAX_VETOR_ESCOLA 5
#define MIN_NOME_ABREVIATURA 1
#define MAX_NOME_ABREVIATURA 4
#define MIN_NOME_CAMPUS 5
#define MAX_NOME_CAMPUS 9
#define MIN_NOME_LOCALIDADE 2
#define MAX_NOME_LOCALIDADE 9

#define NOME_FICHEIRO "estudantes.bin"


//--------- ESTRUTURAS -----------
typedef struct
{
    int numero;
    char nome[MAX_NOME_ESTUDANTE];
    int nota_final;

} t_estudante;

typedef struct
{
    int numero;
    char nome;
    char abreviatura;
    char campus;
    char localidade;

} t_escolas;



//--------- PROTOTIPOS -----------
int menu_opcoes();
int ler_numero_int(char *msg, int min, int max);
void ler_string(char *msg, char *str, int min, int max);
void stop();

void inserir_dados_estudante(t_estudante estudantes[]);
t_estudante ler_dados_estudante();
void mostrar_dados_estudantes(t_estudante estudantes[]);
void escreve_estudante(t_estudante estudante);
void alterar_nota_estudante(t_estudante estudantes[]);
void mostrar_estatisticas(t_estudante estudantes[]);
void gravar_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[]);
void ler_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[]);
void inserir_dados_escola(t_escolas escola[]);
t_escolas ler_dados_escola();

void main()
{
    setlocale(LC_ALL, "Portuguese");

    t_estudante estudantes[MAX_VETOR_ESTUDANTES];
    int opcao;

    for(int i= 0 ; i < MAX_VETOR_ESTUDANTES ; i++)
    {
        estudantes[i].nome[0] = '/0';
        estudantes[i].numero = 0;
        estudantes[i].nota_final = 0;
    }

    ler_ficheiro(estudantes, sizeof(t_estudante), MAX_VETOR_ESTUDANTES, NOME_FICHEIRO);


    do
    {

        opcao = menu_opcoes();

        switch(opcao)
        {
        case 1:
            inserir_dados_estudante(estudantes);
            break;
        case 2:
            mostrar_dados_estudantes(estudantes);
            break;
        case 3:
            alterar_nota_estudante(estudantes);
            break;
        case 4:
            mostrar_estatisticas(estudantes);
            break;
        case 5:
            gravar_ficheiro(estudantes, sizeof(t_estudante), MAX_VETOR_ESTUDANTES, NOME_FICHEIRO);
            break;
        case 6:
            ler_ficheiro(estudantes, sizeof(t_estudante), MAX_VETOR_ESTUDANTES, NOME_FICHEIRO);
            break;

        }
        stop();

    }
    while(opcao != 0 );

    gravar_ficheiro(estudantes, sizeof(t_estudante), MAX_VETOR_ESTUDANTES, NOME_FICHEIRO);

}


//----------------------------------------------------------------------------
// Funcao menu_opcoes
//----------------------------------------------------------------------------
int menu_opcoes()
{
    int opcao;
    system("cls");
    opcao = ler_numero_int(
                            "1 - Escolas        Registar/Consultar\n"
                            "2 - Estudantes     Registar/Consultar\n"
                            "3 - Notas          Registar/Alterar/Consultar\n"
                            "4 - Transações     Registar/Consultar\n\n"
                            "5 - Estatisticas\n"
                            "6 - Guardar/Importar dados\n"
                            "0 - Sair\n -->",
                           0, 6);

    return opcao;
}


//----------------------------------------------------------------------------
// Funcao ler_numero_int
// Desc: Le um unumero interio num intervalo entre min e max e apresenta a
// a menssagem passada em *msg
//----------------------------------------------------------------------------
int ler_numero_int(char *msg, int min, int max)
{
    int valor;
    int numero_inputs_sucesso;

    do
    {
        printf("%s", msg);
        fflush(stdin);
        numero_inputs_sucesso = scanf("%d", &valor);

        if (numero_inputs_sucesso <1 || valor<min || valor>max)
        {
            printf("\nIntroduza um unico valor entre %d e %d !\n", min, max);
            stop();
        }

    }
    while(numero_inputs_sucesso <1 || valor<min || valor> max);

    return valor;
}


void ler_string(char *msg, char *str, int min, int max)
{
    int num_carateres_lidos;

    do
    {
        printf("%s", msg);
        fflush(stdin);

        fgets(str, max, stdin);

        num_carateres_lidos = strlen(str);

        if ( num_carateres_lidos <= (min+1))
        {
            printf("\nO texto introduzido deve ter pelo menos %d caracteres!\n", min);
            stop();
        }

    }
    while(num_carateres_lidos <= (min+1));
}


//----------------------------------------------------------------------------
// Funcao continuar
//----------------------------------------------------------------------------
void stop()
{
    printf("\n .. Prima ENTER para continuar .. \n");
    fflush(stdin);
    getchar();
}




//----------------------------------------------------------------------------
// Funcao inserir_dados_estudante
//----------------------------------------------------------------------------
void inserir_dados_estudante(t_estudante estudantes[])
{

    for(int i= 0 ; i < MAX_VETOR_ESTUDANTES ; i++)
    {
        if(estudantes[i].numero == 0 && estudantes[i].nota_final ==0)
        {
            estudantes[i] = ler_dados_estudante();
            break;
        }
    }

}


//----------------------------------------------------------------------------
// Funcao ler_dados_estudante
//----------------------------------------------------------------------------
t_estudante ler_dados_estudante()
{
    t_estudante estudante;

    ler_string("\nNome: ", estudante.nome, 2, MAX_NOME_ESTUDANTE);

    estudante.numero = ler_numero_int("\nNumero de Estudante: ",
                                      MIN_NUMERO_ESTUDANTE, MAX_NUMERO_ESTUDANTE);

    estudante.nota_final =  ler_numero_int("\nNotal Final (Arredondada): ",0, 20);

    return estudante;
}


//----------------------------------------------------------------------------
// Funcao mostrar_dados_estudantes
//----------------------------------------------------------------------------
void mostrar_dados_estudantes(t_estudante estudantes[])
{
    int i;

    for(i = 0; i < MAX_VETOR_ESTUDANTES ; i++)
    {
        if(estudantes[i].numero != 0 && estudantes[i].nota_final !=0)
        {
            escreve_estudante(estudantes[i]);
        }
    }
}


void escreve_estudante(t_estudante estudante)
{
    printf("\n-----------------------------------");
    printf("\nNome         : %s ", estudante.nome);
    printf("\nNumero       : %d", estudante.numero);
    printf("\nNotal Final  : %d \n", estudante.nota_final);
}


//----------------------------------------------------------------------------
// Funcao continuar
//----------------------------------------------------------------------------
void alterar_nota_estudante(t_estudante estudantes[])
{
    int numero_estudante = 0;

    system("cls");
    printf("\n ---- Alterar Nota Estudante ----\n");

    numero_estudante = ler_numero_int("Qual � o numero do estudante em que a nota ser� alterada: ",
                                      MIN_NUMERO_ESTUDANTE,MAX_NUMERO_ESTUDANTE);

    for(int i=0 ; i<MAX_VETOR_ESTUDANTES ; i++)
    {
        if(estudantes[i].numero == numero_estudante)
        {
            printf("\nAluno encontrado: \n");
            escreve_estudante(estudantes[i]);
            estudantes[i].nota_final = ler_numero_int("Introduza o novo valor da nota: ", 0, 20);

            printf("\nNota alterada: \n");
            escreve_estudante(estudantes[i]);

            break;
        }
    }
}


//----------------------------------------------------------------------------
// Funcao mostrar_estatisticas
//----------------------------------------------------------------------------
void mostrar_estatisticas(t_estudante estudantes[])
{
    int maximo=0;
    int positivas=0;
    float media=0;
    int minimo=20;
    int contador=0;

    for(int i= 0 ; i < MAX_VETOR_ESTUDANTES ; i++)
    {
        if (estudantes[i].numero >= MIN_NUMERO_ESTUDANTE && estudantes[i].numero <= MAX_NUMERO_ESTUDANTE)
        {
            if (estudantes[i].nota_final > maximo)
                maximo = estudantes[i].nota_final;

            if (estudantes[i].nota_final < minimo)
                minimo = estudantes[i].nota_final;

            if (estudantes[i].nota_final >= 9.5)
                positivas++;

            media = media + estudantes[i].nota_final;
            contador++;
        }
    }

    media = media / contador;

    printf("\nNota maxima: %d\n",maximo);
    printf("\nNota minima: %d\n",minimo);
    printf("\nMedia das notas: %.2f\n",media);
    printf("\nNotas positivas: %d\n",positivas);


}
//----------------------------------------------------------------------------
// Funcao gravar_ficheiro
//----------------------------------------------------------------------------
void gravar_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[])
{
    FILE *f = fopen(nome_ficheiro, "wb");
    int num_elementos_escritos_sucesso = 0;

    if(f == NULL)
    {
        printf("\n Erro na abertura do ficheiro \n");
        stop();
    }
    else
    {
        num_elementos_escritos_sucesso = fwrite(ponteiro_dados, tamanho_tipo_dados, num_elementos, f);
        if(num_elementos_escritos_sucesso ==0 )
        {
            printf("Erro a escrever para o ficheiro %s \n ", nome_ficheiro);
        }
        else
        {
            printf("Ficheiro %s escrito com sucesso \n ", nome_ficheiro);
        }
    }
    fclose(f);
}

//----------------------------------------------------------------------------
// Funcao ler_ficheiro
//----------------------------------------------------------------------------
void ler_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[])
{
    FILE *f = fopen(nome_ficheiro, "rb");
    int num_elementos_lidos_sucesso = 0;

    if(f == NULL)
    {
        printf("\n Erro na abertura do ficheiro \n");
        stop();
    }
    else
    {
        num_elementos_lidos_sucesso = fread(ponteiro_dados, tamanho_tipo_dados, num_elementos, f);
        if(num_elementos_lidos_sucesso == 0 )
        {
            printf("Erro a ler o ficheiro %s \n ", nome_ficheiro);
        }
        else
        {
            printf("Ficheiro %s lido com sucesso \n ", nome_ficheiro);
        }
    }
    fclose(f);
}

//----------------------------------------------------------------------------
// Funcao inserir_dados_escola
//----------------------------------------------------------------------------
void inserir_dados_escola(t_escolas escola[])
{

    for(int i= 0 ; i <= 5  ; i++)
    {
        if(escola[i].numero == 0 && escola[i].nome ==0)
        {
            escola[i] = ler_dados_escola();
            break;
        }
    }

}

//----------------------------------------------------------------------------
// Funcao ler_dados_escola
//----------------------------------------------------------------------------
t_escolas ler_dados_escola()
{
    t_escolas escolas;

    ler_string("\nNome: ", escolas.nome, 3, MAX_NOME_ESCOLA);

    ler_string("\nAbreviatura: ", escolas.abreviatura, MIN_NOME_ABREVIATURA, MAX_NOME_ABREVIATURA);

    ler_string("\nCampus: ", escolas.campus, MIN_NOME_CAMPUS, MAX_NOME_CAMPUS);

    ler_string("\nLocalidade: ", escolas.localidade, MIN_NOME_LOCALIDADE, MAX_NOME_LOCALIDADE);

    return escolas;
}
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//-----------INCLUDES--------------

//--------- CONSTANTES -----------
#define MAX_NOME_ESTUDANTE 50
#define MAX_VETOR_ESTUDANTES 120

#define MIN_NUMERO_ESTUDANTE 1000000
#define MAX_NUMERO_ESTUDANTE 9999999

#define NOME_FICHEIRO "estudantes.bin"

//--------- ESTRUTURAS -----------
typedef struct
{
   int numero;
   char nome[MAX_NOME_ESTUDANTE];
   int nota_final;
}t_estudante;


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
void gravar_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, FILE *nome_ficheiro);
void ler_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, FILE *nome_ficheiro);

void main()
{
    setlocale(LC_ALL, "Portuguese");

    t_estudante estudantes[MAX_VETOR_ESTUDANTES];
    int opcao;

    for(int i= 0 ; i < MAX_VETOR_ESTUDANTES ; i++)
    {
        strcpy(estudantes[i].nome, "");
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
    opcao = ler_numero_int("1 - Inserir dados dos estudantes  \n\n"
                           "2 - Mostrar dados dos estudantes  \n\n"
                           "3 - Alterar notas finais dos estudantes\n\n"
                           "4 - Estatísticas das Avaliações  \n\n"
                           "5 - Gravar dados em ficheiro  \n\n"
                           "6 - Ler dados de ficheiro  \n\n"
                           "0 - Sair \n --> ",
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
            printf("\nIntroduza um único valor entre %d e %d !\n", min, max);
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

    numero_estudante = ler_numero_int("Qual é o numero do estudante em que a nota será alterada: ",
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

}
//----------------------------------------------------------------------------
// Funcao gravar_ficheiro
//----------------------------------------------------------------------------
void gravar_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, FILE *nome_ficheiro)
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
void ler_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, FILE *nome_ficheiro)
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

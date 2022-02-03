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
#define MAX_NOME_UTILIZADOR 50
#define MAX_VETOR_UTILIZADOR 120
#define MIN_NUMERO_UTILIZADOR 1000000
#define MAX_NUMERO_UTILIZADOR 9999999
#define MIN_NUMERO_NIF 100000000
#define MAX_NUMERO_NIF 999999999
#define MAX_TIPO_UTILIZADOR 30
#define MAX_EMAIL_UTILIZADOR 50

#define MAX_NOME_ESCOLA 50
#define MAX_VETOR_ESCOLA 5
#define MIN_NOME_ABREVIATURA 1
#define MAX_NOME_ABREVIATURA 4
#define MIN_NOME_CAMPUS 5
#define MAX_NOME_CAMPUS 9
#define MIN_NOME_LOCALIDADE 2
#define MAX_NOME_LOCALIDADE 9

#define MAX_TIPO_TRANSACAO 10
#define MAX_TRANSACAO_DATA 10
#define MAX_TRANSACAO_HORA 8
#define MAX_VETOR_TRANSACAO 5000

#define NOME_FICHEIRO "utilizadores.bin"


//--------- ESTRUTURAS -----------
typedef struct
{
    int id;
    int saldo;
    int nif;
    int numero;
    char nome[MAX_NOME_UTILIZADOR];
    char tipo[MAX_TIPO_UTILIZADOR];
    char email[MAX_EMAIL_UTILIZADOR];

} t_utilizador;

typedef struct
{
    int id;
    char nome[MAX_NOME_ESCOLA];
    char abreviatura[MAX_NOME_ABREVIATURA];
    char campus[MAX_NOME_CAMPUS];
    char localidade[MAX_NOME_LOCALIDADE];

} t_escolas;

typedef struct
{
    int id;
    int idUtilizador;
    char tipo[MAX_TIPO_TRANSACAO];
    float valor;
    char data[MAX_TRANSACAO_DATA];
    char hora[MAX_TRANSACAO_HORA];

} t_transacao;


//--------- PROTOTIPOS -----------
int menu_opcoes();
int ler_numero_int(char *msg, int min, int max);
void ler_string(char *msg, char *str, int min, int max);
void stop();

void inserir_dados_utilizador(t_utilizador utilizadores[]);
t_utilizador ler_dados_utilizador();
void mostrar_dados_utilizadores(t_utilizador utilizadores[]);
void escreve_utilizador(t_utilizador utilizador);
void mostrar_estatisticas(t_utilizador utilizadores[]);
void gravar_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[]);
void ler_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[]);
void inserir_dados_escola(t_escolas escola[]);
t_escolas ler_dados_escola();
void registar_transacao(t_transacao transacao[]);
t_escolas ler_dados_transacao();

void main()
{
    setlocale(LC_ALL, "Portuguese");

    t_utilizador utilizadores[MAX_VETOR_UTILIZADOR];
    t_escolas escolas[MAX_VETOR_ESCOLA];
    t_transacao transacao[MAX_VETOR_TRANSACAO];
    int opcao;

    for(int i= 0 ; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        utilizadores[i].nome[0] = '/0';
        utilizadores[i].id = 0;
        utilizadores[i].abreviatura[0] = '/0';
        utilizadores[i].saldo = 0;
    }
    for(int i= 0 ; i < MAX_VETOR_ESCOLA; i++)
    {
        utilizadores[i].nome[0] = '/0';
        utilizadores[i].id = 0;
        utilizadores[i].saldo = 0;
    }
    for(int i= 0 ; i < MAX_VETOR_TRANSACAO ; i++)
    {
        utilizadores[i].nome[0] = '/0';
        utilizadores[i].id = 0;
        utilizadores[i].saldo = 0;
    }

    ler_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO);


    do
    {

        opcao = menu_opcoes();

        switch(opcao)
        {
        case 1:
            registar_escola(escolas);
            break;
        case 2:
            mostrar_escola(escolas);
            break;
        case 3:
            registar_utilizador(utilizadores);
            break;
        case 4:
            mostrar_utilizador(utilizadores);
            break;
        case 5:
            registar_transacao(transacao);
            break;
        case 6:
            consultar_transacao(transacao);
            break;
        case 7:
            inserir_utilizador(utilizadores);
            break;
        case 8:
            mostrar_utilizadores(utilizadores);
            break;
        case 9:
            gravar_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO);
            break;
        case 10:
            ler_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO);
            break;


        }
        stop();

    }
    while(opcao != 0 );

    gravar_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO);

}


//----------------------------------------------------------------------------
// Funcao menu_opcoes
//----------------------------------------------------------------------------
int menu_opcoes()
{
    int opcao;
    system("cls");
    opcao = ler_numero_int(
                            "1 - Escolas            Registar\n"
                            "2 - Escolas            Consultar\n"
                            "3 - Utilizadores       Registar"
                            "4 - Utilizadores       Consultar\n"
                            "5 - Transações         Registar\n"
                            "6 - Transações         Consultar\n"
                            "7 - Estatisticas       Pagamentos por escola\n"
                            "8 - Estatisticas       Pagamentos por utilizador\n"
                            "9 - Guardar/Importar dados\n"
                            "10 - Importar dados\n"
                            "0 - Sair\n -->",
                           0, 10);

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

//----------------------------------------------------------------------------
// Funcao ler_numero_float
// Desc: Le um unumero interio num intervalo entre min e max e apresenta a
// a menssagem passada em *msg
//----------------------------------------------------------------------------
int ler_numero_float(char *msg, float min, float max)
{
    float valor;
    int numero_inputs_sucesso;

    do
    {
        printf("%s", msg);
        fflush(stdin);
        numero_inputs_sucesso = scanf("%.2f", &valor);

        if (numero_inputs_sucesso <1 || valor<min || valor>max)
        {
            printf("\nIntroduza um unico valor entre %.2f e %.2f !\n", min, max);
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
// Funcao inserir_dados_utilizador
//----------------------------------------------------------------------------
void inserir_dados_utilizador(t_utilizador utilizadores[])
{

    for(int i= 0 ; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        if(utilizadores[i].numero == 0 && utilizadores[i].id==0)
        {
            utilizadores[i] = ler_dados_utilizador();
            break;
        }
    }

}


//----------------------------------------------------------------------------
// Funcao ler_dados_utilizador
//----------------------------------------------------------------------------
t_utilizador ler_dados_utilizador()
{
    t_utilizador utilizador;

    utilizador.numero = ler_numero_int("\nNumero de utilizador: ",MIN_NUMERO_UTILIZADOR, MAX_NUMERO_UTILIZADOR);

    ler_string("\nNome: ", utilizador.nome, MIN_NUMERO_UTILIZADOR, MAX_NOME_UTILIZADOR);

    utilizador.nif = ler_numero_int("\nNIF: ",MIN_NUMERO_NIF, MAX_NUMERO_NIF);

    utilizador.id =  ler_numero_int("\nNotal Final (Arredondada): ",0, 20);

    return utilizador;
}


//----------------------------------------------------------------------------
// Funcao mostrar_dados_utilizadores
//----------------------------------------------------------------------------
void mostrar_dados_utilizadores(t_utilizador utilizadores[])
{
    int i;

    for(i = 0; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        if(utilizadores[i].numero != 0 && utilizadores[i].id !=0)
        {
            escreve_utilizador(utilizadores[i]);
        }
    }
}


void escreve_utilizador(t_utilizador utilizador)
{
    printf("\n-----------------------------------");
    printf("\nNome         : %s ", utilizador.nome);
    printf("\nNumero       : %d", utilizador.numero);
    printf("\nNotal Final  : %d \n", utilizador.id);
}


//----------------------------------------------------------------------------
// Funcao continuar
//----------------------------------------------------------------------------
void alterar_nota_utilizador(t_utilizador utilizadores[])
{
    int numero_utilizador = 0;

    system("cls");
    printf("\n ---- Alterar Nota utilizador ----\n");

    numero_utilizador = ler_numero_int("Qual é o numero do utilizador em que a nota será alterada: ",
                                      MIN_NUMERO_UTILIZADOR,MAX_NUMERO_UTILIZADOR);

    for(int i=0 ; i<MAX_VETOR_UTILIZADOR ; i++)
    {
        if(utilizadores[i].numero == numero_utilizador)
        {
            printf("\nAluno encontrado: \n");
            escreve_utilizador(utilizadores[i]);
            utilizadores[i].id = ler_numero_int("Introduza o novo valor da nota: ", 0, 20);

            printf("\nNota alterada: \n");
            escreve_utilizador(utilizadores[i]);

            break;
        }
    }
}


//----------------------------------------------------------------------------
// Funcao mostrar_estatisticas
//----------------------------------------------------------------------------
void mostrar_estatisticas(t_utilizador utilizadores[])
{
    int maximo=0;
    int positivas=0;
    float media=0;
    int minimo=20;
    int contador=0;

    for(int i= 0 ; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        if (utilizadores[i].numero >= MIN_NUMERO_UTILIZADOR && utilizadores[i].numero <= MAX_NUMERO_UTILIZADOR)
        {
            if (utilizadores[i].id > maximo)
                maximo = utilizadores[i].id;

            if (utilizadores[i].id < minimo)
                minimo = utilizadores[i].id;

            if (utilizadores[i].id >= 9.5)
                positivas++;

            media = media + utilizadores[i].id;
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

void inserir_dados_escola(t_escolas escola[])
{

    for(int i= 0 ; i <= MAX_VETOR_ESCOLA  ; i++)
    {
        if(escola[i].id == 0 && escola[i].nome ==0)
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

void registar_transacao(t_transacao transacao[])
{

    for(int i= 0 ; i <= MAX_VETOR_TRANSACAO  ; i++)
    {
        if(transacao[i].id == 0)
        {
            transacao[i] = ler_dados_transacao();
            break;
        }

    }

}

//----------------------------------------------------------------------------
// Funcao ler_transacao
//----------------------------------------------------------------------------
t_escolas ler_dados_transacao()
{
    t_transacao transacao;

    transacao.idUtilizador = ler_numero_int("Numero do utilizador: ",MIN_NUMERO_UTILIZADOR,MAX_NUMERO_UTILIZADOR);

    ler_string("\nTipo de pagamento: ", transacao.tipo, 1, MAX_TIPO_TRANSACAO);

    transacao.valor = ler_numero_float("Numero do utilizador: ",0.01,9999.99);
    

    return transacao;
}
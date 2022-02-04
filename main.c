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
#define MIN_NUMERO_UTILIZADOR 1
#define MAX_NUMERO_UTILIZADOR 9999999
#define MIN_NUMERO_NIF 100000000
#define MAX_NUMERO_NIF 999999999
#define MAX_TIPO_UTILIZADOR 30
#define MAX_EMAIL_UTILIZADOR 50

#define MAX_NOME_ESCOLA 50
#define MAX_VETOR_ESCOLA 5
#define MIN_NOME_ABREVIATURA 1
#define MAX_NOME_ABREVIATURA 4
#define MIN_NOME_CAMPUS 1
#define MAX_NOME_CAMPUS 9
#define MIN_NOME_LOCALIDADE 2
#define MAX_NOME_LOCALIDADE 9

#define MAX_TIPO_TRANSACAO 15
#define MAX_TRANSACAO_DATA 10
#define MAX_TRANSACAO_HORA 8
#define MAX_VETOR_TRANSACAO 5000

#define NOME_FICHEIRO_UTILIZADORES "utilizadores.bin"
#define NOME_FICHEIRO_ESCOLAS "escolas.bin"
#define NOME_FICHEIRO_TRANSACOES "transacoes.bin"


//--------- ESTRUTURAS -----------
typedef struct
{
    int id;
    int saldo;
    int nif;
    int idEscola;
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

void inserir_utilizador(t_utilizador utilizadores[]);
t_utilizador ler_utilizador();

void mostrar_utilizadores(t_utilizador utilizadores[]);
void escreve_utilizador(t_utilizador utilizador);

void mostrar_estatisticas_escola(t_escolas escola[]);
void mostrar_estatisticas_utilizador(t_utilizador utilizadores[]);

void gravar_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[]);
void ler_ficheiro(void *ponteiro_dados, int tamanho_tipo_dados, int num_elementos, char nome_ficheiro[]);

void registar_escola(t_escolas escola[]);
t_escolas ler_escola();

void registar_transacao(t_transacao transacao[]);
t_transacao ler_transacao();

void mostrar_escolas(t_escolas escola[]);
void escreve_escolas(t_escolas escola);

void mostrar_transacao(t_transacao transacao[]);
void escreve_transacao(t_transacao transacao);

void main()
{
    setlocale(LC_ALL, "Portuguese");

    t_utilizador utilizadores[MAX_VETOR_UTILIZADOR];
    t_escolas escolas[MAX_VETOR_ESCOLA];
    t_transacao transacao[MAX_VETOR_TRANSACAO];

    int opcao;

    for(int i= 0 ; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        utilizadores[i].id = 0;
        utilizadores[i].saldo = 0;
        utilizadores[i].nif = 0;
        utilizadores[i].idEscola = 0;
        utilizadores[i].nome[0] = '/0';
        utilizadores[i].tipo[0] = '/0';
        utilizadores[i].email[0] = '/0';
    }
    for(int i= 0 ; i < MAX_VETOR_ESCOLA; i++)
    {
        escolas[i].id = 0;
        escolas[i].nome[0] = '/0';
        escolas[i].abreviatura[0] = '/0';
        escolas[i].campus[0] = '/0';
        escolas[i].localidade[0] = '/0';
    }
    for(int i= 0 ; i < MAX_VETOR_TRANSACAO ; i++)
    {
        transacao[i].id = 0;
        transacao[i].idUtilizador = 0;
        transacao[i].tipo[0] = '/0';
        transacao[i].valor = 0.00;
        transacao[i].data[0] = '/0';
        transacao[i].hora[0] = '/0';
    }

    ler_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO_UTILIZADORES);
    ler_ficheiro(escolas, sizeof(t_escolas), MAX_VETOR_ESCOLA, NOME_FICHEIRO_ESCOLAS);
    ler_ficheiro(transacao, sizeof(t_transacao), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO_TRANSACOES);

    do
    {

        opcao = menu_opcoes();

        switch(opcao)
        {
        case 1:
            registar_escola(escolas);
            break;
        case 2:
            mostrar_escolas(escolas);
            break;
        case 3:
            inserir_utilizador(utilizadores);
            break;
        case 4:
            mostrar_utilizadores(utilizadores);
            break;
        case 5:
            registar_transacao(transacao);
            break;
        case 6:
            mostrar_transacao(transacao);
            break;
        case 7:
            mostrar_estatisticas_escola(escolas);
            break;
        case 8:
            mostrar_estatisticas_utilizador(utilizadores);
            break;
        case 9:
            gravar_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO_UTILIZADORES);
            gravar_ficheiro(escolas, sizeof(t_escolas), MAX_VETOR_ESCOLA, NOME_FICHEIRO_ESCOLAS);
            gravar_ficheiro(transacao, sizeof(t_transacao), MAX_VETOR_TRANSACAO, NOME_FICHEIRO_TRANSACOES);
            break;
        case 10:
            ler_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO_UTILIZADORES);
            ler_ficheiro(escolas, sizeof(t_escolas), MAX_VETOR_ESCOLA, NOME_FICHEIRO_ESCOLAS);
            ler_ficheiro(transacao, sizeof(t_transacao), MAX_VETOR_TRANSACAO, NOME_FICHEIRO_TRANSACOES);
            break;


        }
        stop();

    }
    while(opcao != 0 );

    gravar_ficheiro(utilizadores, sizeof(t_utilizador), MAX_VETOR_UTILIZADOR, NOME_FICHEIRO_UTILIZADORES);
    gravar_ficheiro(escolas, sizeof(t_escolas), MAX_VETOR_ESCOLA, NOME_FICHEIRO_ESCOLAS);
    gravar_ficheiro(transacao, sizeof(t_transacao), MAX_VETOR_TRANSACAO, NOME_FICHEIRO_TRANSACOES);

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
                            "3 - Utilizadores       Registar\n"
                            "4 - Utilizadores       Consultar\n"
                            "5 - Transacoes         Registar\n"
                            "6 - Transacoes         Consultar\n"
                            "7 - Estatisticas       Pagamentos por escola\n"
                            "8 - Estatisticas       Pagamentos por utilizador\n"
                            "9 - Guardar Dados\n"
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
// Funcao inserir_utilizador
//----------------------------------------------------------------------------
void inserir_utilizador(t_utilizador utilizadores[])
{

    for(int i= 0 ; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        if(utilizadores[i].id == 0)
        {
            utilizadores[i] = ler_utilizador();
            break;
        }
    }

}


//----------------------------------------------------------------------------
// Funcao ler_utilizador
//----------------------------------------------------------------------------
t_utilizador ler_utilizador()
{
    t_utilizador utilizador;

    utilizador.id = ler_numero_int("\nID: ",MIN_NUMERO_UTILIZADOR, MAX_NUMERO_UTILIZADOR);
    utilizador.idEscola = ler_numero_int("\nID da escola: ",1, 5);
    ler_string("\nNome: ", utilizador.nome, MIN_NUMERO_UTILIZADOR, MAX_NOME_UTILIZADOR);
    ler_string("\nTipo(Estudante, Docente, Funcionário): ", utilizador.tipo, 1, 15);
    utilizador.nif = ler_numero_int("\nNIF: ",MIN_NUMERO_NIF, MAX_NUMERO_NIF);
    ler_string("\nEmail: ", utilizador.email, 10, 50);
    utilizador.saldo = ler_numero_int("\nInserir Saldo: ",0, 99999999);

    return utilizador;
}


//----------------------------------------------------------------------------
// Funcao mostrar_utilizadores
//----------------------------------------------------------------------------
void mostrar_utilizadores(t_utilizador utilizadores[])
{
    int i;

    for(i = 0; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        if(utilizadores[i].id != 0)
        {
            escreve_utilizador(utilizadores[i]);
        }
    }
}


void escreve_utilizador(t_utilizador utilizador)
{
    printf("\n-----------------------------------");
    printf("\nID           : %d", utilizador.id);
    printf("\nSaldo        : %d", utilizador.saldo);
    printf("\nNIF          : %d", utilizador.nif);
    printf("\nID da Escola : %d", utilizador.idEscola);
    printf("\nNome         : %s", utilizador.nome);
    printf("\nTipo         : %s", utilizador.tipo);
    printf("\nEmail        : %s", utilizador.email);
    printf("\n-----------------------------------");
}

//----------------------------------------------------------------------------
// Funcao mostrar_transações
//----------------------------------------------------------------------------
void mostrar_transacao(t_transacao transacao[])
{
    int i;

    for(i = 0; i < MAX_VETOR_UTILIZADOR ; i++)
    {
        if(transacao[i].id != 0)
        {
            escreve_transacao(transacao[i]);
        }
    }
}


void escreve_transacao(t_transacao transacao)
{
    printf("\n-----------------------------------");
    printf("\nID                : %d ", transacao.id);
    printf("\nID da Escola      : %d", transacao.idUtilizador);
    printf("\nTipo              : %s", transacao.tipo);
    printf("\nValor             : %.2f", transacao.valor);
    printf("\nData              : %s", transacao.data);
    printf("\nHora              : %s", transacao.hora);
    printf("\n-----------------------------------");
}

//----------------------------------------------------------------------------
// Funcao mostrar_escola
//----------------------------------------------------------------------------
void mostrar_escolas(t_escolas escola[])
{
    int i;

    for(i = 0; i < MAX_VETOR_ESCOLA ; i++)
    {
        if(escola[i].id != 0)
        {
            escreve_escolas(escola[i]);
        }
    }
}


void escreve_escolas(t_escolas escola)
{
    printf("\n-----------------------------------");
    printf("\nID           : %d", escola.id);
    printf("\nNome         : %s", escola.nome);
    printf("\nAbreviatura  : %s", escola.abreviatura);
    printf("\nCampus       : %s", escola.campus);
    printf("\nLocalidade   : %s", escola.localidade);
    printf("\n-----------------------------------");
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
        if(utilizadores[i].id == numero_utilizador)
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
void mostrar_estatisticas_escola(t_escolas escola[])
{

}

void mostrar_estatisticas_utilizador(t_utilizador utilizadores[])
{

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

void registar_escola(t_escolas escola[])
{

    for(int i= 0 ; i <= MAX_VETOR_ESCOLA  ; i++)
    {
        if(escola[i].id == 0)
        {
            escola[i] = ler_escola();
            break;
        }
    }

}

//----------------------------------------------------------------------------
// Funcao ler_escola
//----------------------------------------------------------------------------
t_escolas ler_escola()
{
    t_escolas escolas;

    escolas.id = ler_numero_int("ID da escola: ", 1, MAX_VETOR_ESCOLA);
    ler_string("Nome: ", escolas.nome, 3, MAX_NOME_ESCOLA);
    ler_string("Abreviatura: ", escolas.abreviatura, MIN_NOME_ABREVIATURA, MAX_NOME_ABREVIATURA);
    ler_string("Campus: ", escolas.campus, MIN_NOME_CAMPUS, MAX_NOME_CAMPUS);
    ler_string("Localidade: ", escolas.localidade, MIN_NOME_LOCALIDADE, MAX_NOME_LOCALIDADE);

    return escolas;
}

void registar_transacao(t_transacao transacao[])
{

    for(int i= 0 ; i <= MAX_VETOR_TRANSACAO  ; i++)
    {
        if(transacao[i].id == 0)
        {
            transacao[i] = ler_transacao();
            break;
        }

    }

}

//----------------------------------------------------------------------------
// Funcao ler_transacao
//----------------------------------------------------------------------------
t_transacao ler_transacao()
{
    t_transacao transacao;

    transacao.id = ler_numero_int("ID da Transação: ",MIN_NUMERO_UTILIZADOR,MAX_NUMERO_UTILIZADOR);
    transacao.idUtilizador = ler_numero_int("ID da escola: ",1, 5);
    ler_string("\nTipo de pagamento(Carregamento, Pagamento): ", transacao.tipo, 1, MAX_TIPO_TRANSACAO);
    transacao.valor = ler_numero_int("Valor: ",0,999999);
    ler_string("\nData: ", transacao.data, 1, 10);
    ler_string("\nHora: ", transacao.hora, 1, 10);
    
    return transacao;
}


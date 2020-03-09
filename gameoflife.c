#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int **alocaMatriz(int l, int c)
{ //Função para alocar a matriz de acordo com a linha e a coluna especificada no arquivo de entrada
    int **m, i;

    if (l < 1 || c < 1)
    { //Como a entrada pode ser de 0 a 100, e não existe matriz com nenhuma dimensão igual a 0, deve ser feito um tratamento de erros
        printf("Erro : Dimensoes invalidas para a matriz.\n");
        return (NULL);
    }

    m = (int **)calloc(l + 2, sizeof(int *)); // Alocação dinâmica da memória para a matriz usando calloc, pois os valores já são zerados
    if (m == NULL)
    {
        printf("Erro : Memoria insuficiente para alocar a matriz.\n");
        return (NULL);
    }
    for (i = 0; i < l + 2; i++)
    {
        m[i] = (int *)calloc(c + 2, sizeof(int));
        if (m[i] == NULL)
        {
            printf("Erro : Memoria insuficiente para alocar a matriz.\n");
            return (NULL);
        }
    }

    return (m); //Retorna o ponteiro para a matriz para a função main
}

int **liberaMatriz(int l, int c, int **m)
{ //Função para liberar o espaço alocado para a(s) matriz(es)

    int i;

    if (m == NULL)
        return (NULL);

    if (l < 1 || c < 1)
    {
        printf("Erro : Dimensoes invalidas para a matriz.\n");
        return (m);
    }

    for (i = 0; i < l + 2; i++) //Libera as linhas da matriz
        free(m[i]);

    free(m); //Libera a matriz

    return (NULL); //Retorna um ponteiro nulo, pois a matriz já foi desalocada
}

void imprime(int **matriz, int l, int c)
{ //Função para imprimir na tela a geração atual

    int i, j;

    printf("\tGeracao Atual:\n");

    printf("\n\t==");
    for (i = 0; i < c; i++)
        printf("=");
    printf("\n");

    for (i = 1; i <= l; i++)
    {
        for (j = 1; j <= c; j++)
        {
            if (j == 1)
                printf("\t|");
            if (matriz[i][j] == 1)
                printf("*");
            else
                printf(" ");
            if (j == c)
                printf("|\n");
        }
    }
    printf("\t==");
    for (i = 0; i < c; i++)
        printf("=");
    printf("\n\n");
}

char pergunta()
{
    char choice;

    printf("Deseja simular uma nova geracao?(s/n)\n> ");
    scanf(" %c", &choice);
    choice = toupper(choice);

    return (choice);
}

int main()
{

    int lin, col;           //variáveis para guardar os valores da linha e da coluna, respectivamente
    int **at;               //ponteiro de vetores para alocar a matriz da geração atual
    int **pr;               //ponteiro de vetores para alocar a matriz da próxima geração
    int **cont;             //matriz para guardar os valores dos vizinhos de cada posição da matriz atual
    int i, j, k, l;         //variáveis auxiliares
    char escolha = 's';     //variável para guardar a escolha do usuário a ser feita posteriormente
    FILE *primeira_geracao; //ponteiro para indicar o arquivo que mostra a geração atual
    FILE *ultima_geracao;

    primeira_geracao = fopen("primeira-g.txt", "r"); //Abre o arquivo em modo de leitura somente e testa se ele existe no diretório
    if (primeira_geracao == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        system("pause");
        return (0);
    }
    fscanf(primeira_geracao, "%d %d", &lin, &col); //Leitura dos dois primeiros números, que indicam a qtd. de linhas e colunas da matriz

    at = alocaMatriz(lin, col);   //Aloca a memória necessária para a matriz da geração atual
    pr = alocaMatriz(lin, col);   //Aloca a memória necessária para a matriz da próxima geração
    cont = alocaMatriz(lin, col); //Aloca a memória necessária para a matriz dos contadores da geração atual

    for (i = 1; i <= lin; i++)
    {
        for (j = 1; j <= col; j++)
        {
            fscanf(primeira_geracao, "%d", &at[i][j]); //Lê e armazena os valores da matriz do arquivo em uma matriz no programa
        }
    }

    for (i = 1; i <= lin; i++)
    {
        for (j = 1; j <= col; j++)
        {
            pr[i][j] = at[i][j]; //Iguala a matriz da próxima geração com a da atual, para que ela possa ser modificada
        }
    }

    printf("\n Trabalho Pratico de AEDS I\n\n\tJogo da Vida\n\nLegenda : %c = Celula viva\n\n", 219); //Interface do programa

    imprime(at, lin, col); //Imprime a geração atual

    while (1)
    {
        escolha = pergunta(); //Interação com o usuário sobre o avanço da geração
        // escolha = 'S';
        // sleep(1);
        if (escolha == 'N')
            break; //Escolha do usuário de não avançar mais uma geração

        for (i = 1; i <= lin; i++)
        { //Comparação de cada posição da matriz e de seus vizinhos, gerando uma outra matriz com o número de vizinhos
            for (j = 1; j <= col; j++)
            {
                cont[i][j] = 0;
                if (pr[i][j] == 1)
                    cont[i][j]--; //Se o elemento analisado for '1', a iteração contaria ele, porém ele é retirado nessa linha
                for (k = -1; k <= 1; k++)
                {
                    for (l = -1; l <= 1; l++)
                    {
                        if (pr[i + k][j + l] == 1)
                            cont[i][j]++;
                    }
                }
            }
        }

        for (i = 1; i <= lin; i++)
        { //Análise de qual célula é viva ou morta à partir das regras impostas pelo "Jogo da Vida"
            for (j = 1; j <= col; j++)
            {
                if (cont[i][j] < 2) //Regra 1
                    pr[i][j] = 0;

                else if (pr[i][j] == 1 && (cont[i][j] == 2 || cont[i][j] == 3)) //Regra 2
                    pr[i][j] = 1;

                else if (cont[i][j] > 3) //Regra 3
                    pr[i][j] = 0;

                else if (cont[i][j] == 3) //Regra 4
                    pr[i][j] = 1;
            }
        }

        imprime(pr, lin, col); //Imprime a situação da geração atual
    }

    ultima_geracao = fopen("ultima-geracao.txt", "w"); //Quando o usuário escolhe 'N', é criado um novo arquivo e salvado nele a matriz da ultima geração

    fprintf(ultima_geracao, "%d %d\n", lin, col);

    for (i = 1; i <= lin; i++)
    {
        for (j = 1; j <= col; j++)
        {
            fprintf(ultima_geracao, "%d", pr[i][j]);
            if (j < col)
                fprintf(ultima_geracao, " ");
            else if (j == col)
                fprintf(ultima_geracao, "\n");
        }
    }

    printf("\n*A ultima geracao foi registrada em um arquivo .txt de nome 'ultima_geracao' na pasta local do trabalho*\n\n");

    at = liberaMatriz(lin, col, at);     //Libera o espaço ocupado pela matriz da geração atual na memória
    pr = liberaMatriz(lin, col, pr);     //Libera o espaço ocupado pela matriz da próxima geração na memória
    cont = liberaMatriz(lin, col, cont); //Libera o espaço ocupado pela matriz dos contador dos vizinhos

    fclose(primeira_geracao); //Fecha o arquivo de entrada
    fclose(ultima_geracao);   //Fecha o arquivo da última geração
    return (0);
}

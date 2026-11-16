#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int Nulo(const void *valor)
{
    return valor == NULL;
}

int adicionarItem(const char item[], int qtd)
{
    FILE *original = fopen("inventory.txt", "r");
    int arquivoExistia = original != NULL;

    FILE *temporario = fopen("inventory.tmp", "w");
    if (Nulo(temporario))
        return 1;

    char nome[51];
    char linhaQtd[20];
    int qtdAtual;
    int encontrou = 0;
    int erro = 0;

    while (original != NULL && fgets(nome, sizeof(nome), original) != NULL)
    {
        if (fgets(linhaQtd, sizeof(linhaQtd), original) == NULL ||
            sscanf(linhaQtd, "%d", &qtdAtual) != 1)
        {
            erro = 1;
            break;
        }

        nome[strcspn(nome, "\r\n")] = '\0';

        if (strcmp(nome, item) == 0 && !encontrou)
        {
            qtdAtual += qtd;
            encontrou = 1;
        }

        fprintf(temporario, "%s\n%d\n", nome, qtdAtual);
    }

    if (!encontrou)
        fprintf(temporario, "%s\n%d\n", item, qtd);

    if (original != NULL)
        fclose(original);

    if (fclose(temporario) != 0)
        erro = 1;

    if (erro)
    {
        remove("inventory.tmp");
        return 0;
    }

    if (arquivoExistia && remove("inventory.txt") != 0)
    {
        remove("inventory.tmp");
        return 0;
    }

    if (rename("inventory.tmp", "inventory.txt") != 0)
        return 0;

    return 1;
}

int removerItem(const char item[], int qtdRemover)
{
    FILE *original = fopen("inventory.txt", "r");

    // Se o arquivo nem existe ainda, o item nao tem como estar la
    if (Nulo(original))
    {
        printf("Item nao encontrado.\n");
        return 1;
    }

    FILE *temporario = fopen("inventory.tmp", "w");
    if (Nulo(temporario))
    {
        fclose(original);
        return 0;
    }

    char nome[51];
    char linhaQtd[20];
    int qtdAtual;
    int encontrou = 0;
    int erro = 0;

    while (fgets(nome, sizeof(nome), original) != NULL)
    {
        if (fgets(linhaQtd, sizeof(linhaQtd), original) == NULL ||
            sscanf(linhaQtd, "%d", &qtdAtual) != 1)
        {
            erro = 1;
            break;
        }

        nome[strcspn(nome, "\r\n")] = '\0';

        if (strcmp(nome, item) == 0 && !encontrou)
        {
            encontrou = 1;

            if (qtdRemover > qtdAtual)
            {
                printf("Estoque insuficiente. Quantidade disponivel: %d\n", qtdAtual);
                fprintf(temporario, "%s\n%d\n", nome, qtdAtual);
            }
            else if (qtdAtual - qtdRemover > 0)
            {
                qtdAtual -= qtdRemover;
                printf("Quantidade atualizada com sucesso!\n");
                fprintf(temporario, "%s\n%d\n", nome, qtdAtual);
            }
            else
            {
                printf("Item removido do estoque!\n");
            }
        }
        else
        {
            fprintf(temporario, "%s\n%d\n", nome, qtdAtual);
        }
    }

    if (!encontrou && !erro)
    {
        printf("Item nao encontrado.\n");
    }

    fclose(original);

    if (fclose(temporario) != 0)
        erro = 1;

    if (erro)
    {
        remove("inventory.tmp");
        return 0;
    }

    if (remove("inventory.txt") != 0)
    {
        remove("inventory.tmp");
        return 0;
    }

    if (rename("inventory.tmp", "inventory.txt") != 0)
        return 0;

    return 1;
}

void listarEstoque()
{
    FILE *p = fopen("inventory.txt", "r");
    if (Nulo(p))
    {
        printf("Estoque vazio.\n");
        return;
    }

    char nome[51];
    char linhaQtd[20];
    int qtd;
    int temItens = 0;

    printf("        Estoque Atual        \n");

    while (fgets(nome, sizeof(nome), p) != NULL)
    {
        if (fgets(linhaQtd, sizeof(linhaQtd), p) != NULL &&
            sscanf(linhaQtd, "%d", &qtd) == 1)
        {
            nome[strcspn(nome, "\r\n")] = '\0';
            printf("Nome: %s\n", nome);
            printf("Quantidade: %d\n\n", qtd);
            temItens = 1;
        }
    }

    if (!temItens)
    {
        printf("Estoque vazio.\n");
    }

    fclose(p);
}

int main()
{
    int caso, qtd;
    char respFinal;
    char proximochar = 0;
    char item[51];
    char temp[51];
    do
    {
        proximochar = 0;
        if (scanf("%d%c", &caso, &proximochar) != 2 || proximochar != '\n')
        {
            printf("Erro: Entrada invalida! Digite apenas um numero inteiro de 1 a 4.\n");
            if (proximochar != '\n')
            {
                limparBuffer();
            }
            continue;
        }

        if (caso < 1 || caso > 4)
        {
            printf("Numero Invalido, tente novamente!\n");
            continue;
        }

        printf("Controle de Estoque\n"
               "Selecione Uma opcao\n"
               "1. Adicionar Item\n"
               "2. Remover Item\n"
               "3. Listar Estoque\n"
               "4. Sair\n"
               "Opcao:\n");

        scanf("%d", &caso);
        switch (caso)
        {

        case 1:

            printf("Digite o nome do item: ");
            limparBuffer();
            fgets(item, 51, stdin);
            item[strcspn(item, "\r\n")] = '\0';

            printf("Digite a quantidade: ");
            scanf("%d", &qtd);
            printf("Item adicionado com sucesso!\n");

            if (!adicionarItem(item, qtd))
                return 1;
            do
            {
                printf("Deseja realizar outra operacao? (s/n):\n");
                scanf(" %c", &respFinal);
                if (respFinal != 's' && respFinal != 'S' && respFinal != 'n' && respFinal != 'N')
                {
                    printf("Resposta invalida. Por favor, digite 's' para sim ou 'n' para nao.\n");
                }
            } while (respFinal != 's' && respFinal != 'S' && respFinal != 'n' && respFinal != 'N');
            break;

        case 2:
            printf("Digite o nome do item: ");
            limparBuffer();
            fgets(item, 51, stdin);
            item[strcspn(item, "\r\n")] = '\0';

            printf("Digite a quantidade a ser removida: ");
            scanf("%d", &qtd);

            if (!removerItem(item, qtd))
                return 1;
            do
            {
                printf("Deseja realizar outra operacao? (s/n):\n");
                scanf(" %c", &respFinal);
                if (respFinal != 's' && respFinal != 'S' && respFinal != 'n' && respFinal != 'N')
                {
                    printf("Resposta invalida. Por favor, digite 's' para sim ou 'n' para nao.\n");
                }
            } while (respFinal != 's' && respFinal != 'S' && respFinal != 'n' && respFinal != 'N');
            break;

        case 3:
            listarEstoque();
            do
            {
                printf("Deseja realizar outra operacao? (s/n):\n");
                scanf(" %c", &respFinal);
                if (respFinal != 's' && respFinal != 'S' && respFinal != 'n' && respFinal != 'N')
                {
                    printf("Resposta invalida. Por favor, digite 's' para sim ou 'n' para nao.\n");
                }
            } while (respFinal != 's' && respFinal != 'S' && respFinal != 'n' && respFinal != 'N');
            break;

        case 4:
            printf("Obrigado por usar o Controle de Estoque! Ate a proxima.\n");
            return 0;

        default:
            printf("Opcao invalida! Tente novamente.\n");
            respFinal = 'S';
            break;
        }
    } while (respFinal == 's' || respFinal == 'S');

    if (respFinal == 'n' || respFinal == 'N')
    {
        printf("Obrigado por usar o Controle de Estoque! Ate a proxima.\n");
    }
    return 0;
}
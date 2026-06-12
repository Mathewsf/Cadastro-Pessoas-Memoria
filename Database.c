#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

typedef struct {
    int CPF;
    char Nome[30];
    int Idade;
    int Ativado;
} Pessoa;

typedef struct {
    int cpf;
    int posicao;
} IndiceCpf;

typedef struct {
    char Nome[30];
    int posicao;
} IndiceNome;

void inserePessoaOrdNome(IndiceNome *V, Pessoa A, int N) {
    int i; 

    for (i = N-1; i >= 0 && strcasecmp(A.Nome, V[i].Nome) < 0; i--) {
        V[i + 1] = V[i];
    }
    strcpy(V[i + 1].Nome, A.Nome);
    V[i + 1].posicao = N;
}

void inserePessoaOrdCpf(IndiceCpf *V, Pessoa A, int N) {
    int i; 

    for (i = N-1; i >= 0 && A.CPF < V[i].cpf; i--) {
        V[i + 1] = V[i];
    }
    V[i + 1].cpf = A.CPF;
    V[i + 1].posicao = N;
}

void ListOrdNormal(Pessoa *VetPessoa, int N) {
    int i, qtd = 0;

    for (i = 0; i < N; i++) {

        if (VetPessoa[i].Ativado == 1) {
        
            printf("CPF: %d\n", VetPessoa[i].CPF);
            printf("Nome: %s\n", VetPessoa[i].Nome);
            printf("Idade: %d\n", VetPessoa[i].Idade);
            printf("\n");
            qtd++;
        }
        
    }

    if (qtd == 0) {
        printf("Nao tem pessoas ativas.\n");
    }

}

void ListOrdCpf(Pessoa *VetPessoa, IndiceCpf *VetCpf, int N) {
    int i, qtd = 0;

    for (i = 0; i < N; i++) {

        if (VetPessoa[VetCpf[i].posicao].Ativado == 1) {
        
            printf("CPF: %d\n", VetPessoa[VetCpf[i].posicao].CPF);
            printf("Nome: %s\n", VetPessoa[VetCpf[i].posicao].Nome);
            printf("Idade: %d\n", VetPessoa[VetCpf[i].posicao].Idade);
            printf("\n");
            qtd++;
        }
    }

    if (qtd == 0) {
        printf("Nao tem pessoas ativas.\n");
    }
}

void ListOrdNome(Pessoa *VetPessoa, IndiceNome *VetNome, int N) {
    int i, qtd = 0;

    for (i = 0; i < N; i++) {

        if (VetPessoa[VetNome[i].posicao].Ativado == 1) {
        
            printf("CPF: %d\n", VetPessoa[VetNome[i].posicao].CPF);
            printf("Nome: %s\n", VetPessoa[VetNome[i].posicao].Nome);
            printf("Idade: %d\n", VetPessoa[VetNome[i].posicao].Idade);
            printf("\n");
            qtd++;
        }
    }

    if (qtd == 0) {
        printf("Nao tem pessoas ativas.\n");
    }
}

int BuscaBinNome(char Nome[], IndiceNome *V, int i, int f) {
    if (i >= f) {
        if (i == f && strcasecmp(Nome, V[i].Nome) == 0)
            return V[i].posicao;
        return -1;
    }

    int m = (i + f) / 2;

    if (strcasecmp(Nome, V[m].Nome) <= 0) {
        return BuscaBinNome(Nome, V, i, m);
    }

    return BuscaBinNome(Nome, V, m + 1, f);
}

int BuscaBinCpf(int cpf, IndiceCpf *V, int i, int f) {
    if (i >= f) {
        if (i == f && cpf == V[i].cpf)
            return V[i].posicao;
        return -1;
    }

    int m = (i + f) / 2;

    if (cpf <= V[m].cpf) {
        return BuscaBinCpf(cpf, V, i, m);
    }

    return BuscaBinCpf(cpf, V, m + 1, f);
}

int excluiNome(char nome[30], Pessoa *VetPessoa, IndiceNome *VetNome, int N) {
    char OP;
    int verifica = 0;
    int posicao = BuscaBinNome(nome, VetNome, 0, N-1);

    if (posicao > -1) {
        printf("\nTem certeza que quer excluir essa pessoa: \n");
        printf("CPF: %d\n", VetPessoa[posicao].CPF);
        printf("Nome: %s\n", VetPessoa[posicao].Nome);
        printf("Idade: %d\n", VetPessoa[posicao].Idade);

        printf("\nDigite 'S' para sim e 'N' para nao: ");
        scanf(" %c", &OP);
        OP = toupper(OP);

        if (OP == 'S') {
            VetPessoa[posicao].Ativado = 0;
            printf("Pessoa excluida com sucesso.\n");
            verifica++;
        } else {
            printf("Pessoa nao excluida.\n");
        }

    } else {
        printf("Pessoa nao encontrada.\n");
    }

    return verifica;
}

int excluiCpf(int cpf, Pessoa *VetPessoa, IndiceCpf *VetCpf, int N) {
    char OP;
    int verifica = 0;
    int posicao = BuscaBinCpf(cpf, VetCpf, 0, N-1);

    if (posicao > -1) {
        printf("\nTem certeza que quer excluir essa pessoa: \n");
        printf("CPF: %d\n", VetPessoa[posicao].CPF);
        printf("Nome: %s\n", VetPessoa[posicao].Nome);
        printf("Idade: %d\n", VetPessoa[posicao].Idade);

        printf("\nDigite 'S' para sim e 'N' para nao: ");
        scanf(" %c", &OP);
        OP = toupper(OP);

        if (OP == 'S') {
            VetPessoa[posicao].Ativado = 0;
            printf("Pessoa excluida com sucesso.\n");
            verifica++;
        } else {
            printf("Pessoa nao excluida.\n");
        }
    } else {
        printf("Pessoa nao encontrada.\n");
    }

    return verifica;
}

void excluiPermanente(Pessoa *VetPessoa, IndiceNome *VetOrdNome, IndiceCpf *VetOrdCpf, int *N) {
    int i, j; 

    for (i = 0; i < *N; i++) {
        
        if (VetPessoa[i].Ativado == 0) {

            for (j = i; j < *N - 1; j++) {
                VetPessoa[j] = VetPessoa[j + 1];
            }

            (*N)--;

            i--;
        }
    }

    for (i = 0; i < *N; i++) {
        inserePessoaOrdNome(VetOrdNome, VetPessoa[i], i);
        inserePessoaOrdCpf(VetOrdCpf, VetPessoa[i], i);
    }

    printf("Exclusao permanente realizada.\n");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menuPrincipal() {
    int Opcao;

    system("cls");

    gotoxy(35, 1);
    printf("MENU PRINCIPAL");
    gotoxy(30, 3);
    printf("1 - Inserir pessoas\n");
    gotoxy(30, 4);
    printf("2 - Listar pessoas\n");
    gotoxy(30, 5);
    printf("3 - Buscar pessoas\n");
    gotoxy(30, 6);
    printf("4 - Excluir pessoas\n");
    gotoxy(30, 7);
    printf("5 - Excluir permanentemente\n");
    gotoxy(30, 8);
    printf("6 - Sair\n");

    gotoxy(30, 10);
    printf("Digite a opcao desejada: ");
    scanf("%d", &Opcao);

    system("cls");

    return Opcao;

}

int main() {
    Pessoa Vet[100];
    IndiceNome VetOrdNome[100];
    IndiceCpf VetOrdCpf[100];
    char OP;
    int N = 0, i;
    int Opcao;
    int NumOp;
    int verifica = 0;

    Opcao = menuPrincipal();

    while (Opcao != 6)
    {

        switch (Opcao)
        {
            case 1:
            //INSERIR
                
                printf("Digite o CPF (ou 0 para parar): ");
                scanf("%d", &Vet[N].CPF);

                while (Vet[N].CPF) {
                    if (N >= 100) {
                        printf("Limite atingido.\n");
                        break;
                    }
                    getchar();

                    printf("Nome: ");
                    fgets(Vet[N].Nome, 30, stdin);
                    Vet[N].Nome[strlen(Vet[N].Nome)-1] = '\0';

                    printf("Idade: ");
                    scanf("%d", &Vet[N].Idade);

                    Vet[N].Ativado = 1;

                    inserePessoaOrdNome(VetOrdNome, Vet[N], N);
                    inserePessoaOrdCpf(VetOrdCpf, Vet[N], N);

                    N++;

                    printf("Proximo CPF (ou 0 para sair): ");
                    scanf("%d", &Vet[N].CPF);
                }
            break;
            case 2:
            //LISTAR
                printf("Deseja listar de qual forma?\n");
                printf("1 - Listar pela ordem de insercao\n");
                printf("2 - Listar por ordem de nome\n");
                printf("3 - Listar por ordem de CPF\n");

                printf("\nDigite a opcao desejada: ");
                scanf("%d", &NumOp);

                switch (NumOp) {

                case 1:
                    ListOrdNormal(Vet, N);
                    printf("\nAperte ENTER para continuar");
                    system("pause > null");
                break;
                
                case 2:
                    ListOrdNome(Vet, VetOrdNome, N);
                    printf("\nAperte ENTER para continuar");
                    system("pause > null");
                break;

                case 3:
                    ListOrdCpf(Vet, VetOrdCpf, N); 
                    printf("\nAperte ENTER para continuar");
                    system("pause > null");
                break;
                default:
                    printf("Opcao invalida\n");
                    printf("\nAperte ENTER para continuar");
                    system("pause > null");
                break;
            }
            break;    
            case 3:
            //BUSCA
            OP = 'S';

            while (OP == 'S') 
            {
                system("cls");
                printf("Deseja buscar de qual forma?\n");
                printf("1 - Nome\n");
                printf("2 - CPF\n");

                printf("\nDigite a opcao desejada: ");
                scanf("%d", &NumOp);

                if (NumOp == 1) {
                    char NomeOp[30];
                    printf("\nDigite o nome: ");
                    scanf(" %[^\n]", NomeOp);

                    int posicao = BuscaBinNome(NomeOp, VetOrdNome, 0, N-1);

                    if (posicao > -1) {
                        printf("\nCPF: %d\n", Vet[posicao].CPF);
                        printf("Nome: %s\n", Vet[posicao].Nome);
                        printf("Idade: %d\n", Vet[posicao].Idade);
                    } else {
                        printf("\nPessoa nao encontrada.\n");
                    }
                } else {
                    int cpf;
                    printf("\nDigite o CPF: ");
                    scanf("%d", &cpf);

                    int posicao = BuscaBinCpf(cpf, VetOrdCpf, 0, N-1);

                    if (posicao > -1) {
                        printf("\nCPF: %d\n", Vet[posicao].CPF);
                        printf("Nome: %s\n", Vet[posicao].Nome);
                        printf("Idade: %d\n", Vet[posicao].Idade);
                    } else {
                        printf("\nPessoa nao encontrada.\n");
                    }

                }

                printf("\nDeseja fazer outra busca? S/N\n");
                scanf(" %c", &OP);
                OP = toupper(OP);
            }
            break;
            case 4:
            //EXCLUIR
            OP = 'S';
            
            while (OP == 'S') 
            {
                system("cls");
                printf("Digite a forma que deseja exlcuir a pessoa:\n");
                printf("1 - Pelo Nome\n");
                printf("2 - Pelo CPF\n");
                
                printf("\nDigite a opcao desejada: ");
                scanf("%d", &NumOp);

                switch (NumOp)
                {
                    case 1:
                        printf("\nDigite o nome da pessoa que deseja excluir: \n");
                        char nome[30];
                        scanf(" %[^\n]", nome);

                        verifica += excluiNome(nome, Vet, VetOrdNome, N);
                    break;
                    case 2:
                        printf("\nDigite o CPF da pessoa que deseja excluir: \n");
                        int cpf;
                        scanf("%d", &cpf);

                        verifica += excluiCpf(cpf, Vet, VetOrdCpf, N);
                    break;
                    default:
                        printf("Opcao invalida\n");
                    break;
                }

                printf("\nDeseja excluir outra pessoa? S/N\n");
                scanf(" %c", &OP);
                OP = toupper(OP);
            }
            break;
            case 5:
            //exclui permanentemente

                if (verifica > 0) {
                    excluiPermanente(Vet, VetOrdNome, VetOrdCpf, &N);
                    verifica = 0;
                    printf("\nAperte ENTER para continuar\n");
                    system("pause > null");
                } else {
                    printf("Nenhuma pessoa ainda foi excluida. Exclua pelo menos uma pessoa antes de excluir permanentemente.\n");
                    printf("\nAperte ENTER para continuar\n");
                    system("pause > null");
                }
            break;
        }

        Opcao = menuPrincipal();
    }
    return 0;
}

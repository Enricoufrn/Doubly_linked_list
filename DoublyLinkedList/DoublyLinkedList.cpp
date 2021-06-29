// DoublyLinkedList.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include <stdlib.h>
#include <stdio.h>

struct no {
    struct no* ant;
    int val;
    struct no* prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar();
struct no* alocarNovoNo(int valor);
void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor);

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor);

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao);

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao);

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao);

void imprimirLista(struct doublylinkedlist* lista);

int main()
{
    struct doublylinkedlist* lista = inicializar();
    inserirElementoNoInicio(lista, 0);
    inserirElementoNoFim(lista, 1);
    imprimirLista(lista);
    printf("\n");
    inserirElementoEmPosicao(lista, 50, 2);
    imprimirLista(lista);
    removerElementoEmPosicao(lista, 2);
    removerElementoEmPosicao(lista, 1);
    removerElementoEmPosicao(lista, 0);
    printf("\n");
    imprimirLista(lista);
}

struct doublylinkedlist* inicializar() {
    struct doublylinkedlist* list = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    if (list != NULL) {
        list->cabeca = NULL;
        list->cauda = NULL;
        list->qtdade = 0;
    }
    return list;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    if (novoNo != NULL) {
        novoNo->ant = NULL;
        novoNo->prox = NULL;
        novoNo->val = valor;
    }
    return novoNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor) {
    struct no* novoElemento = alocarNovoNo(valor);
    if (lista->cabeca == NULL) { // lista vazia
        lista->cabeca = novoElemento;
        lista->cauda = novoElemento;
    }
    else { // lista não está vazia
        struct no* aux = lista->cabeca;
        lista->cabeca = novoElemento;
        novoElemento->prox = aux;
        aux->ant = novoElemento;
    }
    lista->qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    struct no* novoElemento = alocarNovoNo(valor);
    if (lista->cabeca == NULL) {
        lista->cabeca = novoElemento;
        lista->cauda = novoElemento;
    }
    else {
        struct no* aux = lista->cauda;
        lista->cauda = novoElemento;
        aux->prox = novoElemento;
        novoElemento->ant = aux;
    }
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        if (posicao == 0 || posicao == lista->qtdade) {
            if (posicao == 0) { // equivalente a inserir no início
                inserirElementoNoInicio(lista, valor);
            }
            else { // equivalente a inserir no fim
                inserirElementoNoFim(lista, valor);
            }
        }
        else { // inserçao em outras posições intermediárias
            struct no* novoElemento = alocarNovoNo(valor);
            struct no* aux = lista->cabeca;
            for (int i = 0; i < posicao - 1; i++) {
                aux = aux->prox;
            }
            struct no* aux2 = aux->prox;
            aux->prox = novoElemento;
            novoElemento->ant = aux;
            novoElemento->prox = aux2;
            aux2->ant = novoElemento;
            lista->qtdade++;
        }
    }
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {
        struct no* aux = lista->cabeca;
        int cont = 0;
        while (aux->prox != NULL) {
            if (cont == posicao)
                break;
            aux = aux->prox;
            cont++;
        }
        return aux->val;
    }
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        struct no* aux = lista->cabeca;
        if (posicao == 0) {// equivalente a remover no início 
            lista->cabeca = aux->prox;
            if (lista->cabeca == NULL) {
                lista->cauda = lista->cabeca;
            }
            else {
                aux->prox->ant = NULL;
            }
            free(aux);
        }
        else { // remoção meio ou fim
            for (int i = 0; i < posicao - 1; i++) {
                aux = aux->prox;
            }
            struct no* aux2 = aux->prox;
            aux->prox = aux2->prox;
            if (lista->cauda == aux2) {
                lista->cauda = aux2->ant;
            }
            else {
                aux2->prox->ant = aux;
            }
            free(aux2);
        }
        lista->qtdade--;
    }
}

void imprimirLista(struct doublylinkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln

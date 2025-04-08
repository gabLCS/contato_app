#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

// cpf (string de 11 caracteres)
// nome (string de 50 caracteres)
// telefone (string de 12 caracteres)
// endereco (string de 100 caracteres)
// cidade (string de 50 caracteres)
// estado (string de 2 caracteres)
typedef struct minha_pessoa {
  int id;
  char nome[50];
  char cpf[11];
  char telefone[12];
  char endereco[100];
  char cidade[50];
  char estado[2];
} Pessoa;

typedef struct node {
  Pessoa *pessoa;
  struct node *proximo;
} Lista;

int tamanho_Lista;
// Aponta para o arquivo principal
FILE *fp;
// Variavel auxiliar para criar o arquivo caso nao exista
FILE *fp_aux;
FILE *fp_qtd_contatos;

Pessoa pessoa_aux;

/*Cria uma lista encadeada vazia*/
Lista *cria_lista_vazia(void) { return (NULL); }

/* retorna 1 se a lista for vazia e 0 se não for vazia*/
int checa_lista_vazia(Lista *lista) { return (lista == NULL); }

// salvando conteudo da lista em arquivo
void Inserir_Lista_Arquivo(Lista *lista) {
  Pessoa pessoa_aux;
  fp = fopen("pessoas.dat", "w");
  fclose(fp);

  fp = fopen("pessoas.dat", "a+");

  if (lista != NULL) {
    Lista *lista_aux;
    lista_aux = lista;
    while (lista_aux != NULL) {
      if (lista_aux->pessoa->id < 0) {
        lista_aux = lista_aux->proximo;
        continue;
      }
      strcpy(pessoa_aux.cidade, lista_aux->pessoa->cidade);
      strcpy(pessoa_aux.estado, lista_aux->pessoa->estado);
      strcpy(pessoa_aux.nome, lista_aux->pessoa->nome);
      strcpy(pessoa_aux.telefone, lista_aux->pessoa->telefone);
      strcpy(pessoa_aux.endereco, lista_aux->pessoa->endereco);
      pessoa_aux.id = lista_aux->pessoa->id;

      strcpy(pessoa_aux.nome, lista_aux->pessoa->nome);

      printf("Nome %s   Id %d\n", pessoa_aux.nome, pessoa_aux.id);
      size_t f_insere = fwrite(&pessoa_aux, sizeof(Pessoa), 1, fp);
      int f_insere_aux = 0;
      f_insere_aux = (int)f_insere;

      lista_aux = lista_aux->proximo;
    }
  } else {
    printf("Lista vazia!\n");
  }
  fclose(fp);
}

/* insere uma nova pessoa na lista encadeada*/
Lista *insere(Pessoa pessoa, Lista *lista) {
  // aloca espaco para nova pessoa
  Pessoa *nova_pessoa = (Pessoa *)malloc(sizeof(Pessoa));
  // aloca espaco para novo no
  Lista *novo_no = (Lista *)malloc(sizeof(Lista));
  // dados de pessoa
  nova_pessoa->id = pessoa.id;
  strcpy(nova_pessoa->nome, pessoa.nome);
  // dados do no (associa nova pessoa ao novo no)
  novo_no->pessoa = nova_pessoa;
  novo_no->proximo = lista;
  tamanho_Lista++;
  return (novo_no);
}

int tamanho_lista(Lista *lista) {
  int cont = 0;
  Lista *p;
  p = lista;
  while (p != NULL) {
    cont++;
    p = p->proximo;
  }
  return cont;
}

/* imprime os elementos da lista*/
void imprime_lista(Lista *lista) {
  if (lista != NULL) {
    Lista *lista_aux;
    lista_aux = lista;
    while (lista_aux != NULL) {
      if (lista_aux->pessoa->id < 0) {
        lista_aux = lista_aux->proximo;
        continue;
      }
      printf("[%s] -> ", lista_aux->pessoa->nome);
      // percorre a lista
      lista_aux = lista_aux->proximo;
    }
  } else {
    printf("Lista vazia! []\n");
  }
}

// Abre o arquivo principal para leitura
int abre_arquivo() {
  // Abre arquivo para leitura
  fp = fopen("pessoas.dat", "r");
  // Cria o arquivo caso ele nao exista
  if (fp == NULL) {
    printf("Arquivo pessoas.dat criado com sucesso!\n");
    fp_aux = fopen("pessoas.dat", "w");
    // aponta para o arquivo principal
    fp = fp_aux;
  }
  return 0;
}

// Abre o arquivo principal e ler a quantidade de pessoas salvas
// retorna o total de pessoas do arquivo
int ler_total_pessoas() {
  fp_qtd_contatos = fopen("pessoas.dat", "r");
  // Checa se tem conteudo do tipo contato
  size_t lidos = fread(&pessoa_aux, sizeof(Pessoa), 1000, fp_qtd_contatos);
  int total_pessoas = 0;
  total_pessoas = (int)lidos;
  // fecha arquivo auxiliar
  fclose(fp_qtd_contatos);
  return total_pessoas;
}

Lista *Recuperar_Pessoas(Lista *lista) {
  if (ler_total_pessoas() > 0) {
    Pessoa pessoa_temp;
    // abre arquivo principal para leitura
    fp = fopen("pessoas.dat", "r");
    // Ler conteudo do arquivo pessoas.dat (percorre os pessoas de forma
    // sequencial)
    while (fread(&pessoa_aux, sizeof(Pessoa), 1, fp)) {
      printf("Id = %d | Nome = %s\n", pessoa_aux.id, pessoa_aux.nome);
      // Ler cada contato e guarda na lista de pessoas em tempo de memoria
      pessoa_temp.id = pessoa_aux.id;
      strcpy(pessoa_temp.cidade, pessoa_aux.cidade);
      strcpy(pessoa_temp.estado, pessoa_aux.estado);
      strcpy(pessoa_temp.nome, pessoa_aux.nome);
      strcpy(pessoa_temp.telefone, pessoa_aux.telefone);
      strcpy(pessoa_temp.endereco, pessoa_aux.endereco);
      lista = insere(pessoa_temp, lista);
    }
    // fecha o arquivo principal
    fclose(fp);
  }
  return lista;
}

// Insere uma pessoa na ultima posicao do arquivo principal
Lista *inserir_pessoa(Lista *lista) {
  int total_pessoas = 0;
  Pessoa pessoa_temp;
  // abre o arquivo principal para escrita no final

  printf("\n");
  pessoa_temp.id = tamanho_Lista + 1;
  printf("Nome da pessoa %d: ", tamanho_Lista + 1);
  scanf("%s", pessoa_temp.nome);
  printf("cpf da pessoa %d: ", tamanho_Lista + 1);
  scanf("%s", pessoa_temp.cpf);
  printf("telefone da pessoa %d: ", tamanho_Lista + 1);
  scanf("%s", pessoa_temp.telefone);
  printf("endereco da pessoa %d: ", tamanho_Lista + 1);
  scanf("%s", pessoa_temp.endereco);
  printf("cidade da pessoa %d: ", tamanho_Lista + 1);
  scanf("%s", pessoa_temp.cidade);
  printf("estado da pessoa %d: ", tamanho_Lista + 1);
  scanf("%s", pessoa_temp.estado);
  printf("\n");
  // salva pessoa na lista de pessoas;
  lista = insere(pessoa_temp, lista);
  return lista;
}

// Pesquisa pelo nome da pessoa
int Pesquisar(char nome[], Lista *lista) {
  Pessoa temp;
  temp.id = -1;
  if (lista != NULL) {
    Lista *lista_aux;
    lista_aux = lista;
    while (lista_aux != NULL) {
      if (strcmp(nome, lista_aux->pessoa->nome) == 0 &&
          lista_aux->pessoa->id > 0) {
        printf("Pessoa %s encontrada\n ", lista_aux->pessoa->nome);
        temp.id = lista_aux->pessoa->id;
        strcpy(temp.cidade, lista_aux->pessoa->cidade);
        strcpy(temp.estado, lista_aux->pessoa->estado);
        strcpy(temp.nome, lista_aux->pessoa->nome);
        strcpy(temp.telefone, lista_aux->pessoa->telefone);
        strcpy(temp.endereco, lista_aux->pessoa->endereco);
        printf("cpf: %s\nnome: %s\n telefone: %s\n endereco: %s\n cidade: %s\n "
             "estado %s\n",
             temp.cpf, temp.nome, temp.telefone,
             temp.endereco, temp.cidade, temp.estado);
        return 0;
      }
      // percorre a lista
      lista_aux = lista_aux->proximo;
    }
    printf("pessoa inexistente\n");

    return 0;
  } else {
    printf("Lista vazia\n");
    return 0;
  }
}
// pesquisar por numero
int Pesquisar_num(char numero[], Lista *lista) {
  Pessoa temp;
  temp.id = -1;
  if (lista != NULL) {
    Lista *lista_aux;
    lista_aux = lista;
    while (lista_aux != NULL) {
      if (strcmp(numero, lista_aux->pessoa->telefone) == 0 &&
          lista_aux->pessoa->id > 0) {
        printf("Pessoa %s encontrada\n ", lista_aux->pessoa->nome);
        temp.id = lista_aux->pessoa->id;

        strcpy(temp.cidade, lista_aux->pessoa->cidade);
        strcpy(temp.estado, lista_aux->pessoa->estado);
        strcpy(temp.nome, lista_aux->pessoa->nome);
        strcpy(temp.telefone, lista_aux->pessoa->telefone);
        strcpy(temp.endereco, lista_aux->pessoa->endereco);
        printf("cpf: %s\nnome: %s\n telefone: %s\n endereco: %s\n cidade: %s\n "
             "estado %s\n",
             temp.cpf, temp.nome, temp.telefone,
             temp.endereco, temp.cidade, temp.estado);
      
        return 0;
      }
      // percorre a lista
      lista_aux = lista_aux->proximo;
    }
    printf("pessoa inexistente\n");

    return 0;
  } else {
    printf("Lista vazia\n");
    return 0;
  }
}
void menu() {
  printf("\n--- Menu Principal ---");
  printf("\n(1) - Inserir Pessoa");
  printf("\n(2) - Listar Pessoas");
  printf("\n(3) - Pesquisar Pessoa por numero");
  printf("\n(4) - Pesquisar Pessoa por nome");
  printf("\n(5) - Remover Pessoa por id");
  printf("\n(6) - Remover Pessoa por nome");
  printf("\n(7) - imprimir ordem crescente");
  printf("\n(8) - imprimir ordem decrescente");
  printf("\n(9) - Salvar e sair");
  printf("\nQual a sua opção?\n");
}

Lista *ordemCrescente(Lista *p) {
  Lista *aux = p;
  Lista *t;
  Pessoa *c;

  if (p == NULL || p->proximo == NULL)
    return NULL;

  while (aux != NULL) {
    t = aux->proximo;
    while (t != NULL) {
      if (strcmp(aux->pessoa->nome, t->pessoa->nome) < 0) {

        c = aux->pessoa;
        aux->pessoa = t->pessoa;
        t->pessoa = c;
      }
      t = t->proximo;
    }
    aux = aux->proximo;
  }

  return p;
}

Lista *ordemDecrescente(Lista *p) {
  Lista *aux = p;
  Lista *t;
  Pessoa *c;

  if (p == NULL || p->proximo == NULL)
    return NULL;

  while (aux != NULL) {
    t = aux->proximo;
    while (t != NULL) {
      if (strcmp(aux->pessoa->nome, t->pessoa->nome) < 0) {

        c = aux->pessoa;
        aux->pessoa = t->pessoa;
        t->pessoa = c;
      }
      t = t->proximo;
    }
    aux = aux->proximo;
  }

  return p;
}
/* imprime os elementos da lista*/
void imprimirLista(Lista *lista) {
  if (lista != NULL) {
    Lista *lista_aux;
    lista_aux = lista;
    while (lista_aux != NULL) {
      if (lista_aux->pessoa->id < 0) {
        lista_aux = lista_aux->proximo;
        continue;
      }
      printf("[%s] -> ", lista_aux->pessoa->nome);
      // percorre a lista
      lista_aux = lista_aux->proximo;
    }
  } else {
    printf("Lista vazia!\n");
  }
}

Lista *imprimir_Lista_Em_Ordem_Crescente(Lista *lista) {
  Lista *p = lista;
  p = ordemCrescente(p);
  printf("ordem crescente:  ");
  imprimirLista(p);
  return lista;
}
Lista *imprimir_Lista_Em_Ordem_Decrescente(Lista *lista) {
  Lista *p = lista;
  printf("ordem decrescente: ");
  p = ordemDecrescente(p);
  imprimirLista(p);
  return lista;
}

Lista *RemoverPessoa(Lista *lista, char id[]) {
  if (lista != NULL) {
    Lista *lista_aux;
    lista_aux = lista;
    while (lista_aux != NULL) {
      if (strcmp(lista_aux->pessoa->telefone, id) == 0) {
        printf("Removendo %s...\n", lista_aux->pessoa->nome);
        lista_aux->pessoa->id = -1;
      }
      lista_aux = lista_aux->proximo;
    }
  } else {
    printf("Lista vazia!\n");
  }
  return lista;
}
Lista *RemoverPessoa_nome(Lista *lista, char nome[]) {
  if (lista != NULL) {
    Lista *lista_aux;
    lista_aux = lista;
    while (lista_aux != NULL) {
      if (strcmp(lista_aux->pessoa->nome, nome) == 0) {
        printf("Removendo %s...\n", lista_aux->pessoa->nome);
        lista_aux->pessoa->id = -1;
      }
      lista_aux = lista_aux->proximo;
    }
  } else {
    printf("Lista vazia!\n");
  }
  return lista;
}

int main() {
  int x = 0, op, id;
  Lista *lista_pessoas;
  lista_pessoas = cria_lista_vazia();
  abre_arquivo();
  lista_pessoas = Recuperar_Pessoas(lista_pessoas);
  tamanho_Lista = tamanho_lista(lista_pessoas);
  Pessoa pessoa_temp;
  char info[100];

  while (x == 0) {
    menu();
    scanf("%d", &op);
    switch (op) {
      strcpy(info, "");
    case 7:
imprimir_Lista_Em_Ordem_Crescente(lista_pessoas);
      break;

    case 8:
imprimir_Lista_Em_Ordem_Decrescente(lista_pessoas);
      break;

    case 2:
      imprime_lista(lista_pessoas);
      break;

    case 4:
      printf("Insira o nome da pessoa: ");
      scanf("%s", info);

      Pesquisar(info, lista_pessoas);
      break;

    case 1:
      if (tamanho_Lista == N) {
        printf("A lista está cheia\n");
        break;
      }
      lista_pessoas = inserir_pessoa(lista_pessoas);
      break;

    case 3:
      printf("Insira o numero da pessoa: ");
      scanf("%s", info);

      Pesquisar_num(info, lista_pessoas);
      break;

    case 5:
      printf("Insira o numero da pessoa que deseja remover: ");
      scanf("%s", info);
      RemoverPessoa(lista_pessoas, info);
      break;

    case 6:
      printf("Insira o nome da pessoa que deseja remover: ");
      scanf("%s", info);
      RemoverPessoa_nome(lista_pessoas, info);
      break;

    case 9:
      x = 1;
      printf("salvando contatos\n");
      Inserir_Lista_Arquivo(lista_pessoas);
      printf("encerrando programa...");
      break;
    }
  }
}
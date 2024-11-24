#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Preço em centavos do combo de refrigante e pipoca
#define PRECO_COMBO 1500

#define SALA_LINHAS 5
#define SALA_COLUNAS 5

struct Sala {
  char filme[65];
  bool lugares[SALA_LINHAS][SALA_COLUNAS];
  unsigned int preco_bilhete;
};

struct Bilhete {
  unsigned int id;
  struct Sala *sala;
  unsigned int valor_pago;
  char lugar_linha;
  unsigned int lugar_coluna;
  bool meia_entrada;
  bool combo;
  bool cancelado;
};

#define SESSAO_NR_SALAS 3
#define SESSAO_NR_BILHETES 100

struct Sessao {
  struct Sala salas[SESSAO_NR_SALAS];
  struct Bilhete bilhetes[SESSAO_NR_BILHETES];
  unsigned int indice_bilhete;
};

void menu_principal(struct Sessao *sessao);
void menu_reservar_lugar(struct Sessao *sessao);
void menu_impressao_bilhete(struct Sessao *sessao);
void menu_cancelamento(struct Sessao *sessao);

void sessao_listar_salas(struct Sessao *sessao);
void sessao_exibir_relatorio(struct Sessao *sessao);
struct Bilhete* sessao_salvar_bilhete(
  struct Sessao *sessao,
  struct Sala *sala,
  char lugar_linha,
  unsigned int lugar_coluna,
  bool meia_entrada,
  bool combo
);

void sala_exibir_lugares(struct Sala *sala);
bool sala_reservar_lugar(struct Sala *sala, char linha, unsigned int coluna);
void sala_liberar_lugar(struct Sala *sala, char linha, unsigned int coluna);

void bilhete_imprimir(struct Bilhete *bilhete);
void bilhete_cancelar(struct Bilhete *bilhete);


int main(void)
{
  struct Sessao sessao = {
    .salas = {
      {
        .filme = "Deadpool",
        .preco_bilhete = 3500,
      },
      {
        .filme = "O Auto da Compadecida 2",
        .preco_bilhete = 2000,
      },
      {
        .filme = "Velozes e Furiosos",
        .preco_bilhete = 2500,
      },
    },
  };

  menu_principal(&sessao);

  return EXIT_SUCCESS;
}

void menu_principal(struct Sessao *sessao)
{
  unsigned int opcao;

  while (true)
  {
    puts("1. Reservar um lugar");
    puts("2. Impressao de bilhete");
    puts("3. Cancelamento de compra");
    puts("4. Finalizar sessao");

    fputs("\nEscolha a opcao: ", stdout);
    scanf("%u", &opcao);

    switch (opcao)
    {
    case 1:
      menu_reservar_lugar(sessao);
      break;
    case 2:
      menu_impressao_bilhete(sessao);
      break;
    case 3:
      menu_cancelamento(sessao);
      break;
    case 4:
      sessao_exibir_relatorio(sessao);
      exit(EXIT_SUCCESS);
    }
  }
}

void menu_reservar_lugar(struct Sessao *sessao)
{
  // @todo: Implementar menu para reserva de lugar.
}

void menu_impressao_bilhete(struct Sessao *sessao)
{
  // @todo: Implementar menu para reserva de lugar.
}

void menu_cancelamento(struct Sessao *sessao)
{
  // @todo: Implementar menu para reserva de lugar.
}


void sessao_listar_salas(struct Sessao *sessao)
{
  // @todo: Implementar função para listar salas
}

void sessao_exibir_relatorio(struct Sessao *sessao)
{
  // @todo: Implementar função para exibir relatório de uma sessão.
}

struct Bilhete* sessao_salvar_bilhete(
  struct Sessao *sessao,
  struct Sala *sala,
  char lugar_linha,
  unsigned int lugar_coluna,
  bool meia_entrada,
  bool combo
) {
  // @todo: Implementar função para salvar bilhete em uma sessão.
  return NULL;
}

void sala_exibir_lugares(struct Sala *sala)
{
  // @todo: Implementar função para exibir a matriz de lugares de uma sala.
}

bool sala_reservar_lugar(struct Sala *sala, char linha, unsigned int coluna)
{
  // @todo: Implementar função para marcar um lugar da sala como reservado.
  return true;
}

void sala_liberar_lugar(struct Sala *sala, char linha, unsigned int coluna)
{
  // @todo: Implementar função para marcar um lugar da sala como disponível.
}

void bilhete_imprimir(struct Bilhete *bilhete)
{
  // @todo: Implementar função para imprimir as informações de um bilhete na tela.
}

void bilhete_cancelar(struct Bilhete *bilhete)
{
  // @todo: Implementar função para cancelar um bilhete previamente comprado.
}

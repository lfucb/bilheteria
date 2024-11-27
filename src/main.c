#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

int lscanf(char *text, const char *format, ...);

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

    lscanf("\nEscolha a opcao: ", "%u", &opcao);

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
      putchar('\n');
      sessao_exibir_relatorio(sessao);
      exit(EXIT_SUCCESS);
    }
  }
}

void menu_reservar_lugar(struct Sessao *sessao)
{
  unsigned int opcao;
  char resposta;
  char linha;
  unsigned int coluna;
  int ret;

  sessao_listar_salas(sessao);

  do {
    ret = lscanf("\nEscolha a sala: ", "%u", &opcao);
  } while(ret != 1 || opcao < 1 || opcao > SESSAO_NR_SALAS);

  struct Sala *sala = &sessao->salas[opcao - 1];

  sala_exibir_lugares(sala);

  do {
    ret = lscanf("\nEscolha o lugar (ex.: A1): ", "%c%u", &linha, &coluna);

    if (linha < 'A' || linha > 'E' || coluna < 1 || coluna > 5)
    {
      continue;
    }

    if (ret == 2 && ! sala->lugares[linha - 'A'][coluna - 1])
    {
      break;
    }
  } while (true);

  lscanf("E meia-entrada? [s/n] ", "%c", &resposta);

  bool meia_entrada = (resposta == 's');

  lscanf("Deseja incluir um combo de pipoca e refrigerante? [s/n] ", "%c", &resposta);

  bool combo = (resposta == 's');

  struct Bilhete *bilhete = sessao_salvar_bilhete(sessao, sala, linha, coluna, meia_entrada, combo);

  sala_reservar_lugar(sala, linha, coluna);

  putchar('\n');
  bilhete_imprimir(bilhete);
  putchar('\n');
}

void menu_impressao_bilhete(struct Sessao *sessao)
{
  unsigned int numero_bilhete;
  int ret;

  do {
    ret = lscanf("Digite o numero do bilhete: ", "%u", &numero_bilhete);
  } while(ret != 1 || numero_bilhete < 1 || numero_bilhete > sessao->indice_bilhete);

  struct Bilhete *bilhete = &sessao->bilhetes[numero_bilhete - 1];

  putchar('\n');
  bilhete_imprimir(bilhete);
  putchar('\n');
}

void menu_cancelamento(struct Sessao *sessao)
{
  unsigned int numero_bilhete;
  int ret;

  do {
    ret = lscanf("Digite o numero do bilhete: ", "%u", &numero_bilhete);
  } while(ret != 1 || numero_bilhete < 1 || numero_bilhete > sessao->indice_bilhete);

  struct Bilhete *bilhete = &sessao->bilhetes[numero_bilhete - 1];

  bilhete_cancelar(bilhete);
  sala_liberar_lugar(bilhete->sala, bilhete->lugar_linha, bilhete->lugar_coluna);

  puts("Compra cancelada com sucesso!");
}


void sessao_listar_salas(struct Sessao *sessao)
{
  for (int i = 0; i < SESSAO_NR_SALAS; i++)
  {
    printf("Sala %d: %s\n", i + 1, sessao->salas[i].filme);
  }
}

void sessao_exibir_relatorio(struct Sessao *sessao)
{
  unsigned int total_bilhetes_vendidos = 0;
  unsigned int total_combos_vendidos = 0;
  unsigned int total_arrecadado = 0;

  for (int i = 0; i < sessao->indice_bilhete; i++)
  {
    if (sessao->bilhetes[i].cancelado)
    {
      continue;
    }

    total_arrecadado += sessao->bilhetes[i].valor_pago;

    if (sessao->bilhetes[i].combo)
    {
      total_combos_vendidos++;
    }

    total_bilhetes_vendidos++;
  }

  printf("Bilhetes vendidos: %d\n", total_bilhetes_vendidos);
  printf("Combos vendidos: %d\n", total_combos_vendidos);
  printf("Total arrecadado: R$ %.2f\n", total_arrecadado / 100.0);
}

struct Bilhete* sessao_salvar_bilhete(
  struct Sessao *sessao,
  struct Sala *sala,
  char lugar_linha,
  unsigned int lugar_coluna,
  bool meia_entrada,
  bool combo
) {
  unsigned int valor_pago = sala->preco_bilhete;
  if (meia_entrada) {
    valor_pago /= 2;
  }

  if (combo) {
    valor_pago += PRECO_COMBO;
  }


  sessao->bilhetes[sessao->indice_bilhete].sala = sala;
  sessao->bilhetes[sessao->indice_bilhete].lugar_coluna = lugar_coluna;
  sessao->bilhetes[sessao->indice_bilhete].lugar_linha = lugar_linha;
  sessao->bilhetes[sessao->indice_bilhete].meia_entrada = meia_entrada;
  sessao->bilhetes[sessao->indice_bilhete].combo = combo;
  sessao->bilhetes[sessao->indice_bilhete].valor_pago = valor_pago;
  sessao->bilhetes[sessao->indice_bilhete].id = sessao->indice_bilhete + 1;

  sessao->indice_bilhete++;
  return &sessao->bilhetes[sessao->indice_bilhete - 1];
}

void sala_exibir_lugares(struct Sala *sala)
{
    int k, i;
    char coluna [5]= {'A', 'B','C', 'D', 'E'};

    printf("  1 2 3 4 5\n");
	  printf("  - - - - -\n");

  	for(i = 0; i < SALA_LINHAS; i++){

      printf("%c|", coluna[i]);

      for(k = 0; k < SALA_COLUNAS; k++){

        if(sala->lugares[i][k]){
          printf("X ");
        }

        else{
          printf("O ");
        }
      }

      printf("\n");
    }

}

bool sala_reservar_lugar(struct Sala *sala, char linha, unsigned int coluna)
{
  if (sala->lugares[linha - 'A'][coluna - 1])
  {
    return false;
  }

  sala->lugares[linha - 'A'][coluna - 1] = true;
  return true;
}

void sala_liberar_lugar(struct Sala *sala, char linha, unsigned int coluna)
{
  sala->lugares[linha - 'A'][coluna - 1] = false;
}

void bilhete_imprimir(struct Bilhete *bilhete)
{
  char *nome[] = {"Nao","Sim"};
  printf("Bilhete N⁰: %d\n",bilhete->id);
  printf("Filme: %s\n",bilhete->sala->filme);
  printf("Valor pago: R$ %.2f\n", bilhete->valor_pago / 100.0 );
  printf("Lugar: %c%d \n",bilhete->lugar_linha, bilhete->lugar_coluna);
  printf("Meia-entrada: %s\n", nome[bilhete->meia_entrada]);
  printf("Incluir combo: %s\n",nome[bilhete->combo]);
}

void bilhete_cancelar(struct Bilhete *bilhete)
{
  bilhete->cancelado = true;
}

int lscanf(char *text, const char *format, ...)
{
  static char buff[MAX_INPUT];
  int ret;
  va_list args;

  if(text)
  {
    fputs(text, stdout);
  }

  fgets(buff, sizeof buff, stdin);

  va_start(args, format);
  ret = vsscanf(buff, format, args);
  va_end(args);

  return ret;
}

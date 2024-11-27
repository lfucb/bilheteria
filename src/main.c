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
    
    sessao->bilhetes->valor_pago = sala->preco_bilhete;
     if (meia_entrada) {
        sessao->bilhetes->valor_pago /= 2; 
    }

    if (combo) {
        sessao->bilhetes->valor_pago += PRECO_COMBO; 
    }

    
    sessao->bilhetes[sessao->indice_bilhete].lugar_coluna = lugar_coluna;
    sessao->bilhetes[sessao->indice_bilhete].lugar_linha = lugar_linha;
    sessao->bilhetes[sessao->indice_bilhete].meia_entrada = meia_entrada;
    sessao->bilhetes[sessao->indice_bilhete].combo = combo;
    sessao->bilhetes[sessao->indice_bilhete].id = sessao->indice_bilhete + 1;
    

    return &sessao->bilhetes[sessao->indice_bilhete];
}

void sala_exibir_lugares(struct Sala *sala)
{
    int k = 0, i = 0;
    char coluna [5]= {'A', 'B','C', 'D', 'E'};
  
    printf("  1 2 3 4 5\n");
	  printf("+ - - - - -\n");
  
  	for(int i; i < SALA_LINHAS; i++){
  		
  	printf("%c|", coluna[i]);
  		
  	for(int k; k < SALA_COLUNAS; k++){

  	  if(sala->lugares[i][k]){
  	    printf("X ");
		  }

	    else{
		    printf("D ");
		  }
  	}
  			
  	printf("\n");
    }
      
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
  // @todo: Implementar função para cancelar um bilhete previamente comprado.
}

#include "header.h"

// Vetor de inteiro para char
void intToChar(char *c,int *cidades,int nCidades){
	int anterior = 0;
	int casaMilhar=0;
	int casaCentena=0;
	int casaDezena=0;
	int casaUnitaria=0;
	int i,indice=0;
	int n[numeroMaximoCidades];
	for(i=0;i<nCidades;i++){
		n[i] = cidades[i];
	}
	for(i=0;i<tamanhoTexto;i++){
		c[i] = '\0';
	}
	for(i=0;i<nCidades;i++){
	  anterior = n[i];
	  while(n[i]>999){
	    n[i] = n[i]-1000;
		casaMilhar++;
	  }
	  while(n[i]>99){
	    n[i] = n[i]-100;
		casaCentena++;
	  }
	  while(n[i]>9){
	    n[i] = n[i]-10;
		casaDezena++;
	  }
	  while(n[i]>0){
		n[i] = n[i]-1;
		casaUnitaria++;
	  }
	  if(anterior > 999){
			c[indice] = casaMilhar + '0';
			indice++;
	  }
	  if(anterior > 99){
			c[indice] = casaCentena + '0';
			indice++;
	  }
	  if(anterior > 9){
			c[indice] = casaDezena + '0';
			indice++;
	  }
	  if(anterior >-1){
			c[indice] = casaUnitaria + '0';
			indice++;
	  }
	  c[indice] = '-';
	  indice++;
	  c[indice] = '>';
	  indice++;
		c[indice] = '0';

		casaMilhar = 0;
		casaCentena = 0;
		casaDezena = 0;
		casaUnitaria = 0;
	}
}

// Imprime os dados da execução
void impimirEstatistica(estatistica *dado,int nGeracoes,caminhos *rota,int nCaminhos,int nCidades){
  int indiceDado,j;
  for(indiceDado=0;indiceDado<nGeracoes;indiceDado++){
    printf("\n");
    printf("****** Geração número %i \n",indiceDado);
    printf("Número de cidades a serem visistas = %i \n",dado[indiceDado].nCidades);
    printf("Número de caminhos (população inicial) = %i\n",dado[indiceDado].nCaminhos);
    printf("Número de gerações (cruzamentos) = %i \n",dado[indiceDado].nCruzamentos);
    printf("Dessas gerações:\n");
    printf("%i foram aceitas\n",dado[indiceDado].caminhosFilhosAceitos);
    printf("%i foram rejeitadas\n",dado[indiceDado].caminhosRejeitados);
    printf("%i mutações que deram certo\n",dado[indiceDado].nMutacaoCertas);
    printf("%i mutações que deram errado\n",dado[indiceDado].nMutacaoErrada);
    printf("%i foram melhor que um dos pais (contando com as mutações certas)\n",dado[indiceDado].caminhosSuperiores);
    printf("O caminho (filho) com menor distância foi = %i \n",dado[indiceDado].menorDistancia);
    printf("O percurso foi = ");
    for(j=0;j<nCidades;j++){
      if(j<nCidades-1){
        printf("%i->",dado[indiceDado].percurso[j]);
      } else {
        printf("%i",dado[indiceDado].percurso[j]);
      }
    }
    printf("->0\n");
    printf("A distância percorrida foi de = %f \n",dado[indiceDado].distancia);
    printf("\n");
  }
}

// Imprime os dados da execução
void impimirEstatisticaSimplificado(estatistica *dado,int nGeracoes,caminhos *rota,int nCaminhos,int nCidades){
  int indiceDado,j;
  for(indiceDado=0;indiceDado<nGeracoes;indiceDado++){
    printf("****** Geração número %i \n",indiceDado);
    printf("O percurso foi = ");
    for(j=0;j<nCidades;j++){
      if(j<nCidades-1){
        printf("%i->",dado[indiceDado].percurso[j]);
      } else {
        printf("%i",dado[indiceDado].percurso[j]);
      }
    }
    printf("->0\n");
    printf("A distância percorrida foi de = %f \n",dado[indiceDado].distancia);
    printf("\n");
  }
}

// Imprimir coordenadas
void imprimirCoordenadas(coordenadas *cidades,int nCidades){
  int i;
  for(i=0;i<nCidades;i++){
    printf("Cidade %i, x=%i, y=%i \n",i,cidades[i].x,cidades[i].y);
  }
}

// Imprime todos os caminhos
void imprimirCaminhos(caminhos *rota,int nCaminhos,int nCidades){
  int i,j;
  for(i=0;i<nCaminhos;i++){
    printf("Caminho %i\n",i);
    for(j=0;j<nCidades;j++){
      if(j<nCidades-1){
        printf("%i->",rota[i].percurso[j]);
      } else {
        printf("%i",rota[i].percurso[j]);
      }
    }
    printf("->0");
    printf("\nDistância %f \n",rota[i].distancia);
  }
}

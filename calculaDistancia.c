#include "header.h"

// Cálcula a raiz quadrada
float raiz(float n) {
  double erro = 0.00001;
  double s = n;
  while ((s - n/s) > erro)
    s = (s + n/s)/2;
  return s;
}

// Cálcula a distância entre as coordenadas
float auxCalculaDistancia(int x0,int y0,int x1,int y1){
	float resultado = (((x1-x0)*(x1-x0)) + ((y1-y0)*(y1-y0)));
	resultado = raiz(resultado);
	return resultado;
}

// Calcula a distância dos caminhos
void calculaDistanciaRota(caminhos *rota,coordenadas *cidades, int indiceRota,int nCidades){
  int cidadeAtual = 0;
  float distancia = 0.0;
  int x0,y0,x1,y1; // Usando auxiliares para maior legibilidade
  int cidadeA,cidadeB;
  for(cidadeAtual;cidadeAtual<nCidades;cidadeAtual++){

    // Calculando a distancia da última até a primeira
    if(cidadeAtual+1 == nCidades){
      // Distância da cidadeA até a cidadeB
      cidadeA = rota[indiceRota].percurso[cidadeAtual];
      cidadeB = 0;
      // Buscando as coordenadas de cada cidade
      x0 = cidades[cidadeA].x;
      y0 = cidades[cidadeA].y;
      x1 = cidades[cidadeB].x;
      y1 = cidades[cidadeB].y;
      // Calculando a distância
      distancia = auxCalculaDistancia(x0,y0,x1,y1);
      // Colocando a distância entre A e B na contagem geral
      rota[indiceRota].distancia += distancia;
      break;
    }
    // Distância da cidadeA até a cidadeB
    cidadeA = rota[indiceRota].percurso[cidadeAtual];
    cidadeB = rota[indiceRota].percurso[cidadeAtual+1];
    // Buscando as coordenadas de cada cidade
    x0 = cidades[cidadeA].x;
    y0 = cidades[cidadeA].y;
    x1 = cidades[cidadeB].x;
    y1 = cidades[cidadeB].y;
    // Calculando a distância
    distancia = auxCalculaDistancia(x0,y0,x1,y1);
    // Colocando a distância entre A e B na contagem geral
    rota[indiceRota].distancia += distancia;
  }
}

// Calcula todas as distancias de todos os caminhos
void calculaTodasDistancias(caminhos *rota,coordenadas *cidades,int nCaminhos,int nCidades){
  int i;
  for(i=0;i<nCaminhos;i++)
    calculaDistanciaRota(rota,cidades,i,nCidades);
}

#include "header.h"

// Cálcula a raiz quadrada
float raiz(float n);

// Cálcula a distância entre as coordenadas
float auxCalculaDistancia(int x0,int y0,int x1,int y1);

// Calcula a distância dos caminhos
void calculaDistanciaRota(caminhos *rota,coordenadas *cidades, int indiceRota,int nCidades);

// Calcula todas as distancias de todos os caminhos
void calculaTodasDistancias(caminhos *rota,coordenadas *cidades,int nCaminhos,int nCidades);

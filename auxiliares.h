#include "header.h"

// Vetor de inteiro para char
void intToChar(char *c,int *n,int nCidades);

// Imprime os dados da execução
void impimirEstatistica(estatistica *dado,int nGeracoes,caminhos *rota,int nCaminhos,int nCidades);

// Imprime os dados da execução de forma simplificada
void impimirEstatisticaSimplificado(estatistica *dado,int nGeracoes,caminhos *rota,int nCaminhos,int nCidades);

// Imprimir coordenadas
void imprimirCoordenadas(coordenadas *cidades,int nCidades);

// Imprime todos os caminhos
void imprimirCaminhos(caminhos *rota,int nCaminhos,int nCidades);

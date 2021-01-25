#ifndef __HEADER
#define __HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <gtk/gtk.h>
#include <pthread.h>
#include <cairo.h>

#define tamanhoTexto 256 // Tamanho usado no texto da interface
#define numeroMaximoCidades 1000 // Número máximo de cidades
#define numeroMaximoGeracoes 1000 // Número máximo gerações
#define numeroMaximoCruzamentos 1000 // Número máximo de cruzamentos

// Struct cidades
typedef struct coordenadas{
  int x;
  int y;
}coordenadas;

// Struct caminhos (população)
typedef struct caminhos{
  int percurso[numeroMaximoCidades];
  float distancia;
}caminhos;

// Struct estatística (Informa como foi a execução)
typedef struct estatistica{
  int nCidades;
  int nCaminhos;
  int nCruzamentos;
  int nMutacaoCertas;
  int nMutacaoErrada;
  int caminhosFilhosAceitos;
  int caminhosRejeitados;
  int caminhosSuperiores;
  int menorDistancia;
  float distancia;
  int percurso[numeroMaximoCidades];
}estatistica;

/**
  AUXILIARES
**/

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


/**
  CÁLCULA A DISTÂNCIA
**/

// Cálcula a raiz quadrada
float raiz(float n);

// Cálcula a distância entre as coordenadas
float auxCalculaDistancia(int x0,int y0,int x1,int y1);

// Calcula a distância dos caminhos
void calculaDistanciaRota(caminhos *rota,coordenadas *cidades, int indiceRota,int nCidades);

// Calcula todas as distancias de todos os caminhos
void calculaTodasDistancias(caminhos *rota,coordenadas *cidades,int nCaminhos,int nCidades);

/**
  ALGORITMO GENÉTICO 
**/

// Atualiza o carregamento na interface
void carregamento(float carrega);

// Inicializa as estatisticas
void inicializarEstatistica(estatistica *dado, int tamanho);

// Inicializa as coordenadas
void inicializarCoordenadas(coordenadas *cidades,int nCidades);

// Inicializa os caminhos (população)
void inicializarCaminhos(caminhos *rota,int nCaminhos,int nCidades);

// Verifica se a cidade já existe dentro do caminhos
int existeCidade(caminhos *rota,int indiceRota,int tamanho,int cidade);

// Gera um caminho aleatório
void geraCaminho(caminhos *rota,int indiceRota,int nCidades);

// Gera uma população de caminhos
void geraPopCaminhos(caminhos *rota,int nCaminhos,int nCidades);

// Retorna o indice do melhor caminho
int melhorCaminho(caminhos *rota,int nCaminhos);

// Verifica se existe cidades repetidas no vetor
int existeCidadesRepetida(int *filho,int nCidades);

// Faz uma mutação aleatório entre duas cidades
int mutacaoAleatoria(caminhos *filho,int nCidades,int i,int cidadeAanterior);

// Faz o cruzamento entre dois caminhos
void cruzamentoCaminhos(caminhos *rota,coordenadas *cidades,int nCidades, int indicePaiMelhor,
                        int indicePaiAleatorio,estatistica *dado,int indiceDado,int nMutacao);

// Realiza todos os cruzamento, de acordo com número de gerações
void cruzamentoGeracoes(caminhos *rota,coordenadas *cidades,int nCidades,int nCaminhos,int nCruzamentos,
                        estatistica *dado,int indiceDado,int nMutacao,int usarMelhorPai);

// Faz a chamada de todas as funções necessárias
int calculaGeracoes(caminhos *rota,coordenadas *cidades,int nCidades,int nCaminhos,int nCruzamentos,
                     int nGeracoes,int nMutacao,estatistica *dado,int usarMelhorPai, int usarCriterioParada);

#endif //__HEADER

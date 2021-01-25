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

#endif //__HEADER

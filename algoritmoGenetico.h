#include "header.h"

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

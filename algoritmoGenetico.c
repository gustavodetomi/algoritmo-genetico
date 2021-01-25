#include "algoritmoGenetico.h"
#include "calculaDistancia.h"

// Inicializa as estatisticas
void inicializarEstatistica(estatistica *dado, int tamanho){
  int i,j;
  for(i=0;i<tamanho;i++){
    dado[i].nCidades = 0;
    dado[i].nCaminhos = 0;
    dado[i].nCruzamentos = 0;
    dado[i].nMutacaoCertas = 0;
    dado[i].nMutacaoErrada = 0;
    dado[i].caminhosFilhosAceitos = 0;
    dado[i].caminhosRejeitados = 0;
    dado[i].caminhosSuperiores = 0;
    dado[i].menorDistancia = 0;
    dado[i].distancia = 0.0;
    for(j=0;j<numeroMaximoCidades;j++){
      dado[i].percurso[j] = 0;
    }
  }
}

// Inicializa as coordenadas
void inicializarCoordenadas(coordenadas *cidades,int nCidades){
  int i;
  for(i=0;i<nCidades;i++){
    cidades[i].x = -1;
    cidades[i].y = -1;
  }
}

// Inicializa os caminhos (população)
void inicializarCaminhos(caminhos *rota,int nCaminhos,int nCidades){
  int i,j;
  for(i=0;i<nCaminhos;i++){
    for(j=0;j<nCidades;j++)
      rota[i].percurso[j] = -1;
    rota[i].distancia = 0;
  }
}

// Verifica se a cidade já existe dentro do caminhos
int existeCidade(caminhos *rota,int indiceRota,int tamanho,int cidade){
  int i;
  for(i=0;i<tamanho;i++){
    if(rota[indiceRota].percurso[i]==cidade)
      // Quer dizer que a cidade já existe na rota
      return 1;
  }
  // Quer dizer que a cidade não existe na rota
  return 0;
}

// Gera um caminho aleatório
void geraCaminho(caminhos *rota,int indiceRota,int nCidades){
  // Aumentando a aleatóriedade
  srand(time(NULL));
  if(indiceRota >= rand() % nCidades){
    srand(time(NULL)*indiceRota);
  } else {
    srand(time(NULL)+indiceRota);
  }
  int i,cidadeAleatoria;
  for(i=0;i<nCidades;i++){
    if(i!=0){
      cidadeAleatoria = rand() % nCidades;
      while(existeCidade(rota,indiceRota,i,cidadeAleatoria))
        cidadeAleatoria = rand() % nCidades;
      rota[indiceRota].percurso[i] = cidadeAleatoria;
    }else{
      rota[indiceRota].percurso[i] = 0;
    }
  }
}

// Gera uma população de caminhos
void geraPopCaminhos(caminhos *rota,int nCaminhos,int nCidades){
  int i;
  for(i=0;i<nCaminhos;i++){
    geraCaminho(rota,i,nCidades);
  }
}

// Retorna o melhor caminhos
int melhorCaminho(caminhos *rota,int nCaminhos){
  int i;
  int indiceMenorCaminho = 0;
  float menorCaminho = rota[0].distancia;
  for(i=0;i<nCaminhos;i++){
      if(rota[i].distancia < menorCaminho){
        menorCaminho = rota[i].distancia;
        indiceMenorCaminho = i;
      }
  }
  return indiceMenorCaminho;
}

// Verifica se existe cidades repetidas no vetor
int existeCidadesRepetida(int *filho,int nCidades){
  int i,j;
  int aux[nCidades];
  for(i=0;i<nCidades;i++)
    aux[i] = 0;
  for(i=0;i<nCidades;i++){
    for(j=0;j<nCidades;j++){
      if(filho[i] == filho [j] && i==j)
        aux[filho[i]]++;
    }
  }
  for(i=0;i<nCidades;i++){
    if(filho[i] == -1){
      printf("Erro ao tentar salvar o fiho!\n");
      exit(0);
    }
    if(filho[i] > nCidades-1){
      printf("Erro cidade invalida!\n");
      exit(0);
    }
    if(aux[i] > 1){
      // Existe alguma cidade repetida
      return 1;
    }
  }
  return 0;
}

// Faz uma mutação aleatório entre duas cidades
int mutacaoAleatoria(caminhos *filho,int nCidades,int i,int cidadeAanterior){
  srand(time(NULL)*i+cidadeAanterior);
  int aux = -1;
  int cidadeA = rand() % nCidades;
  int cidadeB = rand() % nCidades;
  while(cidadeA == 0 || cidadeB == 0 || cidadeA == cidadeB ||
        cidadeA == cidadeAanterior || cidadeB == cidadeAanterior){
    cidadeA = rand() % nCidades;
    cidadeB = rand() % nCidades;
  }
  // Realiza atroca
  aux = filho[0].percurso[cidadeA];
  filho[0].percurso[cidadeA] = filho[0].percurso[cidadeB];
  filho[0].percurso[cidadeB] = aux;
  return filho[0].percurso[cidadeA];
}

// O filho entra no lugar do pai
void trocaPaiFilho(caminhos *rota,int nCidades, int indicePaiAleatorio, caminhos *filho){
  int i;
  for(i=0;i<nCidades;i++){
    rota[indicePaiAleatorio].percurso[i] = filho[0].percurso[i];
  }
  rota[indicePaiAleatorio].distancia = filho[0].distancia;
}

// Tenta salvar um filho com o caminho trocado
void salvaFilho(caminhos *rota,int nCidades, caminhos *filho){
  int i,j;
  int aux[nCidades];
  for(i=0;i<nCidades;i++)
    aux[i] = -1;
  // Retira as ciadades repetidas
  for(i=0;i<nCidades;i++){
    for(j=0;j<nCidades;j++){
      if(filho[0].percurso[j] == filho[0].percurso[i] && i != j)
        filho[0].percurso[i] = -1;
      if(filho[0].percurso[j] == filho[0].percurso[i] && i==j)
        aux[filho[0].percurso[i]]++;
    }
  }
  // Coloca as cidades que estão faltando
  for(i=0;i<nCidades;i++){
    if(aux[i] == -1){
      for(j=0;j<nCidades;j++){
        if(filho[0].percurso[j] == -1){
          filho[0].percurso[j] = i;
          aux[i] = 0;
          break;
        }
      }
    }
  }
}

// Faz o cruzamento entre dois caminhos
void cruzamentoCaminhos(caminhos *rota,coordenadas *cidades,int nCidades, int indicePaiMelhor,
                        int indicePaiAleatorio,estatistica *dado,int indiceDado,int nMutacao){
  int i;
  caminhos filho[1];
  inicializarCaminhos(filho,1,nCidades);
  srand(time(NULL)*indicePaiAleatorio);
	int ponto =  rand() % nCidades;

  // Realiza o cruzamento
  if(!ponto)
    ponto = 1;
  for(i=0;i<ponto;i++)
    filho[0].percurso[i] = rota[indicePaiMelhor].percurso[i];
  for(i=ponto;i<nCidades;i++)
    filho[0].percurso[i] = rota[indicePaiAleatorio].percurso[i];

  // Tetando salvar o filho
  if(existeCidadesRepetida(filho[0].percurso,nCidades))
    salvaFilho(rota,nCidades,filho);

  // Verifica se o filho salvo é válido
  if(existeCidadesRepetida(filho[0].percurso,nCidades)){
    dado[indiceDado].caminhosRejeitados++;
  } else {
    dado[indiceDado].caminhosFilhosAceitos++;
    calculaDistanciaRota(filho,cidades,0,nCidades);

    // Verifica se o filho superou o pai
    if(filho[0].distancia < rota[indicePaiAleatorio].distancia){
      trocaPaiFilho(rota,nCidades,indicePaiAleatorio,filho);
      dado[indiceDado].caminhosSuperiores++;
      return;
    } else {
      // Sorteando o número de mutações
      srand(time(NULL)*indicePaiAleatorio);
      nMutacao = rand() % nMutacao;
      // Através da mutação tenta melhorar o filho para superar o pai
      for(i=0;i<nMutacao;i++){
        if(filho[0].distancia < rota[indicePaiAleatorio].distancia && !existeCidadesRepetida(filho[0].percurso,nCidades)){
          trocaPaiFilho(rota,nCidades,indicePaiAleatorio,filho);
          dado[indiceDado].caminhosSuperiores++;
          dado[indiceDado].nMutacaoCertas++;
          return;
        }
        filho[0].distancia = 0;
        int cidadeAanterior = mutacaoAleatoria(filho,nCidades,i,cidadeAanterior);
        calculaDistanciaRota(filho,cidades,0,nCidades);
        dado[0].nMutacaoErrada++;
      }
    }
  }
}

// Realiza todos os cruzamento, de acordo com número de gerações
void cruzamentoGeracoes(caminhos *rota,coordenadas *cidades,int nCidades,int nCaminhos,int nCruzamentos,
                        estatistica *dado,int indiceDado,int nMutacao,int usarMelhorPai){

  int i,indicePaiMelhor,indicePaiAleatorio,aux;
  srand(time(NULL)*rota[rand() % nCidades].percurso[rand() % nCidades]);
  dado[indiceDado].nCruzamentos = nCruzamentos;
  dado[indiceDado].nCaminhos = nCaminhos;
  dado[indiceDado].nCidades = nCidades;
  int auxNCruzamentos = nCruzamentos;
  // Sorteando o número de nCruzamentos
  nCruzamentos = rand() % auxNCruzamentos;
  while(nCruzamentos < auxNCruzamentos* 0.6)
    nCruzamentos = rand() % auxNCruzamentos;
  for(i=0;i<nCruzamentos;i++){
    srand(time(NULL)*i);
    if(usarMelhorPai){
      indicePaiMelhor = melhorCaminho(rota,nCaminhos);
      indicePaiAleatorio = rand() % nCaminhos;
    } else {
      indicePaiMelhor = rand() % nCaminhos;
      indicePaiAleatorio = rand() % nCaminhos;
      if(rota[indicePaiAleatorio].distancia < rota[indicePaiMelhor].distancia){
        aux = indicePaiAleatorio;
        indicePaiAleatorio = indicePaiMelhor;
        indicePaiMelhor = aux;
      }
    }
    while(indicePaiMelhor == indicePaiAleatorio)
      indicePaiAleatorio = rand() % nCaminhos;
    cruzamentoCaminhos(rota,cidades,nCidades,indicePaiMelhor,indicePaiAleatorio,dado,indiceDado,nMutacao);
  }
  dado[indiceDado].menorDistancia  = melhorCaminho(rota,nCaminhos);
  dado[indiceDado].distancia = rota[dado[indiceDado].menorDistancia].distancia;
  for(i=0;i<nCidades;i++){
    dado[indiceDado].percurso[i] = rota[dado[indiceDado].menorDistancia].percurso[i];
  }
}

// Faz a chamada de todas as funções necessárias
int calculaGeracoes(caminhos *rota,coordenadas *cidades,int nCidades,int nCaminhos,int nCruzamentos,
                     int nGeracoes,int nMutacao,estatistica *dado,int usarMelhorPai,int usarCriterioParada){
  int i,contador=0;
  float anterior = -1;
  for(i=0;i<nGeracoes;i++){
    cruzamentoGeracoes(rota,cidades,nCidades,nCaminhos,nCruzamentos,dado,i,nMutacao,usarMelhorPai);
    if(dado[i].distancia != anterior){
      anterior = dado[i].distancia;
      contador = 0;
    } else if(usarCriterioParada){
      contador++;
    }
    if(contador > 20 && usarCriterioParada){
      contador = 0;
      return i;
    }
  }
  return nGeracoes;
}

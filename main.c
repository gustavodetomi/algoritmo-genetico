#include "header.h"
#include "auxiliares.h"
#include "calculaDistancia.h"
#include "algoritmoGenetico.h"

// Variáveis globais da interface
GtkWidget *entradaCaminhos;
GtkWidget *entradaCruzamentos;
GtkWidget *entradaMutacao;
GtkWidget *entradaGeracoes;
GtkWidget *janela;
GtkWidget *label_saida;
GtkWidget *label_saida2;
GtkWidget *label_saida3;
GtkWidget *label_saida4;

// Variáveis globais de controle da interface
int nCidades;
int usarMelhorPai = 0;
int usarCriterioParada = 0;
int botaoClicavel = 1;
int leituraArquivo = 1;
int percursoAchado = 0;
int nGeracaoFinal = 0;

// Variáveis globais do algoritmo genético
coordenadas cidades[numeroMaximoCidades];
caminhos rota[numeroMaximoCruzamentos];
estatistica dados[numeroMaximoGeracoes];
int nCaminhos,nCruzamentos,nMutacao,nGeracoes,aux;

// Cria uma janela com uma mensagem de erro
void MensagemErro(char *mensagem){
    // Variáveis de interface local
    GtkWidget *JanelaErro;
    GtkWidget *Label;
    GtkWidget *HBox;

    // Cria uma nova janela para exibir a mensagem de erro
    JanelaErro = gtk_dialog_new_with_buttons ("ERRO!",(gpointer)janela,GTK_DIALOG_MODAL,GTK_STOCK_OK, GTK_RESPONSE_OK,NULL);
    gtk_dialog_set_has_separator (GTK_DIALOG(JanelaErro), FALSE);

    // Label que vai receber a mensagem
    Label = gtk_label_new (mensagem);

    // Cria um horizontal box para adicionar o label
    HBox = gtk_hbox_new (FALSE, 5);
    gtk_container_set_border_width (GTK_CONTAINER (HBox), 10);
    gtk_box_pack_start_defaults (GTK_BOX (HBox), Label);
    gtk_box_pack_start_defaults(GTK_BOX (GTK_DIALOG (JanelaErro)->vbox), HBox);

    // Mostra na tela
    gtk_widget_show_all (JanelaErro);
    gtk_dialog_run (GTK_DIALOG (JanelaErro));
    gtk_widget_destroy (JanelaErro);
}

// Alterna o checkBox de acordo com os cliques
void eventoCliqueCheckBox(GtkWidget *widget, char *data){
    if(usarMelhorPai && data == "check1"){
      usarMelhorPai = 0;
    } else if(data == "check1") {
      usarMelhorPai = 1;
    }
    if(usarCriterioParada && data == "check2"){
      usarCriterioParada = 0 ;
    } else if(data == "check2"){
      usarCriterioParada = 1;
    }
}

// Cria um checkBox
GtkWidget *criaCheckBox (GtkWidget *box, char *szLabel){
    GtkWidget *check;
    // Pega o bt de checagem
    check = gtk_check_button_new_with_label (szLabel);
    // Coloca dentro do box
    gtk_box_pack_start (GTK_BOX (box), check, FALSE, FALSE, 5);
    // Mostra na tela
    gtk_widget_show (check);
    return (check);
}

// Chama o algoritmo Genético
void *chamaAlgoritmo() {
  char texto[tamanhoTexto],texto2[tamanhoTexto],texto3[tamanhoTexto],texto4[tamanhoTexto];

  // Obtém os valores digitados
  nCaminhos = atol(gtk_entry_get_text(GTK_ENTRY(entradaCaminhos)));
  nCruzamentos = atol(gtk_entry_get_text(GTK_ENTRY(entradaCruzamentos)));
  nMutacao = atol(gtk_entry_get_text(GTK_ENTRY(entradaMutacao)));
  nGeracoes = atol(gtk_entry_get_text(GTK_ENTRY(entradaGeracoes)));

  // Verifica se o que foi digitado é válido
  if(!nCaminhos || !nCruzamentos || !nGeracoes || nGeracoes > 1000
                || nCaminhos > 1000 || nCruzamentos > 1000 || nMutacao > 1000){
      gtk_label_set_text(GTK_LABEL(label_saida), "DIGITE VALORES VÁLIDOS!");
    if(nGeracoes > 1000)
      gtk_label_set_text(GTK_LABEL(label_saida), "NÚMERO DE GERAÇÕES MUITO ALTO!");
    if(nCaminhos > 1000)
      gtk_label_set_text(GTK_LABEL(label_saida), "NÚMERO DE CAMINHOS (POPULAÇÃO INICIAL) MUITO ALTO!");
    if(nCruzamentos > 1000)
      gtk_label_set_text(GTK_LABEL(label_saida), "NÚMERO DE CRUZAMENTOS MUITO ALTO!");
    if(nMutacao > 1000)
      gtk_label_set_text(GTK_LABEL(label_saida), "NÚMERO DE MUTAÇÕES MUITO ALTO!");
  } else {

    // Inicializa marcação de tempo
    clock_t Ticks[2];
    Ticks[0] = clock();

    // Incializa as variáveis
    inicializarEstatistica(dados,nGeracoes);
    inicializarCaminhos(rota,nCaminhos,nCidades);
    geraPopCaminhos(rota,nCaminhos,nCidades);
    calculaTodasDistancias(rota,cidades,nCaminhos,nCidades);

    // Realiza o cálculo do percurso
    aux = nGeracoes;
    nGeracaoFinal = calculaGeracoes(rota,cidades,nCidades,nCaminhos,nCruzamentos,
                               nGeracoes,nMutacao,dados,usarMelhorPai,usarCriterioParada);
    // Finaliza a marcação de tempo
    Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

    // Converte o percurso e o adiciona na tela
    intToChar(texto4,dados[nGeracaoFinal-1].percurso,nCidades);
    if(aux >= nGeracaoFinal)
      gtk_label_set_text(GTK_LABEL(label_saida), "Algoritmo parado, pois o mesmo não apresentou evolução!");

    // Coloca as informações principais na tela
    gtk_label_set_text(GTK_LABEL(label_saida),"Concluído!");
    sprintf(texto2, "Número de gerações geradas = %i",nGeracaoFinal);
    gtk_label_set_text(GTK_LABEL(label_saida2), texto2);
    sprintf(texto3, "Custo menor caminho = %f, percurso:",dados[nGeracaoFinal-1].distancia);
    gtk_label_set_text(GTK_LABEL(label_saida3), texto3);
    gtk_label_set_text(GTK_LABEL(label_saida4), texto4);

    // Imprime o resultado no log do sistema (Quando executado pelo terminal)
    impimirEstatistica(dados,nGeracaoFinal,rota,nCaminhos,nCidades);
    impimirEstatisticaSimplificado(dados,nGeracaoFinal,rota,nCaminhos,nCidades);
    printf("População = %i; Cruzamentos = %i; Mutações = %i; Gerações = %i; Custo Caminho = %f; Tempo = %g\n",nCaminhos,nCruzamentos,nMutacao,nGeracoes,dados[nGeracaoFinal-1].distancia,Tempo);

  }

  // Tornando a função chamável novamente (Usado para não ocorrer duas execuções simultaneas)
  botaoClicavel = 1;

  // Torna o percurso desenhável
  percursoAchado = 1;

  // Finaliza thread
  pthread_exit(NULL);
}

// Chama uma thread para realizar os calculos
void *chamaThread(){
  // Seta os labels
  gtk_label_set_text(GTK_LABEL(label_saida),"Calculando...");
  gtk_label_set_text(GTK_LABEL(label_saida2), "   ");
  gtk_label_set_text(GTK_LABEL(label_saida3), "   ");
  gtk_label_set_text(GTK_LABEL(label_saida4), "   ");
  // Verifica se é possível chamar a função e se a leitura do arquivo deu certo
  if(botaoClicavel && leituraArquivo){
   botaoClicavel = 0;
   pthread_t thread;
   // Chama uma thread para realizar o cálculo
   pthread_create(&thread, NULL, chamaAlgoritmo, (void *)NULL);
 } else if(!botaoClicavel){
   MensagemErro("Aguarde o fim da execução!");
 } else if(!leituraArquivo){
   MensagemErro("Problema na leitura do arquivo");
 }
}

// Procura a a maior coordena passada (Usado no controle das dimensões da tela de desenho)
int maiorCoordenada(){
  int i;
  int maior = -99999999;
  for(i=0;i<nCidades;i++){
    if(cidades[i].x > maior)
      maior = cidades[i].x;
    if(cidades[i].y > maior)
      maior = cidades[i].y;
  }
  return maior;
}

// Realiza o desenho do mapa de cidades na tela
gboolean desenha(GtkWidget *w, GdkEventExpose *e, gpointer p) {
    // Variáveis da biblioteca cairo usada para realizar o desenho
    cairo_t *texto,*cr;

    // Variáveis auxiliares
    char auxTexto[tamanhoTexto];
    int maior = maiorCoordenada();

    // Define a proporção de acordo com a maior coordena encontrada
    float tamanhoDesenhoX =  640 / maior;
    float tamanhoDesenhoY =  480 / maior;
    int i;

    // Trançando a linha que interliga as 'cidades' pelo percurso
    if(percursoAchado){
      for(i=0;i<nCidades-1;i++){
        cr = gdk_cairo_create(gtk_widget_get_window(w));
        cairo_set_source_rgb(cr,199,21,133);
        cairo_set_line_width(cr, 2);
        cairo_move_to(cr, cidades[dados[nGeracaoFinal-1].percurso[i]].x*tamanhoDesenhoX+30,
                          cidades[dados[nGeracaoFinal-1].percurso[i]].y*tamanhoDesenhoY+30);
        cairo_line_to(cr, cidades[dados[nGeracaoFinal-1].percurso[i+1]].x*tamanhoDesenhoX+30,
                          cidades[dados[nGeracaoFinal-1].percurso[i+1]].y*tamanhoDesenhoY+30);
        cairo_stroke(cr);
      }
      cr = gdk_cairo_create(gtk_widget_get_window(w));
      cairo_set_source_rgb(cr, 199,21,133);
      cairo_set_line_width(cr, 2);
      cairo_move_to(cr, cidades[dados[nGeracaoFinal-1].percurso[i]].x*tamanhoDesenhoX+30,
                        cidades[dados[nGeracaoFinal-1].percurso[i]].y*tamanhoDesenhoY+30);
      cairo_line_to(cr, cidades[0].x*tamanhoDesenhoX+30,
                        cidades[0].y*tamanhoDesenhoY+30);
      cairo_stroke(cr);
    }
    // Desenha a Coluna do eixo Y
    for(i=maior;i>=0;i--){
      texto = gdk_cairo_create(gtk_widget_get_window(w));
      cairo_set_source_rgb(texto, 50.1, 50.1, 50.1);
      cairo_select_font_face(texto, "Times",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
      cairo_set_font_size(texto, 14);
      cairo_move_to(texto, 10, i*tamanhoDesenhoY+30);
      sprintf(auxTexto, "%i",i);
      cairo_show_text(texto, auxTexto);
    }
    // Desenha a Coluna do eixo X
    for(i=maior;i>=0;i--){
      texto = gdk_cairo_create(gtk_widget_get_window(w));
      cairo_set_source_rgb(texto, 50.1, 50.1, 50.1);
      cairo_select_font_face(texto, "Times",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
      cairo_set_font_size(texto, 14);
      cairo_move_to(texto, i*tamanhoDesenhoX+30, 10);
      sprintf(auxTexto, "%i",i);
      cairo_show_text(texto, auxTexto);
    }
    // Insere as 'cidades' no mapa
    for(i=0;i<nCidades;i++){
      texto = gdk_cairo_create(gtk_widget_get_window(w));
      cairo_set_source_rgb(texto, 0.1, 0.1, 0.1);
      cairo_select_font_face(texto, "Times",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
      cairo_set_font_size(texto, 14);
      cairo_move_to(texto, cidades[i].x*tamanhoDesenhoX+30, cidades[i].y*tamanhoDesenhoY+30);
      sprintf(auxTexto, ".%i",i);
      cairo_show_text(texto, auxTexto);
    }
    return FALSE;
}

// Cria a janela de desenho e chama função auxiliar de desenho
void chamaDesenho(){
  int maior = maiorCoordenada();
  // Verifica se existe uma coordenada muito alta e cria uma tela do tipo desenho
  if(maior <= 50){
    // Variáveis locais da tela de desenho
    GtkWidget *desenho, *w;

    // Propriedades da tela
    w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(w), "Visualizar mapa de cidades");
    gtk_window_set_resizable(GTK_WINDOW (w),FALSE);
    gtk_widget_set_size_request(w, 700, 520);

    // Chmanado o Desenho do mapa de cidades
    desenho = gtk_drawing_area_new();
    g_signal_connect(desenho, "expose_event", G_CALLBACK(desenha), NULL);
    g_signal_connect(w, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    // Mostra na tela
    gtk_container_add(GTK_CONTAINER(w), desenho);
    gtk_widget_show(desenho);
    gtk_widget_show(w);
  } else {
      gtk_label_set_text(GTK_LABEL(label_saida), "COORDENADA MUITO ALTO PARA DESENHAR O MAPA!");
  }
}

int main(int argc, char **argv){

  // Variáveis locais de interface
  GtkWidget *conteudo,*nCaminhos,*nCruzamentos,*nMutacao,*nGeracoes,*check,*botao,*botao2,*label_Arquivo;
  GdkGeometry windowProperties;
  GList *cbitems = NULL;

  // Variáveis auxiliares
  int i,x,y;

  gtk_init(&argc, &argv);

  // Propriedades da janela
  janela=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER (janela), 20);
  windowProperties.min_width = 500;
  windowProperties.min_height = 600;
  gtk_window_set_geometry_hints(GTK_WINDOW(janela), NULL, &windowProperties, GDK_HINT_MIN_SIZE);
  gtk_window_set_title(GTK_WINDOW (janela), "Algoritmo Genético - Gustavo Detomi");
  gtk_window_set_resizable(GTK_WINDOW (janela),FALSE);
  gtk_window_set_default_icon_from_file("ico.png", NULL);

  // Vertical Box usado para salvar as informações grafícas na tela
  conteudo=gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(janela), conteudo);

  // Adiciona o label de aviso sobre a leitura do arquivo na tela
  label_Arquivo=gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(conteudo), label_Arquivo, FALSE, FALSE, 5);

  // Lendo as cidades através do arquivo
	FILE* entrada = fopen("instancia.txt","r");

  if(entrada == NULL){
    gtk_label_set_text(GTK_LABEL(label_Arquivo), "Problema na leitura do arquivo!");
    leituraArquivo = 0;
    chamaThread();
    exit(0);
  } else {
    gtk_label_set_text(GTK_LABEL(label_Arquivo), "Leitura do arquivo realizada com sucesso!");
  }

  // Número de cidades a serem lidas
	fscanf(entrada,"%i",&nCidades);
	for(i=0;i<nCidades;i++){
		fscanf(entrada,"%i %i",&x,&y);
    cidades[i].x = x;
    cidades[i].y = y;
  }

  // Cria os checkBox
  check = criaCheckBox (conteudo, "Usar sempre o melhor pai para o cruzamento");
  gtk_signal_connect (GTK_OBJECT (check), "clicked",GTK_SIGNAL_FUNC (eventoCliqueCheckBox), "check1");
  check = criaCheckBox (conteudo, "Usar critério de parada (Termina o algoritmo quando não há evolução)");
  gtk_signal_connect (GTK_OBJECT (check), "clicked",GTK_SIGNAL_FUNC (eventoCliqueCheckBox), "check2");

  // Criando os labels e os textBox de entrada de informações
  nCaminhos=gtk_label_new("Digite o número de caminhos (população inicial):");
  gtk_box_pack_start(GTK_BOX(conteudo), nCaminhos, FALSE, FALSE, 5);
  entradaCaminhos=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(conteudo), entradaCaminhos, FALSE, FALSE, 0);

  nCruzamentos=gtk_label_new("Digite o número máximo de cruzamentos (irá ocorrer em cada geração):");
  gtk_box_pack_start(GTK_BOX(conteudo), nCruzamentos, FALSE, FALSE, 5);
  entradaCruzamentos=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(conteudo), entradaCruzamentos, FALSE, FALSE, 0);

  nMutacao=gtk_label_new("Digite o número máximo de tentativas de mutações para o filho superar o pai:");
  gtk_box_pack_start(GTK_BOX(conteudo), nMutacao, FALSE, FALSE, 5);
  entradaMutacao=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(conteudo), entradaMutacao, FALSE, FALSE, 0);

  nGeracoes=gtk_label_new("Digite o número de gerações:");
  gtk_box_pack_start(GTK_BOX(conteudo), nGeracoes, FALSE, FALSE, 5);
  entradaGeracoes=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(conteudo), entradaGeracoes, FALSE, FALSE, 0);

  // Botão para calcular a rota através do algoritmo genético
  botao=gtk_button_new_with_label("Calcular rota!");
  gtk_box_pack_start(GTK_BOX(conteudo), botao, FALSE, FALSE, 10);

  // Botão chama a tela de desenho
  botao2=gtk_button_new_with_label("Visualizar caminhos");
  gtk_box_pack_start(GTK_BOX(conteudo), botao2, FALSE, FALSE, 10);

  // Labels de saida (Onde as informações principais serão escritas)
  label_saida2=gtk_label_new("   ");
  gtk_box_pack_start(GTK_BOX(conteudo), label_saida2, TRUE, FALSE, 8);

  label_saida3=gtk_label_new("   ");
  gtk_box_pack_start(GTK_BOX(conteudo), label_saida3, TRUE, FALSE, 8);

  label_saida4=gtk_label_new("   ");
  gtk_box_pack_start(GTK_BOX(conteudo), label_saida4, TRUE, FALSE, 8);

  label_saida=gtk_label_new("   ");
  gtk_box_pack_start(GTK_BOX(conteudo), label_saida, TRUE, FALSE, 8);

  // Passando a ação de cada botão
  g_signal_connect(G_OBJECT(botao), "clicked", G_CALLBACK(chamaThread), NULL);
  g_signal_connect(G_OBJECT(botao2), "clicked", G_CALLBACK(chamaDesenho), NULL);
  g_signal_connect(G_OBJECT(janela), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(janela);
  gtk_main();

	return 0;
}

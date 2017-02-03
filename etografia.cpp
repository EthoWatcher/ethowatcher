#include "etografia.h"
#include "ui_etografia.h"



//Inicialização
Etografia::Etografia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Etografia)
{
    ui->setupUi(this);

    ui->btVideo->setVisible(false);
     video= new cv::VideoCapture();
     processando=false;


      chaveEtog=true;
      chaveProce=false;
//    //Maximiza a interface
//    this->showMaximized();

//    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint|Qt::WindowFullscreenButtonHint=false);

//    this->installEventFilter(this);
//    //this->setMouseTracking(true);

//    processando=false;

//    //Inicia interface com os parametros do processamento inativados
//    ui->stackedWidgetProcessingParameters->setCurrentIndex(0);

//    //Inicializa estados dos botões de controle de vídeo
//    ui->btPlay->setEnabled(false);
//    ui->btStop->setEnabled(false);
//    ui->btAvancar->setEnabled(false);
//    ui->btVoltar->setEnabled(false);

    //Inicializa contador de controle de reprodução e processamento do video
    tmrTimer= new QTimer(this);

//    //Declara conecções de sinais de alguns objetos com a sua função correspondente
//    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processVideo()));
    connect(ui->SliderVelocidade, SIGNAL(valueChanged(int)), this, SLOT(atualizaVelocidade()));

//    //Declara atalhos do teclado
//    new QShortcut( Qt::Key_D, this, SLOT(on_btAvancar_clicked()));          //D -> Avançar frame
//    new QShortcut( Qt::Key_A, this, SLOT(on_btVoltar_clicked()));           //A -> Voltar frame
//    new QShortcut( Qt::Key_W, this, SLOT(incrementaFatorDesloc()));         //W -> Incrementa fator de navegação frame a frame
//    new QShortcut( Qt::Key_S, this, SLOT(decrementaFatorDesloc()));         //S -> Decrementa fator de navegação frame a frame
//    new QShortcut( Qt::Key_Q, this, SLOT(on_btPlay_clicked()));             //Q -> Reproduz video
//    new QShortcut( Qt::Key_E, this, SLOT(on_btStop_clicked()));             //E -> Pausa video
//    new QShortcut( Qt::Key_Minus, this, SLOT(incrementaFatorVeloc()));      //- -> Diminui velocidade de reprodução do video
//    new QShortcut( Qt::Key_Plus, this, SLOT(decrementaFatorVeloc()));       //+ -> Aumenta velocidade de reprodução do video

//    //Declara caixa de diálogo dos botões ao passar o maouse sobre os mesmos
//    ui->btAvancar->setToolTip("Click or press 'D' to go forward.");
//    ui->btVoltar->setToolTip("Click or press 'A' to go back.");
//    ui->edtFatordesloc->setToolTip("Click or press 'W' to increase and 'S' for decrement.");
//    ui->btPlay->setToolTip("Click or press 'Q' to play the video.");
//    ui->btStop->setToolTip("Click or press 'E' to pause the video.");
//    ui->btVideo->setToolTip("Click to open the video.");
//    ui->SliderVelocidade->setToolTip("Select the speed video playback. Drag the slider or press '+' to fast forward and '-' to slow motion.");

//    controleAvancaVideo=false;
    //so ajustando
    escolheSelecao=false;  //true apenas um botão por vez
                          //false pode apertar todos os botões

    dados = new moduloProcessamento();


    connect(dados, SIGNAL(desenhaFigura(QImage,bool,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)),
            this,  SLOT(recebeDesenho(QImage,bool,double,double,double,double,double,double,
                                      double,double,double,double,double,
                                      double,double,double,double,double,double,double)));

    //maxVaria=400;//apenas protoboard
}

//Fechar interface
Etografia::~Etografia()
{
    video->release();
    tmrTimer->stop();
    this->close();

   // delete ui;
}

////Cria objeto para a interface anterior (ethowatcher), para retornar a ela quando a interface de
////calibração for encerrada
//void Etografia::setEthoWatcher(QMainWindow *param)
//{
//    video.release();
//    tmrTimer->stop();
//    this->close();
//    //this->etw = param;
//}

////Recebe dados da identificação do experimento
//void Etografia::setDadosIdentificacao(QString param1, QString param2, QString param3,
//                                      QString param4, QString param5, QString param6,
//                                      QString param7, QString param8, QString param9)
//{
//    identificacao.experimento=param1;       //Experimento
//    identificacao.data=param2;              //Data
//    identificacao.laboratorio=param3;       //Laboratório
//    identificacao.idPesquisador=param4;     //Pesquisador
//    identificacao.idAnimal=param5;          //Animal
//    identificacao.peso=param6;              //Peso
//    identificacao.sexo=param7;              //Sexo
//    identificacao.tratamento=param8;        //tratamento
//    identificacao.outrasInfo=param9;        //outras informações

//    dadosExperimento.dadosIdentificacao=identificacao;
//}

////Identifica o tipo de análise escolhida (etografia em tempo real, etografia baseada em
////vídeo, rastreamento)
// void Etografia::setTipoAnalise(int param[3])
//{
//    dadosExperimento.tipoAnalise[0]=param[0];
//    dadosExperimento.tipoAnalise[1]=param[1];
//    dadosExperimento.tipoAnalise[2]=param[2];

//    //Se análise for em tempo real, seta a pagina de análise em tempo real
//    if(dadosExperimento.tipoAnalise[0]==1)
//    {
//        ui->stackedWidgetTipoAnalise->setCurrentIndex(1);
//    }

//    //Se análise for baseada em vídeo, seta a pagina de análise com vídeos
//    if(dadosExperimento.tipoAnalise[0]==0)
//    {
//        ui->stackedWidgetTipoAnalise->setCurrentIndex(0);
//    }

//    if(dadosExperimento.tipoAnalise[1]==1)
//    {
//        ui->scrollAreaEtografiaBotoes->setHidden(false);
//    }

//    if(dadosExperimento.tipoAnalise[1]==0)
//    {
//        ui->scrollAreaEtografiaBotoes->setHidden(true);
//    }
//}

////Identifica o tipo de registro de eventos escolhido (auto exclusivo ou sobrepostos)
//void Etografia::setTipoRegistroEventos(QString param)
//{
//    dadosExperimento.tipoRegistroEventos=param;
//}

////Identifica o endereço do arquivo de catálogo escolhido
//void Etografia::setArquivoCatalogo(QString param)
//{
//    dadosExperimento.arquivoCatalogo=param;

//    if(dadosExperimento.tipoAnalise[1]==1)
//    {
//       // if(leituraCatalogo(dadosExperimento.arquivoCatalogo));
//     //       carregaCatalogo();
//    }
//}

////Recebe os dados da calibração do experimento
//void Etografia::setDadosCalibracao(QString param1, cv::Mat param2, int param3, int param4,
//                                   QString param5, QList<cv::Mat> param6, int param7[2],
//                                   double param8)
//{
//    resultadoCalibracao.video=param1;           //Endereço do arquivo de vídeo
//    resultadoCalibracao.background=param2;      //Frame de background
//    resultadoCalibracao.threshold=param3;       //Valor do threshold
//    resultadoCalibracao.erosao=param4;          //valor da erosão
//    resultadoCalibracao.tipoArea=param5;        //Tipo de área (poligonais ou matricial)
//    resultadoCalibracao.areas=param6;           //Lista das máscaras das áreas calibradas
//    resultadoCalibracao.matriz[0]=param7[0];    //Número de linhas da área matricial
//    resultadoCalibracao.matriz[1]=param7[1];    //Número de colunas da área matricial
//    resultadoCalibracao.escala=param8;          //Escala

//    dadosExperimento.dadosCalibracao=resultadoCalibracao;

//    //Se foi selecionado análise com rastreamento
//    if(dadosExperimento.tipoAnalise[2]==1)
//    {
//        ui->stackedWidgetControleDesenho->setHidden(false);

//        //Abre video calibrado
//        abreArquivoVideo(dadosExperimento.dadosCalibracao.video);

//        //Desabilita botão de abrir novo vídeo
//        ui->btVideo->setEnabled(false);

//        //Reinicializa frames para asegmentação
//        frameBackground.release();          //referente ao fundo
//        frameAnimal.release();              //referente ao animal

//        //Captura o frame referente ao fundo de acordo com o resultado da calibração
//        frameBackground=resultadoCalibracao.background;

//        //frameSubtracao.release();       //referente ao frame animal menos o frame de fundo
//        //frameSubtracao=cv::Mat::zeros(video_heigth, video_width, CV_8UC3);
//        //frameSubtracao_gray.release();  //referente ao frame animal menos o frame de fundo em tons de cinza
//        //frameSubtracao_gray=cv::Mat::zeros(video_heigth, video_width, CV_8UC3);
//        //frameLimiarizacao.release();
//        //frameLimiarizacao=cv::Mat::zeros(video_heigth, video_width, CV_8UC3);
//        //frameSegmentacao.release();     //referente ao resultado final do processo de segmentação
//    }

//    else
//        ui->stackedWidgetControleDesenho->setHidden(true);
//}

//bool Etografia::leituraCatalogo(QString arqCatalogo)
//{
////    FILE *arquivo;
////    int nroSujCat=0;
////    int nroCatCat=0;
////    char dadoRecuperado[500]="";


////    sujeito *sujTmp = NULL;
////    Categoria *catTmp = NULL;

////    arquivo = fopen(arqCatalogo.toStdString().c_str(),"r");

////    if(arquivo==NULL)
////    {
////        QMessageBox::information(this,"Atention!", mensagemErro08_TFNC);
////    }

////    else
////    {
////        //getObjExperimento()->setCatalogoEmUso(new catalogo());
////        catalogoEmUso = new catalogo();

////        fscanf(arquivo, "%s", &dadoRecuperado);

////        nroSujCat = (QString::fromUtf8(dadoRecuperado)).toInt();

////        for(int cont = 0; cont<nroSujCat; cont++)
////        {
////            sujTmp  =       new     sujeito();
////            fscanf(arquivo, " %[^\n]", &dadoRecuperado);
////            sujTmp->setNome(dadoRecuperado);
////            fscanf(arquivo, " %[^\n]", &dadoRecuperado);
////            sujTmp->setCodigo(dadoRecuperado);
////            fscanf(arquivo, " %[^\n]", &dadoRecuperado);
////            sujTmp->setDescricao(dadoRecuperado);

////            //getObjExperimento()->getCatalogoEmUso()->adicionaSujeito(sujTmp);
////            catalogoEmUso->adicionaSujeito(sujTmp);
////        }

////        fscanf(arquivo, "%s", &dadoRecuperado);
////        nroCatCat = (QString::fromUtf8(dadoRecuperado)).toInt();

////        for(int cont=0;cont<nroCatCat;cont++)
////        {
////            catTmp  =       new     Categoria();
////            fscanf(arquivo, " %[^\n]", &dadoRecuperado);
////            catTmp->setNome(dadoRecuperado);
////            fscanf(arquivo, " %[^\n]", &dadoRecuperado);
////            catTmp->setCodigo(dadoRecuperado);
////            fscanf(arquivo, " %[^\n]", &dadoRecuperado);
////            catTmp->setDescricao(dadoRecuperado);

////            //getObjExperimento()->getCatalogoEmUso()->adicionaCategoria(catTmp);
////            catalogoEmUso->adicionaCategoria(catTmp);
////        }

////        //fecha arquivo
////        fclose(arquivo);

////        //this->getObjExperimento()->setCatalogoEtograficoOk(true);   //sinaliza carga do cat�logo correta

////        return  true;
////    }

////    //this->getObjExperimento()->setCatalogoEtograficoOk(false);

////    return  false;
//}

//void Etografia::carregaCatalogo()
//{

////    categoriasCatalogo *catsTmp = catalogoEmUso->getCategoriasCatalogo();
////    sujeitosCatalogo *sujsTmp = catalogoEmUso->getSujeitosCatalogo();

////    QPushButton *b[catalogoEmUso->getNroCategorias()];
////    QSignalMapper *mapperCategorias = new QSignalMapper(this);

////    int contCat = 0;

////    while(catsTmp!=NULL)
////    {
////        b[contCat] = new QPushButton;
////        b[contCat]->setText(catsTmp->getElemento()->getNome());

////        connect(b[contCat], SIGNAL(clicked()), mapperCategorias, SLOT(map()));
////        mapperCategorias->setMapping(b[contCat],contCat);

////        if(catsTmp->getElemento()->getCodigo().count()==1)
////        {
////            b[contCat]->setShortcut(QKeySequence("Ctrl+" + catsTmp->getElemento()->getCodigo()));
////            if(catsTmp->getElemento()->getDescricao()=="NULL")
////                b[contCat]->setToolTip(splitTooltip("(CTRL+" + catsTmp->getElemento()->getCodigo().toUpper() + ")",300));
////            else
////                b[contCat]->setToolTip(splitTooltip(catsTmp->getElemento()->getDescricao() + " (CTRL+" + catsTmp->getElemento()->getCodigo().toUpper() + ")",300));
////        }

////        if(catsTmp->getElemento()->getCodigo().count()==2)
////        {
////            QString l1=catsTmp->getElemento()->getCodigo().at(0);
////            QString l2=catsTmp->getElemento()->getCodigo().at(1);
////            b[contCat]->setShortcut(QKeySequence("Ctrl+" + l1 + ", Ctrl+" + l2));
////            if(catsTmp->getElemento()->getDescricao()=="NULL")
////                b[contCat]->setToolTip(splitTooltip("(CTRL+" + l1.toUpper() + "+" + l2.toUpper() + ")",300));
////            else
////                b[contCat]->setToolTip(splitTooltip(catsTmp->getElemento()->getDescricao() + " (CTRL+" + l1.toUpper() + "+" + l2.toUpper() + ")",300));
////        }

////        if(catsTmp->getElemento()->getCodigo().count()==3)
////        {
////            QString l1=catsTmp->getElemento()->getCodigo().at(0);
////            QString l2=catsTmp->getElemento()->getCodigo().at(1);
////            QString l3=catsTmp->getElemento()->getCodigo().at(2);
////            b[contCat]->setShortcut(QKeySequence("Ctrl+" + l1 + ", Ctrl+" + l2 + ", Ctrl+" + l3));
////            if(catsTmp->getElemento()->getDescricao()=="NULL")
////                b[contCat]->setToolTip(splitTooltip("(CTRL+" + l1.toUpper() + "+" + l2.toUpper() + "+" + l3.toUpper() + ")",300));
////            else
////                b[contCat]->setToolTip(splitTooltip(catsTmp->getElemento()->getDescricao() + " (CTRL+" + l1.toUpper() + "+" + l2.toUpper() + "+" + l3.toUpper() + ")",300));
////        }

////        ui->verticalLayoutBotoesCategoria->insertWidget(contCat,b[contCat]);

////        contCat++;
////        catsTmp = catsTmp->getProx();
////    }

////    connect(mapperCategorias, SIGNAL(mapped(int)), this, SLOT(clicarBotaoCategoria(int)));

////    if(catalogoEmUso->getNroSujeitos()==1)
////    {
////        QLabel *l=new QLabel;
////        l->setText(sujsTmp->getElemento()->getNome());
////        if(sujsTmp->getElemento()->getDescricao()!="NULL")
////        l->setToolTip(splitTooltip(sujsTmp->getElemento()->getDescricao(),300));
////        sujeitoSelecionado=0;
////        ui->verticalLayoutBotoesSujeitos->insertWidget(0,l);
////    }

////    else
////    {
////        QRadioButton *r[catalogoEmUso->getNroSujeitos()];
////        QSignalMapper *mapperSujeitos = new QSignalMapper(this);

////        int contSuj=0;

////        while(sujsTmp!=NULL)
////        {
////            r[contSuj] = new QRadioButton;
////            r[contSuj]->setText(sujsTmp->getElemento()->getNome());
////            if(contSuj==0)
////                r[contSuj]->setChecked(true);
////            sujeitoSelecionado=0;

////            connect(r[contSuj], SIGNAL(clicked()), mapperSujeitos, SLOT(map()));
////            mapperSujeitos->setMapping(r[contSuj],contSuj);

////            if(sujsTmp->getElemento()->getCodigo().count()==1)
////            {
////                r[contSuj]->setShortcut(QKeySequence("Ctrl+" + sujsTmp->getElemento()->getCodigo()));
////                if(sujsTmp->getElemento()->getDescricao()=="NULL")
////                    r[contSuj]->setToolTip(splitTooltip("(CTRL+" + sujsTmp->getElemento()->getCodigo().toUpper() + ")",300));
////                else
////                    r[contSuj]->setToolTip(splitTooltip(sujsTmp->getElemento()->getDescricao() + " (CTRL+" + sujsTmp->getElemento()->getCodigo().toUpper() + ")",300));
////            }

////            if(sujsTmp->getElemento()->getCodigo().count()==2)
////            {
////                QString l1=sujsTmp->getElemento()->getCodigo().at(0);
////                QString l2=sujsTmp->getElemento()->getCodigo().at(1);
////                r[contSuj]->setShortcut(QKeySequence("Ctrl+" + l1 + ", Ctrl+" + l2));
////                if(sujsTmp->getElemento()->getDescricao()=="NULL")
////                    r[contSuj]->setToolTip(splitTooltip("(CTRL+" + l1.toUpper() + "+" + l2.toUpper() + ")",300));
////                else
////                    r[contSuj]->setToolTip(splitTooltip(sujsTmp->getElemento()->getDescricao() + " (CTRL+" + l1.toUpper() + "+" + l2.toUpper() + ")",300));
////            }

////            if(sujsTmp->getElemento()->getCodigo().count()==3)
////            {
////                QString l1=sujsTmp->getElemento()->getCodigo().at(0);
////                QString l2=sujsTmp->getElemento()->getCodigo().at(1);
////                QString l3=sujsTmp->getElemento()->getCodigo().at(2);
////                r[contSuj]->setShortcut(QKeySequence("Ctrl+" + l1 + ", Ctrl+" + l2 + ", Ctrl+" + l3));
////                if(sujsTmp->getElemento()->getDescricao()=="NULL")
////                    r[contSuj]->setToolTip(splitTooltip("(CTRL+" + l1.toUpper() + "+" + l2.toUpper() + "+" + l3.toUpper() + ")",300));
////                else
////                    r[contSuj]->setToolTip(splitTooltip(sujsTmp->getElemento()->getDescricao() + " (CTRL+" + l1.toUpper() + "+" + l2.toUpper() + "+" + l3.toUpper() + ")",300));
////            }

////            ui->verticalLayoutBotoesSujeitos->insertWidget(contSuj,r[contSuj]);

////            sujsTmp = sujsTmp->getProx();
////            contSuj++;
////        }

////        connect(mapperSujeitos, SIGNAL(mapped(int)), this, SLOT(clicarCheckBoxSujeito(int)));
////    }
//}

//QString Etografia::splitTooltip(QString text, int width)
//{
//    QFontMetrics fm(QToolTip::font());
//    QString result;

//    for (;;) {
//        int i = 0;
//        while (i < text.length()) {
//            if (fm.width(text.left(++i + 1)) > width) {
//                int j = text.lastIndexOf(' ', i);
//                if (j > 0)
//                    i = j;
//                result += text.left(i);
//                result += '\n';
//                text = text.mid(i+1);
//                break;
//            }
//        }
//        if (i >= text.length())
//            break;
//    }
//    return result + text;
//}

//void Etografia::clicarBotaoCategoria(int index)
//{
//    categoriaSelecionada=index;

//    QList <double> eventoOcorrido;
//    eventoOcorrido.insert(0,tempo_atual);
//    eventoOcorrido.insert(1,sujeitoSelecionado);
//    eventoOcorrido.insert(2,categoriaSelecionada);
//    eventos.insert(eventos.count()-1,eventoOcorrido);
//}

//void Etografia::clicarCheckBoxSujeito(int index)
//{
//    sujeitoSelecionado=index;
//}

////Clicar no botão de fechar interface
void Etografia::closeEvent(QCloseEvent *param)
{

    video->release();
    tmrTimer->stop();
    this->close();
    //Habilita a interface "ethowarcher" (interface principal)
    //etw->setEnabled(true);

    //Fecha a interface de calibração
   // this->event = param;
   // event->accept();
}

////Clicar no botão de abrir video
//void Etografia::on_btVideo_clicked()
//{
//    //Captura string referente ao diretório do vídeo delecionado na caixa de diálogo
//    //Tipos de arquivo limotados para: .avi, .mp4, .mpeg, .mpg, .wmv, .flv, .mkv
//    fonteVideo = QFileDialog::getOpenFileName(
//                this,
//                tr("Open File"),
//                "C://Users//Bio//Desktop//videos//",
//                "Video Files (*.avi *.mp4 *.mpeg *.mpg *.wmv *.flv *mkv)"
//                );

//    //Se a string capturada for vazia (casos: fechar ou cancelar janela de diálogo), sai da função
//    //abrir video e não executa os códicos a seguir
//    if(fonteVideo=="")
//    {
//        return;
//    }

//    //Para contador se o mesmo estiver rodando (ou seja, se estivaer no meio da execução de um vídeo)
//    if(tmrTimer->isActive()==true)
//    {
//        tmrTimer->stop();
//    }

//    //Inativa os parametros do processamento
//    ui->stackedWidgetProcessingParameters->setCurrentIndex(0);

//    //Seleciona imagens padrão para a tela de video (imagem que aparece antes de abrir um video)
//    QPixmap defaultVideo(":/icons/video.png");
//    ui->panTela->setPixmap(defaultVideo);

//    ui->panProcess->setScaledContents(true);
//    QPixmap defaultProcessing(":/icons/fundoBranco.png");
//    ui->panProcess->setPixmap(defaultProcessing);

//    //Abre video selecionado
//    abreArquivoVideo(fonteVideo);
//}

////Função de abrir vídeo
void Etografia::abreArquivoVideo(QString param)
{

    //Reinicializa frames
    frame.release();                //referente ao frame atual de leitura de video
    frameReduzido.release();        //referente ao frame atual de leitura de video proporcional ao tamanho padrão 320x240
    frameAumentado.release();
    tracking.release();
    trackingBranco.release();
    linhaAnimal.release();
    linhaAnimalBranco.release();
    caixaAnimal.release();
    caixaAnimalBranco.release();
    coordenadas.release();
    coordenadasBranco.release();

    //Variável de controle que indica se a velocidade pode ser atualizada. Setada para não atualizar
    controleAtualizaVelocidade=false;

    //Inicializa velocidade de leitura do video para a velocidade normal de reprodução
    ui->SliderVelocidade->setSliderPosition(0);

    //Muda estado da variável de controle indicando que a velocidade pode ser atualizada
    controleAtualizaVelocidade=true;

    //Transforma a variável fonteVideo (QString) em string
    //const std::string arquivoVideo = param. toUtf8 (). constData ();
    std::string arquivoVideo = fonteVideo.toStdString();
    //Abre o vídeo selecionado
    video->open(arquivoVideo);

    //Caso não foi possível abrir o vídeo (devido a problemas de compatibilidade do formato do vídeo
    //com a a versão usada do OpenCV)
    if(!video->isOpened())
    {
        //Desabilita botões de controle do vídeo
        ui->btPlay->setEnabled(false);
        ui->btStop->setEnabled(false);
        ui->btAvancar->setEnabled(false);
        ui->btVoltar->setEnabled(false);

        //Habilita botão para abrir novo vídeo
        ui->btVideo->setEnabled(true);

        //Zera campos de informação da reprodução do vídeo (frames/tempo e atual/total)
        ui->labelFrames->setText("0");
        ui->labelFramesTotal->setText("0");
        ui->labelTempo->setText("0");
        ui->labelTempoTotal->setText("0");

        //Zera campo de título do vídeo
        //ui->labelVideo->setText("");

        //Emite uma mensagem de erro e sai da função abrir video, não executando os códicos a seguir
        QMessageBox::information(this,"Error","The video was not successfully opened.");
        return;
    }

    //Atualiza campo de título do vídeo
    //ui->labelVideo->setText(param);

    //Atualiza botões de controle de vídeo, possibilitando reproduzir o vídeo, avançar frame-a-frame
    //ou abrir novo vídeo
    ui->btPlay->setEnabled(true);
    ui->btStop->setEnabled(false);
    ui->btVideo->setEnabled(true);
    ui->btAvancar->setEnabled(true);
    ui->btVoltar->setEnabled(false);

    //Zera informações de reprodução de vídeo
    frame_atual=0;
    tempo_atual=0;

    //captura dados do vídeo
    video_fps = video->get(CV_CAP_PROP_FPS);                 //captura frames por segundo
    video_frames = video->get(CV_CAP_PROP_FRAME_COUNT);      //captura quantidade de frames
    video_tempo = video_frames/video_fps;                   //calcula tempo do video
    video_width = video->get(CV_CAP_PROP_FRAME_WIDTH);       //captura largura do video
    video_heigth = video->get(CV_CAP_PROP_FRAME_HEIGHT);     //captura altura do video

    //Calcula proporções do vídeo para o formato padrão 320x240
    //Nessa interface, os tamanhos máximos do vídeo são 320px para largura e 240px para altura
    //Vídeos de tamanhos maiores que este padrão serão reduzidos de forma a encaixar em 320x240
    //Vídeos menores ou igual a esse padrão serão mantidos suas dimensões (vídeo_prop=1)
    prop_width=video_width/320;
    prop_heigth=video_heigth/240;

    if(prop_width>=prop_heigth && prop_width>1)
        video_prop=1/prop_width;

    else if(prop_heigth>prop_width && prop_heigth>1)
        video_prop=1/prop_heigth;

    else
        video_prop=1;

    //Calculo das dimensões do vídeo a partir da proporção obtida acima
    widthReduzido=video_width*video_prop;
    heigthReduzido=video_heigth*video_prop;

  //  if(dadosExperimento.tipoAnalise[2]==0)
   //
    calculaProporcaoAumentada(); //mudado

    //Atualiza campos de frames e tempo total de acordo com as informações extraidas do video
    ui->labelFrames->setText("0");
   // ui->labelFramesTotal->setText(QString::number(video_frames));
    ui->labelFramesTotal->setText(QString::number(finalFrame));

    ui->labelTempo->setText("0");
    //ui->labelTempoTotal->setText(QString::number(video_tempo));
    ui->labelTempoTotal->setText(QString::number(finalFrame/video_fps));

    controleInitialFrame=true;
    controleFinalFrame=true;

    //ui->spinBoxInitialFrame->setMaximum(video_frames);
   // ui->spinBoxFinalFrame->setMaximum(video_frames);
   // ui->spinBoxInitialFrame->setMinimum(1);
    //ui->spinBoxFinalFrame->setMinimum(1);
    //ui->spinBoxInitialFrame->setValue(1);
    //ui->spinBoxFinalFrame->setValue(video_frames);

    //ui->pushButtonProcess->setEnabled(true);
    //ui->pushButtonStop->setEnabled(false);
    //ui->pushButtonFinalFrame->setEnabled(true);
   // ui->pushButtonInitialFrame->setEnabled(true);
    //ui->spinBoxFinalFrame->setReadOnly(false);
   // ui->spinBoxInitialFrame->setReadOnly(false);
}

void Etografia::calculaProporcaoAumentada()
{
    widthPanProcess=ui->panProcess->size().width();
    heightPanProcess=ui->panProcess->size().height();
    propAumentada_width=video_width/widthPanProcess;
    propAumentada_heigth=video_heigth/heightPanProcess;

    if(propAumentada_width>=propAumentada_heigth)
        video_propAumentada=1/propAumentada_width;

    if(propAumentada_heigth>propAumentada_width)
        video_propAumentada=1/propAumentada_heigth;

    controleTamanhoAumentado=true;
}

////Clicar no botão de reproduzir vídeo
void Etografia::on_btPlay_clicked()
{

    if(chaveEtog){

        connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processVideo()));

    }
    //novo procesamento
    if(chaveProce){

       connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processVideoMorf()));
       connect(this,SIGNAL(processe()),dados,SLOT(processamentoDeVideo()));
       connect(this,SIGNAL(fimProce()),this,SLOT(geraValoresCinematicos()));
       connect(this,SIGNAL(fimProce()),this,SLOT(termina()));


       connect(dados,SIGNAL(dadosMorfologicos(QImage,bool,double,double,double,float,float)),
               this,SLOT(recebeDadosMorfologicos(QImage,bool,double,double,double,float,float)));
       //video.set(CV_CAP_PROP_POS_FRAMES,0);

      // dWidth = video.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
       //dHeight = video.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
    }

    processando= true; //false; //fazendo a compatibilidade de versao

//    initialFrame=1; //fazendo a compatibilidade de versao
//    finalFrame=1000; //fazendo a compatibilidade


    //Se o botão de reproduzir estiver habilitado
    //(se o video já foi aberto, se o video está pausado, se está na navegação frame a frame)
    if(ui->btPlay->isEnabled()==true)
    {
        //Habilita os parametros do processamento
     //   ui->stackedWidgetProcessingParameters->setCurrentIndex(1);

        //Atualiza botões de controle de vídeo, possibilitando pausar o vídeo, avançar/voltar ou
        //frame-a-frame
        ui->btPlay->setEnabled(false);
        ui->btStop->setEnabled(true);
        ui->btAvancar->setEnabled(true);
        ui->btVoltar->setEnabled(true);

        if(processando==true)
            ui->btVideo->setEnabled(false);

        else
        {
            //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
        //    if(dadosExperimento.tipoAnalise[2]==1)
      //          ui->btVideo->setEnabled(false);

            //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
    //        if(dadosExperimento.tipoAnalise[2]==0)
  //              ui->btVideo->setEnabled(true);
        }

        //Calcula o fator de aceleração/desaceleração do vídeo a partir do controle disponível na
        //interface
        fatorVeloc= qPow(2,ui->SliderVelocidade->value());

        //Inicia o contador de controle de reprodução e processamento do video.
        //Calcula o tempo de disparo igual ao tempo de reprodução de 1 frame (1000ms/fps) multiplicado
        //pelo fator de velocidade(aceleração/desaceleração) do video
        tmrTimer->start((1000/video_fps)*fatorVeloc);
        ui->groupBoxCategorias->setEnabled(true);
    }
}

////Clicar no botão de pausar video
void Etografia::on_btStop_clicked()
{
    //Se o botão de pausar estiver habilitado (se o video está sendo reproduzido)
    if(ui->btStop->isEnabled()==true)
    {
        //Atualiza botões de controle de vídeo, possibilitando reproduzir o vídeo
        //ou abrir novo vídeo
        ui->btStop->setEnabled(false);
        ui->btPlay->setEnabled(true);

        if(processando==true)
            ui->btVideo->setEnabled(false);

        else
        {
            //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
           // if(dadosExperimento.tipoAnalise[2]==1)
           //     ui->btVideo->setEnabled(false);

            //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
           // if(dadosExperimento.tipoAnalise[2]==0)
             //   ui->btVideo->setEnabled(true);
        }

        //Pausa o contador de controle de reprodução e processamento do video.
        tmrTimer->stop();
    }
}

////Função de processamento do vídeo, executada a cada disparo do contador
void Etografia::processVideo()
{
    //Atualiza valores de frame e tempo atual
    frame_atual=video->get(CV_CAP_PROP_POS_FRAMES);
    tempo_atual=video->get(CV_CAP_PROP_POS_MSEC)/1000;   //Transforma para segundos

    //Faz a leitura do vídeo e retorna para a variável frame
    video -> read ( frame );

    //Se a o contador de frames igualar ao total de frames do video, ou seja, foram lidos
    //todos o frames do video (contador de frame inicia como 0)
    if((processando== false && frame_atual==video_frames)||(processando==true && frame_atual==finalFrame))
    {
        //Pausa o contador de controle de reprodução e processamento do video.
        tmrTimer->stop();

        //Retorna o vídeo para o primeiro frame
        video->set(CV_CAP_PROP_POS_FRAMES,0);

        if(processando==false)
        {
            //Atualiza botões de controle de vídeo, possibilitando reproduzir o vídeo, avançar video
            //frame-a-frame ou abrir novo vídeo
            ui->btPlay->setEnabled(true);
            ui->btStop->setEnabled(false);
            ui->btAvancar->setEnabled(false);

            //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
            //if(dadosExperimento.tipoAnalise[2]==1)
             //   ui->btVideo->setEnabled(false);

            //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
           // if(dadosExperimento.tipoAnalise[2]==0)
            //    ui->btVideo->setEnabled(true);
        }

        if(processando==true)
        {
            ui->btPlay->setEnabled(false);
            ui->btStop->setEnabled(false);
            ui->btAvancar->setEnabled(false);
            ui->btVoltar->setEnabled(false);

            //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
           // if(dadosExperimento.tipoAnalise[2]==1)
           //     ui->btVideo->setEnabled(false);

            //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
          //  if(dadosExperimento.tipoAnalise[2]==0)
           //     ui->btVideo->setEnabled(true);

            //ui->pushButtonProcess->setEnabled(false);
           // ui->pushButtonStop->setEnabled(false);

            ui->checkBoxRoute->setEnabled(false);
            ui->checkBoxRoute->setChecked(false);
            ui->checkBoxCenterMass->setEnabled(false);
            ui->checkBoxCenterMass->setChecked(false);
            ui->checkBoxBoundingBox->setEnabled(false);
            ui->checkBoxBoundingBox->setChecked(false);
            ui->checkBoxLengthAnimal->setEnabled(false);
            ui->checkBoxLengthAnimal->setChecked(false);
            ui->checkBoxCoordinates->setEnabled(false);
            ui->checkBoxCoordinates->setChecked(false);
            //ui->groupBoxSujeitos->setEnabled(false);
            ui->groupBoxCategorias->setEnabled(false);

            processando=false;
            QMessageBox::information(this,"Finish","Processing was completed successfully! Você "
                                                   "ira para gravação dos dados Etograficos");

            video->release();
            tmrTimer->stop();
            this->close();

            //emitindo os valores etograficos

            emit enviandoDadosEtograficos();


        }

        //Decrementa o valor frame atual, retornando para o valor referente ao ultimo frame do video
        frame_atual--;

        //sai da função de processar video e não executa os códigos a seguir
        return;
    }

    //Transforma a estrutura de cor da imagem capturada na variável frame de BGR para RGB, e armazena na
    //mesma variavel
    cv::cvtColor(frame,frame,CV_BGR2RGB);

    //Redimensiona frame (que tem dimensões originais do video) a partir das informações de proporção
    //de video calculadas anteriormente para o padrão 320x240, e armazena na variavel frameReduzido
    cv::resize(frame,frameReduzido,frameReduzido.size(),video_prop,video_prop,cv::INTER_LANCZOS4);

    if(controleAvancaVideo==false)
    {
        //Transforma o frame em uma imagem e depois em um QPixmap, e joga essa imagem na tela de visualização
        //do video
        QImage imgVideoOriginal((uchar*)frameReduzido.data, frameReduzido.cols, frameReduzido.rows, frameReduzido.step, QImage::Format_RGB888);
        ui->panTela->setPixmap(QPixmap::fromImage(imgVideoOriginal));

        //Atualiza campos de informação do vídeo (frame/tempo e atual/ total)
        int frAtual= frame_atual + 1;
        ui->labelFrames->setText(QString::number(frAtual));     //soma 1 pois o contador inicia como 0

        ui->labelFramesTotal->setText(QString::number(finalFrame));

        //ui->labelFramesTotal->setText(QString::number(video_frames));
        ui->labelTempo->setText(QString::number(tempo_atual,'f', 0));

        ui->labelTempoTotal->setText(QString::number(finalFrame/video_fps));

        //ui->labelTempoTotal->setText(QString::number(video_tempo));
    }

    //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
    if(processando==true)
    {
        //Captura o frame atual do vídeo como o correspondente ao animal
        frameAnimal=frame;

        //Atualiza a análise
        //atualizaAnalise();

       calculaProporcaoAumentada();
    cv::resize(frame,frameAumentado,frameAumentado.size(),video_propAumentada,video_propAumentada,cv::INTER_LANCZOS4);
    //cv::resize(frame,frameAumentado,frameAumentado.size(),1,1,cv::INTER_LANCZOS4);
    QImage imgVideoAumentado((uchar*)frameAumentado.data, frameAumentado.cols, frameAumentado.rows, frameAumentado.step, QImage::Format_RGB888);
      ui->panProcess->setScaledContents(false);
      ui->panProcess->setPixmap(QPixmap::fromImage(imgVideoAumentado));

    }
}

////Clicar no botão avançar frames
void Etografia::on_btAvancar_clicked()
{
//    //Se o botão de avançar frame estiver habilitado (se o video não estiver no último frame)
//    if(ui->btAvancar->isEnabled()==true)
//    {
//        //Habilita os parametros do processamento
//        //ui->stackedWidgetProcessingParameters->setCurrentIndex(1);

//        //Atualiza botões de controle de vídeo, possibilitando reproduzir o vídeo ou
//        //voltar em frames anteriores
        ui->btStop->setEnabled(false);
        ui->btPlay->setEnabled(true);
        ui->btVoltar->setEnabled(true);

//        if(processando==true)
//            ui->btVideo->setEnabled(false);

//        else
//        {
//            //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
//           // if(dadosExperimento.tipoAnalise[2]==1)
//           //     ui->btVideo->setEnabled(false);

//            //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
//           // if(dadosExperimento.tipoAnalise[2]==0)
//           //     ui->btVideo->setEnabled(true);
//        }

//        //Pausa o contador de controle de reprodução e processamento do video
        tmrTimer->stop();

//        //Atualiza o fator de deslocamento de frames a partir da informação contida na interface
        fatorDesloc = ui->edtFatordesloc->value();

//      //  if(C==false)
//       // {
//            //Se a soma do fator de deslocamento com o frame atual for maior do que a quantidade de frames
//            //total do video
            if((frame_atual+fatorDesloc)>= video_frames-1)
            {
                //Avança o vídeo para o último frame
               video->set(CV_CAP_PROP_POS_FRAMES,video_frames-1);

//                //Executa a função de processamento do video, já que o timer está parado
                 processVideo();
            }

//            //Se a soma do fator de deslocamento com o frame atual for menor do que a quantidade de frames
//            //total do video
            else
            {
//                //Avança o vídeo para esse valor
              video->set(CV_CAP_PROP_POS_FRAMES,frame_atual+fatorDesloc);
                 }

//        if(processando==true)
//        {
//           // if(dadosExperimento.tipoAnalise[2]==1)
//             //   this->setCursor(Qt::WaitCursor);

            int frameResultante;

            if((frame_atual+fatorDesloc)>= finalFrame-1)
            {
               frameResultante=finalFrame-1;
            }

//            //Se a soma do fator de deslocamento com o frame atual for menor do que a quantidade de frames
//            //total do video
            else
            {
                frameResultante=frame_atual+fatorDesloc;
            }

////           // if(dadosExperimento.tipoAnalise[2]==1)
////            {
////                cv::Scalar colorBranco = cv::Scalar( 255, 255, 255 );
////                cv::Scalar colorVermelho = cv::Scalar( 255, 0, 0 );

////                if(fatorDesloc!=1)
////                {
////                    for(int i=frame_atual+1;i<(frameResultante);i++)
////                    {
////                        controleAvancaVideo=true;
////                        processVideo();
////                        controleAvancaVideo=false;
////                    }
////                }

////            }

            if((frame_atual+fatorDesloc)>= finalFrame-1)
            {
                video->set(CV_CAP_PROP_POS_FRAMES,frameResultante);

//                //Executa a função de processamento do video, já que o timer está parado
                processVideo();
            }

//            //Se a soma do fator de deslocamento com o frame atual for menor do que a quantidade de frames
//            //total do video
            else
            {
//                //Avança o vídeo para esse valor
                video->set(CV_CAP_PROP_POS_FRAMES,frameResultante);
            }

//            //if(dadosExperimento.tipoAnalise[2]==1)
//             //   this->setCursor(Qt::ArrowCursor);
//        }

//        //Executa a função de processamento do video
        processVideo();
//    }
}

////Clicar no botão de voltar frames
void Etografia::on_btVoltar_clicked()
{
    if(ui->btVoltar->isEnabled()==true)
    {
        //Atualiza botões de controle de vídeo, possibilitando reproduzir o vídeo ou
        //avançar para próximos frames
        ui->btStop->setEnabled(false);
        ui->btPlay->setEnabled(true);
        ui->btAvancar->setEnabled(true);

        if(processando==true)
            ui->btVideo->setEnabled(false);

        else
        {
//            //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
//            if(dadosExperimento.tipoAnalise[2]==1)
//                ui->btVideo->setEnabled(false);

//            //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
//            if(dadosExperimento.tipoAnalise[2]==0)
//                ui->btVideo->setEnabled(true);
        }

        //Pausa o contador de controle de reprodução e processamento do video
        tmrTimer->stop();

        //Atualiza o fator de deslocamento de frames a partir da informação contida na interface
        fatorDesloc = ui->edtFatordesloc->value();

        if(processando==false)
        {
            //Se a subtração do fator de deslocamento do frame atual for menor do que zero, ou seja,
            //o fator de deslocamento for maior que o frame atual
            if((frame_atual-fatorDesloc)<= 0)
            {
                //Retorna o video para o primeiro frame
                video->set(CV_CAP_PROP_POS_FRAMES,0);

                //Desabilita o botão voltar frames, pois está no primeiro frame do video
                ui->btVoltar->setEnabled(false);
            }

            //Se a subtração do fator de deslocamento do frame atual for maior do que zero, ou seja,
            //o fator de deslocamento for menor que o frame atual
            else
                //Retorna o vídeo para esse valor
                video->set(CV_CAP_PROP_POS_FRAMES,frame_atual-fatorDesloc);
        }

        if(processando==true)
        {
            int frameResultante;

            //Se a subtração do fator de deslocamento do frame atual for menor do que zero, ou seja,
            //o fator de deslocamento for maior que o frame atual
            if((frame_atual-fatorDesloc)<= initialFrame-1)
            {
                frameResultante = initialFrame-1;

                //Retorna o video para o primeiro frame
                video->set(CV_CAP_PROP_POS_FRAMES,frameResultante);

                //Desabilita o botão voltar frames, pois está no primeiro frame do video
                ui->btVoltar->setEnabled(false);
            }

            //Se a subtração do fator de deslocamento do frame atual for maior do que zero, ou seja,
            //o fator de deslocamento for menor que o frame atual
            else
            {
                frameResultante = frame_atual-fatorDesloc;

                //Retorna o vídeo para esse valor
                video->set(CV_CAP_PROP_POS_FRAMES,frameResultante);
            }

//            if(dadosExperimento.tipoAnalise[2]==1)
//            {
//                tracking = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//                trackingBranco = cv::Mat::zeros( trackingBranco.size(), CV_8UC3 );

//                if(desenhaRota==true)
//                {
//                    cv::Scalar colorBranco = cv::Scalar( 255, 255, 255 );
//                    cv::Scalar colorVermelho = cv::Scalar( 255, 0, 0 );

//                    if((frameResultante+1)!=initialFrame)
//                    {
//                        for(int i=0;i<(frameResultante-(initialFrame-1));i++)
//                        {
//                            if(i==0)
//                            {
//                                cv::circle( trackingBranco, centroMassaAumentado[i], 0.5, colorBranco, -1, 8, 0 );
//                                cv::circle( tracking, centroMassaAumentado[i], 0.5, colorVermelho, -1, 8, 0 );
//                            }

//                            if(i!=0)
//                            {
//                                cv::line(trackingBranco,centroMassaAumentado[i-1],centroMassaAumentado[i],colorBranco,1,8,0);
//                                cv::line(tracking,centroMassaAumentado[i-1],centroMassaAumentado[i],colorVermelho,1,8,0);
//                            }
//                        }
//                    }
//                }
//            }
        }

        //Executa a função de processamento do video, já que o timer está parado
      processVideo();
    }
}

////Função de incrementar o fator de deslocamento de frames (chamada ao teclar "W")
//void Etografia::incrementaFatorDesloc()
//{
//    //Atualiza o fator de deslocamento de frames somando uma unidade a partir da informação
//    //contida na interface
//    fatorDesloc = ui->edtFatordesloc->value();
//    fatorDesloc++;
//    ui->edtFatordesloc->setValue(fatorDesloc);
//}

////Função de decrementar o fator de deslocamento de frames (chamada ao teclar "S")
//void Etografia::decrementaFatorDesloc()
//{
//    //Atualiza o fator de deslocamento de frames subtraindo uma unidade a partir da informação
//    //contida na interface
//    fatorDesloc = ui->edtFatordesloc->value();
//    fatorDesloc--;
//    ui->edtFatordesloc->setValue(fatorDesloc);
//}

////Função de atualizar o valor da velocidade de reprodução do vídeo (chamada ao mudar a posição do
////controle de velocidade da interface ou ao teclar "+" ou "-")
void Etografia::atualizaVelocidade()
{
    //Se foi acionada enquanto o vídeo está em reprodução
    if(ui->btPlay->isEnabled()==false && ui->btStop->isEnabled()==true)
    {
        //Se estiver permitido atualização da velocidade
        if(controleAtualizaVelocidade!=false)
        {
            //Calcula o fator de aceleração/desaceleração do vídeo a partir do controle disponível na
            //interface
            fatorVeloc= qPow(2,ui->SliderVelocidade->value());

            //Pausa o contador de controle de reprodução e processamento do video
            tmrTimer->stop();

            //Reinicia o contador de controle de reprodução e processamento do video com a nova velocidade.
            //Calcula o tempo de disparo igual ao tempo de reprodução de 1 frame (1000ms/fps) multiplicado
            //pelo novo fator de velocidade(aceleração/desaceleração) do video
            tmrTimer->start((1000/video_fps)*fatorVeloc);
        }
    }
}

////Função de incrementar o valor da velocidade de reprodução do video (chamada ao teclar "+")
//void Etografia::incrementaFatorVeloc()
//{
//    //Muda a posição do controle de velocidade da interface para uma posição a frente e atualiza
//    //a velocidade
//    ui->SliderVelocidade->setSliderPosition(ui->SliderVelocidade->value()+1);
//    atualizaVelocidade();
//}

////Função de decrementar o valor da velocidade de reprodução do video (chamada ao teclar "-")
//void Etografia::decrementaFatorVeloc()
//{
//    //Muda a posição do controle de velocidade da interface para uma posição atrás e atualiza
//    //a velocidade
//    ui->SliderVelocidade->setSliderPosition(ui->SliderVelocidade->value()-1);
//    atualizaVelocidade();
//}

//void Etografia::atualizaAnalise()
//{
//    if(dadosExperimento.tipoAnalise[2]==0)
//    {
//        cv::resize(frame,frameAumentado,frameAumentado.size(),video_propAumentada,video_propAumentada,cv::INTER_LANCZOS4);

//        QImage imgVideoAumentado((uchar*)frameAumentado.data, frameAumentado.cols, frameAumentado.rows, frameAumentado.step, QImage::Format_RGB888);
//        ui->panProcess->setScaledContents(false);
//        ui->panProcess->setPixmap(QPixmap::fromImage(imgVideoAumentado));
//    }

//    if(dadosExperimento.tipoAnalise[2]==1)
//    {
//        cv::Mat frameSubtracao;
//        cv::Mat frameSubtracao_gray;
//        cv::Mat frameLimiarizacao;
//        cv::Mat frameErosao;
//        cv::Mat frameSegmentacao;

//        if((frame_atual-(initialFrame-1)) >=centroMassa.count())
//        {
//            //------subtração do plano de fundo-------------------------------------------------------------------

//            frameSubtracao= abs(frameAnimal-frameBackground);

//            //---------------------------------------------------------------------------------------------------------
//            //------FrameLimiarizcao: Máscara do animal (animal preto e fundo branco) - threshold --------------------

//            cv::cvtColor( frameSubtracao, frameSubtracao_gray, CV_RGB2GRAY );
//            cv::threshold( frameSubtracao_gray, frameLimiarizacao, dadosExperimento.dadosCalibracao.threshold, 255,CV_THRESH_BINARY);

//            //---------------------------------------------------------------------------------------------------
//            //------FrameErosao: Erosão da máscara do animal------------------------------------------------------

//            cv::Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(2*dadosExperimento.dadosCalibracao.erosao+1,
//                                                    2*dadosExperimento.dadosCalibracao.erosao+1),
//                                                    cv::Point(dadosExperimento.dadosCalibracao.erosao,
//                                                    dadosExperimento.dadosCalibracao.erosao));
//            cv::erode( frameLimiarizacao, frameErosao, element );

//            //---------------------------------------------------------------------------------------------------
//            //------Encontra e desenha contornos da máscara------------------------------------------------------------------------------

//            cv::vector<cv::vector<cv::Point> > contours;
//            cv::vector<cv::Vec4i> hierarchy;
//            cv::Vec4f comprimento;
//            QList <cv::Point2f> comprimentoAnimal;
//            cv::RotatedRect caixaDelAnimal;

//            cv::findContours( frameErosao, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

//            cv::vector<cv::Point> c;
//            cv::Moments mu;
//            cv::Point2f mc;

//            if( contours.size() != 0 )
//            {
//                int idx = 0, largestComp = 0;
//                double maxArea = 0;

//                for( ; idx >= 0; idx = hierarchy[idx][0] )
//                {
//                    c = contours[idx];
//                    double area = fabs(cv::contourArea(cv::Mat(c)));
//                    if( area > maxArea )
//                    {
//                        maxArea = area;
//                        largestComp = idx;
//                    }
//                }

//                mu = moments( contours[largestComp], false );
//                mc = cv::Point2f( mu.m10/mu.m00 , mu.m01/mu.m00 );

//                centroMassa.insert(frame_atual-(initialFrame-1),mc);
//                centroMassaAumentado.insert(frame_atual-(initialFrame-1), mc*video_propAumentada);

//                cv::fitLine(cv::Mat(contours[largestComp]),comprimento,CV_DIST_L2,0,0.01,0.01);
//                int lefty = (-comprimento[2]*comprimento[1]/comprimento[0])+comprimento[3];
//                int righty = ((frameErosao.cols-comprimento[2])*comprimento[1]/comprimento[0])+comprimento[3];

//                caixaDelAnimal= cv::minAreaRect(cv::Mat(contours[largestComp]));
//                cv::Point2f vtx[4];
//                caixaDelAnimal.points(vtx);

//                for( int i = 0; i < 4; i++ )
//                {
//                    calculaIntersection(cv::Point(frameErosao.cols-1,righty),cv::Point(0,lefty),vtx[i],vtx[(i+1)%4]);
//                    if(intersection==true)
//                   comprimentoAnimal.insert(comprimentoAnimal.count(),pointIntersection);
//                }

//                if(comprimentoAnimal.count()!=2)
//                {
//                    int d;
//                    int dmax=0;
//                    cv::Point2f p1, p2;
//                    for(int i=0; i<3;i++)
//                    {
//                        for(int j=i+1;j<4;j++)
//                        {
//                            d = qSqrt( qPow( (comprimentoAnimal[i].x -comprimentoAnimal[j].x), 2 ) +
//                                       qPow( (comprimentoAnimal[i].y -comprimentoAnimal[j].y) ,2 ) );
//                            if(d>dmax)
//                            {
//                                dmax=d;
//                                p1=comprimentoAnimal[i];
//                                p2=comprimentoAnimal[j];
//                            }

//                        }
//                    }

//                    comprimentoAnimal.removeOne(p1);
//                    comprimentoAnimal.removeOne(p2);
//                }

//                linhaComprimentoAnimal.insert(frame_atual-(initialFrame-1),comprimentoAnimal);
//                caixaDelimitadoraAnimal.insert(frame_atual-(initialFrame-1), caixaDelAnimal);

//            }
//        }

//        //---------------------------------------------------------------------------------------------------
//        //------FrameSegmentação: segmentação final do animal (imagem completa + mascara do animal)----------

//        frameSegmentacao= frameAnimal;

//        //---------------------------------------------------------------------------------------------------
//        //------plotar na tela---------------------------------------------------------------------------------

//        cv::resize(frameSegmentacao,frameAumentado,frameAumentado.size(),video_propAumentada,video_propAumentada,cv::INTER_LANCZOS4);

//        if(controleTamanhoAumentado==true)
//        {
//            tracking = cv::Mat::zeros(frameAumentado.size(), CV_8UC3 );
//            trackingBranco = cv::Mat::zeros(frameAumentado.size(), CV_8UC3 );
//            controleTamanhoAumentado=false;
//        }

//        cv::Scalar colorBranco = cv::Scalar( 255, 255, 255 );
//        cv::Scalar colorVermelho = cv::Scalar( 255, 0, 0 );
//        cv::Scalar colorAzul = cv::Scalar( 0, 0, 255 );
//        cv::Scalar colorVerde = cv::Scalar( 0, 255, 0 );
//        cv::Scalar colorAmarelo = cv::Scalar( 255, 255, 0 );

//        if(desenhaRota==true)
//        {
//            if(frame_atual-(initialFrame-1)==0)
//            {
//                cv::circle( trackingBranco, centroMassaAumentado[frame_atual-(initialFrame-1)], 0.5, colorBranco, -1, 8, 0 );
//                cv::circle( tracking, centroMassaAumentado[frame_atual-(initialFrame-1)], 0.5, colorVermelho, -1, 8, 0 );
//            }

//            if(frame_atual-(initialFrame-1)!=0)
//            {
//                cv::line(trackingBranco,centroMassaAumentado[frame_atual-(initialFrame-1)-1],
//                        centroMassaAumentado[frame_atual-(initialFrame-1)],colorBranco,1,8,0);
//                cv::line(tracking,centroMassaAumentado[frame_atual-(initialFrame-1)-1],
//                        centroMassaAumentado[frame_atual-(initialFrame-1)],colorVermelho,1,8,0);
//            }
//        }

//        if(desenhaCentroMassa==true)
//        {
//            tracking = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//            trackingBranco = cv::Mat::zeros( trackingBranco.size(), CV_8UC3 );
//            cv::circle( trackingBranco, centroMassaAumentado[frame_atual-(initialFrame-1)], 3, colorBranco, -1, 8, 0 );
//            cv::circle( tracking, centroMassaAumentado[frame_atual-(initialFrame-1)], 3, colorVermelho, -1, 8, 0 );
//        }

//        if(controleAvancaVideo==false)
//        {
//            if(desenhaComprimentoAnimal==true)
//            {
//                linhaAnimal = cv::Mat::zeros(tracking.size(), CV_8UC3);
//                linhaAnimalBranco = cv::Mat::zeros(tracking.size(), CV_8UC3);
//                cv::line(linhaAnimalBranco,linhaComprimentoAnimal[frame_atual-(initialFrame-1)][0]*video_propAumentada,linhaComprimentoAnimal[frame_atual-(initialFrame-1)][1]*video_propAumentada,colorBranco,1);
//                cv::line(linhaAnimal,linhaComprimentoAnimal[frame_atual-(initialFrame-1)][0]*video_propAumentada,linhaComprimentoAnimal[frame_atual-(initialFrame-1)][1]*video_propAumentada,colorAzul,1);
//            }

//            if(desenhaCaixaAnimal==true)
//            {
//                caixaAnimal=cv::Mat::zeros(tracking.size(), CV_8UC3);
//                caixaAnimalBranco=cv::Mat::zeros(tracking.size(), CV_8UC3);
//                cv::Point2f vertice[4];
//                caixaDelimitadoraAnimal[frame_atual-(initialFrame-1)].points(vertice);
//                for( int i = 0; i < 4; i++ )
//                {
//                    cv::line(caixaAnimalBranco, vertice[i]*video_propAumentada, vertice[(i+1)%4]*video_propAumentada, colorBranco, 1);
//                    cv::line(caixaAnimal, vertice[i]*video_propAumentada, vertice[(i+1)%4]*video_propAumentada, colorVerde, 1);
//                }
//            }

//            if(desenhaCoordenadas==true)
//            {
//                coordenadas=cv::Mat::zeros(tracking.size(), CV_8UC3);
//                coordenadasBranco=cv::Mat::zeros(tracking.size(), CV_8UC3);
//                cv::line(coordenadasBranco,cv::Point(centroMassaAumentado[frame_atual-(initialFrame-1)].x,0),cv::Point(centroMassaAumentado[frame_atual-(initialFrame-1)].x, video_heigth*video_propAumentada),colorBranco,1);
//                cv::line(coordenadas,cv::Point(centroMassaAumentado[frame_atual-(initialFrame-1)].x,0),cv::Point(centroMassaAumentado[frame_atual-(initialFrame-1)].x, video_heigth*video_propAumentada),colorAmarelo,1);
//                cv::line(coordenadasBranco,cv::Point(0,centroMassaAumentado[frame_atual-(initialFrame-1)].y),cv::Point(video_width*video_propAumentada,centroMassaAumentado[frame_atual-(initialFrame-1)].y),colorBranco,1);
//                cv::line(coordenadas,cv::Point(0,centroMassaAumentado[frame_atual-(initialFrame-1)].y),cv::Point(video_width*video_propAumentada,centroMassaAumentado[frame_atual-(initialFrame-1)].y),colorAmarelo,1);
//            }

//            frameAumentado=frameAumentado-coordenadasBranco+coordenadas-linhaAnimalBranco+linhaAnimal-caixaAnimalBranco+caixaAnimal-trackingBranco+tracking;

//            QImage imgSegmentacao((uchar*)frameAumentado.data, frameAumentado.cols,frameAumentado.rows, frameAumentado.step, QImage::Format_RGB888);
//            ui->panProcess->setScaledContents(false);
//            ui->panProcess->setPixmap(QPixmap::fromImage(imgSegmentacao));
//        }
//    }
//}

//void Etografia::calculaIntersection(cv::Point2f o1, cv::Point2f p1, cv::Point2f o2, cv::Point2f p2)
//{
//    cv::Point2f x = o2 - o1;
//    cv::Point2f d1 = p1 - o1;
//    cv::Point2f d2 = p2 - o2;

//    float cross = d1.x*d2.y - d1.y*d2.x;
//    if (abs(cross) < /*EPS*/1e-8)
//    {
//        intersection=false;
//        return;
//    }

//    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
//    pointIntersection = o1 + d1 * t1;
//    intersection=true;
//}

//void Etografia::on_pushButtonInitialFrame_clicked()
//{
//    if(ui->labelFrames->text().toInt()<ui->spinBoxFinalFrame->value())
//    {
//        ui->spinBoxInitialFrame->setValue(ui->labelFrames->text().toInt());
//    }

//    else
//        QMessageBox::information(this,"Error","The initial frame must be lower than the final frame.");
//}

//void Etografia::on_pushButtonFinalFrame_clicked()
//{
//    if(ui->labelFrames->text().toInt()>ui->spinBoxInitialFrame->value())
//    {
//        ui->spinBoxFinalFrame->setValue(ui->labelFrames->text().toInt());
//    }

//    else
//        QMessageBox::information(this,"Error","The final frame must be greater than the initial frame.");
//}

//void Etografia::on_spinBoxInitialFrame_editingFinished()
//{
//    if(controleInitialFrame==true)
//    {
//        if(ui->spinBoxInitialFrame->value()>=ui->spinBoxFinalFrame->value())
//        {

//            controleInitialFrame=false;
//            QMessageBox::information(this,"Error","The initial frame must be lower than the final frame.");
//            ui->spinBoxInitialFrame->setValue(ui->spinBoxFinalFrame->value()-1);
//            controleInitialFrame=true;
//        }
//    }
//}

//void Etografia::on_spinBoxFinalFrame_editingFinished()
//{
//    if(controleFinalFrame==true)
//    {
//        if(ui->spinBoxFinalFrame->value()<=ui->spinBoxInitialFrame->value())
//        {

//            controleFinalFrame=false;
//            QMessageBox::information(this,"Error","The final frame must be greater than the initial frame.");
//            ui->spinBoxFinalFrame->setValue(ui->labelFrames->text().toInt());
//            ui->spinBoxFinalFrame->setValue(ui->spinBoxInitialFrame->value()+1);
//            controleFinalFrame=true;
//        }
//    }
//}

//void Etografia::on_pushButtonProcess_clicked()
//{
//    tmrTimer->stop();

//    processando=true;

//    ui->pushButtonProcess->setEnabled(false);
//    ui->pushButtonStop->setEnabled(true);

//    ui->pushButtonFinalFrame->setEnabled(false);
//    ui->pushButtonInitialFrame->setEnabled(false);
//    ui->spinBoxFinalFrame->setReadOnly(true);
//    ui->spinBoxInitialFrame->setReadOnly(true);

//    initialFrame=ui->spinBoxInitialFrame->value();
//    finalFrame=ui->spinBoxFinalFrame->value();

//    //Atualiza botões de controle de vídeo, possibilitando pausar o vídeo, avançar/voltar ou
//    //frame-a-frame
//    ui->btPlay->setEnabled(false);
//    ui->btStop->setEnabled(true);
//    ui->btAvancar->setEnabled(true);
//    ui->btVoltar->setEnabled(true);
//    ui->btVideo->setEnabled(false);

//    //Calcula o fator de aceleração/desaceleração do vídeo a partir do controle disponível na
//    //interface
//    fatorVeloc= qPow(2,ui->SliderVelocidade->value());

//    //Inicia o video do frame selecionado como inicial
//    video.set(CV_CAP_PROP_POS_FRAMES,initialFrame-1);

//    //Inicia o contador de controle de reprodução e processamento do video.
//    //Calcula o tempo de disparo igual ao tempo de reprodução de 1 frame (1000ms/fps) multiplicado
//    //pelo fator de velocidade(aceleração/desaceleração) do video
//    tmrTimer->start((1000/video_fps)*fatorVeloc);

//    controleAvancaVideo=false;

//    if(dadosExperimento.tipoAnalise[1]==1)
//    {
//        ui->groupBoxCategorias->setEnabled(true);
//        ui->groupBoxSujeitos->setEnabled(true);
//    }

//    if(dadosExperimento.tipoAnalise[2]==1)
//    {
//        ui->checkBoxRoute->setEnabled(true);
//        ui->checkBoxRoute->setChecked(true);
//        ui->checkBoxCenterMass->setEnabled(true);
//        ui->checkBoxCenterMass->setChecked(false);
//        ui->checkBoxBoundingBox->setEnabled(true);
//        ui->checkBoxBoundingBox->setChecked(true);
//        ui->checkBoxLengthAnimal->setEnabled(true);
//        ui->checkBoxLengthAnimal->setChecked(true);
//        ui->checkBoxCoordinates->setEnabled(true);
//        ui->checkBoxCoordinates->setChecked(true);

//        desenhaRota=true;
//        desenhaComprimentoAnimal=true;
//        desenhaCaixaAnimal=true;
//        desenhaCentroMassa=false;
//        desenhaCoordenadas=true;

//    }
//}

//void Etografia::on_pushButtonStop_clicked()
//{
//    tmrTimer->stop();

//    processando=false;

//    //Retorna o vídeo para o primeiro frame
//    video.set(CV_CAP_PROP_POS_FRAMES,initialFrame-1);
//    processVideo();

//    frame_atual=initialFrame-1;

//    ui->pushButtonProcess->setEnabled(true);
//    ui->pushButtonStop->setEnabled(false);

//    ui->pushButtonFinalFrame->setEnabled(true);
//    ui->pushButtonInitialFrame->setEnabled(true);
//    ui->spinBoxFinalFrame->setReadOnly(false);
//    ui->spinBoxInitialFrame->setReadOnly(false);

//    //Atualiza botões de controle de vídeo, possibilitando reproduzir o vídeo, avançar video
//    //frame-a-frame ou abrir novo vídeo
//    ui->btPlay->setEnabled(true);
//    ui->btStop->setEnabled(false);
//    ui->btAvancar->setEnabled(true);
//    ui->btVoltar->setEnabled(true);

//    //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
//    if(dadosExperimento.tipoAnalise[2]==1)
//        ui->btVideo->setEnabled(false);

//    //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
//    if(dadosExperimento.tipoAnalise[2]==0)
//        ui->btVideo->setEnabled(true);

//    ui->panProcess->setScaledContents(true);
//    QPixmap defaultProcessing(":/icons/fundoBranco.png");
//    ui->panProcess->setPixmap(defaultProcessing);

//    if(dadosExperimento.tipoAnalise[1]==1)
//    {
//        ui->groupBoxCategorias->setEnabled(false);
//        ui->groupBoxSujeitos->setEnabled(false);
//    }

//    if(dadosExperimento.tipoAnalise[2]==1)
//    {
//        ui->checkBoxRoute->setEnabled(false);
//        ui->checkBoxRoute->setChecked(false);
//        ui->checkBoxCenterMass->setEnabled(false);
//        ui->checkBoxCenterMass->setChecked(false);
//        ui->checkBoxBoundingBox->setEnabled(false);
//        ui->checkBoxBoundingBox->setChecked(false);
//        ui->checkBoxLengthAnimal->setEnabled(false);
//        ui->checkBoxLengthAnimal->setChecked(false);
//        ui->checkBoxCoordinates->setEnabled(false);
//        ui->checkBoxCoordinates->setChecked(false);

//        desenhaRota=false;
//        desenhaCentroMassa=false;
//        desenhaComprimentoAnimal=false;
//        desenhaCaixaAnimal=false;
//        desenhaCoordenadas=false;

//        tracking = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//        trackingBranco = cv::Mat::zeros( trackingBranco.size(), CV_8UC3 );
//        linhaAnimal = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//        linhaAnimalBranco = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//        caixaAnimal = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//        caixaAnimalBranco = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//        coordenadas = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//        coordenadasBranco = cv::Mat::zeros( tracking.size(), CV_8UC3 );

//        centroMassa.clear();
//        centroMassaAumentado.clear();
//        linhaComprimentoAnimal.clear();
//        caixaDelimitadoraAnimal.clear();
//    }
//}

//bool Etografia::eventFilter(QObject *target, QEvent *event)
//{
//    if (event->type() == QEvent::Resize)
//    {
//        if(redimensionar==true)
//        {
//            int w=this->size().width();
//            int h=this->size().height();
//            this->setMinimumSize(w,h);
//            this->setMaximumSize(w,h);
//            this->updateGeometry();
//            this->showMaximized();
//            widthPanProcess=ui->panProcess->size().width();
//            heightPanProcess=ui->panProcess->size().height();
//            redimensionar=false;

//            if(dadosExperimento.tipoAnalise[2]==1)
//                calculaProporcaoAumentada();
//        }
//    }
//}

//void Etografia::on_checkBoxRoute_stateChanged(int arg1)
//{
//    tracking = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//    trackingBranco = cv::Mat::zeros( trackingBranco.size(), CV_8UC3 );

//    if(arg1==0)
//    {
//        desenhaRota=false;
//    }

//    if(arg1==2)
//    {
//        desenhaRota=true;
//        ui->checkBoxCenterMass->setChecked(false);

//        cv::Scalar colorBranco = cv::Scalar( 255, 255, 255 );
//        cv::Scalar colorVermelho = cv::Scalar( 255, 0, 0 );

//        if(centroMassaAumentado.count()!=0)
//        {
//            for(int i=0;i<=frame_atual-(initialFrame-1);i++)
//            {
//                if(i==0)
//                {
//                    cv::circle( trackingBranco, centroMassaAumentado[i], 0.5, colorBranco, -1, 8, 0 );
//                    cv::circle( tracking, centroMassaAumentado[i], 0.5, colorVermelho, -1, 8, 0 );
//                }

//                if(i!=0)
//                {
//                    cv::line(trackingBranco,centroMassaAumentado[i-1],centroMassaAumentado[i],colorBranco,1,8,0);
//                    cv::line(tracking,centroMassaAumentado[i-1],centroMassaAumentado[i],colorVermelho,1,8,0);
//                }
//            }
//        }
//    }


//    if(ui->btPlay->isEnabled()==true)
//    {
//        video.set(CV_CAP_PROP_POS_FRAMES,frame_atual);
//        processVideo();
//    }
//}

//void Etografia::on_checkBoxCenterMass_stateChanged(int arg1)
//{
//    tracking = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//    trackingBranco = cv::Mat::zeros( trackingBranco.size(), CV_8UC3 );

//    if(arg1==0)
//    {
//        desenhaCentroMassa=false;
//    }

//    if(arg1==2)
//    {
//        desenhaCentroMassa=true;
//        ui->checkBoxRoute->setChecked(false);
//    }

//    if(ui->btPlay->isEnabled()==true)
//    {
//        video.set(CV_CAP_PROP_POS_FRAMES,frame_atual);
//        processVideo();
//    }
//}

//void Etografia::on_checkBoxBoundingBox_stateChanged(int arg1)
//{
//    caixaAnimal = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//    caixaAnimalBranco = cv::Mat::zeros( tracking.size(), CV_8UC3 );

//    if(arg1==0)
//    {
//        desenhaCaixaAnimal=false;
//    }

//    if(arg1==2)
//    {
//        desenhaCaixaAnimal=true;
//    }

//    if(ui->btPlay->isEnabled()==true)
//    {
//        video.set(CV_CAP_PROP_POS_FRAMES,frame_atual);
//        processVideo();
//    }
//}

//void Etografia::on_checkBoxLengthAnimal_stateChanged(int arg1)
//{
//    linhaAnimal = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//    linhaAnimalBranco = cv::Mat::zeros( tracking.size(), CV_8UC3 );

//    if(arg1==0)
//    {
//        desenhaComprimentoAnimal=false;
//    }

//    if(arg1==2)
//    {
//        desenhaComprimentoAnimal=true;
//    }

//    if(ui->btPlay->isEnabled()==true)
//    {
//        video.set(CV_CAP_PROP_POS_FRAMES,frame_atual);
//        processVideo();
//    }
//}

//void Etografia::on_checkBoxCoordinates_stateChanged(int arg1)
//{
//    coordenadas = cv::Mat::zeros( tracking.size(), CV_8UC3 );
//    coordenadasBranco = cv::Mat::zeros( tracking.size(), CV_8UC3 );

//    if(arg1==0)
//    {
//        desenhaCoordenadas=false;
//    }

//    if(arg1==2)
//    {
//        desenhaCoordenadas=true;
//    }

//    if(ui->btPlay->isEnabled()==true)
//    {
//        video.set(CV_CAP_PROP_POS_FRAMES,frame_atual);
//        processVideo();
//    }
//}

//faz funcionar os botões
void Etografia::setCatalago(){


   // QString valor = "4";
   // numeroDeBotoes= 6;

    QVBoxLayout *vlay = new QVBoxLayout(ui->widget);

 //  QPushButton *buttonList[numeroDeBotoes];


    QSignalMapper *mapperCategorias = new QSignalMapper(this);

    for(int j=0; j<numeroDeBotoes;j++){

        //criar um novo botão
        pb = new QPushButton();
      buttonList.append(pb);

        //buttonList[j]->setText(nomeCate[j]); //seta o nome
        buttonList[j]->setText(nomeCate[j]+ " (pronto)");
        buttonList[j]->setStyleSheet("background-color: green;""color: black;");

        clicado.push_back(false); //false funciona
        //fazendo o buffer
        saida.frameFinalBuffer.push_back(0); //coloca o valor de zero
        saida.pontosPostos.push_back(0);

        vlay->addWidget(buttonList[j]);

    //colocando os botões no layute faz aparecer na tela
    ui->widget->setLayout(vlay);

    //conecta o sinal de clicar no slot de mapa
    connect(buttonList[j], SIGNAL(clicked()), mapperCategorias, SLOT(map()));

    //colocar o botão no int
    mapperCategorias->setMapping(buttonList[j],j);


    }


    //conectando os botões criados
    //primeiro se mapeia
 //   QSignalMapper *mapperCategorias = new QSignalMapper(this);

   // connect(buttonList[numeroDeBotoes], SIGNAL(clicked()), mapperCategorias, SLOT(map()));
    //depois coneta os sinal de clique de cada botão no mapa
    //connect(button, SIGNAL(clicked()), mapperCategorias, SLOT(map()));
   // connect(button1, SIGNAL(clicked()), mapperCategorias, SLOT(map()));
   // connect(button2, SIGNAL(clicked()), mapperCategorias, SLOT(map()));

    //depois seta o index de cada botão
   // mapperCategorias->setMapping(button,0);
   // mapperCategorias->setMapping(button1,1);
   // mapperCategorias->setMapping(button2,2);

    //e depois conecta para aonde deve ser enviado o sinal do slotMapeado
    connect(mapperCategorias, SIGNAL(mapped(int)), this, SLOT(slotMapeado(int)));
    //cria os botões

}

void Etografia::slotMapeado(int a){


    //escolheSelecao=false; //true é auto
                          //false nested
 if(!escolheSelecao){ //se pode clicar mais de um botão por vez
    for(int i=0; i<numeroDeBotoes; i++){
    if(i==a){

      if(!clicado[i]){
       clicado[i]=true;
        buttonList[i]->setStyleSheet("background-color: yellow;""color: blue;");
        buttonList[i]->setText(nomeCate[i]+ " (Marcando)");

       //criando novo ponto apos clique
        saida.id.push_back(a);
        saida.frameComeco.push_back( frame_atual);
        //saida.frameFinalBuffer[i]=frame_atual;
        saida.framFim.push_back(finalFrame);
        saida.pontosPostos[i]=count;
        saida.quantidadeDepontos=count++;



      }else {
      clicado[i]=false;
         // for(int k=0;k<numeroDeBotoes;k++){
         buttonList[i]->setStyleSheet("background-color: green;""color: black;");
         buttonList[i]->setText(nomeCate[i]);
         //saida.frameComeco.push_back(frame_atual);
        //    }

         saida.frameFinalBuffer[i]=frame_atual;
         //if(botaoJaClicado){
         int valorSaida;
         valorSaida= saida.pontosPostos[i];
         saida.framFim[valorSaida]=frame_atual;
         //}
//        saida.frameFinalBuffer[i]=frame_atual;
      }
    }


    }
}else{ //se for apenas um botao por vez (auto esclusivo

     //encontra o botão precionado
     for(int i=0; i<numeroDeBotoes; i++){
     if(i==a){

         //diferencia se o botão esta clicado esta release
       if(!clicado[i]){
         clicado[i]=true;
         buttonList[i]->setStyleSheet("background-color: yellow;""color: black;");
         buttonList[i]->setText(nomeCate[i] +" (Marcando)");

         //dados
         saida.id.push_back(a);
         saida.frameComeco.push_back( frame_atual);
         //dados
         //saida.frameFinalBuffer[i]=frame_atual;
         saida.framFim.push_back(finalFrame);
         saida.pontosPostos[i]=count;
          count++;
          saida.quantidadeDepontos= count;

       }else {
        clicado[i]=false;
          // for(int k=0;k<numeroDeBotoes;k++){
          buttonList[i]->setStyleSheet("background-color: green;""color: black;");
          buttonList[i]->setText(nomeCate[i]);

          saida.frameFinalBuffer[i]=frame_atual;
          //if(botaoJaClicado){
          int valorSaida;
          valorSaida= saida.pontosPostos[i];
          //dados
          saida.framFim[valorSaida]=frame_atual;
          //dados

          }

       }

     }

      if(habilita){
          habilita=false;
          for(int k=0;k<numeroDeBotoes;k++){
              if(k==a){
                   //clicado[k]=true;
                    buttonList[k]->setStyleSheet("background-color: yellow;""color: black;");
                    buttonList[k]->setText(nomeCate[k] + " (Marcando)");
                    buttonList[k]->setEnabled(true);

              }else{
                  //clicado[k]=false;
                  buttonList[k]->setStyleSheet("background-color: red;""color: black;");
                  buttonList[k]->setText(nomeCate[k]+" (bloqueado)");
                  buttonList[k]->setEnabled(false);

              }
          }

       } else {
          habilita=true;
          for(int k=0;k<numeroDeBotoes;k++){
          //clicado[k]=true; /fase
           buttonList[k]->setStyleSheet("background-color: green;""color: black;");
           buttonList[k]->setText(nomeCate[k]+" (pronto)");
           buttonList[k]->setEnabled(true);
          }
      }





 }


//    if(escolheSelecao){
//        for(int i=0; i<numeroDeBotoes;i++){
//            if(!clicado[i]){
//            clicado[i]=true;
//            buttonList[i]->setText("block");
//            buttonList[i]->setEnabled(clicado[i]);
//            buttonList[i]->setStyleSheet("background-color: green;""color: blue;");

//            }else{
//                clicado[i]=false;
//                buttonList[i]->setText("block");
//                buttonList[i]->setEnabled(clicado[i]);
//                buttonList[i]->setStyleSheet("background-color: red;""color: blue;");

//            }


//        }


//    }

//    if(escolheSelecao) {
//    for(int i=0; i<numeroDeBotoes; i++){
//    if(i!=a){
//      buttonList[i]->setText("block");
//      buttonList[i]->setEnabled(habilita);
//      buttonList[i]->setStyleSheet("background-color: red;""color: blue;");
//         }


//      }
//   }else{


//    }

//    if(habilita){
//        habilita=false;
//    } else
//    {
//        habilita=true;
//    }




}

void Etografia::processVideoMorf()
{


    video -> read ( frame );
    dados->fraRecebido = frame;

    int frAtual= frame_atual;
    ui->labelFrames->setText(QString::number(frAtual));
    if((frame_atual==numFrameBack)&&(entrou12)){
    entrou12=false;
//    fundoFrame1=frame;
    video -> read ( fundoFrame1);
        dados->frameBackground= fundoFrame1;
        //dados->setBackground(fundoFrame1);
        dados->setCalibracao(60,0);

    }

    if(frame_atual>=numFrameProce){

       emit processe();

    }



    if(frame_atual==numeroFrameFinal){

        tmrTimer->stop();

        emit fimProce();


    }

    frame_atual= frame_atual+1;
    video->set(CV_CAP_PROP_POS_FRAMES,frame_atual);

}

void Etografia::recebeDesenho(QImage des1, bool desenhar, double centX, double centY, double poLongeX, double poLongey, double agulhX, double agulhy, double pRetaA1X, double pRetaA1Y, double pRetaA2X, double pRetaA2Y, double vtxX1, double vtxY1, double vtxX2, double vtxY2, double vtxX3, double vtxY3, double vtxX4, double vtxY4)
{

    widthPanProcess=ui->panProcess->size().width();
    heightPanProcess=ui->panProcess->size().height();

    // if(desenhar){

         QPainter painter(&des1); //o pintor vai pintar nesse inderesso
         //define qual sera a caneta que ira pintar
         QPen canetaVermelha;
         canetaVermelha.setWidth(8);
         canetaVermelha.setColor(Qt::red);

         painter.setPen(canetaVermelha);
         painter.drawPoint(centX,centY);

         QPen canetaPreta;
         canetaPreta.setWidth(10);
         canetaPreta.setColor(QColor(0,0,0));
         painter.setPen(canetaPreta);
         painter.drawPoint(agulhX,agulhy);

         QPen canetaAmarela;
         canetaAmarela.setWidth(16);
         canetaAmarela.setColor(QColor(0,255,255));
         painter.setPen(canetaAmarela);
         painter.drawPoint(poLongeX,poLongey);
         painter.drawPoint(pRetaA1X,pRetaA1Y);
         painter.drawPoint(pRetaA2X,pRetaA2Y);
         //desenha o centro de massa
         QPen canetaQuadro;
         canetaQuadro.setWidth(6);
         canetaQuadro.setColor(QColor(255,100,255));
         painter.setPen(canetaQuadro);
         painter.drawPoint(vtxX1,vtxY1);
         painter.drawPoint(vtxX2,vtxY2);
         painter.drawPoint(vtxX3,vtxY3);
          painter.drawPoint(vtxX4,vtxY4);

         QImage qimDisplay= des1.scaled(widthPanProcess,heightPanProcess,Qt::IgnoreAspectRatio);
         ui->panProcess->setPixmap(QPixmap::fromImage(qimDisplay));

}

void Etografia::recebeDadosMorfologicos(QImage imReceb, bool objetoEnco, double areaRecebida, double centroideX, double centroideY, float angObjeto, float tamObjet)
{

    ui->lblArea1->setText(QString::number(areaRecebida));

    if(objetoEnco){

        ui->lblObjetoEncont->setText("Objeto Encontrado");

    }else{

        ui->lblObjetoEncont->setText("Sem Objeto");

    }

//    centroObjeto.x=centroideX;
//    centroObjeto.y= centroideY;


    //ui->lblFigura2->setPixmap(QPixmap::fromImage(imReceb));


    ui->lblCenX->setText(QString::number(centroideX));
    ui->lblCenY->setText(QString::number(centroideY));

    ui->lblAnguloObjeto->setText(QString::number(angObjeto));
    ui->lblTaman->setText(QString::number(tamObjet));


//chaveObjeto



   if((!chaveObjeto)&&(contadorMorfo<numFrameProce)){ //numero do background
       //pega os valores iniciais
       //tem que garantir
       if(objetoEnco){
           reMorfo.area.push_back(areaRecebida);
           reMorfo.objetoEncontrado.push_back(objetoEnco);
           reMorfo.centroidX.push_back(centroideX);
           reMorfo.centroidY.push_back(centroideY);
           reMorfo.anguloObj.push_back(angObjeto);
           reMorfo.tamanhoObj.push_back(tamObjet);
           reMorfo.ruido.push_back(false);

         centroideXAntiga= centroideX;
         centroideYAntiga= centroideY;
           chaveObjeto= true;

       }else{ //se o objeto nao encotrado

           reMorfo.area.push_back(areaRecebida); //vai ser tudo zero
           reMorfo.objetoEncontrado.push_back(objetoEnco);
           reMorfo.centroidX.push_back(centroideX);
           reMorfo.centroidY.push_back(centroideY);
           reMorfo.anguloObj.push_back(angObjeto);
           reMorfo.tamanhoObj.push_back(tamObjet);
           reMorfo.ruido.push_back(false);

       }


        reCinema.varAngular.push_back(0);
        reCinema.varArea.push_back(0);
        reCinema.varCenX.push_back(0);
        reCinema.varCenY.push_back(0);
        reCinema.varDistancia.push_back(0);

   }else{

       if(objetoEnco){

           moduloVaria= qSqrt( qPow(centroideX-centroideXAntiga,2));

           if((maxVaria) > (moduloVaria) )
           {
               //se tudo ocorreu corretamente
                   reMorfo.area.push_back(areaRecebida);
                   reMorfo.objetoEncontrado.push_back(objetoEnco);
                   reMorfo.centroidX.push_back(centroideX);
                   reMorfo.centroidY.push_back(centroideY);
                   reMorfo.anguloObj.push_back(angObjeto);
                   reMorfo.tamanhoObj.push_back(tamObjet);

                 centroideXAntiga= centroideX;
                 centroideYAntiga= centroideY;
                reMorfo.ruido.push_back(false);


                reCinema.varAngular.push_back(angObjeto-reMorfo.anguloObj[contadorMorfo-1]);
                reCinema.varArea.push_back(areaRecebida-reMorfo.area[contadorMorfo-1]);
                reCinema.varCenX.push_back(centroideX-reMorfo.centroidX[contadorMorfo-1]);
                reCinema.varCenY.push_back(centroideY-reMorfo.centroidY[contadorMorfo-1]);

                double dis;
                dis=qSqrt( qPow(reCinema.varCenY[contadorMorfo],2)+ qPow(reCinema.varCenX[contadorMorfo],2)  );

                reCinema.varDistancia.push_back(dis);


           }else{
               //se aconteceu o ruido
               //ele coloca os pontos anteriores
               reMorfo.area.push_back(reMorfo.area[contadorMorfo-1]);
               reMorfo.objetoEncontrado.push_back(reMorfo.objetoEncontrado[contadorMorfo-1]);
               reMorfo.centroidX.push_back(reMorfo.centroidX[contadorMorfo-1]);
               reMorfo.centroidY.push_back(reMorfo.centroidY[contadorMorfo-1]);
               reMorfo.anguloObj.push_back(reMorfo.anguloObj[contadorMorfo-1]);
               reMorfo.tamanhoObj.push_back(reMorfo.tamanhoObj[contadorMorfo-1]);

               reMorfo.ruido.push_back(true);

               reCinema.varAngular.push_back(0);
               reCinema.varArea.push_back(0);
               reCinema.varCenX.push_back(0);
               reCinema.varCenY.push_back(0);
               reCinema.varDistancia.push_back(0);

           }//fim teste de ruido


       }else{ //se nao encontrado o objeto
           
           reMorfo.area.push_back(reMorfo.area[contadorMorfo-1]);
           reMorfo.objetoEncontrado.push_back(reMorfo.objetoEncontrado[contadorMorfo-1]);
           reMorfo.centroidX.push_back(reMorfo.centroidX[contadorMorfo-1]);
           reMorfo.centroidY.push_back(reMorfo.centroidY[contadorMorfo-1]);
           reMorfo.anguloObj.push_back(reMorfo.anguloObj[contadorMorfo-1]);
           reMorfo.tamanhoObj.push_back(reMorfo.tamanhoObj[contadorMorfo-1]);



           reMorfo.ruido.push_back(true);

           reCinema.varAngular.push_back(0);
           reCinema.varArea.push_back(0);
           reCinema.varCenX.push_back(0);
           reCinema.varCenY.push_back(0);
           reCinema.varDistancia.push_back(0);

       }






   } //fim contador zero




contadorMorfo++;



}



void Etografia::geraValoresCinematicos()
{



}

void Etografia::setInicioVideo(QString nomeOpencvVideo, int frameIncial1, int frameBack,  int frameProcessamento,int frameFinal1){


    initialFrame=frameIncial1; //fazendo a compatibilidade de versao
    finalFrame=frameFinal1; //fazendo a compatibilidade
    numFrameBack= frameBack;
    numFrameProce= frameProcessamento;


    //Captura string referente ao diretório do vídeo delecionado na caixa de diálogo
    //Tipos de arquivo limotados para: .avi, .mp4, .mpeg, .mpg, .wmv, .flv, .mkv
    fonteVideo=nomeOpencvVideo;

    //Se a string capturada for vazia (casos: fechar ou cancelar janela de diálogo), sai da função
    //abrir video e não executa os códicos a seguir
    if(fonteVideo=="")
    {
        return;
    }

    //Para contador se o mesmo estiver rodando (ou seja, se estivaer no meio da execução de um vídeo)
   // if(tmrTimer->isActive()==true)
   // {
       // tmrTimer->stop();
   // }

    //Inativa os parametros do processamento
    //ui->stackedWidgetProcessingParameters->setCurrentIndex(0);

    //Seleciona imagens padrão para a tela de video (imagem que aparece antes de abrir um video)
    QPixmap defaultVideo(":/icons/video.png");
    ui->panTela->setPixmap(defaultVideo);

    ui->panProcess->setScaledContents(true);
    QPixmap defaultProcessing(":/icons/fundoBranco.png");
    ui->panProcess->setPixmap(defaultProcessing);

    //Abre video selecionado
    abreArquivoVideo(fonteVideo);
    setFrameInicialFinal(initialFrame,finalFrame);


    //botão inicialzar


}

void Etografia::setCalibracao(int tres, int eros, double escala)
{

}

void Etografia::setAutoNested(bool nested){


    escolheSelecao=nested; //true auto= só um botão por vez




}

void Etografia::setChavesPrograma(bool chaveEtogr, bool chaveProces)
{
    chaveEtog = chaveEtogr;
    chaveProce= chaveProces;

}

void Etografia::setInfoCatalago(std::vector<QString> nomeCategoria, std::vector<QString> atalho, int quantidadeDeDados){


     numeroDeBotoes= quantidadeDeDados;

     nomeCate=nomeCategoria;








}

void Etografia::setTratamentoRuido(double origX, double origY, double width, double height, bool chMove,
                                   double tamanhoMax)
{

    maxVaria=tamanhoMax; //para maxima variação

    jaInte.origX=origX;
    jaInte.origY=origY;
    jaInte.width=width;
    jaInte.height=height;
    jaInte.chMobile=chMove;


   // dados->setParametrosVideo(video_width,video_heigth);
    //dados->confiCameraVir(origX,origY,width,height,chMove);

    //paramentros para janela de interesse

    //origem
    //height
    //width



}


void Etografia::setFrameInicialFinal(int frameInicial2, int frameFinal2){


    frame_atual= (double) frameInicial2;
    numeroFrameFinal =  (double) frameFinal2;

    //    //Se o botão de avançar frame estiver habilitado (se o video não estiver no último frame)
    //    if(ui->btAvancar->isEnabled()==true)
    //    {
    //        //Habilita os parametros do processamento
    //        //ui->stackedWidgetProcessingParameters->setCurrentIndex(1);

    //        //Atualiza botões de controle de vídeo, possibilitando reproduzir o vídeo ou
    //        //voltar em frames anteriores
            ui->btStop->setEnabled(false);
            ui->btPlay->setEnabled(true);
            ui->btVoltar->setEnabled(true);

            video->set(CV_CAP_PROP_POS_FRAMES,frameInicial2);

            processVideo();



}

void Etografia::termina()
{
    ui->btPlay->setEnabled(false);
    ui->btStop->setEnabled(false);
    ui->btAvancar->setEnabled(false);
    ui->btVoltar->setEnabled(false);

    //Se foi selecionado análise com rastreamento, desabilita botão de abrir novo video
   // if(dadosExperimento.tipoAnalise[2]==1)
   //     ui->btVideo->setEnabled(false);

    //Se foi selecionado análise com rastreamento, habilita botão de abrir novo video
  //  if(dadosExperimento.tipoAnalise[2]==0)
   //     ui->btVideo->setEnabled(true);

    //ui->pushButtonProcess->setEnabled(false);
   // ui->pushButtonStop->setEnabled(false);

    ui->checkBoxRoute->setEnabled(false);
    ui->checkBoxRoute->setChecked(false);
    ui->checkBoxCenterMass->setEnabled(false);
    ui->checkBoxCenterMass->setChecked(false);
    ui->checkBoxBoundingBox->setEnabled(false);
    ui->checkBoxBoundingBox->setChecked(false);
    ui->checkBoxLengthAnimal->setEnabled(false);
    ui->checkBoxLengthAnimal->setChecked(false);
    ui->checkBoxCoordinates->setEnabled(false);
    ui->checkBoxCoordinates->setChecked(false);
    //ui->groupBoxSujeitos->setEnabled(false);
    ui->groupBoxCategorias->setEnabled(false);

    processando=false;
    QMessageBox::information(this,"Finish","Processing was completed successfully! Você "
                                           "ira para gravação dos dados Etograficos");

    emit enviandoDadosEtograficos();

}




//void Etografia::on_labelFramesTotal_linkActivated(const QString &link)
//{

//}

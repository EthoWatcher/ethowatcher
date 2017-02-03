#include "estruturas.h"
//#include <iostream.h>

//Categoria

Categoria::Categoria(){
        this->setDescricao("");
        this->setCodigo("");
        this->setNome("");
}

Categoria::~Categoria(){}

QString      Categoria::getDescricao(){
        return  this->descricao;
}

QString      Categoria::getCodigo(){
        return  this->codigo;
}

QString      Categoria::getNome(){
        return  this->nome;
}

void            Categoria::setDescricao(QString elem){
        this->descricao =       elem;
}

void            Categoria::setCodigo(QString elem){
        this->codigo    =       elem;
}

void            Categoria::setNome(QString elem){
        this->nome      =       elem;
}

//---------------------------------------------------------------------------------------------------------------

//Ocorrencia Categoria

ocorrenciaCategoria::ocorrenciaCategoria(){
        this->setCategoria(NULL);
        this->setFrameInicio(0);
        this->setFrameFim(0);
}

ocorrenciaCategoria::~ocorrenciaCategoria(){}

Categoria*              ocorrenciaCategoria::getCategoria(){
        return  this->categoria;
}

int                     ocorrenciaCategoria::getFrameInicio(){
        return  this->frameInicio;
}

int                     ocorrenciaCategoria::getFrameFim(){
        return  this->frameFim;
}

void                    ocorrenciaCategoria::setCategoria(Categoria *elem){
        this->categoria =       elem;
}

void                    ocorrenciaCategoria::setFrameInicio(int  elem){
        this->frameInicio    =       elem;
}

void                    ocorrenciaCategoria::setFrameFim(int  elem){
        this->frameFim    =       elem;
}

void                    ocorrenciaCategoria::setDuracao(float    drc){
        this->duracao   =       drc;
}

float                   ocorrenciaCategoria::getDuracao(){
        return  this->duracao;
}

float  ocorrenciaCategoria::getLatencia(){
        return  this->latencia;
}

void   ocorrenciaCategoria::setLatencia(float lat){
        this->latencia  =       lat;
}

//---------------------------------------------------------------------------------------------------------------

//lista de categorias

listaCategorias::listaCategorias(){
        this->setProx(NULL);
        this->setElemento(NULL);
}

listaCategorias::~listaCategorias(){}

void                    listaCategorias::setProx(listaCategorias*  elem){
        this->prox    =       elem;
}

listaCategorias*       listaCategorias::getProx(){
        return  this->prox;
}

void    listaCategorias::setElemento(ocorrenciaCategoria *ocorCat){
        this->elemento  =       ocorCat;
}

ocorrenciaCategoria*            listaCategorias::getElemento(){
        return        this->elemento;
}

//---------------------------------------------------------------------------------------------------------------

//Sujeito

sujeito::sujeito(){
        this->setCodigo("");
        this->setDescricao("");
        this->setNome("");
}

sujeito::~sujeito(){}

QString      sujeito::getCodigo       (){
        return  this->codigo;
}

QString      sujeito::getNome         (){
        return  this->nome;
}

QString      sujeito::getDescricao    (){
        return  this->descricao;
}

void            sujeito::setCodigo       (QString    elem){
        this->codigo    =       elem;
}

void            sujeito::setNome         (QString    elem){
        this->nome      =       elem;
}

void            sujeito::setDescricao    (QString    elem){
        this->descricao =       elem;
}

//---------------------------------------------------------------------------------------------------------------

//Ocorrencia Sujeito

ocorrenciaSujeito::ocorrenciaSujeito(){
        this->frameInicio       =       0;
        this->setCategoriasOcorridas(NULL);
        this->setSujeitoOcorrencia(NULL);
}

ocorrenciaSujeito::~ocorrenciaSujeito(){}

void    ocorrenciaSujeito::setSujeitoOcorrencia(sujeito        *elem){
        this->sujeitoOcorrencia         =       elem;
}

void    ocorrenciaSujeito::setCategoriasOcorridas(listaCategorias      *elem){
        this->categoriasOcorridas       =       elem;
}

sujeito*        ocorrenciaSujeito::getSujeitoOcorrencia(){
        return  this->sujeitoOcorrencia;
}

listaCategorias*        ocorrenciaSujeito::getCategoriasOcorridas(){
        return  this->categoriasOcorridas;
}

void    ocorrenciaSujeito::setFrameInicio(int      frame){
        this->frameInicio       =       frame;
}

void    ocorrenciaSujeito::adicionaCategoria(ocorrenciaCategoria* ocorCat){

        listaCategorias *tmpLista        = this->categoriasOcorridas;

        if (tmpLista!=NULL){
                while(tmpLista->getProx()!=NULL){
                        tmpLista        =       tmpLista->getProx();
                }

                tmpLista->setProx(new listaCategorias());
                tmpLista->getProx()->setElemento(ocorCat);
        }else{
                categoriasOcorridas     =       new     listaCategorias();
                categoriasOcorridas->setElemento(ocorCat);
        }
}

ocorrenciaCategoria*     ocorrenciaSujeito::get1OcorrenciaCategoriaSemFim(Categoria* catPesquisa){

        listaCategorias *listaTmp       =     categoriasOcorridas;

        if(categoriasOcorridas==NULL)
                return  NULL;
        else{
                while(listaTmp!=NULL){
                        if(listaTmp->getElemento()->getCategoria()==catPesquisa){
                                if(listaTmp->getElemento()->getFrameFim()<=0){
                                        return  listaTmp->getElemento();
                                }
                        }
                        listaTmp        =       listaTmp->getProx();
                }
        }
        return  NULL;
}

ocorrenciaCategoria*     ocorrenciaSujeito::getUltimaCategoriaOcorrida(){
        listaCategorias *listaTmp       =     categoriasOcorridas;

        if(categoriasOcorridas==NULL)
                return  NULL;
        else{
                while(listaTmp->getProx()!=NULL){

                        listaTmp        =       listaTmp->getProx();
                }
                return  listaTmp->getElemento();
        }

}

//---------------------------------------------------------------------------------------------------------------

//Categorias Catalogo

categoriasCatalogo::categoriasCatalogo(){
        this->setElemento(NULL);
        this->setProx(NULL);
}

categoriasCatalogo::~categoriasCatalogo(){}

int      categoriasCatalogo::getPosicaoElemento(){
        return  this->posicaoElemento;
}

Categoria*      categoriasCatalogo::getElemento(){
        return  this->elemento;
}

categoriasCatalogo      *categoriasCatalogo::getProx(){
        return  this->prox;
}

void    categoriasCatalogo::setElemento(Categoria *elemento){
        this->elemento  =       elemento;
}

void    categoriasCatalogo::setPosicaoElemento(int      pos){
        this->posicaoElemento   =       pos;
}

void    categoriasCatalogo::setProx(categoriasCatalogo  *proxCat){
        this->prox      =       proxCat;
}

//---------------------------------------------------------------------------------------------------------------

//sujeitos Catalogo

sujeitosCatalogo::sujeitosCatalogo(){
        this->setProx(NULL);
        this->setElemento(NULL);
}

sujeitosCatalogo::~sujeitosCatalogo(){}

int      sujeitosCatalogo::getPosicaoElemento(){
        return  this->posicaoElemento;
}

sujeitosCatalogo*    sujeitosCatalogo::getProx(){
        return  this->prox;
}

sujeito*        sujeitosCatalogo::getElemento(){
        return  this->elemento;
}

void    sujeitosCatalogo::setElemento(sujeito* suj){
        this->elemento  =       suj;
}

void    sujeitosCatalogo::setPosicaoElemento(int        pos){
        this->posicaoElemento   =       pos;
}

void    sujeitosCatalogo::setProx(sujeitosCatalogo*      proxSuj)
{
        this->prox      =       proxSuj;
}

//---------------------------------------------------------------------------------------------------------------

//Catálogo

catalogo::catalogo(){
        this->sujeitos          =       NULL;
        this->categorias        =       NULL;
        this->nroCategorias     =       0;
        this->nroSujeitos       =       0;
}

catalogo::~catalogo(){}

int     catalogo::getNroSujeitos(){
        return  this->nroSujeitos;
}

int     catalogo::getNroCategorias(){
        return  this->nroCategorias;
}

void    catalogo::adicionaSujeito       (sujeito *suj){
        sujeitosCatalogo        *ponteiroTmpSujeitos;

        if(sujeitos==NULL){

                this->sujeitos  =       new     sujeitosCatalogo();
                this->sujeitos->setElemento(suj);
                this->sujeitos->setPosicaoElemento(1);
        }else{

                ponteiroTmpSujeitos     =       sujeitos;

                while(ponteiroTmpSujeitos->getProx()!=NULL){
                        ponteiroTmpSujeitos     =       ponteiroTmpSujeitos->getProx();
                }

                ponteiroTmpSujeitos->setProx(new sujeitosCatalogo());
                ponteiroTmpSujeitos->getProx()->setElemento(suj);
                ponteiroTmpSujeitos->getProx()->setPosicaoElemento(ponteiroTmpSujeitos->getPosicaoElemento()+1);
        }

        nroSujeitos     =       nroSujeitos     +1;

}

void    catalogo::removeSujeito         (sujeito *suj){
        //removendo sujeito
        sujeitosCatalogo *atual, *ptApagar;

        if(sujeitos!=NULL){//verifica se o nro de sujeitos está vazio

                //se nao encontrou aki
                if(sujeitos->getElemento()->getCodigo()==suj->getCodigo()){
                        ptApagar        =       sujeitos;
                        sujeitos        =       sujeitos->getProx();
                        delete          ptApagar;

                }
                else{//realiza do/while de busca

                        atual    =       sujeitos;

                        while(atual->getProx()!=NULL){

                                //se o proximo elemento do ponto atual for o elemento procurado
                                if(atual->getProx()->getElemento()->getCodigo()==suj->getCodigo()){
                                        //verifica se o prox. elemento é o ultimo elemento da lista
                                        if(atual->getProx()->getProx()!=NULL){//se nao

                                                ptApagar      =       atual->getProx();

                                                atual->setProx(atual->getProx()->getProx());

                                                delete ptApagar;
                                        }else{
                                                //se for
                                                delete  atual->getProx();
                                                atual->setProx(NULL);
                                        }
                                        break;
                                }
                                atual    =       atual->getProx();


                        };
                }
                this->nroSujeitos--;
        }
}

void    catalogo::adicionaCategoria(Categoria *cat){

        categoriasCatalogo        *ponteiroTmpCategorias;

        if(categorias==NULL){

                this->categorias  =       new     categoriasCatalogo();
                this->categorias->setElemento(cat);
                this->categorias->setPosicaoElemento(1);
        }else{

                ponteiroTmpCategorias     =       categorias;

                while(ponteiroTmpCategorias->getProx()!=NULL){
                        ponteiroTmpCategorias     =       ponteiroTmpCategorias->getProx();
                }

                ponteiroTmpCategorias->setProx(new categoriasCatalogo());
                ponteiroTmpCategorias->getProx()->setElemento(cat);
                ponteiroTmpCategorias->getProx()->setPosicaoElemento(ponteiroTmpCategorias->getPosicaoElemento()+1);
        }
        nroCategorias   =       nroCategorias   +       1;
}

void    catalogo::removeCategoria(Categoria       *categExc){

       //removendo categoria
        categoriasCatalogo *atual, *ptApagar;

        if(categorias!=NULL){//verifica se o nro de sujeitos está vazio

                //se nao encontrou aki
                if(categorias->getElemento()->getCodigo()==categExc->getCodigo()){
                        ptApagar                =       categorias;
                        categorias              =       categorias->getProx();
                        delete          ptApagar;

                }
                else{//realiza do/while de busca

                        atual    =       categorias;

                        while(atual->getProx()!=NULL){

                                //se o proximo elemento do ponto atual for o elemento procurado
                                if(atual->getProx()->getElemento()->getCodigo()==categExc->getCodigo()){
                                        //verifica se o prox. elemento é o ultimo elemento da lista
                                        if(atual->getProx()->getProx()!=NULL){//se nao

                                                ptApagar      =       atual->getProx();

                                                atual->setProx(atual->getProx()->getProx());

                                                delete ptApagar;
                                        }else{
                                                //se for
                                                delete  atual->getProx();
                                                atual->setProx(NULL);
                                        }
                                        break;
                                }
                                atual    =       atual->getProx();


                        };
                }
                this->nroCategorias--;
        }        
}

categoriasCatalogo*      catalogo::getCategoriasCatalogo(){
        return  categorias;
}

sujeitosCatalogo*        catalogo::getSujeitosCatalogo(){
        return  sujeitos;
}

//---------------------------------------------------------------------------------------------------------------

//Lista Sujeito

listaSujeitos::listaSujeitos(){
        this->elemento  =       NULL;
        this->prox      =       NULL;
}

listaSujeitos::~listaSujeitos(){}

ocorrenciaSujeito*      listaSujeitos::getElemento(){
        return  this->elemento;
}

void                    listaSujeitos::setElemento(ocorrenciaSujeito* ocorSuj){
        this->elemento  =       ocorSuj;
}

listaSujeitos*          listaSujeitos::getProx(){
        return  this->prox;
}

void                    listaSujeitos::setProx(listaSujeitos* proxList){
        prox    =       proxList;
}

//---------------------------------------------------------------------------------------------------------------

//destrutor de Estruturas

destrutorEstruturas::destrutorEstruturas(){}

destrutorEstruturas::~destrutorEstruturas(){}

template<class t>
void    destrutorEstruturas::liberaMemoriaListaGenerica(t         *param){

        t*     ptTmp;//ponteiro temporario

        while(param!=NULL){
                ptTmp   =       param;
                delete  ptTmp->getElemento();
                param   =       param->getProx();
                delete  ptTmp;

        }

}

void    destrutorEstruturas::liberaMemoriaListaCategorias(categoriasCatalogo             *param){

        liberaMemoriaListaGenerica(param);
}

void    destrutorEstruturas::liberaMemoriaListaSujeitos(sujeitosCatalogo                *param){

        liberaMemoriaListaGenerica(param);        
}

void    destrutorEstruturas::liberaMemoriaCatalogo(catalogo                             *param){

        if(param!=NULL){
                liberaMemoriaListaGenerica(param->getSujeitosCatalogo());
                liberaMemoriaListaGenerica(param->getCategoriasCatalogo());
        }

        delete  param;
}

void    destrutorEstruturas::liberaMemoriaListaOcorrenciaCategorias(listaCategorias     *param){

        liberaMemoriaListaGenerica(param);
}

void    destrutorEstruturas::liberaMemoriaListaOcorrenciaSujeitos(listaSujeitos         *param){

        listaSujeitos*     ptTmp;//ponteiro temporario

        while(param!=NULL){

                ptTmp   =       param;

                liberaMemoriaListaOcorrenciaCategorias(ptTmp->getElemento()->getCategoriasOcorridas());

                delete  ptTmp->getElemento();

                param   =       param->getProx();

                delete  ptTmp;


        }


}

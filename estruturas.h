#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

//#include "TEspiao2.h"
//#include <fstream.h>
#include <QString>

//-------------------------------------------------------------------------------------------------------------------

//estrutura de uma categoria do catalogo
class Categoria{
        private:
                QString      descricao;
                QString      codigo;
                QString      nome;
        public:
                Categoria();
                ~Categoria();
                QString      getDescricao();
                QString      getCodigo();
                QString      getNome();
                void            setDescricao(QString elem);
                void            setCodigo(QString elem);
                void            setNome(QString elem);
};

//-------------------------------------------------------------------------------------------------------------------

//estrutura de um sujeito do catalogo
class sujeito{
        private:
                QString      codigo;
                QString      nome;
                QString      descricao;
        public:
                sujeito();
                ~sujeito();
                QString      getCodigo       ();
                QString      getNome         ();
                QString      getDescricao    ();
                void            setCodigo       (QString);
                void            setNome         (QString);
                void            setDescricao    (QString);
};

//-------------------------------------------------------------------------------------------------------------------

class   categoriasCatalogo{
        private:
                Categoria               *elemento;
                categoriasCatalogo      *prox;
                int                     posicaoElemento;
        public:
                categoriasCatalogo();
                ~categoriasCatalogo();
                int                     getPosicaoElemento();
                void                    setPosicaoElemento(int);
                void                    setElemento(Categoria*);
                Categoria*              getElemento();
                void                    setProx(categoriasCatalogo*);
                categoriasCatalogo*     getProx();
};

//-------------------------------------------------------------------------------------------------------------------

class   sujeitosCatalogo{
        private:
                sujeito                 *elemento;
                sujeitosCatalogo        *prox;
                int                     posicaoElemento;
        public:
                sujeitosCatalogo();
                ~sujeitosCatalogo();
                int                     getPosicaoElemento();
                void                    setPosicaoElemento(int);
                void                    setElemento(sujeito*);
                sujeito                 *getElemento();
                void                    setProx(sujeitosCatalogo*);
                sujeitosCatalogo*       getProx();
};

//-------------------------------------------------------------------------------------------------------------------

class catalogo{
        private:
                //... lista sujeitos;
                sujeitosCatalogo        *sujeitos;
                int                     nroSujeitos;
                //... lista categorias;
                categoriasCatalogo      *categorias;
                int                     nroCategorias;
        public:
                catalogo();
                ~catalogo();
                int                     getNroSujeitos();
                int                     getNroCategorias();
                void                    adicionaSujeito(sujeito *suj);
                void                    removeSujeito(sujeito *suj);
                void                    adicionaCategoria(Categoria *cat);
                void                    removeCategoria(Categoria       *cat);
                categoriasCatalogo*     getCategoriasCatalogo();
                sujeitosCatalogo*       getSujeitosCatalogo();
};

//-------------------------------------------------------------------------------------------------------------------

//estrutura para guardar uma categoria e seu inicio e fim num experimento
class ocorrenciaCategoria{
        private:
                Categoria               *categoria;
                int                     frameInicio, frameFim;
                float                   duracao;
                float                   latencia;
        public:
                ocorrenciaCategoria();
                ~ocorrenciaCategoria();
                Categoria*              getCategoria();

                int                     getFrameInicio();
                int                     getFrameFim();

                void                    setCategoria(Categoria*);

                void                    setFrameInicio(int);
                void                    setFrameFim(int);

                void                    setDuracao(float);
                float                   getDuracao();

                float                   getLatencia();
                void                    setLatencia(float);

};

//-------------------------------------------------------------------------------------------------------------------

//estrutura para guardar as diversas categorias que ocorrem num experimento
class listaCategorias{
        private:
                listaCategorias                 *prox;
                ocorrenciaCategoria             *elemento;
        public:
                listaCategorias();
                ~listaCategorias();
                void                            setProx(listaCategorias*);
                void                            setElemento(ocorrenciaCategoria*);
                listaCategorias*                getProx();
                ocorrenciaCategoria*            getElemento();

};

//-------------------------------------------------------------------------------------------------------------------

//estrutura que mantem a ocorrencia dos sujeitos em um catalogo
class   ocorrenciaSujeito{
        private:
               sujeito          *sujeitoOcorrencia;
               int              frameInicio;
               listaCategorias  *categoriasOcorridas;
        public:
               ocorrenciaSujeito();
               ~ocorrenciaSujeito();
               void                     setSujeitoOcorrencia(sujeito*);
               void                     setCategoriasOcorridas(listaCategorias*);
               void                     setFrameInicio(int      frame);
               sujeito*                 getSujeitoOcorrencia();
               listaCategorias*         getCategoriasOcorridas();
               void                     adicionaCategoria(ocorrenciaCategoria*);
               ocorrenciaCategoria*     get1OcorrenciaCategoriaSemFim(Categoria*);
               ocorrenciaCategoria*     getUltimaCategoriaOcorrida();
};

//-------------------------------------------------------------------------------------------------------------------

class   listaSujeitos{
        private:
                ocorrenciaSujeito       *elemento;
                listaSujeitos           *prox;
        public:
                listaSujeitos();
                ~listaSujeitos();
                ocorrenciaSujeito*      getElemento();
                void                    setElemento(ocorrenciaSujeito*);
                listaSujeitos*          getProx();
                void                    setProx(listaSujeitos*);
};

//-------------------------------------------------------------------------------------------------------------------

class destrutorEstruturas{
        private:

        public:
                destrutorEstruturas();
                ~destrutorEstruturas();
                template<class t>
                void    liberaMemoriaListaGenerica(t*);
                void    liberaMemoriaListaCategorias(categoriasCatalogo*);
                void    liberaMemoriaListaSujeitos(sujeitosCatalogo*);
                void    liberaMemoriaCatalogo(catalogo*);
                void    liberaMemoriaListaOcorrenciaCategorias(listaCategorias*);
                void    liberaMemoriaListaOcorrenciaSujeitos(listaSujeitos*);

};

#endif // ESTRUTURAS_H

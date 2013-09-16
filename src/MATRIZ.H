#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*       1.00   hg e nf  15/09/2013 Adaptação do módulo para manipular matrizes
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar matrizes.
*     A matriz possui uma cabeça que contém uma referência para a raíz da
*     matriz e outra para um nó corrente da matriz.
*     O modulo permite a manipulação de múltiplas matrizes, porém as funções
*     só manipulam uma matriz de cada vez.
*     Ao iniciar a execução do programa não existe matriz.
*     A matriz poderá estar vazia. Neste caso a origem e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a matriz estiver vazia.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

#include "LISTA.H"

typedef struct tgMatriz MAT_tpMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetNaoCriouOrigem = 1 ,
               /* Não criou nó origem */

         MAT_CondRetNaoEhNo = 2 ,
               /* Não é nó na direção desejada */

         MAT_CondRetMatrizNaoExiste = 3 ,
               /* Matriz não existe */

         MAT_CondRetNaoTemCorrente = 4 ,
               /* Matriz está vazia */

         MAT_CondRetFaltouMemoria = 5
               /* Faltou memória ao alocar dados */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/
   MAT_tpCondRet MAT_CriarMatriz( MAT_tpMatriz ** ppMatriz ) ;



/***********************************************************************
*
*  $FC Função: MAT Inicializar a matriz
*
*  $EP Parâmetros
*     $P pMatriz - matriz que será inicializada.
*                    Este parâmetro é passado por referência.
*     $P Linhas - quantidade de linhas que a matriz terá.
*     $P Colunas - quantidade de colunas que a matriz terá.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/
   MAT_tpCondRet MAT_InicializarMatriz( MAT_tpMatriz * pMatriz , int Linhas , int Colunas ) ;



/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente não exista.
*
*  $EP Parâmetros
*     $P ppMatriz - é o ponteiro para a matriz que será destruida.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*
***********************************************************************/
   MAT_tpCondRet MAT_DestruirMatriz( MAT_tpMatriz ** ppMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó ao norte.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção norte
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
***********************************************************************/
   MAT_tpCondRet MAT_IrNoNorte( MAT_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó ao sul.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção sul
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
***********************************************************************/
   MAT_tpCondRet MAT_IrNoSul( MAT_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó à este.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção este.
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
***********************************************************************/
   MAT_tpCondRet MAT_IrNoEste( MAT_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó à oeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção oeste
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
***********************************************************************/
   MAT_tpCondRet MAT_IrNoOeste( MAT_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó à nordeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção nordeste
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
***********************************************************************/
   MAT_tpCondRet MAT_IrNoNordeste( MAT_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó à sudeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção sudeste
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
***********************************************************************/
   MAT_tpCondRet MAT_IrNoSudeste( MAT_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó à sudoeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção sudoeste
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
***********************************************************************/
   MAT_tpCondRet MAT_IrNoSudoeste( MAT_tpMatriz * pMatriz ) ;


/***************************************************************************
*
*  $FC Função: MAT Ir para nó à noroeste.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção noroeste
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*  
***********************************************************************/
   MAT_tpCondRet MAT_IrNoNoroeste( MAT_tpMatriz * pMatriz ) ;



/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorr( MAT_tpMatriz * pMatriz , LIS_tppLista * ValorParm ) ;

/***********************************************************************
*
*  $FC Função: MAT Atribuir valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - o valor que será atribuido ao nó corrente.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*
***********************************************************************/
   
   MAT_tpCondRet MAT_AtribuirValorCorr( MAT_tpMatriz * pMatriz , LIS_tppLista ValorParm ) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif

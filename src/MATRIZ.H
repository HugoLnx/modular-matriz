#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar matrizs binárias.
*     A matriz possui uma cabeça que contém uma referência para a raíz da
*     matriz e outra para um nó corrente da matriz.
*     A cada momento o módulo admite no máximo uma única matriz.
*     Ao iniciar a execução do programa não existe matriz.
*     A matriz poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a matriz estiver vazia.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

typedef struct tgMatriz MAT_tpMatriz ;
typedef struct tgNoMatriz tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetNaoCriouRaiz = 1 ,
               /* Não criou nó raiz */

         MAT_CondRetErroEstrutura = 2 ,
               /* Estrutura da matriz está errada */

         MAT_CondRetNaoEhFolha = 3 ,
               /* Não é folha relativa à direção de inserção desejada */

         MAT_CondRetMatrizNaoExiste = 4 ,
               /* Matriz não existe */

         MAT_CondRetMatrizVazia = 5 ,
               /* Matriz está vazia */

         MAT_CondRetNohEhRaiz = 6 ,
               /* Nó corrente é raiz */

         MAT_CondRetNaoPossuiFilho = 7 ,
               /* Nó corrente não possui filho na direção desejada */

         MAT_CondRetFaltouMemoria = 8
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

   MAT_tpCondRet MAT_InicializarMatriz( MAT_tpMatriz * pMatriz , int Linhas , int Colunas ) ;

   MAT_tpCondRet MAT_TestarEstruturaMatriz( MAT_tpMatriz * pMatriz , int Linhas , int Colunas ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente não exista.
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( MAT_tpMatriz ** ppMatriz ) ;


 ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó pai
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEhRaiz
*
***********************************************************************/

   MAT_tpCondRet MAT_IrPai( MAT_tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó à esquerda
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNoEsquerda( MAT_tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó à direita
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNoDireita( MAT_tpMatriz * pMatriz ) ;


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
*     MAT_CondRetMatrizVazia
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorr( MAT_tpMatriz * pMatriz , char * ValorParm ) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif

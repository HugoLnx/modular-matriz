/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              MATRIZ.C
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
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN



   /***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoMatriz {

         struct tgNoMatriz * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoMatriz * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoMatriz * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */


		 struct tgNoMatriz * pNorte;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoMatriz * pSul;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

		 struct tgNoMatriz * pEste;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

		 struct tgNoMatriz * pOeste;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

		 struct tgNoMatriz * pNordeste;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */


		 struct tgNoMatriz * pSudeste;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */


		 struct tgNoMatriz * pNoroeste;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */


		 struct tgNoMatriz * pSudoeste;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */


         char Valor ;
               /* Valor do nó */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgMatriz {

         tpNoMatriz * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpMatriz ;

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoMatriz * CriarNo( char ValorParm ) ;

   static MAT_tpCondRet CriarNoRaiz( tpMatriz * pMatriz , char ValorParm ) ;

   static void DestroiMatriz( tpNoMatriz * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar árvore
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( tpMatriz ** ppMatriz )
   {
	  tpMatriz * pMatriz;

      if ( ppMatriz != NULL && *ppMatriz != NULL )
      {
         MAT_DestruirMatriz( ppMatriz ) ;
      } /* if */
	  
	  pMatriz = ( tpMatriz * ) malloc( sizeof( tpMatriz )) ;
      if ( pMatriz == NULL )
      {
         return MAT_CondRetFaltouMemoria ;
      } /* if */


      pMatriz->pNoRaiz = NULL ;
      pMatriz->pNoCorr = NULL ;

	  *ppMatriz = pMatriz;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Criar árvore */

/***************************************************************************
*
*  Função: MAT Destruir árvore
*  ****/

   MAT_tpCondRet MAT_DestruirMatriz( tpMatriz ** ppMatriz )
   {
	  tpMatriz * pMatriz;

      if ( ppMatriz != NULL && *ppMatriz != NULL )
      {
		 pMatriz = *ppMatriz;
         if ( pMatriz->pNoRaiz != NULL )
         {
            DestroiMatriz( pMatriz->pNoRaiz ) ;
         } /* if */
         free( pMatriz ) ;
         *ppMatriz = NULL ;
		 return MAT_CondRetOK;
      } /* if */
	  return MAT_CondRetMatrizNaoExiste;
   } /* Fim função: MAT Destruir árvore */

/***************************************************************************
*
*  Função: MAT Adicionar filho à esquerda
*  ****/

   MAT_tpCondRet MAT_InserirEsquerda( tpMatriz * pMatriz , char ValorParm )
   {

      MAT_tpCondRet CondRet ;

      tpNoMatriz * pCorr ;
      tpNoMatriz * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( pMatriz , ValorParm ) ;
         if ( CondRet != MAT_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pMatriz->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MAT_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pMatriz->pNoCorr = pNo ;

            return MAT_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim função: MAT Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: MAT Adicionar filho à direita
*  ****/

   MAT_tpCondRet MAT_InserirDireita( tpMatriz * pMatriz , char ValorParm )
   {

      MAT_tpCondRet CondRet ;

      tpNoMatriz * pCorr ;
      tpNoMatriz * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( pMatriz , ValorParm ) ;
         if ( CondRet != MAT_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pMatriz->pNoCorr ;
         if ( pCorr == NULL )
         {
            return MAT_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MAT_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pMatriz->pNoCorr = pNo ;

            return MAT_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim função: MAT Adicionar filho à direita */

/***************************************************************************
*
*  Função: MAT Ir para nó pai
*  ****/

   MAT_tpCondRet MAT_IrPai( tpMatriz * pMatriz )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoPai != NULL )
      {
         pMatriz->pNoCorr = pMatriz->pNoCorr->pNoPai ;
         return MAT_CondRetOK ;
      } else {
         return MAT_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: MAT Ir para nó pai */

/***************************************************************************
*
*  Função: MAT Ir para nó à esquerda
*  ****/

   MAT_tpCondRet MAT_IrNoEsquerda( tpMatriz * pMatriz )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoEsq == NULL )
      {
         return MAT_CondRetNaoPossuiFilho ;
      } /* if */

      pMatriz->pNoCorr = pMatriz->pNoCorr->pNoEsq ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Ir para nó à esquerda */

/***************************************************************************
*
*  Função: MAT Ir para nó à direita
*  ****/

   MAT_tpCondRet MAT_IrNoDireita( tpMatriz * pMatriz )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

      if ( pMatriz->pNoCorr->pNoDir == NULL )
      {
         return MAT_CondRetNaoPossuiFilho ;
      } /* if */

      pMatriz->pNoCorr = pMatriz->pNoCorr->pNoDir ;
      return MAT_CondRetOK ;

   } /* Fim função: MAT Ir para nó à direita */

/***************************************************************************
*
*  Função: MAT Obter valor corrente
*  ****/

   MAT_tpCondRet MAT_ObterValorCorr( tpMatriz * pMatriz , char * ValorParm )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */
      * ValorParm = pMatriz->pNoCorr->Valor ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: MAT Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoMatriz * CriarNo( char ValorParm )
   {

      tpNoMatriz * pNo ;

      pNo = ( tpNoMatriz * ) malloc( sizeof( tpNoMatriz )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim função: MAT Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: MAT Criar nó raiz da árvore
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoCriouRaiz
*
***********************************************************************/

   MAT_tpCondRet CriarNoRaiz(tpMatriz * pMatriz , char ValorParm )
   {

      MAT_tpCondRet CondRet ;
      tpNoMatriz * pNo ;

      if ( pMatriz == NULL )
      {
         CondRet = MAT_CriarMatriz( &pMatriz ) ;

         if ( CondRet != MAT_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pMatriz->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */
         pMatriz->pNoRaiz = pNo ;
         pMatriz->pNoCorr = pNo ;

         return MAT_CondRetOK ;
      } /* if */

      return MAT_CondRetNaoCriouRaiz ;

   } /* Fim função: MAT Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: MAT Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoMatriz != NULL
*
***********************************************************************/

   void DestroiMatriz( tpNoMatriz * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiMatriz( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiMatriz( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: MAT Destruir a estrutura da árvore */

/********** Fim do módulo de implementação: Módulo árvore **********/


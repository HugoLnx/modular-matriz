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

   typedef enum {
	     NORTE = 1 ,
		 
		 SUL = 2 ,
		 
		 ESTE = 3 ,

		 OESTE = 4 ,

		 NORDESTE = 5 ,

		 SUDESTE = 6 ,

		 SUDOESTE = 7 ,

		 NOROESTE = 8 ,

         ESQ = 9 ,

         DIR = 10

   } tpDirecao;

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoMatriz * CriarNo( char ValorParm ) ;

   static MAT_tpCondRet CriarNoRaiz( tpMatriz * pMatriz , char ValorParm ) ;

   static void DestroiMatriz( tpNoMatriz * pNo ) ;

   tpNoMatriz * GetVizinho( tpNoMatriz * pNo , tpDirecao dir );

   void SetNovoVizinho( tpNoMatriz * pNo , tpNoMatriz * pNoNovo , tpDirecao dir );

   MAT_tpCondRet AddColuna( tpMatriz * pMatriz );

   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo ) ;

   MAT_tpCondRet InserirGenerico( tpMatriz * pMatriz , char ValorParm , tpDirecao dir );
   
   tpDirecao DirecaoReversa( tpDirecao dir );

/*****  Código das funções exportadas pelo módulo  *****/

    MAT_tpCondRet MAT_TestarEstruturaMatriz( tpMatriz * pMatriz , int Linhas , int Colunas )
	{
		tpNoMatriz * pNo = pMatriz->pNoRaiz;
		tpNoMatriz * pNoExtremidade;
		int i , j;
		int LinhasInternas = Linhas - 2;
		int ColunasInternas = Colunas - 2;

		// Verificar extremidades
		for( i = 0 ; i < Colunas ; i++)
		{
			if( pNo->pNorte != NULL )
			{
				return MAT_CondRetErroEstrutura;
			}

			if( i != Colunas - 1 ) // nao eh ultimo
			{
				if( pNo->pEste == NULL )
				{
					return MAT_CondRetNaoEhFolha;
				}

				pNo = pNo->pEste;
			}
			else if( pNo->pEste != NULL )
			{
				pNo = NULL;
				return MAT_CondRetErroEstrutura;
			}
		}
		
		for( i = 0 ; i < Linhas ; i++)
		{
			if( pNo->pEste != NULL )
			{
				return MAT_CondRetErroEstrutura;
			}

			if( i != Linhas - 1 )
			{
				if( pNo->pSul == NULL )
				{
					return MAT_CondRetNaoEhFolha;
				}

				pNo = pNo->pSul;
			}
			else if( pNo->pSul != NULL )
			{
				return MAT_CondRetErroEstrutura;
			}
		}

		
		for( i = 0 ; i < Colunas ; i++)
		{
			if( pNo->pSul != NULL )
			{
				return MAT_CondRetErroEstrutura;
			}

			if( i != Colunas - 1 )  // nao eh ultimo
			{
				if( pNo->pOeste == NULL )
				{
					return MAT_CondRetNaoEhFolha;
				}

				pNo = pNo->pOeste;
			}
			else if( pNo->pOeste != NULL )
			{
				return MAT_CondRetErroEstrutura;
			}
		}
		
		for( i = 0 ; i < Linhas ; i++)
		{
			if( pNo->pOeste != NULL )
			{
				return MAT_CondRetErroEstrutura;
			}

			if( i != Linhas - 1 )   // nao eh ultimo
			{
				if( pNo->pNorte == NULL )
				{
					return MAT_CondRetNaoEhFolha;
				}

				pNo = pNo->pNorte;
			}
			else if( pNo->pNorte != NULL )
			{
				return MAT_CondRetErroEstrutura;
			}
		}

		// Verificar referencias dos nos internos
		pNoExtremidade = pMatriz->pNoRaiz->pSudeste;
		for( i = 0 ; i < LinhasInternas ; i++)
		{
			pNo = pNoExtremidade;
			for( j = 0 ; j < ColunasInternas ; j++ )
			{
				if( 
					pNo->pNorte == NULL ||
					pNo->pSul == NULL ||
					pNo->pEste == NULL ||
					pNo->pOeste == NULL ||
					pNo->pNordeste == NULL ||
					pNo->pSudeste == NULL ||
					pNo->pSudoeste == NULL ||
					pNo->pNoroeste == NULL
				  )
				{
					return MAT_CondRetErroEstrutura;
				}

				if( j != ColunasInternas - 1 )  // nao eh ultimo
				{
					if( pNo->pSul == NULL )
					{
						return MAT_CondRetNaoEhFolha;
					}

					pNo = pNo->pSul;
				}
			}
			pNoExtremidade = pNoExtremidade->pEste;
			pNo = pNoExtremidade;
		}

		// Verificar todas as referencias para cada no
		pNoExtremidade = pMatriz->pNoRaiz;
		for( i = 0 ; i < Linhas ; i++)
		{
			pNo = pNoExtremidade;
			for( j = 0 ; j < Colunas ; j++ )
			{
				if( pNo->pNorte != NULL && pNo->pNorte->pSul != pNo ) {
					return MAT_CondRetErroEstrutura;
				}
				
				if( pNo->pSul != NULL && pNo->pSul->pNorte != pNo ) {
					return MAT_CondRetErroEstrutura;
				}
				
				if( pNo->pEste != NULL && pNo->pEste->pOeste != pNo ) {
					return MAT_CondRetErroEstrutura;
				}
				
				if( pNo->pOeste != NULL && pNo->pOeste->pEste != pNo ) {
					return MAT_CondRetErroEstrutura;
				}

				if( pNo->pNordeste != NULL && pNo->pNordeste->pSudoeste != pNo ) {
					return MAT_CondRetErroEstrutura;
				}
				
				if( pNo->pSudeste != NULL && pNo->pSudeste->pNoroeste != pNo ) {
					return MAT_CondRetErroEstrutura;
				}
				
				if( pNo->pSudoeste != NULL && pNo->pSudoeste->pNordeste != pNo ) {
					return MAT_CondRetErroEstrutura;
				}
				
				if( pNo->pNoroeste != NULL && pNo->pNoroeste->pSudeste != pNo ) {
					return MAT_CondRetErroEstrutura;
				}

				if( j != Colunas - 1 )  // nao eh ultimo
				{
					if( pNo->pSul == NULL )
					{
						return MAT_CondRetNaoEhFolha;
					}

					pNo = pNo->pSul;
				}
			}
			pNoExtremidade = pNoExtremidade->pEste;
		}


		return MAT_CondRetOK;
	}

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

   MAT_tpCondRet MAT_InicializarMatriz(tpMatriz * pMatriz , int Linhas , int Colunas )
   {
	   int i;
	   tpNoMatriz * pNoNovo;
	   tpNoMatriz * pNoAnterior;
	   MAT_tpCondRet Cond;

	   if( pMatriz == NULL )
	   {
		   return MAT_CondRetMatrizNaoExiste;
	   }

	   Cond = CriarNoRaiz( pMatriz , NULL );
	   if ( Cond != MAT_CondRetOK )
	   {
		   return Cond;
	   }

	   pNoAnterior = pMatriz->pNoRaiz;

	   for( i = 1 ; i < Linhas+1 ; i++ )
	   {
		   pNoNovo = CriarNo( NULL );
		   if( pNoNovo == NULL )
		   {
			   return MAT_CondRetFaltouMemoria;
		   }
		   pNoNovo->pNorte = pNoAnterior;
		   pNoAnterior->pSul = pNoNovo;
	   }
	   
	   for ( i = 1 ; i < Colunas ; i++ )
	   {
		   AddColuna( pMatriz );
	   }

	   return MAT_CondRetOK;
   }

   MAT_tpCondRet AddColuna( tpMatriz * pMatriz )
   {
	   tpNoMatriz * pRaiz = pMatriz->pNoRaiz;
	   tpNoMatriz * pNoNovo;
	   tpNoMatriz * pNoExtremidade;

	   pNoExtremidade = pMatriz->pNoRaiz;
	   while( pNoExtremidade->pEste != NULL )
	   {
		   pNoExtremidade = pNoExtremidade->pEste;
	   }

	   while( pNoExtremidade != NULL )
	   {
		   pNoNovo = CriarNo( NULL );
		   if( pNoNovo == NULL )
		   {
			   return MAT_CondRetFaltouMemoria;
		   }


		   pNoNovo->pOeste = pNoExtremidade;
		   pNoNovo->pNoroeste = pNoExtremidade->pNorte;
		   pNoNovo->pSudoeste = pNoExtremidade->pSul;
		   pNoNovo->pNorte = pNoExtremidade->pNordeste;
		   pNoNovo->pSul = pNoExtremidade->pSudeste;

		   ApontarDeVoltaEmTodasAsDirecoes( pNoNovo );

		   pNoExtremidade = pNoExtremidade->pSul;
	   }

	   return MAT_CondRetOK;
   }

   
   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo )
   {
		if( pNo->pNorte != NULL )
		{
			pNo->pNorte->pSul= pNo;
		}

		if( pNo->pSul != NULL )
		{
			pNo->pSul->pNorte= pNo;
		}
		
		if( pNo->pEste != NULL )
		{
			pNo->pEste->pOeste = pNo;
		}
		
		if( pNo->pOeste != NULL )
		{
			pNo->pOeste->pEste= pNo;
		}
	   
		if( pNo->pNordeste != NULL )
		{
			pNo->pNordeste->pSudoeste = pNo;
		}
		
		if( pNo->pSudeste != NULL )
		{
			pNo->pSudeste->pNoroeste = pNo;
		}
		
		if( pNo->pSudoeste != NULL )
		{
			pNo->pSudoeste->pNordeste = pNo;
		}
		
		if( pNo->pNoroeste != NULL )
		{
			pNo->pNoroeste->pSudeste = pNo;
		}
   }

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
      return InserirGenerico(pMatriz, ValorParm, ESQ);
   } /* Fim função: MAT Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: MAT Adicionar filho à direita
*  ****/

   MAT_tpCondRet MAT_InserirDireita( tpMatriz * pMatriz , char ValorParm )
   {
	   return InserirGenerico(pMatriz, ValorParm, DIR);
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
      pNo->pNoDir = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNorte = NULL ;
	  pNo->pSul = NULL ;
	  pNo->pEste = NULL ;
	  pNo->pOeste = NULL ;
	  pNo->pNordeste = NULL ;
	  pNo->pSudeste = NULL ;
	  pNo->pSudoeste = NULL ;
	  pNo->pNoroeste = NULL ;
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
   
   
   
   MAT_tpCondRet InserirGenerico( tpMatriz * pMatriz , char ValorParm , tpDirecao Dir )
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
               
         if ( GetVizinho( pCorr, Dir ) == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return MAT_CondRetFaltouMemoria ;
            } /* if */
            SetNovoVizinho( pCorr , pNo , Dir ) ;
            pMatriz->pNoCorr = pNo ;

            return MAT_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return MAT_CondRetNaoEhFolha ;

   } /* Fim função: MAT Adicionar filho generico */

   
   tpNoMatriz * GetVizinho( tpNoMatriz * pNo , tpDirecao dir )
   {
		if ( dir == ESQ )
			return pNo->pNoEsq;

		if ( dir== DIR )
			return pNo->pNoDir;

		return NULL;
   }
   
   void SetNovoVizinho( tpNoMatriz * pNo , tpNoMatriz * pNoNovo , tpDirecao dir )
   {
	   pNoNovo->pNoPai = pNo;
	   if ( dir == ESQ )
			pNo->pNoEsq = pNoNovo;

	   if ( dir == DIR )
			pNo->pNoDir = pNoNovo;
   }

   tpDirecao DirecaoReversa( tpDirecao dir )
   {
	   switch( dir )
	   {
			case NORTE: return SUL;
			case SUL: return NORTE;
			case ESTE: return OESTE;
			case NORDESTE: return SUDOESTE;
			case SUDESTE: return NOROESTE;
			case SUDOESTE: return NORDESTE;
			case NOROESTE: return SUDESTE;
	   }
   }

/********** Fim do módulo de implementação: Módulo árvore **********/


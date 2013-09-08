/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MAT
*
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*           hg - Hugo Roque
*           ?? = Nino Fabrizio
*		    ?? = Robert Correa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       4.00   ???   ??/??/???? Adaptação do módulo para manipular matrizes
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
*  $TC Tipo de dados: MAT Descritor do nó da matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoMatriz {

         struct tgNoMatriz * pNoPai ; /* será apagado*/
         struct tgNoMatriz * pNoEsq ; /* será apagado*/
         struct tgNoMatriz * pNoDir ; /* será apagado*/


		 struct tgNoMatriz * pNorte ;
               /* Ponteiro para nó adjacente ao norte
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a raiz, então pNorte = NULL
			   *   se pNorte do nó X != NULL então pSul de pNorte aponta para nó X */

         struct tgNoMatriz * pSul ;
               /* Ponteiro para nó adjacente ao sul
               *
               *$EED Assertivas estruturais
			   *   se pSul do nó X != NULL então pNorte de pSul aponta para nó X */

		 struct tgNoMatriz * pEste ;
               /* Ponteiro para nó adjacente à este
               *
               *$EED Assertivas estruturais
			   *   se pEste do nó X != NULL então pOeste de pEste aponta para nó X */

		 struct tgNoMatriz * pOeste ;
               /* Ponteiro para nó adjacente à oeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a raiz, então pOeste = NULL
			   *   se pOeste do nó X != NULL então pEste de pOeste aponta para nó X */

		 struct tgNoMatriz * pNordeste ;
               /* Ponteiro para nó adjacente à nordeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a raiz, então pNordeste = NULL
			   *   se pNordeste do nó X != NULL então pSudoeste de pNordeste aponta para nó X */


		 struct tgNoMatriz * pSudeste ;
               /* Ponteiro para nó adjacente à sudeste
               *
               *$EED Assertivas estruturais
			   *   se pSudeste do nó X != NULL então pNoroeste de pSudeste aponta para nó X */


		 struct tgNoMatriz * pNoroeste ;
               /* Ponteiro para nó adjacente à noroeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a raiz, então pNoroeste = NULL
			   *   se pNoroeste do nó X != NULL então pSudeste de pNoroeste aponta para nó X */


		 struct tgNoMatriz * pSudoeste ;
               /* Ponteiro para nó adjacente à sudoeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a raiz, então pSudoeste = NULL
			   *   se pSudoeste do nó X != NULL então pNordeste de pSudoeste aponta para nó X */


         char Valor ;
               /* Valor do nó */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma matriz
*
*
*  $ED Descrição do tipo
*     A cabeça da matriz é o ponto de acesso para uma determinada matriz.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a matriz em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgMatriz {

         tpNoMatriz * pNoRaiz ;
               /* Ponteiro para a raiz da matriz */

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o nó corrente da matriz */

   } MAT_tpMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Direções que o nó pode ter ponteiros para outro nó.
*
*
***********************************************************************/
   typedef enum {
	     NORTE = 1 ,
		 
		 SUL = 2 ,
		 
		 ESTE = 3 ,

		 OESTE = 4 ,

		 NORDESTE = 5 ,

		 SUDESTE = 6 ,

		 SUDOESTE = 7 ,

		 NOROESTE = 8

   } tpDirecao ;
   const tpDirecao DIRECOES[] = { NORTE , SUL , ESTE , OESTE , NORDESTE , SUDESTE , SUDOESTE , NOROESTE } ;
   const int DIRECOES_SIZE = 8 ;

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoMatriz * CriarNo( char ValorParm ) ;

   static MAT_tpCondRet CriarNoRaiz( MAT_tpMatriz * pMatriz , char ValorParm ) ;

   static void DestroiMatriz( tpNoMatriz * pNo ) ;

   tpNoMatriz * GetVizinho( tpNoMatriz * pNo , tpDirecao dir ) ;

   void SetNovoVizinho( tpNoMatriz * pNo , tpNoMatriz * pNoNovo , tpDirecao dir ) ;

   MAT_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoRaiz , int QntLinhas ) ;

   MAT_tpCondRet AddColuna( MAT_tpMatriz * pMatriz ) ;

   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo ) ;
   
   tpDirecao DirecaoReversa( tpDirecao dir ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: MAT Criar matriz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tpMatriz ** ppMatriz )
   {
	  MAT_tpMatriz * pMatriz ;

      if ( ppMatriz != NULL && *ppMatriz != NULL )
      {
         MAT_DestruirMatriz( ppMatriz ) ;
      } /* if */
	  
	  pMatriz = ( MAT_tpMatriz * ) malloc( sizeof( MAT_tpMatriz )) ;
      if ( pMatriz == NULL )
      {
         return MAT_CondRetFaltouMemoria ;
      } /* if */


      pMatriz->pNoRaiz = NULL ;
      pMatriz->pNoCorr = NULL ;

	  *ppMatriz = pMatriz ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Criar matriz */

   /***************************************************************************
*
*  Função: MAT Inicializar matriz
*  ****/

   MAT_tpCondRet MAT_InicializarMatriz(MAT_tpMatriz * pMatriz , int Linhas , int Colunas )
   {
	   int i ;
	   tpNoMatriz * pNoNovo ;
	   tpNoMatriz * pNoAnterior ;
	   MAT_tpCondRet Cond ;

	   if( pMatriz == NULL )
	   {
		   return MAT_CondRetMatrizNaoExiste ;
	   }

	   Cond = CriarNoRaiz( pMatriz , NULL ) ;
	   if ( Cond != MAT_CondRetOK )
	   {
		   return Cond ;
	   }

	   Cond = ConstruirPrimeiraColuna( pMatriz->pNoRaiz , Linhas) ;
	   if ( Cond != MAT_CondRetOK )
	   {
		   return Cond ;
	   }

	   for ( i = 0 ; i < Colunas - 1 ; i++ )
	   {
		   AddColuna( pMatriz ) ;
	   }

	   return MAT_CondRetOK ;
   }  /* Fim função: MAT Inicializar matriz */


/***************************************************************************
*
*  Função: MAT Destruir matriz
*  ****/

   MAT_tpCondRet MAT_DestruirMatriz( MAT_tpMatriz ** ppMatriz )
   {
	  MAT_tpMatriz * pMatriz ;

      if ( ppMatriz != NULL && *ppMatriz != NULL )
      {
		 pMatriz = *ppMatriz ;
         if ( pMatriz->pNoRaiz != NULL )
         {
            DestroiMatriz( pMatriz->pNoRaiz ) ;
         } /* if */
         free( pMatriz ) ;
         *ppMatriz = NULL ;
		 return MAT_CondRetOK ;
      } /* if */
	  return MAT_CondRetMatrizNaoExiste ;
   } /* Fim função: MAT Destruir matriz */


/***************************************************************************
*
*  Função: MAT Ir para nó pai
*  ****/

   MAT_tpCondRet MAT_IrPai( MAT_tpMatriz * pMatriz )
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

   MAT_tpCondRet MAT_IrNoEsquerda( MAT_tpMatriz * pMatriz )
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

   MAT_tpCondRet MAT_IrNoDireita( MAT_tpMatriz * pMatriz )
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

   MAT_tpCondRet MAT_ObterValorCorr( MAT_tpMatriz * pMatriz , char * ValorParm )
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
*  $FC Função: MAT Criar nó da matriz
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

   } /* Fim função: MAT Criar nó da matriz */


/***********************************************************************
*
*  $FC Função: MAT Criar nó raiz da matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoCriouRaiz
*
***********************************************************************/

   MAT_tpCondRet CriarNoRaiz(MAT_tpMatriz * pMatriz , char ValorParm )
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

   } /* Fim função: MAT Criar nó raiz da matriz */


/***********************************************************************
*
*  $FC Função: MAT Destruir a estrutura da matriz
*
*  $EAE Assertivas de entradas esperadas
*     pNo != NULL
*
***********************************************************************/

   void DestroiMatriz( tpNoMatriz * pNo )
   {
	   tpNoMatriz * pNoExtremidade = pNo ;
	   tpNoMatriz * pProxNoExtremidade ;
	   tpNoMatriz * pProxNo ;

	   while ( pNoExtremidade != NULL )
	   {
		   pProxNoExtremidade = pNoExtremidade->pEste ;
			while ( pNo != NULL )
			{
				pProxNo = pNo->pSul ;
				free( pNo ) ;
				pNo = pProxNo ;
			}
			pNoExtremidade = pProxNoExtremidade ;
			pNo = pNoExtremidade ;
	   }
	   
   } /* Fim função: MAT Destruir a estrutura da matriz */
   

/***********************************************************************
*
*  $FC Função: MAT Recupera o ponteiro para um nó adjacente
*
*  Exemplo de uso: getVizinho(noRaiz, ESTE)
*
***********************************************************************/

   tpNoMatriz * GetVizinho( tpNoMatriz * pNo , tpDirecao dir )
   {
		switch( dir )
		{
		case NORTE:    return pNo->pNorte ;
		case SUL:      return pNo->pSul ;
		case ESTE:     return pNo->pEste ;
		case NORDESTE: return pNo->pNordeste ;
		case SUDESTE:  return pNo->pSudeste ;
		case SUDOESTE: return pNo->pSudoeste ;
		case NOROESTE: return pNo->pNoroeste ;
		}
   }  /* Fim função: MAT Recupera o ponteiro para um nó adjacente*/
   
   
/***********************************************************************
*
*  $FC Função: MAT Troca o ponteiro de um nó adjacente.
*
*  Exemplo de uso: SetNovoVizinho(noRaiz, pNoNovo, ESTE)
*
***********************************************************************/

   void SetNovoVizinho( tpNoMatriz * pNo , tpNoMatriz * pNoNovo , tpDirecao dir )
   {
	   switch( dir )
		{
		case NORTE:    pNo->pNorte    = pNoNovo ; break ;
		case SUL:      pNo->pSul      = pNoNovo ; break ;
		case ESTE:     pNo->pEste     = pNoNovo ; break ;
		case NORDESTE: pNo->pNordeste = pNoNovo ; break ;
		case SUDESTE:  pNo->pSudeste  = pNoNovo ; break ;
		case SUDOESTE: pNo->pSudoeste = pNoNovo ; break ;
		case NOROESTE: pNo->pNoroeste = pNoNovo ; break ;
		}
   }  /* Fim função: MAT Troca o ponteiro de um nó adjacente */

/***********************************************************************
*
*  $FC Função: MAT Descobre a direção oposta.
*
*  Exemplo de uso: DirecaoReversa(ESTE) => OESTE
*
***********************************************************************/

   tpDirecao DirecaoReversa( tpDirecao dir )
   {
	   switch( dir )
	   {
			case NORTE: return SUL ;
			case SUL: return NORTE ;
			case ESTE: return OESTE ;
			case NORDESTE: return SUDOESTE ;
			case SUDESTE: return NOROESTE ;
			case SUDOESTE: return NORDESTE ;
			case NOROESTE: return SUDESTE ;
	   }
   }  /* Fim função: MAT Descobre a direção oposta */


/***********************************************************************
*
*  $FC Função: MAT Constroi a primeira coluna da matriz.
*  
*  $ED Descrição da função
*  Essa função é chamada no momento de inicialização da matriz para
*  criar a primeira coluna com o número de linhas correto e referenciando
*  todos os nós adjacentes nas direções norte e sul
*
*  $EAE Assertivas de entradas esperadas
*     - pNoMatriz deve ser a raiz.
*     - pNoMatriz nao deve apontar para outro nó.
*
***********************************************************************/

   MAT_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoRaiz , int QntLinhas )
   {
	   int i ;
	   tpNoMatriz * pNoNovo ;
	   tpNoMatriz * pNoAnterior ;
	   
	   pNoAnterior = pNoRaiz ;
	   for( i = 0 ; i < QntLinhas - 1 ; i++ )
	   {
		   pNoNovo = CriarNo( NULL ) ;
		   if( pNoNovo == NULL )
		   {
			   return MAT_CondRetFaltouMemoria ;
		   }
		   pNoNovo->pNorte = pNoAnterior ;
		   pNoAnterior->pSul = pNoNovo ;
		   pNoAnterior = pNoNovo ;
	   }
	   
	   return MAT_CondRetOK ;
   }  /* Fim função: MAT Construi a primeira coluna da matriz */

/***********************************************************************
*
*  $FC Função: MAT Adiciona coluna.
*  
*  $ED Descrição da função
*  Adiciona mais uma coluna à matriz, mantendo o número de linhas e
*  referenciando os nós adjacentes em todas as 8 direções.
*
*  $EAE Assertivas de entradas esperadas
*     - pMatriz deve ter raiz.
*
***********************************************************************/
   MAT_tpCondRet AddColuna( MAT_tpMatriz * pMatriz )
   {
	   tpNoMatriz * pRaiz = pMatriz->pNoRaiz ;
	   tpNoMatriz * pNoNovo ;
	   tpNoMatriz * pNoExtremidade ;

	   pNoExtremidade = pMatriz->pNoRaiz ;
	   while( pNoExtremidade->pEste != NULL )
	   {
		   pNoExtremidade = pNoExtremidade->pEste ;
	   }

	   while( pNoExtremidade != NULL )
	   {
		   pNoNovo = CriarNo( NULL ) ;
		   if( pNoNovo == NULL )
		   {
			   return MAT_CondRetFaltouMemoria ;
		   }


		   pNoNovo->pOeste = pNoExtremidade ;
		   pNoNovo->pNoroeste = pNoExtremidade->pNorte ;
		   pNoNovo->pSudoeste = pNoExtremidade->pSul ;
		   pNoNovo->pNorte = pNoExtremidade->pNordeste ;
		   pNoNovo->pSul = pNoExtremidade->pSudeste ;

		   ApontarDeVoltaEmTodasAsDirecoes( pNoNovo ) ;

		   pNoExtremidade = pNoExtremidade->pSul ;
	   }

	   return MAT_CondRetOK ;
   }  /* Fim função: MAT Adiciona Coluna */

/***********************************************************************
*
*  $FC Função: MAT Apontar de volta em todas as direções.
*  
*  $ED Descrição da função
*  A função faz com que os adjacentes de um nó referenciem à ele.
*  
*
*  $EAE Assertivas de entradas esperadas.
*     - pNo não pode ser nulo
*
***********************************************************************/
   
   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo )
   {
		if( pNo->pNorte != NULL )
		{
			pNo->pNorte->pSul= pNo ;
		}

		if( pNo->pSul != NULL )
		{
			pNo->pSul->pNorte= pNo ;
		}
		
		if( pNo->pEste != NULL )
		{
			pNo->pEste->pOeste = pNo ;
		}
		
		if( pNo->pOeste != NULL )
		{
			pNo->pOeste->pEste= pNo ;
		}
	   
		if( pNo->pNordeste != NULL )
		{
			pNo->pNordeste->pSudoeste = pNo ;
		}
		
		if( pNo->pSudeste != NULL )
		{
			pNo->pSudeste->pNoroeste = pNo ;
		}
		
		if( pNo->pSudoeste != NULL )
		{
			pNo->pSudoeste->pNordeste = pNo ;
		}
		
		if( pNo->pNoroeste != NULL )
		{
			pNo->pNoroeste->pSudeste = pNo ;
		}
   }  /* Fim função: MAT Apontar de volta em todas as direções */


/********** Fim do módulo de implementação: Módulo matriz **********/


   // Função temporária, não mexam, depois vou converter para um script de teste (Hugo)
    MAT_tpCondRet MAT_TestarEstruturaMatriz( MAT_tpMatriz * pMatriz , int Linhas , int Colunas )
	{		
		tpNoMatriz * pNo = pMatriz->pNoRaiz ;
		tpNoMatriz * pNoExtremidade ;
		int i , j ;
		int LinhasInternas = Linhas - 2 ;
		int ColunasInternas = Colunas - 2 ;

		// Verificar extremidades
		for( i = 0 ; i < Colunas ; i++)
		{
			if( pNo->pNorte != NULL )
			{
				return MAT_CondRetErroEstrutura ;
			}

			if( i != Colunas - 1 ) // nao eh ultimo
			{
				if( pNo->pEste == NULL )
				{
					return MAT_CondRetNaoEhFolha ;
				}

				pNo = pNo->pEste ;
			}
		}

		if( pNo->pEste != NULL )
		{
			return MAT_CondRetErroEstrutura ;
		}
		

		for( i = 0 ; i < Linhas ; i++)
		{
			if( pNo->pEste != NULL )
			{
				return MAT_CondRetErroEstrutura ;
			}

			if( i != Linhas - 1 )
			{
				if( pNo->pSul == NULL )
				{
					return MAT_CondRetNaoEhFolha ;
				}

				pNo = pNo->pSul ;
			}
		}

		if( pNo->pSul != NULL )
		{
			return MAT_CondRetErroEstrutura ;
		}

		
		for( i = 0 ; i < Colunas ; i++)
		{
			if( pNo->pSul != NULL )
			{
				return MAT_CondRetErroEstrutura ;
			}

			if( i != Colunas - 1 )  // nao eh ultimo
			{
				if( pNo->pOeste == NULL )
				{
					return MAT_CondRetNaoEhFolha ;
				}

				pNo = pNo->pOeste ;
			}
		}

		if( pNo->pOeste != NULL )
		{
			return MAT_CondRetErroEstrutura ;
		}
		
		for( i = 0 ; i < Linhas ; i++)
		{
			if( pNo->pOeste != NULL )
			{
				return MAT_CondRetErroEstrutura ;
			}

			if( i != Linhas - 1 )   // nao eh ultimo
			{
				if( pNo->pNorte == NULL )
				{
					return MAT_CondRetNaoEhFolha ;
				}

				pNo = pNo->pNorte ;
			}
		}
		if( pNo->pNorte != NULL )
		{
			return MAT_CondRetErroEstrutura ;
		}

		// Verificar referencias dos nós internos
		pNoExtremidade = pMatriz->pNoRaiz->pSudeste ;
		for( i = 0 ; i < LinhasInternas ; i++)
		{
			pNo = pNoExtremidade ;
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
					return MAT_CondRetErroEstrutura ;
				}

				if( j != ColunasInternas - 1 )  // nao eh ultimo
				{
					if( pNo->pSul == NULL )
					{
						return MAT_CondRetNaoEhFolha ;
					}

					pNo = pNo->pSul ;
				}
			}
			pNoExtremidade = pNoExtremidade->pEste ;
			pNo = pNoExtremidade ;
		}

		// Verificar todas as referencias para cada no
		pNoExtremidade = pMatriz->pNoRaiz ;
		for( i = 0 ; i < Linhas ; i++)
		{
			pNo = pNoExtremidade ;
			for( j = 0 ; j < Colunas ; j++ )
			{
				if( pNo->pNorte != NULL && pNo->pNorte->pSul != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}
				
				if( pNo->pSul != NULL && pNo->pSul->pNorte != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}
				
				if( pNo->pEste != NULL && pNo->pEste->pOeste != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}
				
				if( pNo->pOeste != NULL && pNo->pOeste->pEste != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}

				if( pNo->pNordeste != NULL && pNo->pNordeste->pSudoeste != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}
				
				if( pNo->pSudeste != NULL && pNo->pSudeste->pNoroeste != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}
				
				if( pNo->pSudoeste != NULL && pNo->pSudoeste->pNordeste != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}
				
				if( pNo->pNoroeste != NULL && pNo->pNoroeste->pSudeste != pNo ) {
					return MAT_CondRetErroEstrutura ;
				}

				if( j != Colunas - 1 )  // nao eh ultimo
				{
					if( pNo->pSul == NULL )
					{
						return MAT_CondRetNaoEhFolha ;
					}

					pNo = pNo->pSul ;
				}
			}
			pNoExtremidade = pNoExtremidade->pEste ;
		}

		
		return MAT_CondRetOK ;
	}
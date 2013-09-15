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

#include <malloc.h>
#include <stdio.h>
#include "LISTA.H"

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
		 struct tgNoMatriz * pNorte ;
               /* Ponteiro para nó adjacente ao norte
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pNorte = NULL
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
               *   se é o nó X é a origem, então pOeste = NULL
			   *   se pOeste do nó X != NULL então pEste de pOeste aponta para nó X */

		 struct tgNoMatriz * pNordeste ;
               /* Ponteiro para nó adjacente à nordeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pNordeste = NULL
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
               *   se é o nó X é a origem, então pNoroeste = NULL
			   *   se pNoroeste do nó X != NULL então pSudeste de pNoroeste aponta para nó X */


		 struct tgNoMatriz * pSudoeste ;
               /* Ponteiro para nó adjacente à sudoeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pSudoeste = NULL
			   *   se pSudoeste do nó X != NULL então pNordeste de pSudoeste aponta para nó X */


         LIS_tppLista Valor ;
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

         tpNoMatriz * pNoOrigem ;
               /* Ponteiro para a origem da matriz */

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

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoMatriz * CriarNo() ;

   static MAT_tpCondRet CriarNoOrigem( MAT_tpMatriz * pMatriz ) ;

   static void DestroiMatriz( tpNoMatriz * pNo ) ;

   tpNoMatriz * GetVizinho( tpNoMatriz * pNo , tpDirecao dir ) ;

   MAT_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoOrigem , int QntLinhas ) ;

   MAT_tpCondRet AddColuna( MAT_tpMatriz * pMatriz ) ;

   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo ) ;
   
   MAT_tpCondRet IrPara( MAT_tpMatriz * pMatriz , tpDirecao direcao );

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


      pMatriz->pNoOrigem = NULL ;
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
	   MAT_tpCondRet Cond ;

	   if( pMatriz == NULL )
	   {
		   return MAT_CondRetMatrizNaoExiste ;
	   }

	   Cond = CriarNoOrigem( pMatriz ) ;
	   if ( Cond != MAT_CondRetOK )
	   {
		   return Cond ;
	   }

	   Cond = ConstruirPrimeiraColuna( pMatriz->pNoOrigem , Linhas) ;
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

		if ( ppMatriz == NULL || *ppMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		pMatriz = *ppMatriz ;
		if ( pMatriz->pNoOrigem == NULL )
		{
			return MAT_CondRetNaoCriouOrigem;
		} /* if */
         
		DestroiMatriz( pMatriz->pNoOrigem ) ;
		free( pMatriz ) ;
		*ppMatriz = NULL ;

		return MAT_CondRetOK ;
	  
   } /* Fim função: MAT Destruir matriz */


/***************************************************************************
*
*  Função: MAT Obter valor corrente
*  ****/

   MAT_tpCondRet MAT_ObterValorCorr( MAT_tpMatriz * pMatriz , LIS_tppLista * ValorParm )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetNaoTemCorrente ;
      } /* if */
      * ValorParm = pMatriz->pNoCorr->Valor ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Obter valor corrente */

   
/***************************************************************************
*
*  Função: MAT Atribuir para valor corrente
*  ****/

   MAT_tpCondRet MAT_AtribuirValorCorr( MAT_tpMatriz * pMatriz , LIS_tppLista ValorParm )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetNaoTemCorrente ;
      } /* if */
      pMatriz->pNoCorr->Valor =ValorParm ;

      return MAT_CondRetOK ;

   } /* Fim função: MAT Atribuir valor corrente */


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

   tpNoMatriz * CriarNo()
   {

      tpNoMatriz * pNo ;

      pNo = ( tpNoMatriz * ) malloc( sizeof( tpNoMatriz )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNorte = NULL ;
	  pNo->pSul = NULL ;
	  pNo->pEste = NULL ;
	  pNo->pOeste = NULL ;
	  pNo->pNordeste = NULL ;
	  pNo->pSudeste = NULL ;
	  pNo->pSudoeste = NULL ;
	  pNo->pNoroeste = NULL ;
      pNo->Valor  = NULL ;
      return pNo ;

   } /* Fim função: MAT Criar nó da matriz */


/***********************************************************************
*
*  $FC Função: MAT Criar nó origem da matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoCriouOrigem
*
***********************************************************************/

   MAT_tpCondRet CriarNoOrigem(MAT_tpMatriz * pMatriz )
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

      if ( pMatriz->pNoOrigem == NULL )
      {
         pNo = CriarNo() ;
         if ( pNo == NULL )
         {
            return MAT_CondRetFaltouMemoria ;
         } /* if */
         pMatriz->pNoOrigem = pNo ;
         pMatriz->pNoCorr = pNo ;

         return MAT_CondRetOK ;
      } /* if */

      return MAT_CondRetNaoCriouOrigem ;

   } /* Fim função: MAT Criar nó origem da matriz */


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


   MAT_tpCondRet MAT_IrNoNorte( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORTE );
   }

   MAT_tpCondRet MAT_IrNoSul( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUL );
   }

   MAT_tpCondRet MAT_IrNoEste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , ESTE );
   }

   MAT_tpCondRet MAT_IrNoOeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , OESTE );
   }
   
   MAT_tpCondRet MAT_IrNoNordeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORDESTE );
   }
   
   MAT_tpCondRet MAT_IrNoSudeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDESTE );
   }
   
   MAT_tpCondRet MAT_IrNoSudoeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDOESTE );
   }

   MAT_tpCondRet MAT_IrNoNoroeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NOROESTE );
   }

/***********************************************************************
*
*  $FC Função: MAT Recupera o ponteiro para um nó adjacente
*
*  Exemplo de uso: getVizinho(noOrigem, ESTE)
*
***********************************************************************/

   tpNoMatriz * GetVizinho( tpNoMatriz * pNo , tpDirecao dir )
   {
		switch( dir )
		{
		case NORTE:    return pNo->pNorte ;
		case SUL:      return pNo->pSul ;
		case ESTE:     return pNo->pEste ;
		case OESTE:    return pNo->pOeste ;
		case NORDESTE: return pNo->pNordeste ;
		case SUDESTE:  return pNo->pSudeste ;
		case SUDOESTE: return pNo->pSudoeste ;
		case NOROESTE: return pNo->pNoroeste ;
		}
		return NULL;
   }  /* Fim função: MAT Recupera o ponteiro para um nó adjacente*/

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
*     - pNoMatriz deve ser a origem.
*     - pNoMatriz nao deve apontar para outro nó.
*
***********************************************************************/

   MAT_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoOrigem , int QntLinhas )
   {
	   int i ;
	   tpNoMatriz * pNoNovo ;
	   tpNoMatriz * pNoAnterior ;
	   
	   pNoAnterior = pNoOrigem ;
	   for( i = 0 ; i < QntLinhas - 1 ; i++ )
	   {
		   pNoNovo = CriarNo() ;
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
*     - pMatriz deve ter origem.
*
***********************************************************************/
   MAT_tpCondRet AddColuna( MAT_tpMatriz * pMatriz )
   {
	   tpNoMatriz * pOrigem = pMatriz->pNoOrigem ;
	   tpNoMatriz * pNoNovo ;
	   tpNoMatriz * pNoExtremidade ;

	   pNoExtremidade = pMatriz->pNoOrigem ;
	   while( pNoExtremidade->pEste != NULL )
	   {
		   pNoExtremidade = pNoExtremidade->pEste ;
	   }

	   while( pNoExtremidade != NULL )
	   {
		   pNoNovo = CriarNo() ;
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


      


/***************************************************************************
*
*  Função: MAT Ir para nó genérico
*  ****/

   MAT_tpCondRet IrPara( MAT_tpMatriz * pMatriz , tpDirecao direcao )
   {

      if ( pMatriz == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return MAT_CondRetNaoTemCorrente ;
      } /* if */

      if ( GetVizinho( pMatriz->pNoCorr , direcao ) == NULL )
      {
		  return MAT_CondRetNaoEhNo ;
      } /* if */

	  pMatriz->pNoCorr = GetVizinho( pMatriz->pNoCorr , direcao ) ;
	  return MAT_CondRetOK ;

   } /* Fim função: MAT Ir para nó genérico */

/********** Fim do módulo de implementação: Módulo matriz **********/
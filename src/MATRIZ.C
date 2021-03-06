/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
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
*  $TC Tipo de dados: MAT Descritor do n� da matriz
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoMatriz {
		 struct tgNoMatriz * pNorte ;
               /* Ponteiro para n� adjacente ao norte
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNorte = NULL
			   *   se pNorte do n� X != NULL ent�o pSul de pNorte aponta para n� X */

         struct tgNoMatriz * pSul ;
               /* Ponteiro para n� adjacente ao sul
               *
               *$EED Assertivas estruturais
			   *   se pSul do n� X != NULL ent�o pNorte de pSul aponta para n� X */

		 struct tgNoMatriz * pEste ;
               /* Ponteiro para n� adjacente � este
               *
               *$EED Assertivas estruturais
			   *   se pEste do n� X != NULL ent�o pOeste de pEste aponta para n� X */

		 struct tgNoMatriz * pOeste ;
               /* Ponteiro para n� adjacente � oeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pOeste = NULL
			   *   se pOeste do n� X != NULL ent�o pEste de pOeste aponta para n� X */

		 struct tgNoMatriz * pNordeste ;
               /* Ponteiro para n� adjacente � nordeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNordeste = NULL
			   *   se pNordeste do n� X != NULL ent�o pSudoeste de pNordeste aponta para n� X */


		 struct tgNoMatriz * pSudeste ;
               /* Ponteiro para n� adjacente � sudeste
               *
               *$EED Assertivas estruturais
			   *   se pSudeste do n� X != NULL ent�o pNoroeste de pSudeste aponta para n� X */


		 struct tgNoMatriz * pNoroeste ;
               /* Ponteiro para n� adjacente � noroeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNoroeste = NULL
			   *   se pNoroeste do n� X != NULL ent�o pSudeste de pNoroeste aponta para n� X */


		 struct tgNoMatriz * pSudoeste ;
               /* Ponteiro para n� adjacente � sudoeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pSudoeste = NULL
			   *   se pSudoeste do n� X != NULL ent�o pNordeste de pSudoeste aponta para n� X */


         LIS_tppLista Valor ;
               /* Valor do n� */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabe�a de uma matriz
*
*
*  $ED Descri��o do tipo
*     A cabe�a da matriz � o ponto de acesso para uma determinada matriz.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*
***********************************************************************/

   typedef struct tgMatriz {

         tpNoMatriz * pNoOrigem ;
               /* Ponteiro para a origem da matriz */

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o n� corrente da matriz */

   } MAT_tpMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Dire��es que o n� pode ter ponteiros para outro n�.
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

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   tpNoMatriz * CriarNo() ;

   MAT_tpCondRet CriarNoOrigem( MAT_tpMatriz * pMatriz ) ;

   void EsvaziarMatriz( MAT_tpMatriz * pMatriz ) ;

   tpNoMatriz * GetAdjacente( tpNoMatriz * pNo , tpDirecao dir ) ;

   MAT_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoOrigem , int QntLinhas ) ;

   MAT_tpCondRet AddColuna( MAT_tpMatriz * pMatriz ) ;

   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo ) ;
   
   MAT_tpCondRet IrPara( MAT_tpMatriz * pMatriz , tpDirecao direcao );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/



/***************************************************************************
*
*  Fun��o: MAT Criar matriz
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

   } /* Fim fun��o: MAT Criar matriz */



   /***************************************************************************
*
*  Fun��o: MAT Inicializar matriz
*  ****/
   MAT_tpCondRet MAT_InicializarMatriz(MAT_tpMatriz * pMatriz , int Linhas , int Colunas )
   {
	   int i ;
	   MAT_tpCondRet Cond ;

	   if( pMatriz == NULL )
	   {
		   return MAT_CondRetMatrizNaoExiste ;
	   }

	   if ( pMatriz->pNoOrigem != NULL )
	   {
		   EsvaziarMatriz( pMatriz ) ;
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
		   Cond = AddColuna( pMatriz ) ;
		   if ( Cond != MAT_CondRetOK )
			{
				return Cond ;
			}
	   }

	   return MAT_CondRetOK ;
   }  /* Fim fun��o: MAT Inicializar matriz */




/***************************************************************************
*
*  Fun��o: MAT Destruir matriz
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
         
		EsvaziarMatriz( pMatriz ) ;
		free( pMatriz ) ;
		*ppMatriz = NULL ;

		return MAT_CondRetOK ;
	  
   } /* Fim fun��o: MAT Destruir matriz */



/***************************************************************************
*
*  Fun��o: MAT Obter valor corrente
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

   } /* Fim fun��o: MAT Obter valor corrente */

   

/***************************************************************************
*
*  Fun��o: MAT Atribuir para valor corrente
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

   } /* Fim fun��o: MAT Atribuir valor corrente */

   

/***************************************************************************
*
*  Fun��o: MAT Ir para n� ao norte.
*  ****/
   MAT_tpCondRet MAT_IrNoNorte( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORTE );
   } /* Fim fun��o: MAT Ir para n� ao norte*/



/***************************************************************************
*
*  Fun��o: MAT Ir para n� ao sul.
*  ****/
   MAT_tpCondRet MAT_IrNoSul( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUL );
   } /* Fim fun��o: MAT Ir para n� ao sul*/



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � este.
*  ****/
   MAT_tpCondRet MAT_IrNoEste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , ESTE );
   } /* Fim fun��o: MAT Ir para � n� este*/



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � oeste.
*  ****/
   MAT_tpCondRet MAT_IrNoOeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , OESTE );
   } /* Fim fun��o: MAT Ir para � n� oeste*/
   



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � nordeste.
*  ****/
   MAT_tpCondRet MAT_IrNoNordeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORDESTE );
   } /* Fim fun��o: MAT Ir para n� � nordeste*/
   



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � sudeste.
*  ****/
   MAT_tpCondRet MAT_IrNoSudeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDESTE );
   } /* Fim fun��o: MAT Ir para n� � sudeste*/
   



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � sudoeste.
*  ****/
   MAT_tpCondRet MAT_IrNoSudoeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDOESTE );
   } /* Fim fun��o: MAT Ir para n� � sudoeste */




/***************************************************************************
*
*  Fun��o: MAT Ir para n� � noroeste.
*  ****/
   MAT_tpCondRet MAT_IrNoNoroeste( MAT_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NOROESTE );
   } /* Fim fun��o: MAT Ir para n� � noroeste*/



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: MAT Criar n� da matriz
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
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

   } /* Fim fun��o: MAT Criar n� da matriz */


/***********************************************************************
*
*  $FC Fun��o: MAT Criar n� origem da matriz
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

   } /* Fim fun��o: MAT Criar n� origem da matriz */



/***********************************************************************
*
*  $FC Fun��o: MAT Esvaziar matriz
*  
*  $ED Descri��o da fun��o
*  Libera a mem�ria de todos os n�s que comp�e a estrutura da matriz.
*  da matriz.
*  
*  $EP Par�metros
*     pMatriz - ponteiro para a matriz que ser� esvaziada.
*
***********************************************************************/
   void EsvaziarMatriz( MAT_tpMatriz * pMatriz )
   {
	   tpNoMatriz * pNo = pMatriz->pNoOrigem;
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
	   
	   pMatriz->pNoOrigem = NULL;
	   pMatriz->pNoCorr = NULL;
	   
   } /* Fim fun��o: MAT Destruir a estrutura da matriz */




/***********************************************************************
*
*  $FC Fun��o: MAT Get n� adjacente
*  
*  $ED Descri��o da fun��o
*     Recupera o ponteiro para um n� adjacente
*     Exemplo de uso: GetAdjacente(noOrigem, ESTE)
*  
*  $EP Par�metros
*     pNo - ponteiro para n� que ser� usado como refer�ncia.
*     dir - representa a dire��o � qual ser� buscado o n�.
*
*  $FV Valor retornado
*    Ponteiro para n� adjacente na dire��o passada por
*    par�metro.
*
***********************************************************************/
   tpNoMatriz * GetAdjacente( tpNoMatriz * pNo , tpDirecao dir )
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
   }  /* Fim fun��o: MAT Recupera o ponteiro para um n� adjacente*/



/***********************************************************************
*
*  $FC Fun��o: MAT Constroi a primeira coluna da matriz.
*  
*  $ED Descri��o da fun��o
*  Essa fun��o � chamada no momento de inicializa��o da matriz para
*  criar a primeira coluna com o n�mero de linhas correto e referenciando
*  todos os n�s adjacentes nas dire��es norte e sul
*
*  $EP Par�metros
*     pNoOrigem - ponteiro para o n� origem da matriz.
*     QntLinhas - quantidade de linhas que a coluna ter�.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
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
   }  /* Fim fun��o: MAT Construi a primeira coluna da matriz */



/***********************************************************************
*
*  $FC Fun��o: MAT Adiciona coluna.
*  
*  $ED Descri��o da fun��o
*  Adiciona mais uma coluna � matriz, mantendo o n�mero de linhas e
*  referenciando os n�s adjacentes em todas as 8 dire��es.
*
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que ser� manipulada.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
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
   }  /* Fim fun��o: MAT Adiciona Coluna */



/***********************************************************************
*
*  $FC Fun��o: MAT Apontar de volta em todas as dire��es.
*  
*  $ED Descri��o da fun��o
*  A fun��o faz com que os adjacentes de um n� referenciem � ele.
*  
*  $EP Par�metros
*     pNo - ponteiro para n� que � referenciado por cada dire��o.
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
   }  /* Fim fun��o: MAT Apontar de volta em todas as dire��es */


      


/***************************************************************************
*
*  $FC Fun��o: MAT Ir para n� gen�rico.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o apontada
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*     direcao - representa a dire��o que o n� corrente navegar�.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetNaoTemCorrente
*     MAT_CondRetNaoEhNo
*
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

      if ( GetAdjacente( pMatriz->pNoCorr , direcao ) == NULL )
      {
		  return MAT_CondRetNaoEhNo ;
      } /* if */

	  pMatriz->pNoCorr = GetAdjacente( pMatriz->pNoCorr , direcao ) ;
	  return MAT_CondRetOK ;

   } /* Fim fun��o: MAT Ir para n� gen�rico */

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/
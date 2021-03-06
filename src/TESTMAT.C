/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TMAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*     "=criar"           - chama a fun��o MAT_CriarMatriz( )
*     "=irnorte"         - chama a fun��o MAT_IrNorte( )
*     "=irsul"           - chama a fun��o MAT_IrSul( )
*     "=ireste"          - chama a fun��o MAT_IrEste( )
*     "=iroeste"         - chama a fun��o MAT_IrOeste( )
*     "=irnordeste"      - chama a fun��o MAT_IrNordeste( )
*     "=irsudeste"       - chama a fun��o MAT_IrSudeste( )
*     "=irsudoeste"      - chama a fun��o MAT_IrSudoeste( )
*     "=irnoroeste"      - chama a fun��o MAT_IrNoroeste( )
*     "=atribuir" <Char> - chama a fun��o MAT_AtribuirValorCorr(  )
*     "=destroi"         - chama a fun��o MAT_DestruirMatriz( )
*     "=obter" <Char>    - chama a fun��o MAT_ObterValorCorr( ) e compara
*                          o valor retornado com o valor <Char>
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"
#include    "LISTA.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "matriz.h"

/* Tabela dos nomes dos comandos de teste relacionados ao m�dulo */

#define     CRIAR_MAT_CMD       "=criar"
#define     INIT_MAT_CMD        "=init"
#define     OBTER_VAL_CMD       "=obter"
#define     ATRIBUIR_VAL_CMD    "=atribuir"
#define     DESTROI_CMD         "=destruir"

#define     IR_NORTE_CMD       "=irnorte"
#define     IR_SUL_CMD         "=irsul"
#define     IR_ESTE_CMD        "=ireste"
#define     IR_OESTE_CMD       "=iroeste"
#define     IR_NORDESTE_CMD    "=irnordeste"
#define     IR_SUDESTE_CMD     "=irsudeste"
#define     IR_SUDOESTE_CMD    "=irsudoeste"
#define     IR_NOROESTE_CMD    "=irnoroeste"

/* Tabela dos nomes dos comandos de teste espec�ficos do teste */
#define     VALIDAR_EST_MAT_CMD "=validarEstrutura"
#define     SELECIONAR_CMD       "=selecionar"
#define     VALORES_SIZE 9
#define     MATRIZES_SIZE 10


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
int IndiceDoValor( LIS_tppLista Valor );
void PreencherArrayDeValores();

static MAT_tpMatriz * Matrizes[MATRIZES_SIZE] ;
static LIS_tppLista VALORES[VALORES_SIZE] ;

static int iMat = 0 ;

/***********************************************************************
*
*  $FC Fun��o: TMAT Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      MAT_tpCondRet CondRetObtido   = MAT_CondRetOK ;
      MAT_tpCondRet CondRetEsperada = MAT_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int IndiceValorEsperado = -1;
	  int IndiceValorObtido = -1;
	  int IndiceValorDado = -1;
	  
	  LIS_tppLista ValorObtido = NULL;

	  int Linhas = 0 ;
	  int Colunas = 0 ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;


	  PreencherArrayDeValores();

      /* Testar MAT Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_CriarMatriz( Matrizes + iMat ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." ) ;

         } /* fim ativa: Testar MAT Criar matriz */


      /* Testar MAT Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &IndiceValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ObterValorCorr( Matrizes[iMat] , &ValorObtido ) ;
            
			Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." ) ;

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			
			IndiceValorObtido = IndiceDoValor(ValorObtido) ;

            return TST_CompararInt( IndiceValorEsperado , IndiceValorObtido ,
                                     "Conte�do do n� est� errado." ) ;

         } /* fim ativa: Testar MAT Obter valor corrente */


		/* Testar MAT Atribuir valor corrente */

         else if ( strcmp( ComandoTeste , ATRIBUIR_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
							&IndiceValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_AtribuirValorCorr( Matrizes[iMat] , VALORES[IndiceValorDado] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." ) ;

         } /* fim ativa: Testar MAT Atribuir valor corrente */


      /* Testar MAT Destruir matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_DestruirMatriz( Matrizes + iMat ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o � poss�vel destruir uma matriz que n�o existe.") ;

         } /* fim ativa: Testar MAT Destruir matriz */

		 
      /* Testar MAT Inicializar Matriz */

         else if ( strcmp( ComandoTeste , INIT_MAT_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "iii" ,
                               &Linhas, &Colunas, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_InicializarMatriz( Matrizes[iMat] , Linhas, Colunas ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"Erro ao inicializar matriz.") ;

         } /* fim ativa: Testar MAT Inicializar matriz */

		 
      /* Testar MAT Ir norte */

		 else if ( strcmp( ComandoTeste , IR_NORTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoNorte( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Norte.") ;

         } /* fim ativa: Testar MAT Ir norte */


		/* Testar MAT Ir sul */

		 else if ( strcmp( ComandoTeste , IR_SUL_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoSul( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Sul.") ;

         } /* fim ativa: Testar MAT Ir sul */


		/* Testar MAT Ir este */

		 else if ( strcmp( ComandoTeste , IR_ESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoEste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Este.") ;

         } /* fim ativa: Testar MAT Ir este */


		/* Testar MAT Ir oeste */

		 else if ( strcmp( ComandoTeste , IR_OESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoOeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Oeste.") ;

         } /* fim ativa: Testar MAT Ir oeste */

		 
		/* Testar MAT Ir nordeste */

		 else if ( strcmp( ComandoTeste , IR_NORDESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoNordeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Nordeste.") ;

         } /* fim ativa: Testar MAT Ir nordeste */


		/* Testar MAT Ir sudeste */

		 else if ( strcmp( ComandoTeste , IR_SUDESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoSudeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Sudeste.") ;

         } /* fim ativa: Testar MAT Ir sudeste */


		/* Testar MAT Ir sudoeste */

		 else if ( strcmp( ComandoTeste , IR_SUDOESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoSudoeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Sudoeste.") ;

         } /* fim ativa: Testar MAT Ir sudoeste */


		/* Testar MAT Ir noroeste */

		 else if ( strcmp( ComandoTeste , IR_NOROESTE_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_IrNoNoroeste( Matrizes[iMat] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"N�o foi poss�vel ir para Noroeste.") ;

         } /* fim ativa: Testar MAT Ir noroeste */



      /* Testar Selecionar indice na array de matrizes */

         else if ( strcmp( ComandoTeste , SELECIONAR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &iMat ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( iMat < 0 || iMat > MATRIZES_SIZE - 1 )
			{
				TST_NotificarFalha("S� � poss�vel fazer sele��o nos indices de 0 � 9") ;
				return TST_CondRetErro ;
			} /* if */

			return TST_CondRetOK ;

         } /* fim ativa: Testar MAT Validar estrutura matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TMAT Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

int IndiceDoValor( LIS_tppLista Valor )
{
	int i;

	if ( Valor == NULL )
	{
		return -1;
	}

	for ( i = 0 ; i < VALORES_SIZE ; i++ )
	{
		if ( VALORES[i] == Valor )
		{
			return i;
		}
	}

	return -1;
}

void PreencherArrayDeValores()
{
	int i;

	if ( VALORES[0] != NULL )
	{
		return;
	}

	for ( i = 0 ; i < VALORES_SIZE ; i++ )
	{
		LIS_CriarLista( &VALORES[i] );
	}
}
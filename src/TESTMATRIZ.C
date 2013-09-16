/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TMAT
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
*     Este mÇodulo contém as funções específicas para o teste do
*     módulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo matriz:
*
*     "=criar"           - chama a função MAT_CriarMatriz( )
*     "=irnorte"         - chama a função MAT_IrNorte( )
*     "=irsul"           - chama a função MAT_IrSul( )
*     "=ireste"          - chama a função MAT_IrEste( )
*     "=iroeste"         - chama a função MAT_IrOeste( )
*     "=irnordeste"      - chama a função MAT_IrNordeste( )
*     "=irsudeste"       - chama a função MAT_IrSudeste( )
*     "=irsudoeste"      - chama a função MAT_IrSudoeste( )
*     "=irnoroeste"      - chama a função MAT_IrNoroeste( )
*     "=atribuir" <Char> - chama a função MAT_AtribuirValorCorr(  )
*     "=destroi"         - chama a função MAT_DestruirMatriz( )
*     "=obter" <Char>    - chama a função MAT_ObterValorCorr( ) e compara
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

/* Tabela dos nomes dos comandos de teste relacionados ao módulo */

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

/* Tabela dos nomes dos comandos de teste específicos do teste */
#define     VALIDAR_EST_MAT_CMD "=validarEstrutura"
#define     SELECIONAR_CMD       "=selecionar"
#define     VALORES_SIZE 9
#define     MATRIZES_SIZE 10


/*****  Código das funções exportadas pelo módulo  *****/
int IndiceDoValor( LIS_tppLista Valor );
void PreencherArrayDeValores();

static MAT_tpMatriz * Matrizes[MATRIZES_SIZE] ;
static LIS_tppLista VALORES[VALORES_SIZE] ;

static int iMat = 0 ;

/***********************************************************************
*
*  $FC Função: TMAT Efetuar operações de teste específicas para matriz
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     matriz sendo testado.
*
*  $EP Parâmetros
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
                                     "Conteúdo do nó está errado." ) ;

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
									"Não é possível destruir uma matriz que não existe.") ;

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
									"Não foi possível ir para Norte.") ;

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
									"Não foi possível ir para Sul.") ;

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
									"Não foi possível ir para Este.") ;

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
									"Não foi possível ir para Oeste.") ;

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
									"Não foi possível ir para Nordeste.") ;

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
									"Não foi possível ir para Sudeste.") ;

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
									"Não foi possível ir para Sudoeste.") ;

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
									"Não foi possível ir para Noroeste.") ;

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
				TST_NotificarFalha("Só é possível fazer seleção nos indices de 0 à 9") ;
				return TST_CondRetErro ;
			} /* if */

			return TST_CondRetOK ;

         } /* fim ativa: Testar MAT Validar estrutura matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TMAT Efetuar operações de teste específicas para matriz */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

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
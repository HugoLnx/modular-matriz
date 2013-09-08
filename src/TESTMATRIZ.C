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
*     =criar        - chama a função MAT_CriarMatriz( )
*     =insdir <Char>
*                   - chama a função MAT_InserirDireita( <Char> )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     "=insesq" <Char>
*                   - chama a função MAT_InserirEsquerda( <Char> )
*     "=irpai"      - chama a função MAT_IrPai( )
*     "=iresq"      - chama a função MAT_IrEsquerda( )
*     "=irdir"      - chama a função MAT_IrDireita( )
*     "=obter" <Char>
*                   - chama a função MAT_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a função MAT_DestruirMatriz( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "matriz.h"

/* Tabela dos nomes dos comandos de teste relacionados ao módulo */

#define     CRIAR_MAT_CMD       "=criar"
#define     INIT_MAT_CMD        "=init"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"

/* Tabela dos nomes dos comandos de teste específicos do teste */
#define     VALIDAR_EST_MAT_CMD "=validarEstrutura"
#define     SELECIONAR_CMD       "=selecionar"



/*****  Código das funções exportadas pelo módulo  *****/

static MAT_tpMatriz * Matrizes[10];
static int iMat = 0;

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

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  int Linhas = 0 ;
	  int Colunas = 0 ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;


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

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorEsperado , &CondRetEsperada ) ;
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

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar MAT Obter valor corrente */

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

		 
      /* Testar MAT Validar estrutura Matriz */

         else if ( strcmp( ComandoTeste , VALIDAR_EST_MAT_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "iii" ,
                               &Linhas, &Colunas , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_TestarEstruturaMatriz( Matrizes[iMat] , Linhas, Colunas) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"Estrutura da matriz esta errada.") ;

         } /* fim ativa: Testar MAT Validar estrutura matriz */
		 
      /* Testar Selecionar indice na array de matrizes */

         else if ( strcmp( ComandoTeste , SELECIONAR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &iMat ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( iMat < 0 || iMat > 9 )
			{
				TST_NotificarFalha("Só é possível fazer seleção nos indices de 0 à 9") ;
				return TST_CondRetErro ;
			} /* if */

			return TST_CondRetOK ;

         } /* fim ativa: Testar MAT Validar estrutura matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TMAT Efetuar operações de teste específicas para matriz */

/********** Fim do módulo de implementação: Módulo de teste específico **********/


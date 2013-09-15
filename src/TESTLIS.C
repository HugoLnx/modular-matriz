/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char PROCURAR_ELEM_CMD        [ ] = "=procurarelem"  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  char  CondRetEsp
*     =inselemapos                  inxLista  char  CondRetEsp
*     =obtervalorelem               inxLista  char  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*     =procurarelem                 inxLista  char    CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
      int inxLista   = -1,
          numLidos   = -1,
          CondRetEsp = -1;

      TST_tpCondRet CondRet;
	  LIS_tppLista ppLista = NULL;

      /* Efetuar reset de teste de lista */

         if ( strcmp (ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {
			int i;
            for(i = 0 ; i < DIM_VT_LISTA ; i++)
            {
               vtListas[ i ] = NULL;
            } /* for */

            return TST_CondRetOK;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp ( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii", 
				&inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ! ValidarInxLista ( inxLista , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = LIS_CriarLista( &ppLista );

			if( CondRet ==  LIS_CondRetOK )
			{
				vtListas[ inxLista ] = ppLista;
				return TST_CompararPonteiroNulo( 1 ,vtListas[ inxLista ] , "Erro em ponteiro de nova lista." ) ;
			}

			return TST_CondRetErro;

         } /* fim ativa: Testar CriarLista */

		 /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */
     
      /* Testar inserir elemento antes */

         else if ( strcmp ( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {
            char dadoAInserir = 0;

            numLidos = LER_LerParametros( "ici", 
				&inxLista , &dadoAInserir, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista( inxLista , NAO_VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
   
            CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , dadoAInserir ) ;

            if ( CondRet != LIS_CondRetOK )
            {
                TST_NotificarFalha( "Não foi possivel inserir elemento antes" ) ;
				return TST_CondRetErro;
            } /* if */

            return TST_CompararInt( CondRetEsp, CondRet , "Condicao de retorno errada ao inserir antes." ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp ( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {
			char dadoAInserir;

            numLidos = LER_LerParametros( "ici" , 
				  &inxLista, &dadoAInserir , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) 
				|| ( ! ValidarInxLista ( inxLista, NAO_VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_InserirElementoApos( vtListas [ inxLista ], dadoAInserir ) ;

            if ( CondRet != LIS_CondRetOK )
            {
				TST_NotificarFalha ( "Não foi possivel inserir elemento apos" ) ;
				return TST_CondRetErro;
            } /* if */

            return TST_CompararInt( CondRetEsp, CondRet, "Condicao de retorno errada ao inserir apos." ) ;

         } /* fim ativa: Testar inserir elemento apos */

		  /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

		 /* Testar obter valor do elemento corrente */

         else if ( strcmp ( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {
			char dadoObtido = 0;
			char dadoEsperado = 0;

            numLidos = LER_LerParametros("ici", 
				&inxLista , &dadoEsperado , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ! ValidarInxLista ( inxLista, NAO_VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_ObterValor( vtListas[inxLista] , &dadoObtido ) ;

			if( CondRet != TST_CondOK )
			{
				return CondRet;
			}

			return TST_CompararChar(dadoEsperado,dadoObtido,"Valor do elemento errado.");

         } /* fim ativa: Testar obter valor do elemento corrente */


		 /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

		  /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

		 /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

	  /* LIS  &Avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {
			 int numElem = -1;

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */

		  /* LIS  &Procurar elemento */

         else if ( strcmp( ComandoTeste , PROCURAR_ELEM_CMD ) == 0 )
         {
			char dadoASerProcurado = -1;

            numLidos = LER_LerParametros( "ici" , &inxLista , &dadoASerProcurado ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ProcurarValor(vtListas[ inxLista ], dadoASerProcurado),
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/


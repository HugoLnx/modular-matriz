/***************************************************************************
*  $MCI M�dulo de implementa��o: TLIS Teste lista de s�mbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: rc
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       rc    12/set/2013 Adapta��o da fun��o CriarLista para ser testavel e testes para inser��o de somente valores char.
*     2       rc    15/set/2013 Implementa��o e adapta��o do restante das fun��es de teste para testar somente dado o tipo char.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"


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

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS &Testar lista
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =criarlista                   inxLista  CondRetEsp
*     =destruirlista                inxLista  CondRetEsp
*     =esvaziarlista                inxLista  CondRetEsp
*     =inselemantes                 inxLista  char  CondRetEsp
*     =inselemapos                  inxLista  char  CondRetEsp
*     =obtervalorelem               inxLista  char  CondRetEsp
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista  CondRetEsp
*     =irfinal                      inxLista  CondRetEsp
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

      /* Testar CriarLista */

         if ( strcmp ( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
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

            numLidos = LER_LerParametros( "ii" ,
				&inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

           return TST_CompararInt( CondRetEsp, CondRet, "Erro ao destruir lista" ) ;

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
                TST_NotificarFalha( "N�o foi possivel inserir elemento antes" ) ;
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
				TST_NotificarFalha ( "N�o foi possivel inserir elemento apos" ) ;
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
                     "Condi��o de retorno errada ao excluir."   ) ;

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

            numLidos = LER_LerParametros( "ii" ,
				&inxLista, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_IrInicioLista( vtListas[ inxLista ] ) ;

			return TST_CompararInt(CondRetEsp, LIS_IrInicioLista( vtListas[ inxLista ] ), "Erro ao ir para o inicio da lista" );

         } /* fim ativa: Testar ir para o elemento inicial */

		  /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , 
				&inxLista ,  &CondRetEsp) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt(CondRetEsp, LIS_IrFinalLista( vtListas[ inxLista ] ), "Erro ao ir para o final da lista" );

         } /* fim ativa: LIS  &Ir para o elemento final */

		 /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
				&inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			return TST_CompararInt(CondRetEsp, LIS_EsvaziarLista( vtListas[ inxLista ] ), "Erro ao esvaziar a lista" ) ;

         } /* fim ativa: Testar Esvaziar lista lista */

	  /* LIS  &Avan�ar elemento */

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

         } /* fim ativa: LIS  &Avan�ar elemento */

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

         } /* fim ativa: LIS  &Avan�ar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TLIS &Testar lista */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
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

   } /* Fim fun��o: TLIS -Validar indice de lista */

/********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/


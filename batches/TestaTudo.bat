REM executa os testes dos módulos LISTA e MATRIZ

mkdir resultadosDosTestes

del estatisticas.estat

TRAB1-1\executavel\TRAB1-1      /sTRAB1-1\scripts\TesteLista.script     /lresultadosDosTestes\TesteLista.log     /aresultadosDosTestes\estatisticas

TRAB1-2\executavel\TRAB1-2      /sTRAB1-1\scripts\TesteMatriz.script     /lresultadosDosTestes\TesteMatriz.log     /aresultadosDosTestes\estatisticas

ferramentas\CompileBanner     /c"Estatisticas acumuladas"
ferramentas\exbestat /eresultadosDosTestes\estatisticas
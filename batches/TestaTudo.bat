REM executa os testes dos módulos LISTA e MATRIZ

del estatisticas.estat

..\Debug\lista      /s..\src\TesteLista.script     /lTesteLista.log     /aestatisticas

..\Debug\matriz      /s..\src\TesteMatriz.script     /lTesteMatriz.log     /aestatisticas

..\ferramentas\CompileBanner     /c"Estatisticas acumuladas"
..\ferramentas\exbestat /eestatisticas
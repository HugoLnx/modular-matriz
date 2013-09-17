
rmdir /s /q entrega

mkdir deploy
mkdir deploy\ferramentas

mkdir deploy\TRAB1-1
mkdir deploy\TRAB1-1\src
mkdir deploy\TRAB1-1\scripts
mkdir deploy\TRAB1-1\lib
mkdir deploy\TRAB1-1\src
mkdir deploy\TRAB1-1\batches
mkdir deploy\TRAB1-1\executavel
mkdir deploy\TRAB1-1\src
mkdir deploy\TRAB1-1\src\definicao
mkdir deploy\TRAB1-1\src\implementacao

mkdir deploy\TRAB1-2
mkdir deploy\TRAB1-2\src
mkdir deploy\TRAB1-2\scripts
mkdir deploy\TRAB1-2\lib
mkdir deploy\TRAB1-2\src
mkdir deploy\TRAB1-2\batches
mkdir deploy\TRAB1-2\executavel
mkdir deploy\TRAB1-2\src
mkdir deploy\TRAB1-2\src\definicao
mkdir deploy\TRAB1-2\src\implementacao

copy ferramentas\compilebanner.exe deploy\ferramentas
copy ferramentas\exbestat.exe deploy\ferramentas
copy ferramentas\exe2txt.bat deploy\ferramentas
copy ferramentas\txt2exe.bat deploy\ferramentas
copy Debug\lista.exe deploy\TRAB1-1\executavel
rename deploy\TRAB1-1\executavel\lista.exe TRAB1-1.EXE
copy src\ArcaboucoTeste.lib deploy\TRAB1-1\lib
copy src\TesteLista.script deploy\TRAB1-1\scripts
copy src\LISTA.H deploy\TRAB1-1\src\definicao
copy src\LISTA.C deploy\TRAB1-1\src\implementacao
copy src\TESTLIS.C deploy\TRAB1-1\src\implementacao
copy batches\TestaLista.bat deploy\TRAB1-1\batches
copy batches\LimpaTudo.bat deploy\TRAB1-1\batches

copy Debug\matriz.exe deploy\TRAB1-2\executavel
rename deploy\TRAB1-2\executavel\matriz.exe TRAB1-2.EXE
copy src\ArcaboucoTeste.lib deploy\TRAB1-2\lib
copy src\lista.lib deploy\TRAB1-2\lib
copy src\TesteMatriz.script deploy\TRAB1-2\scripts
copy src\MATRIZ.H deploy\TRAB1-2\src\definicao
copy src\MATRIZ.C deploy\TRAB1-2\src\implementacao
copy src\TESTMATRIZ.C deploy\TRAB1-2\src\implementacao
copy batches\TestaMatriz.bat deploy\TRAB1-2\batches
copy batches\LimpaTudo.bat deploy\TRAB1-2\batches

copy batches\TestaTudo.bat deploy\
copy batches\LimpaTudo.bat deploy\

call ferramentas\exe2txt.bat deploy

copy LEIAME.txt deploy\

del deploy.zip

ferramentas\7za a -tzip deploy.zip deploy

rmdir /s /q deploy



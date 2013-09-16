
rmdir /s /q entrega

mkdir entrega
mkdir entrega\ferramentas

mkdir entrega\TRAB1-1
mkdir entrega\TRAB1-1\src
mkdir entrega\TRAB1-1\scripts
mkdir entrega\TRAB1-1\lib
mkdir entrega\TRAB1-1\src
mkdir entrega\TRAB1-1\batches
mkdir entrega\TRAB1-1\executavel
mkdir entrega\TRAB1-1\src
mkdir entrega\TRAB1-1\src\definicao
mkdir entrega\TRAB1-1\src\implementacao

mkdir entrega\TRAB1-2
mkdir entrega\TRAB1-2\src
mkdir entrega\TRAB1-2\scripts
mkdir entrega\TRAB1-2\lib
mkdir entrega\TRAB1-2\src
mkdir entrega\TRAB1-2\batches
mkdir entrega\TRAB1-2\executavel
mkdir entrega\TRAB1-2\src
mkdir entrega\TRAB1-2\src\definicao
mkdir entrega\TRAB1-2\src\implementacao

copy ferramentas\ entrega\ferramentas
copy Debug\lista.exe entrega\TRAB1-1\executavel
rename entrega\TRAB1-1\executavel\lista.exe TRAB1-1.exe
copy src\ArcaboucoTeste.lib entrega\TRAB1-1\lib
copy src\TesteLista.script entrega\TRAB1-1\scripts
copy src\LISTA.H entrega\TRAB1-1\src\definicao
copy src\LISTA.C entrega\TRAB1-1\src\implementacao
copy src\TESTLIS.C entrega\TRAB1-1\src\implementacao
copy batches\TestaLista.bat entrega\TRAB1-1\batches
copy batches\LimpaTudo.bat entrega\TRAB1-1\batches

copy Debug\matriz.exe entrega\TRAB1-2\executavel
rename entrega\TRAB1-2\executavel\matriz.exe TRAB1-2.exe
copy src\ArcaboucoTeste.lib entrega\TRAB1-2\lib
copy src\lista.lib entrega\TRAB1-2\lib
copy src\TesteMatriz.script entrega\TRAB1-2\scripts
copy src\MATRIZ.H entrega\TRAB1-2\src\definicao
copy src\MATRIZ.C entrega\TRAB1-2\src\implementacao
copy src\TESTMATRIZ.C entrega\TRAB1-2\src\implementacao
copy batches\TestaMatriz.bat entrega\TRAB1-2\batches
copy batches\LimpaTudo.bat entrega\TRAB1-2\batches

copy batches\TestaTudo.bat entrega\
copy batches\LimpaTudo.bat entrega\

pkzipc entrega -add=up 





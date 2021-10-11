cd D:\C++\inventory\bl\src
del *.o
g++ -c *.cpp -I ..\include -I ..\..\common\include -I ..\..\dl\include
ar rcs ..\lib\blinventory.lib *.o
cd ..\testcases
g++ add.cpp -o add.exe -I ..\..\common\include -I ..\..\bl\include -L ..\..\dl\lib -L ..\..\common\lib -L ..\lib -l blinventory -l dlinventory -l common
g++ getall.cpp -o getall.exe -I ..\..\common\include -I ..\..\bl\include -L ..\..\dl\lib -L ..\..\common\lib -L ..\lib -l blinventory -l dlinventory -l common
g++ get.cpp -o get.exe -I ..\..\common\include -I ..\..\bl\include -L ..\..\dl\lib -L ..\..\common\lib -L ..\lib -l blinventory -l dlinventory -l common
g++ getbytitle.cpp -o getbytitle.exe -I ..\..\common\include -I ..\..\bl\include -L ..\..\dl\lib -L ..\..\common\lib -L ..\lib -l blinventory -l dlinventory -l common
g++ update.cpp -o update.exe -I ..\..\common\include -I ..\..\bl\include -L ..\..\dl\lib -L ..\..\common\lib -L ..\lib -l blinventory -l dlinventory -l common
g++ remove.cpp -o remove.exe -I ..\..\common\include -I ..\..\bl\include -L ..\..\dl\lib -L ..\..\common\lib -L ..\lib -l blinventory -l dlinventory -l common
g++ removebytitle.cpp -o removebytitle.exe -I ..\..\common\include -I ..\..\bl\include -L ..\..\dl\lib -L ..\..\common\lib -L ..\lib -l blinventory -l dlinventory -l common
pause
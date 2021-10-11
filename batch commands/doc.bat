cd D:\C++\inventory\dl\src
del *.o
g++ -c *.cpp -I ..\include -I ..\..\common\include
ar rcs ..\lib\dlinventory.lib *.o
cd ..\testcases
g++ add.cpp -o add.exe -I ..\include -I ..\..\common\include -L ..\lib -L ..\..\common\lib -ldlinventory -l common
g++ get.cpp -o get.exe -I ..\include -I ..\..\common\include -L ..\lib -L ..\..\common\lib -ldlinventory -l common
g++ getall.cpp -o getall.exe -I ..\include -I ..\..\common\include -L ..\lib -L ..\..\common\lib -ldlinventory -l common
g++ remove.cpp -o remove.exe -I ..\include -I ..\..\common\include -L ..\lib -L ..\..\common\lib -ldlinventory -l common
g++ update.cpp -o update.exe -I ..\include -I ..\..\common\include -L ..\lib -L ..\..\common\lib -ldlinventory -l common
g++ getbytitle.cpp -o getbytitle.exe -I ..\include -I ..\..\common\include -L ..\lib -L ..\..\common\lib -ldlinventory -l common
pause
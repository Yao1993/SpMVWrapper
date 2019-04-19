"C:\Program Files (x86)\IntelSWTools\compilers_and_libraries_2019\windows\mkl\bin\mklvars.bat" intel64
if not exist build mkdir build
cd build
del * /s /q
FOR /D %%p IN ("./*.*") DO rmdir "%%p" /s /q
cmake -G "Visual Studio 15 2017 Win64"  -DCMAKE_TOOLCHAIN_FILE=c:/MyLib/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cd ..
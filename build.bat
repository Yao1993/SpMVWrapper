cd build
del * /s /q
FOR /D %%p IN ("./*.*") DO rmdir "%%p" /s /q
cmake -G "Visual Studio 15 2017 Win64"  -DCMAKE_TOOLCHAIN_FILE=c:/MyLib/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cd ..
cd build
del * /s /q
FOR /D %%p IN ("./*.*") DO rmdir "%%p" /s /q
cmake -G "Visual Studio 15 2017 Win64" ..
cd ..
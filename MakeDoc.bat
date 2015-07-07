echo off
set WEB_PATH=D:\proyectos\stream\doc
del /F /S /Q %WEB_PATH%
docxx.exe -H -p -R -v -a -S -b -nd -u -y -G -M -W -T header.html -d %WEB_PATH% -M .\src\io\*.h .\src\sync\*.h .\src\cryptoapi\*.h .\src\exceptions\*.h .\src\net\*.h .\src\sql\*.h .\src\util\*.h .\src\zip\*.h
echo "Doc++"
echo on

cc=cl /c
ii=/I ..\..\ctree.drivers\include /I ..\..\ctree.drivers\include\openssl
linker=link /DLL
libdirs=/LIBPATH:"..\..\ctree.drivers\lib\License.Lib\openssl\winX64\Microsoft Visual Studio 2017" /LIBPATH:"..\..\ctree.drivers\lib\License.Lib\openssl\win32\Microsoft Visual Studio 2017"
libs=libeay32.lib ssleay32.lib gdi32.lib advapi32.lib user32.lib

all: bin\maskeylib.dll

maskeylib.obj:src\maskeylib.c
  $(cc) $(ii) src\maskeylib.c

ctmsklib.obj:src\ctmsklib.c
  $(cc) $(ii) src\ctmsklib.c

bin\maskeylib.dll: maskeylib.obj ctmsklib.obj
  $(linker) $(libdirs) maskeylib.obj ctmsklib.obj $(libs) /OUT:bin\maskeylib.dll

clean:
  del *.obj
  del bin\*.lib
  del bin\*.dll
  del bin\*.exp
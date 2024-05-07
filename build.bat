@echo off
del *.pdb > NUL 2> NUL

set CL_OPTS=/EHsc /nologo /W4 /Zi /MTd /std:c++17 /DDEBUG

cl %CL_OPTS% %*

del *.obj

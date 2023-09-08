@echo off
del *.pdb > NUL 2> NUL

set CL_OPTS=/EHsc /nologo /W4 /Zi /DEBUG /std:c++17

cl %CL_OPTS% %*

del *.obj

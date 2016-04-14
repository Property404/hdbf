@SET pwd=%CD%
@cd "%~dp0"
@tcc main.c hdbf.c binarytree.c -o hdbf.exe
@cd "%pwd%"


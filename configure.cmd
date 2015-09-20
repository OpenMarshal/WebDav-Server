@echo off

@if exist makefile del /f makefile

@echo OPERATING_SYSTEM = windows > makefile
@echo -include _makefile >> makefile

echo Configuration finished.
echo Now you can use "make".
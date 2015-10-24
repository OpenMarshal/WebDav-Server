@echo off

@if exist makefile del /f makefile

@echo OPERATING_SYSTEM = windows > makefile
@echo -include _makefile >> makefile

scanfiles.cmd

echo Configuration finished.
echo Now you can use "make".
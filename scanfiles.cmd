@echo off
setlocal EnableDelayedExpansion

@if exist makefile del /f _objs

echo OBJSX = \> _objs

setlocal disableDelayedExpansion
for /f "delims=" %%A in ('forfiles /s /p src /m *.cpp /c "cmd /c echo @FNAME"') do (
	set "file=%%~A"
	setlocal enableDelayedExpansion
	set "tps=	$(OBJECT_DIR)/"
	set "tps2=.o \"
	set tps=!tps!!file!!tps2!
	
	echo !tps!>> _objs
	endlocal
)
echo. >> _objs

setlocal enableDelayedExpansion
set lxn=
for /f "delims=" %%A in ('forfiles /s /p src /m *.cpp /c "cmd /c echo @FNAME"') do (
	set "file=%%~A"
	set "tps=$(OBJECT_DIR)/"
	set "tps2=.o"
	set tps=!tps!!file!!tps2!
	
	set lxn=!lxn! !tps!
)
echo build_objs: !lxn!>> _objs
endlocal

echo. >> _objs


for /f "delims=" %%A in ('forfiles /s /p src /m *.cpp /c "cmd /c echo @relpath"') do (
setlocal enableDelayedExpansion
	set name=
	for %%F in (%%~A) do set name=%%~nxF
	set name=!name:.cpp=!
	
	set "dest=$(OBJECT_DIR)/"
	set "dest2=.o"
	set dest=!dest!!name!!dest2!
	
	set "source=%%~A"
	set source=!source:~2!

	set "firstLine=: $(SOURCE_DIR)/"
	
	set "secondLine1=	@$(COMP) $(CFLAGS) -c $(SOURCE_DIR)/"
	set "secondLine2= -o "
	set "secondLine3= $(LIBS)"
	
	echo !dest!!firstLine!!source! >> _objs
	echo !secondLine1!!source!!secondLine2!!dest!!secondLine3! >> _objs
endlocal
)

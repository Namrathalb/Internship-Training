@echo off

echo py -0
py -0
set n=0
for /f "tokens=* USEBACKQ" %%G IN (`py -0`) do (
set vector[!n!]=%%G
set /A n+=1
echo %%G    
)
for /l %%a in (0,1,3) do (
   echo %!vector[%%a]!%
   echo/
)

PAUSE
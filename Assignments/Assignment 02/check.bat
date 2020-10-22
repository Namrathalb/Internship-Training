@echo off
title Python 3.6.0 Extensions Installer
echo.
GOTO greetings

rem ========================================Menu Function========================================
:mainMenu  
echo ===================MAIN MENU===========================
echo Check Python Version     [PRESS 1]
echo Exit                     [PRESS 0]
echo =======================================================
set cv=3.6.0
set /P id=Please enter number: 
call:log "User entered the choice %id%"
IF '%id%' == '1' GOTO 1
IF '%id%' == '0' GOTO 0
call:log "mainMenu"
GOTO mainMenu 

rem ====================================Check Python Version======================================
:1
echo Checking python against version 3.6.0 Please wait
echo ......................................................
call:log "Checking version 3.6.0 in system"
for /f "tokens=* USEBACKQ" %%F IN (`python --version`) do (
set var=%%F
) 
echo.%var%
call:log "%var% version found." 
pause

IF "%var%"=="" (
   call:log "No Python version present."
   goto :5
) 
for /f "tokens=1,2 delims= " %%G IN ("%var%") do ( 
  set t=%%G  
  set v=%%H
)
if "%v%" EQU "%cv%" (
  call:log "Recommended Version %v% present."
  call:log "calling: Existing Function."
  goto :2
)
if "%v%" GTR "%cv%" ( 
  call:log "%v% is Greater than %cv%, Higher version present."
  call:log "calling: Dowgrade Function."
  goto :3
)
if "%v%" LSS "%cv%" (  
  call:log "%v% is Lesser than %cv%, Lower version present."
  call:log "calling: Upgrade Function."
  goto :4
)
call:log "mainMenu"
GOTO mainMenu
exit 

rem ==================================Already Exist Function========================================
:2
call:log "%cv% version is present(Recommended) in system."
echo "...current version installed; exiting ..."
pause
call:log "mainMenu"
GOTO mainMenu

rem ========================================Downgrade Function======================================
:3
echo "it is greater want to downgrade?:  Y/N" 
set /P ot=:
call:log "User choice: %ot%." 
IF '%ot%' == 'N' goto :eof
IF '%ot%' == 'n' goto :eof
call:log "Now Downgrading %v% to %cv% please wait."
echo "Please wait for few moments...."
start "" /w /b "python-3.6.0-amd64.exe" /quiet InstallAllUsers=1 PrependPath=1 Include_test=1 Include_launcher=1 Include_exe=1 AssociateFiles=1 Include_tcltk=1
echo "Software Python 3.6.0 version Installation Completed...." ^& echo."Downgrade Done"
call:log "Recommended version Installation is Completed."
pause
call:log "mainMenu"
GOTO mainMenu

rem =========================================Upgrade Function========================================
:4
echo "it is lower want to upgrade?:  Y/N"
set /P ot=: 
call:log "User choice: %ot%." 
IF '%ot%' == 'N' goto :eof
IF '%ot%' == 'n' goto :eof
call:log "Now Upgrading %v% to %cv% please wait."
echo "Please wait for few moments...."
start "" /w /b "python-3.6.0-amd64.exe" /quiet InstallAllUsers=1 PrependPath=1 Include_test=0 Include_launcher=1 Include_exe=1 AssociateFiles=1 Include_tcltk=1
echo "Software Python 3.6.0 version Installation Completed...." ^& echo."Upgrade Done"
call:log "Recommended version Installation is Completed."
pause
call:log "mainMenu"
GOTO mainMenu

rem ========================================Install Function==========================================
:5
echo "no python version is present, Installing Python 3.6.0 Please wait for few moments...." 
call:log "Installing Python %cv% version Please wait for few moments."
start "" /w /b "python-3.6.0-amd64.exe" /quiet InstallAllUsers=1 PrependPath=1 Include_test=0 Include_launcher=1 Include_exe=1 AssociateFiles=1 Include_tcltk=1
echo "Installation Completed."
call:log "Recommended version %cv% Installation is Completed." 
pause
call:log "mainMenu"
GOTO mainMenu

rem ==========================================Exit Function===========================================
:0
echo Are you sure you want to exit? Y/N
call:log "Exit Program?"
set /P opt=:
call:log "user selected %ot% option."
IF '%opt%' == 'N' GOTO mainMenu
IF '%opt%' == 'n' GOTO mainMenu
call:log "User exited the program."
exit /B 0

::=========================================Greetings Function=========================================
:greetings
echo                * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
echo                * Hi %USERNAME%,                                             *
echo                * Welcome to Python Extensions Installer, a quick and easy   * 
echo                * way to install Python 3.6.0 Version.                       *                   
echo                *                                                            *
echo                * Created by:         QuEST Global Pvt Ltd.                  *
echo                * Modified Date : Oct 22, 2020                               *
echo                * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **

for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%"
set "fullstamp=%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%"
echo LOG FILE: "%fullstamp%"
SET filename=%fullstamp%.txt
echo Please press 'ENTER' to continue
pause >nul
call:log "mainMenu"	
GOTO mainMenu 

:log
  echo %date% %time% %~1 >> %filename%.txt
exit /B 0

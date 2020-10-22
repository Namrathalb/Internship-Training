@echo off
title Python 3.6.0 Extensions Installer
echo.
GOTO greetings

rem ========================================Menu Function========================================
:mainMenu  
echo %date%, %time%, mainMENU Function >> %filename%.txt
echo.
echo ===================MAIN MENU===========================
echo Check Python Version     [PRESS 1]
echo Exit                     [PRESS 0]
echo =======================================================
echo.
set cv=3.6.0
set /P id=Please enter number: 
echo %date%, %time%, user entered the choice %id% >> %filename%.txt
IF '%id%' == '1' GOTO 1
IF '%id%' == '0' GOTO 0
GOTO mainMenu 

rem ====================================Check Python Version======================================
:1
echo Checking python against version 3.6.0 Please wait
echo ......................................................
echo %date%, %time%, Checking for version 3.6.0 in system >> %filename%.txt
for /f "tokens=* USEBACKQ" %%F IN (`python --version`) do (
set var=%%F
) 
echo.%var% 
pause

IF "%var%"=="" (
   echo "No Python version is present. Please Install"
   echo %date%, %time%, No Python id present in the system >> %filename%.txt
   goto :5
) 

for /f "tokens=1,2 delims= " %%G IN ("%var%") do ( 
  set t=%%G  
  set v=%%H
)

if "%v%" EQU "%cv%" (
  goto :2
)

if "%v%" GTR "%cv%" ( 
  goto :3
)

if "%v%" LSS "%cv%" (  
  goto :4
)
GOTO mainMenu
exit 

rem ==================================Already Exist Function========================================
:2
echo %date%, %time%, 3.6.0 version is present(Recommended) in system >> %filename%.txt
echo "...current version installed; exiting ..."
echo %date%, %time%, Recommended version installed in system.>> %filename%.txt
pause
GOTO mainMenu

rem ========================================Downgrade Function======================================
:3
echo %date%, %time%, %v% version is present and it is Greater than Recommended version >> %filename%.txt
echo "it is greater want to downgrade?:  Y/N" 
echo %date%, %time%, it is greater want to downgrade? >> %filename%.txt
set /P ot=:
echo %date%, %time%, user selected %ot% option >> %filename%.txt
IF '%ot%' == 'N' goto :eof
IF '%ot%' == 'n' goto :eof
echo %date%, %time%, Now downgrading %v% to %cv% >> %filename%.txt
echo %date%, %time%, Installing %cv%... >> %filename%.txt
echo "Please wait for few moments...."
echo %date%, %time%, waiting for few moments to finish installing %cv%... >> %filename%.txt
start "" /w /b "python-3.6.0-amd64.exe" /quiet InstallAllUsers=1 PrependPath=1 Include_test=1 Include_launcher=1 Include_exe=1 AssociateFiles=1 Include_tcltk=1
echo "Software Python 3.6.0 version Installation Completed...."
echo "Downgrade Done"
echo %date%, %time%, %cv% Recommended version Installation is Completed... >> %filename%.txt
pause
GOTO mainMenu

rem =========================================Upgrade Function========================================
:4
echo %date%, %time%, %v% version is present and it is Lesser than Recommended version>> %filename%.txt
echo "it is lower want to upgrade?:  Y/N"
echo %date%, %time%, it is lower want to upgrade? >> %filename%.txt
set /P ot=: 
echo %date%, %time%, user selected %ot% option >> %filename%.txt
IF '%ot%' == 'N' goto :eof
IF '%ot%' == 'n' goto :eof
echo %date%, %time%, Now Upgrading %v% to %cv% >> %filename%.txt
echo %date%, %time%, Installing %cv%... >> %filename%.txt
echo "Please wait for few moments...."
echo %date%, %time%, waiting for few moments to finish installing %cv%... >> %filename%.txt
start "" /w /b "python-3.6.0-amd64.exe" /quiet InstallAllUsers=1 PrependPath=1 Include_test=0 Include_launcher=1 Include_exe=1 AssociateFiles=1 Include_tcltk=1
echo "Software Python 3.6.0 version Installation Completed...."
echo "Upgrade Done"
echo %date%, %time%, %cv% Recommended version Installation is Completed... >> %filename%.txt
pause
GOTO mainMenu

rem ========================================Install Function==========================================
:5
echo "Installing Python 3.6.0...." 
echo %date%, %time%, Installing Python %cv% version... >> %filename%.txt
echo "Please wait for few moments...."
echo %date%, %time%, waiting for few moments to finish installing %cv%... >> %filename%.txt
start "" /w /b "python-3.6.0-amd64.exe" /quiet InstallAllUsers=1 PrependPath=1 Include_test=0 Include_launcher=1 Include_exe=1 AssociateFiles=1 Include_tcltk=1
echo "Python 3.6.0 version Installation Completed...."
echo %date%, %time%, %cv% Recommended version Installation is Completed >> %filename%.txt
pause
GOTO mainMenu

rem ==========================================Exit Function===========================================
:0
echo Are you sure you want to exit? Y/N
echo %date%, %time%, Are you sure you want to exit? >> %filename%.txt
set /P opt=:
echo %date%, %time%, user selected %ot% option >> %filename%.txt
IF '%opt%' == 'N' GOTO mainMenu
IF '%opt%' == 'n' GOTO mainMenu
echo %date%, %time%, User exited the program >> %filename%.txt
exit /b %errorlevel%

::=========================================Greetings Function=========================================
:greetings
echo                       * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
echo                       * Hi %USERNAME%,                                             *
echo                       * Welcome to Python Extensions Installer, a quick and easy   * 
echo                       * way to install Python 3.6.0 Version.                       *                   
echo                       *                                                            *
echo                       * Created by:         QuEST Global Pvt Ltd.                  *
echo                       * Date last modified: Oct 21, 2020                           *
echo                       *                                                            *
echo                       * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
echo.

for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%"

set "datestamp=%YYYY%%MM%%DD%" & set "timestamp=%HH%%Min%%Sec%"
set "fullstamp=%YYYY%-%MM%-%DD%_%HH%-%Min%-%Sec%"

echo LOG FILE: "%fullstamp%"
SET filename=%fullstamp%.txt

echo Please press 'ENTER' to continue
pause >nul	
echo.
GOTO mainMenu > %filename%.txt

$recommendversion = "3.6.0"

$x = python --version
$CharArray =$x.Split(" ")
$presentversion = $CharArray[1]
$presentversion


if($presentversion -eq $recommendversion){
    write-host("same")
 } elseif($presentversion -gt $recommendversion){
    write-host("install")
 } elseif($presentversion -lt $recommendversion){
    write-host("update")
 } else {
    write-host("install again")
 }


 $pythonVersion = "3.6.0"

$pythonDownloadPath = 'C:\Users\questuser\Desktop\Assigments\Assignment 02\Python Installer\python-3.6.0-amd64.exe'
$pythonInstallDir = "C:\Tools\Python$pythonVersion"

$Arguments = @()
$Arguments += "/i"
$Arguments += 'InstallAllUsers="1"'
$Arguments += 'TargetDir="' + $pythonInstallDir + '"'
$Arguments += 'DefaultAllUsersTargetDir="' + $pythonInstallDir + '"'
$Arguments += 'AssociateFiles="1"'
$Arguments += 'PrependPath="1"'
$Arguments += 'Include_doc="1"'
$Arguments += 'Include_debug="1"'
$Arguments += 'Include_dev="1"'
$Arguments += 'Include_exe="1"'
$Arguments += 'Include_launcher="1"'
$Arguments += 'InstallLauncherAllUsers="1"'
$Arguments += 'Include_lib="1"'
$Arguments += 'Include_pip="1"'
$Arguments += 'Include_symbols="1"'
$Arguments += 'Include_tcltk="1"'
$Arguments += 'Include_test="1"'
$Arguments += 'Include_tools="1"'
$Arguments += 'Include_launcher="1"'

$Arguments += "/passive"

start-process $pythonDownloadPath -ArgumentList $Arguments
if ($LASTEXITCODE -ne 0) {
    throw "The python installer at '$pythonDownloadPath' exited with error code '$LASTEXITCODE'"
}
# Set the PATH environment variable for the entire machine to include the Python install dir
[Environment]::SetEnvironmentVariable("PATH", "${env:path};${pythonInstallDir}", "Machine")
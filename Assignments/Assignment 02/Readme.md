The check.bat is a batch file used to check the version of python in the system presnt and perform operation based on it.

**NOTE :** 
**python-3.6.0-amd64.exe is more than 25 MB, Hence not inculded in this repo please download the file and keep it in same directory as Batch file.**


Option 1): if a version of PYTHON is already installed check its version. If the VERSION is less than 3.6 or NO VERSION is installed then install PYTHON 3.6.0 version. 
Note: BATCH file should check the installed software version anywhere in the system.

Option 2):  if Lesser VERSION is present BACKGROUND UPGRADE (Hidden mode update) to 3.6.0 PYTHON VERSION.
Note: BATCH file should perform the process in background so user can’t see the process.

Option 3): if PYTHON VERSION 3.6.0 is present Nothing to be done.
Note: ECHO message to user that Recommended Software version is installed a running.

Option 4): if PYTHON VERSION greater than 3.6.0 is present let user know that 3.6.0 is the VERSION to be installed and make appropriate comment asking for the installing.
Note: if PYTHON is not all present in the system it should install 3.6.0 VERSION.

Option 5): Install the recommended version if python is not at all present in the system.
Note: version check command returns a null empty space 


Note: logs are created for the program respectively

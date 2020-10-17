param([string]$installFolder = "C:\\")
Set-PSDebug -Trace 1

python.exe ZenUnitPy\ZenUnitPy\BuildAndInstallZenUnitAndMetalMock.py `
   --cmake-generator="Visual Studio 16 2019" `
   --cmake-architecture="x64" `
   --cmake-build-type="Debug" `
   --cmake-definitions="-DCMAKE_INSTALL_PREFIX=$installFolder"
   
Set-PSDebug -Trace 0

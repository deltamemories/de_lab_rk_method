## In develop
paste in IDE env:  
PATH="PATH_TO_QT_BIN;%PATH%";
QML2_IMPORT_PATH=PATH_TO_QT_QML

## Build release
build .exe in release mode  
copy .exe in separate folder  
open qt console  
change dir to path to .exe  
run:  
```shell
windeployqt6 --qmldir "PATH TO REPOSITORY WITH .qml files" de_lab_rk_method.exe
```
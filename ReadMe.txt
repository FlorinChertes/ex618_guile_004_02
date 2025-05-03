# ex618_guile_004_01
I learn guile.

add to PATH
C:\Qt\5.15.2\msvc2019_64

QT_QPA_PLATFORM_PLUGIN_PATH 
C:\Qt\5.15.2\msvc2019_64\plugins\platforms

CMake GUI
H:/users/prj_app/dev/ex618_guile_004_01
H:/users/prj_app/build/ex618_guile_004_01

$env:PATH += ";U:\3rdparty\qt64_5.15.12\bin"

CMake gui
	Ungrouped Entries PATH

	Qt5_DIR				U:/3rdparty/qt64_5.15.12/lib/cmake/Qt5
	Qt5Core_DIR			U:/3rdparty/qt64_5.15.12/lib/cmake/Qt5Core
	Qt5Gui_DIR			U:/3rdparty/qt64_5.15.12/lib/cmake/Qt5Gui
	Qt5Script_DIR		U:/3rdparty/qt64_5.15.12/lib/cmake/Qt5Script
	Qt5Widgets_DIR		U:/3rdparty/qt64_5.15.12/lib/cmake/Qt5Widgets

	Qt5Quick_DIR		U:/3rdparty/qt64_5.15.12/lib/cmake/Qt5Quick	
	Qt5Qml_DIR			U:/3rdparty/qt64_5.15.12/lib/cmake/Qt5Qml
	
H:\users\prj_app\build\ex618_guile_005\Debug	

//---
	Qt5_DIR				C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5

//---
Get-ChildItem Env: | Format-Table -AutoSize
...
QML2_IMPORT_PATH            C:\Qt\5.15.2\msvc2019_64\qml
QT_QPA_PLATFORM_PLUGIN_PATH C:\Qt\5.15.2\msvc2019_64\plugins\platforms
QTDIR                       C:\Qt\5.15.2\msvc2019_64

//---
$env:PATH += ";C:\Qt\5.15.2\msvc2019_64\bin"

($Env:PATH -split ';') | ForEach-Object { $_ }


//---
2025-02-20

### 1. Ensure you are on `main`
```bash
git checkout main
git pull origin main
```
- **git checkout main**: Switches your local repo to the `main` branch.
- **git pull origin main**: Fetches the latest changes from the remote `origin` and merges them into your local `main`. (Recommended to keep your `main` branch up-to-date before creating a new branch.)

---

### 2. Create a new branch `branch_01` from `main` and switch to it
```bash
git checkout -b branch_01
```
- The `-b` flag does two things at once:
  - Creates a new branch called `branch_01`.
  - Checks out that new branch so you are now working on it.

*(Alternatively, you can use `git switch -c branch_01` on newer Git versions, which does the same thing.)*

---

### 3. Switch back to `main`
```bash
git checkout main
```
- This will take you out of `branch_01` and back to `main`.

//---
2025-04-19
//---
CMake

This line that was useful for MSVC 2022 was the cause of the previous error I deleted it and all worked as expected:
set(CMAKE_GENERATOR_PLATFORM x64)

E:/users/chfl/mingw/dev/ex618_guile_004_02
E:/users/chfl/mingw/build/ex618_guile_004_02

PS E:\users\chfl\mingw\build\ex618_guile_004_02> mingw32-make -j8

[  0%] Built target guile_app_04_02_01_autogen_timestamp_deps
[  0%] Built target guile_app_04_02_02_autogen_timestamp_deps
[  0%] Built target guile_app_04_02_04_autogen_timestamp_deps
[  4%] Automatic MOC for target guile_app_04_02_01
[  9%] Automatic MOC for target guile_app_04_02_02
[ 14%] Automatic MOC for target guile_app_04_02_04
[ 14%] Built target guile_app_04_02_04_autogen
[ 19%] Building CXX object CMakeFiles/guile_app_04_02_04.dir/guile_app_04_02_04_autogen/mocs_compilation.cpp.obj
[ 23%] Building CXX object CMakeFiles/guile_app_04_02_04.dir/src/widget_factory_04.cpp.obj
[ 28%] Building CXX object CMakeFiles/guile_app_04_02_04.dir/src/dialog_dynamic_04.cpp.obj
[ 33%] Building CXX object CMakeFiles/guile_app_04_02_04.dir/main/main_04.cpp.obj
[ 33%] Built target guile_app_04_02_01_autogen
[ 33%] Built target guile_app_04_02_02_autogen
[ 38%] Building CXX object CMakeFiles/guile_app_04_02_01.dir/guile_app_04_02_01_autogen/mocs_compilation.cpp.obj
[ 42%] Building CXX object CMakeFiles/guile_app_04_02_01.dir/src/widget_factory.cpp.obj
[ 47%] Building CXX object CMakeFiles/guile_app_04_02_02.dir/guile_app_04_02_02_autogen/mocs_compilation.cpp.obj
[ 52%] Building CXX object CMakeFiles/guile_app_04_02_01.dir/src/dialog_dynamic.cpp.obj
[ 57%] Building CXX object CMakeFiles/guile_app_04_02_02.dir/src/widget_factory_02.cpp.obj
[ 61%] Building CXX object CMakeFiles/guile_app_04_02_02.dir/src/dialog_dynamic_02.cpp.obj
[ 66%] Building CXX object CMakeFiles/guile_app_04_02_02.dir/main/main_02.cpp.obj
[ 71%] Building CXX object CMakeFiles/guile_app_04_02_01.dir/main/main_01.cpp.obj
[ 76%] Linking CXX executable guile_app_04_02_04.exe
[ 80%] Built target guile_app_04_02_04
[ 85%] Linking CXX executable guile_app_04_02_01.exe
[ 90%] Linking CXX executable guile_app_04_02_02.exe
[ 95%] Built target guile_app_04_02_01
[100%] Built target guile_app_04_02_02

PS E:\users\chfl\mingw\build\ex618_guile_004_02> ls


    Verzeichnis: E:\users\chfl\mingw\build\ex618_guile_004_02


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----        19.04.2025     11:15                .qt
d-----        19.04.2025     11:19                CMakeFiles
d-----        19.04.2025     11:19                guile_app_04_02_01_autogen
d-----        19.04.2025     11:19                guile_app_04_02_02_autogen
d-----        19.04.2025     11:19                guile_app_04_02_04_autogen
-a----        19.04.2025     11:15          61064 CMakeCache.txt
-a----        19.04.2025     11:15           1628 cmake_install.cmake
-a----        19.04.2025     11:19         278916 guile_app_04_02_01.exe
-a----        19.04.2025     11:19         298508 guile_app_04_02_02.exe
-a----        19.04.2025     11:19         284331 guile_app_04_02_04.exe
-a----        19.04.2025     11:15          24087 Makefile


PS E:\users\chfl\mingw\build\ex618_guile_004_02> .\guile_app_04_02_02.exe
start guile 04_02
QApplication started

*** instantiate a class, C_List and expose it to QJSEngine  ***
ctor C_List_Basis called
ctor C_List called

*** start the prototype approach, instantiate a class,          MyResource and expose it to QJSEngine  ***

*** end the prototype approach, instantiate a class,            MyResource and expose it to QJSEngine  ***

*** start the wrapper approach  ***

*** end the the wrapper approach  ***

*** end setup engine  ***
Layout and buttons built.
Buton clicked that!

*** exec script, calling the C++ object C_List_obj exposed to QJSEngine ***
called: C_List::update, i =  42
list update done
call implicit of myToString unsing prototype
after evaluate using prototype
Result of myObj.toString() in JS is: "MyResource(0x265f6e12040) some text"
call explicit of myToString unsing only Q_INVOKABLE
after evaluate using Q_INVOKABLE
Result of myObj.toString() in JS is: "Hello from MyResource::myToString() some text"
toString done
text start
called: MyResource::getTexts
texts length of 3 is:  "3"
call implicit of myToString unsing Wrapper
after evaluate using Wrapp
Result of Wrapp in JS is: "Hello from MyResource::myToString() some text"
Result of Wrapp in JS is: "Hello from MyResource::someOtherInvokable() some more text"
Result of Wrapp in JS is: "before hello: Hello from MyResource::someMoreInvokable() some more more text"
toString Wrapp done
text start
called: MyResource::getTexts
texts 3 is:  "123,456,some string"
dtor C_List called
dtor C_List_Basis called

//---
https://code.visualstudio.com/download
Visual Studio Code documentation
https://code.visualstudio.com/docs/?dv=win32arm64user

VSCodeUserSetup-x64-1.99.3

installed in: C:\Users\T14s\AppData\Local\Programs

 






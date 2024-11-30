@ECHO OFF

::set BASEDIR=%~dp0
::PUSHD %BASEDIR%

::RMDIR /Q /S build

::@ECHO ON

::conan install . --output-folder=build --build=missing
::cd build
::cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=build\conan_toolchain.cmake
::cmake --build . --config=Debug
::cd ../build-scripts
<<<<<<< HEAD
python3 TechstormConfigure.py --release --debug
=======
python3 TechstormConfigure.py --release
>>>>>>> 54653e5aab996b3ca5dfae6c481ea281d8cba5dc
echo "Generating project"
python3 TechstormGenerate.py

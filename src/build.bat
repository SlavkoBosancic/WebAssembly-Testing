@echo off

if "%~1"=="--release" (set var1=O3) else set var1=g4

xcopy /s /y .\html ..\build
emcc WebAssemblyTesting.cpp MovableGameObject.cpp GameObject.cpp GameEngine.cpp -std=c++11 -%var1% -s WASM=1 -s EXPORTED_FUNCTIONS="['_main', '_MoveBall', '_MovePaddle']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -o ./../build/pong.js
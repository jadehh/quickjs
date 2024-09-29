# quickjs
quickjs


## Windows动态库生成

```bash
cmake  -DCMAKE_BUILD_TYPE=Release "-DCMAKE_MAKE_PROGRAM=C:/Program Files/JetBrains/CLion 2023.2.1/bin/ninja/win/x64/ninja.exe" -G Ninja -B  cmake-build-release-mingw
cmake --build cmake-build-release-mingw --target quickjs -j 10
```
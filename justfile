run:
  just init
  just build
  ./build/$(cat build/CMakeCache.txt | grep CMAKE_PROJECT_NAME | awk -F '=' '{print $2}')

debug:
  cmake -B build -DCMAKE_BUILD_TYPE=Debug
  just build
  gdb -q --args ./build/$(cat build/CMakeCache.txt | grep CMAKE_PROJECT_NAME | awk -F '=' '{print $2}')

init:
  cmake -B build

build:
  cmake --build build -j8

clean:
  rm -rf build

install:
  cmake -B build -DCMAKE_BUILD_TYPE=Release
  just build
  cp ./build/kaleido ~/.local/bin

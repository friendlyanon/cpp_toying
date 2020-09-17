#!/bin/sh

CWD="$(cd "$(dirname "$0")" && pwd)"
TARGET="build/test"

cd $CWD/..

configure() {
  if [ -d $TARGET ]; then
    return 0
  fi

  cmake -Htest -B $TARGET -GNinja \
    -DCMAKE_BUILD_TYPE:STRING=Debug \
    -DUSE_CCACHE:BOOL=ON \
    -DCPM_SOURCE_CACHE:PATH="$(pwd)/.cpm-cache"
}

build() {
  cmake --build $TARGET --config Debug
}

test() {
  cd build/test
  ctest --build-config Debug
}

configure && build && test

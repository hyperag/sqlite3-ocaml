#!/usr/bin/env bash

set -xeuo pipefail

mkdir -p _test
cd _test

if which x86_64-w64-mingw32-gcc; then
    CC=x86_64-w64-mingw32-gcc
else
    CC=gcc
fi

$CC ./../../esy/test.c -o ./test.exe -I$SQLITE_INCLUDE_PATH -L$OPENSSL_LIB_PATH -lsqlite3
test -x ./test.exe
./test.exe

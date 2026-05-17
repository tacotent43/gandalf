#!/bin/bash

set -e

mkdir -p build/
gcc -I include/ src/*.c -o build/main
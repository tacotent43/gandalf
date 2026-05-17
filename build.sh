#!/bin/bash

set -e

mkdir -p build/
gcc -std=gnu23 -I include/ src/*.c -o build/gandalf
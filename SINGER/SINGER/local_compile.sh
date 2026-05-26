#!/bin/bash

#g++ -std=c++17 -O3 -g -static *.cpp -o singer
#g++ -std=c++17 -g -static *.cpp -o singer_debug

# NSP: keeping binaries from main, and adding a new one that is "singer-custom".
# So the "singer" and "singer_debug" binaries do not reflect the source code.
# Dropping the dead "Test" code.

g++ -std=c++17 -O3 -g -static $(ls *.cpp | grep -v '^Test\.cpp$') -o "singer-custom" && {
    sha256sum singer-custom >singer-custom.sha256
}

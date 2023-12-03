#!/bin/bash
pathSelect=$(pwd)

codeStyle=$pathSelect/code_style.txt

for ext in h hpp c cpp ino; do
    for pathFile in $(find $pathSelect -maxdepth 2 -type f -name "*.$ext"); do
        clang-format -i --verbose --style="file:$codeStyle" $pathFile
    done
done


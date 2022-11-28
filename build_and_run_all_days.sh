 #!/bin/bash

rm -rf _build
cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release
cmake --build _build --config Release
for files in "_build/Day*/Day*"
do
    for file in $files
    do
        echo $file
        ./$file
    done
done
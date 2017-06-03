#!/bin/bash

cd build
cmake ./..
make
cd ..

function get_engine_module
{
    local res=""

    [[ $1 =~ ^.*/src/engine/public/bitwise/([a-z_]+).* ]]  && res=${BASH_REMATCH[1]}
    [[ $1 =~ ^.*/src/engine/private/bitwise/([a-z_]+).* ]] && res=${BASH_REMATCH[1]}

    echo $res
}

function get_sample_engine_program
{
    local res=""

    [[ $1 =~ ^.*/samples/engine/([a-z_]+)/.* ]] && res=${BASH_REMATCH[1]}

    echo $res
}

program=""
program_path=bin/samples/engine/

echo $1

if   [[ $1 == *"/src/engine/"*     ]]; then program="./bin/samples/engine/module_"$(get_engine_module $1)
elif [[ $1 == *"/samples/engine/"* ]]; then program="./bin/samples/engine/"$(get_sample_engine_program $1)
fi

if [ $program -a -e $program ]; then
    echo $program
    $program
else
    if [ $program ]; then
        echo "Executable not found '$program'"
    else
        echo "The file that launched this script '$1' is not in any CMake target"
    fi
fi
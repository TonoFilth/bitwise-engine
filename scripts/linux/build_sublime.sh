#!/bin/bash

cd build
cmake ./..
make
cd ..

function get_engine_module
{
    local res=""

    [[ $1 =~ ^.*bitwise/src/engine/public/bitwise/([a-z_]+).* ]]  && res=${BASH_REMATCH[1]}
    [[ $1 =~ ^.*bitwise/src/engine/private/bitwise/([a-z_]+).* ]] && res=${BASH_REMATCH[1]}

    echo $res
}

function get_sample_engine_program
{
    local res=""

    [[ $1 =~ ^.*bitwise/samples/engine/([a-z_]+/[a-z_]+)/.* ]] && res=${BASH_REMATCH[1]}

    echo $res
}

program=""
program_path=bin/samples/engine/

if   [[ $1 == *"bitwise/src/engine/"*     ]]; then program="./bin/samples/engine/"$(get_engine_module $1)"/quick_test"
elif [[ $1 == *"bitwise/samples/engine/"* ]]; then program="./bin/samples/engine/"$(get_sample_engine_program $1)
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
#!/bin/bash

OPTIONS=""
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -a)
    ALGO="$2"
    shift
    ;;
    -e)
    EX_PATH="$2"
    shift
    ;;
    -p|-t|-s)
    OPTIONS="${OPTIONS}${1} "
    ;;
    *)
        echo "Argument inconnu: ${1}"
        exit
    ;;
esac
shift
done

if [ ! -f ./src/main.out ]; then
    cd src && make && cd ..
fi

./src/main.out -a $ALGO -e $EX_PATH $OPTIONS

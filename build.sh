#!/usr/bin/bash

#bold normal
bold=$(tput bold)
normal=$(tput sgr0)

#colors
red=`tput setaf 1`
green=`tput setaf 2`

mkdir -p build
if [[ $1 == "--genDoc" ]] 
then
    doxygen dconfig
    if [[ "$?" -ne 0 ]]
    then 
        echo echo "${bold}${red}[ Documentation Generation Failed ]${normal}"
        exit 1;
    else
        clear
        echo "${bold}${green}[ Documentation Generated ]${normal}"
    fi
fi

echo "${bold}${green}[ Configuring CMakeLists.txt ]${normal}"

#cmake testing
cmake -B build/ -S .
if [[ "$?" -ne 0 ]]
then 
    echo "${bold}${red}[ Configuring CMake failed ]${normal}"
    exit 1;
else
    echo "${bold}${green}[ CMake configured successfully ]${normal}"
fi

cd build
echo "${bold}${green}[ Building Makefile ]${normal}"

#make testing
make
if [[ "$?" -ne 0 ]]
then 
    echo "${bold}${red}[ make failed ]${normal}"
    exit 1;
else
    echo "${bold}${green}[ OUTPUT ]${normal}"
    ./Dharahara
fi
#!/bin/bash
CWD=${PWD}
BUILD_DIRECTORY=${CWD}/build/ut
TEST_DIR=${CWD}/test

# check if directory exist
if [ ! -d "${BUILD_DIRECTORY}" ]; then
  mkdir -p ${BUILD_DIRECTORY}
fi

if [[ $1 == "clean" ]]
then
echo Cleaning...
rm -rf ${BUILD_DIRECTORY}/*
fi

if [[ $1 == "-one-line" ]]  || [[ $2 == "-one-line" ]]
then
echo Print Report as one-line... No Fancy report
ONE_LINE_MODE=1
else
ONE_LINE_MODE=0
fi


cd $BUILD_DIRECTORY
cmake -B . -Wno-dev ${TEST_DIR}
cmake --build . 

if [[ $? -ne 0 ]]
then
echo Build failure error [$?]
exit
fi

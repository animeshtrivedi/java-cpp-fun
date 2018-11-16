#!/bin/bash
echo "This will an identical Java and C++ program and put their output"
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
function make_java {
home=`pwd`
cd $home/java/
mvn package 
cd - 
}

function make_cpp {
mkdir -p $home/cpp/release 
rm -rf $home/cpp/release/* 
cd $home/cpp/release/ && cmake .. && make 
cd - 
}

make_java
make_cpp 

echo "________________________________________________________________"
echo "Running the java program ... "
java -cp $home/java/target/benchmark-fun-1.0.jar com.github.animeshtrivedi.jcf.Main
echo "________________________________________________________________"
echo "Running the c++ program ... "
$home/cpp/bin/benchmark-fun 


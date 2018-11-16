#!/bin/bash
echo "This will an identical Java and C++ program and put their output"
echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
function make_java {
home=`pwd`
cd $home/java/
mvn package && cp ./target/benchmark-fun-1.0.jar ..
cd - 
}

function make_cpp {
mkdir -p $home/cpp/release 
rm -rf $home/cpp/release/* 
cd $home/cpp/release/ && cmake .. && make 
cp ../bin/benchmark-fun ../../
cd - 
}

make_java
make_cpp 

echo "________________________________________________________________"
echo "Running the java program ... "
java -cp ./benchmark-fun-1.0.jar com.github.animeshtrivedi.jcf.Main
echo "________________________________________________________________"
echo "Running the c++ program ... "
./benchmark-fun 


# Performance debugging (fun) in Java and CPP

I have an identical program in Java 

  * java : https://github.com/animeshtrivedi/java-cpp-fun/blob/master/java/src/main/java/com/github/animeshtrivedi/jcf/PeakPerformance.java#L73
  * C++  : https://github.com/animeshtrivedi/java-cpp-fun/blob/master/cpp/src/PeakPerformanceJava.cpp#L14

Conceptually, both programs have an integer array and a bitmap array. The size of these are configuration but 
for the default run these are set to 100,000,000 integers, hence giving 400 MB of integer array and 12.5 MB 
of the bitmap array. In the bitmap every millionth integer is marked null, hence in total 100 M / 1M = 100 entries 
are missing. The core benchmark in both, java and c++ is suppose to sum up valid integers and count them. That is 
all. Here is the performance numbers :

On a server class machine (SandyBridge) 
```bash
$./run.sh 
[...]
________________________________________________________________
Running the java program ... 
Picked up JAVA_TOOL_OPTIONS: -XX:+PreserveFramePointer
100000000 items = buffers of int size 400000000 bitmap size 12500000 allocated 
initialization done
-----------------------------------------------------------------------
Total bytes: 39999960000( ints = 9999990000 ) time = 21129223517 nsec => bandwidth 15.14 Gbps
-----------------------------------------------------------------------
________________________________________________________________
Running the c++ program ... 
100000000 items = buffers of int size 400000000 bitmap size 12500000 allocated 
initialization doneRunning the benchmark 
starting the benchmark loop 100 items 100000000
total ints are 9999990000 
-----------------------------------------------------------------------
Total bytes: 39999960000( ints = 9999990000 ) time = 10665789408 nsec => bandwidth 30.0024 Gbps
-----------------------------------------------------------------------
```

On my local laptop x201
```bash
$./run.sh 
[...]
________________________________________________________________
Running the java program ... 
100000000 items = buffers of int size 400000000 bitmap size 12500000 allocated 
initialization done
-----------------------------------------------------------------------
Total bytes: 39999960000( ints = 9999990000 ) time = 23933181988 nsec => bandwidth 13.37 Gbps
-----------------------------------------------------------------------
________________________________________________________________
Running the c++ program ... 
100000000 items = buffers of int size 400000000 bitmap size 12500000 allocated 
initialization doneRunning the benchmark 
starting the benchmark loop 100 items 100000000
total ints are 9999990000 
-----------------------------------------------------------------------
Total bytes: 39999960000( ints = 9999990000 ) time = 11896358537 nsec => bandwidth 26.899 Gbps
-----------------------------------------------------------------------
```

***That is the interesting bit _WHY_?***

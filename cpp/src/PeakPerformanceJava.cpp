#include <chrono>
#include "PeakPerformanceJava.h"//
// Created by atr on 16.11.18.
//

void PeakPerformanceJava::runUnroll(){
    // init consts
    const uint8_t* const bitmapAddress = this->bitmapBuffer;
    const uint8_t* const valueAddress = this->intValueBuffer;
    const int localLoopMax = this->loop;
    const long local_items = this->items;
    // variables
    long intCount=0, runningCheckSum=0;
    int loopCount = 0;
    std::cout  << "[c++] " << "starting the benchmark loop " << localLoopMax << " items " << local_items << "\n";
    // start
    auto start = std::chrono::high_resolution_clock::now();
    while (loopCount < localLoopMax) {
        for (long i = 0; i < local_items; i++) {
            if((bitmapAddress[(i >> 3L)] & (1L << (i & 7L))) != 0) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
        }
        loopCount++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    //end
    this->_runtime_in_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    this->_checksum+=runningCheckSum;
    this->_total_Ints+=intCount;
}

void PeakPerformanceJava::runRoll(){
    long checkSum = 0, count = 0;
    const uint8_t* const bitmapAddress = this->bitmapBuffer;
    const uint8_t* const valueAddress = this->intValueBuffer;
    //final byte[] map = {1, 2, 4, 8, 16, 32, 64, (byte) 128};
    int loopCount = 0, localLoopMax = this->loop;
    long localitems = this->items;
    long intCount=0, runningCheckSum=0;
    std::cout << "starting the benchmark loop " << localLoopMax << " items " << localitems << "\n";
    auto start = std::chrono::high_resolution_clock::now();
    while (loopCount < localLoopMax) {
        for (long i = 0; i < localitems;) {
            uint8_t b = bitmapAddress[i >> 3L];
            if((b & 1)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
            if((b & 2)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
            if((b & 4)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
            if((b & 8)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
            if((b & 16)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
            if((b & 32)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
            if((b & 64)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
            if((b & 128)) {
                intCount++;
                runningCheckSum += valueAddress[(i << 2)];
            }
            i++;
        }
        loopCount++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    this->_runtime_in_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    this->_checksum+=runningCheckSum;
    this->_total_Ints+=intCount;
}
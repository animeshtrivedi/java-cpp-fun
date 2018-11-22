#include <chrono>
#include "PeakPerformanceJava.h"//
// Created by atr on 16.11.18.
//

void PeakPerformanceJava::runStock(){
    // init consts
    const uint8_t* const bitmapAddress = this->bitmapBuffer;
    const uint8_t* const valueAddress = this->intValueBuffer;
    const int localLoopMax = this->loop;
    const long local_items = this->items;
    // variables
    long intCount=0, runningCheckSum=0;
    int loopCount = 0;
    std::cout << "starting the benchmark loop " << localLoopMax << " items " << local_items << "\n";
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

void PeakPerformanceJava::runAsm(){
    // init consts
    const uint8_t* const bitmapAddress = this->bitmapBuffer;
    const uint8_t* const valueAddress = this->intValueBuffer;
    const int localLoopMax = this->loop;
    const long local_items = this->items;
    // variables
    long intCount=0, runningCheckSum=0;
    int loopCount = 0;
    std::cout << "starting the benchmark loop " << localLoopMax << " items " << local_items << "\n";
    // start
    auto start = std::chrono::high_resolution_clock::now();
    while (loopCount < localLoopMax) {
        for (long i = 0; i < local_items; i++) {
                uint8_t x;
                asm (   "mov %[i], %%rax\n"
                        "sar $0x3, %%rax\n"
                        "add %[bitmapAddress], %%rax\n"
                        "mov %[i], %%r11\n"
                        "and $0x7, %%r11\n"
                        "movsbq (%%rax), %%rax\n"
                        "mov %%r11d, %%ecx\n"
                        "mov $0x1, %%r11d\n"
                        "shl %%cl, %%r11\n"
                        "and %%r11, %%rax\n"
                        : [x] "=a" (x)
                        : [i] "r" (i), [bitmapAddress] "m" (bitmapAddress)
                        : "r11", "ecx");
            if(x != 0) {
                intCount++;
                // runningCheckSum += valueAddress[(i << 2)];
                asm (   "mov %[i], %%r10\n"
                        "shl $0x2, %%r10\n"
                        "add %[valueAddress], %%r10\n"
                        "movslq (%%r10), %%r10\n"
                        "add %%rax, %%r10\n"
                        : [runningCheckSum] "=a" (runningCheckSum)
                        : [i] "r" (i), [valueAddress] "m" (valueAddress)
                        : "r10");
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

void PeakPerformanceJava::runUnroll(){
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

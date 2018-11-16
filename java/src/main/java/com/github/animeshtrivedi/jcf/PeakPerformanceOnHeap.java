/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.github.animeshtrivedi.jcf;

import java.nio.ByteBuffer;

public class PeakPerformanceOnHeap {
    final public static int MAX_INT_ITEMS = 1 << 28;
    final private long items;
    final private int loop;
    final private ByteBuffer bitmapBuffer;
    final private ByteBuffer intValueBuffer;

    public long runtimeInNS;
    public long checksum;
    public long intCount;

    PeakPerformanceOnHeap() throws Exception {
        this(100000000, true, 1000000, 100);
    }

    PeakPerformanceOnHeap(int items, boolean doNulls, int steps, int loop) throws Exception {
        if(items > MAX_INT_ITEMS){
            throw new Exception("items cannot be more than the max ");
        }
        this.loop = loop;
        this.items = (long) items;
        int intSize = items << 2;
        int bitmapSize = items >> 3;
        bitmapBuffer = ByteBuffer.allocate(bitmapSize);
        intValueBuffer = ByteBuffer.allocate(intSize);
        bitmapBuffer.clear();
        intValueBuffer.clear();
        System.out.println(items + " items = buffers of int size " + intSize + " bitmap size " + bitmapSize + " allocated ");
        for(int i = 0;i < bitmapSize; i++){
            bitmapBuffer.put(i, (byte) 0xFF);
        }
        // doNull - if enabled then mark in stepping items null
        for(int i = 0; doNulls && i < items; i+=steps){
            bitmapBuffer.put((i>>3), (byte) 0xEF);
        }

        for(int i = 0; i < items; i++){
            intValueBuffer.putInt(i<<2, i);
        }
        System.out.println("initialization done");
    }

    private void runNoRoll() {
        long checkSum = 0, count = 0;
        int loopCount = 0;
        long intCount=0, runningCheckSum=0;

        final long start = System.nanoTime();
        while (loopCount < loop) {
            for (int i = 0; i < items; i++) {
                if((bitmapBuffer.get(i >> 3) & (1L << (i & 7L))) != 0) {
                    intCount++;
                    runningCheckSum += intValueBuffer.getInt(i << 2);
                }
            }
            loopCount++;
        }
        final long end = System.nanoTime();
        this.runtimeInNS = end - start;
        this.checksum+= runningCheckSum;
        this.intCount+= intCount;
    }

    public void run(){
        runNoRoll();
    }
}

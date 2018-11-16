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

#include "PeakPerformanceJava.h"

int main(int argc, char **argv) {
  PeakPerformanceJava *r = new PeakPerformanceJava();
  std::cout<<"Running the benchmark \n";
  r->run();
  std::cout<<"total ints are " << r->_total_Ints << " \n";
  long totalBytes = ((long) r->_total_Ints) << 2;
  double bandwidthGbps = (((double) totalBytes * 8) / r->_runtime_in_ns);
  std::cout<<"-----------------------------------------------------------------------\n";
  std::cout<<"Total bytes: " << totalBytes << "( ints = " << r->_total_Ints << " ) time = " << r->_runtime_in_ns << " nsec => bandwidth " << bandwidthGbps << " Gbps\n";
  std::cout<<"-----------------------------------------------------------------------\n";
  return 0;
}
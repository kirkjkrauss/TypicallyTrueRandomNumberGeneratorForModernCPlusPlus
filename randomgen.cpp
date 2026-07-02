// GetTypicallyTrueRandomNumber() -- portable C/C++ implementation.
// 
// Copyright 2026 Kirk J Krauss.  This is a Derivative Work based on 
// material that is copyright 2018 developforperformance.com and 
// available at
//
//     https://developforperformance.com/RandomTreatmentForRandomData.html#ListingThree
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     https://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Returns a 16-bit random number based on the system clock.  In case the 
// clock hasn't changed significantly since this function was last called, 
// returns a pseudorandom number based on a simple Park-Miller algorithm 
// seeded from the clock.  Outperforms rand() / srand() on most platforms.
//
#include <stdio.h>
#include <chrono>

const unsigned int uMultiplier = 16807;  // Park-Miller's 7 to the 5th power
const unsigned int uMask = 0xFFFF;       // Mask for random bits to be returned

unsigned int GetTypicallyTrueRandomNumber(void)
{
   static unsigned int uSeed;            // Seed value
   unsigned int        uRandom = 0;      // Random bits
   std::chrono::time_point<std::chrono::high_resolution_clock> timeCurrent;

   // Get a number based on the clock shifted & masked to a tenth-picosecond.
   timeCurrent = std::chrono::high_resolution_clock::now();
   uRandom = (unsigned int) (~(unsigned int) 0) & 
      (std::chrono::duration_cast<std::chrono::nanoseconds>(
         std::chrono::high_resolution_clock::now().time_since_epoch()).count() 
           >> 2);

   if (uRandom - uSeed < uMask)
   {
      // Get a pseudorandom number based on the last seed value.
      uSeed = uRandom = (unsigned int) ((uSeed * uMultiplier) % uMask);
   }
   else
   {
       // Save this number as a seed value for next time.
       uSeed = uRandom;
   }
  
   return uRandom & uMask;
}


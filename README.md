# TypicallyTrueRandomNumberGeneratorForModernCPlusPlus
Small, fast, typically true random number generator for modern C++

Most methods for generating random numbers don’t act very random.  Many of them won’t necessarily even dish out a different set of numbers for each run.  Their performance usually isn’t optimal, either.  This native code random number generator provides cross-platform interoperability to a high-performance method for deriving typically true random numbers based on the system clock.  Its design and history, plus common use cases, are described at https://developforperformance.com/RandomTreatmentForRandomData.html.

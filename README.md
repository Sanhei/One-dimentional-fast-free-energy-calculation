# One-dimentional-fast-free-energy-calculation
Free energy calculation:
## Package/Environment
1. Boost (which is used as parse, the part of filename) You can change the Free_energy.cpp filename part to avoid it.
2. Cmake compile environment.
## Algorithm
Free energy calculation from the Boltzmann distribution,
 $$F = -k_BTln(P(x)),$$
here $k_BT$ is thermol energy ($k_B$ Boltzmann constant, T is temperature). P(x) is the probability of whole trajectory on position x.
Therefore, first we need to construct histogram to calculate. For each datapoint, we use int type to transfer the double type data. Then, this int can directly used as bin (index), where we don't need to go through the whole scale of position to find the datapoint corresponding bin index.

## Parameter
1. discretize, this is used to define how large of your bins, and the size of bins should be 1/discretize.
2. Temperature, since this is embedded in the simulation part, so no need to mention (default: 1000).
## Execute
1. Compile with Cmake.
```bash
mkdir build
cd build & camke ..
```
2. Go to ./build/src, run the free_energy.
```bash
./free_energy --filename $filename$
```

************
## Notice
For the parse part, option.get() is defined as std::string, if you want to add discretize and tempareture, also need to change the type in options.hpp.
options.hpp is directly copied from Felix. 

# LIF

Langrange Interpolating Formula. This program uses the Lagrange Interpolating Formula to find an approximate value between a given dataset.

## Requirements

- A linux system
- Cmake ^3.10

## How do I run it on my system?

Clone this repo into your system and cd inside of the repo directory

```
git clone https://github.com/D0T-B0X/LIF.git
cd LIF
```

Run cmake to generate the build files for our project and compile it.

```
cmake -S . -B build
cmake --build build
```

Next, cd into the build directory and run the executable

```
cd build/
./LIF
```

You should now have a working Lagrange Interpolating Formula Function!

<code>!! If you are on a windows system, make sure cmake is installed and edit `CMakeLists.txt` to use windows path syntax !!</code>
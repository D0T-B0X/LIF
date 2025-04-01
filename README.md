# LIF

Langrange Interpolating Formula. This program uses the Lagrange Interpolating Formula to find an approximate value between a given dataset.

## Requirements

- A linux system
- Cmake ^3.10
- python 3

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

## Error Visualization

To create plots of the error % and true value vs approximation deviation:
First cd into the `visualization` directory:

```
cd {HOME_DIRECTORY}/visualization
```

Then create and activate a virtual environment.

```
python -m venv .venv
source .venv/bin/activate
```

Install the required packages

```
pip install -r requirements.txt
```

Now, simply run the python script and the plots will be saved in `{HOME_DIRECTORY}/visualization/plots/`

```
python3 accuracy_plot.py
```

<code>!! If you are on a windows system, make sure cmake is installed and edit `CMakeLists.txt` to use windows path syntax !!</code>
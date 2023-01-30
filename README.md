# CS5330 Project1 Real-Time-Filtering

## Project Description

This is a image filtering program using c++ and opencv. With many different filters you can apply to live cam stream images. 

## How to install and run

Have the following 4 programs ready on your **Linux** machine:
- opencv 4.7.0
- g++
- vscode
- make

open the project in vscode and open a terminal window and make sure you are in the desired directory and type `make`. A excutable would appear in your current directory - `imageDisplay` or `vidDisplay` depending on which directory you are in. Then type in to run the excutable - `./imageDisplay` or `./vidDisplay`. Now you can play around with the filters. Have fun.

## Program features (filters)

### Basic requirments

- `s` - save image
- `g` - greyscale filter (using opencv function cvtColor)
- `h` - greyscale filter (copy green channel to the other two channels)
- `b` - Gaussian blur filter
- `x` - Sobel X filter 
- `y` - Sobel Y filter
- `m` - gradient magnitude image
- `l` - blur and quantization
- `c` - cartoonization
- `o` - negative image
- `n` - romve filter and change stream to normal
- `q` - quit the program

### Extensions

- `s` - save image with filters & enable user to name the saved image
## Demo Video


## Time travel days used - 3 days
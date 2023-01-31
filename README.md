# CS5330 Project1 Real-Time-Filtering

## Project Description

This is a image filtering program using c++ and opencv. With many different filters you can apply to live cam stream images. 

## How to install and run

Have the following 4 programs ready on your **Linux** machine:

- opencv 4.7.0
- g++
- vscode
- make

open the project in vscode and open a terminal window and make sure you are in the desired directory and type `make`. A excutable would appear in your current directory - `imageDisplay` or `vidDisplay` depending on which directory you are in. Then type in to run the excutable - `./imageDisplay` or `./vidDisplay`. To enable still image mode, just type in the image path after `./vidDisplay` to run. For example, to run the lena image in the folder, just do  `./vidDisplay lena.png`.Now you can play around with the filters. Have fun.

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
- `q` - quit the program

### Extensions

- `p` - laplacian filter (another edge detector)
- `n` - romve filter and change image/video stream to normal
- `s` - save image with filters in both video stream mode and still image mode & enable user to name the saved image
- `r` - start recording an 'avi' formate video
- `z` - stops recording and allows user to enter filename of their choice
- default image is webcam stream video. User can add an image path after the excutable when starting the program, so the user can apply all the filters to the image as well.

## Demo Video
https://www.youtube.com/watch?v=TuA1M8gJDAs

## Time travel days used - 3 days
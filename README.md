# Fractal Generator

Contains a fractal generator as well as some tools to analyze fractal dimension. This was originally written for the final project of Physics 2G03 at McMaster University in Fall 2017.

## Generating and plotting fractals

Compile and run fractals.c, and then run scatter.py to plot the generated fractal. Feel free to tweak some constants to generate a variety of structures. Feel free to modify the axes/colors.

## Analyzing fractals

You can analyze fractal dimension using bestfit.py. Randomize either r or stickiness and run the program some number of times to see how fractal dimension varies with stickiness or r.

## Examples

Here is 1000 particles on a 101 by 101 square lattice. No stickiness.

![1000 particles on a 101 by 101 square lattice.](https://image.ibb.co/nhn6H6/Fractal_1.png)

Here is 1000 particles on a 101 by 101 square lattice. Stickiness was set to 0.9. A lot more clumping occurs. Fractal dimension is greater. 

![1000 particles on a 101 by 101 square lattice.](https://image.ibb.co/kk5qAR/fractalstick4.png)


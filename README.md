# Solving the heat equation

Full report on that program can be found ![here](https://victorostertag.fr/files/Computation_Methods_And_CPP_Assignment_Victor_OSTERTAG.pdf)

C++ program that solves the heat equation using various numerical schemes for the problem introduced in the [Problem Definition](#problem-definition) section.

## Index
[1. Problem Definition](#problem-definition)  
[2. What does it do](#what-does-it-do)  

## Problem Definition

![Alt Text](https://image.ibb.co/i8NzYb/wall_problem.jpg)

A wall 1 ft.  thick and infinite in other directions (see Figure 1) has an initial uniform temperature T in of 100°F. The surface temperatures Tsur at the two sides are suddenly increased and maintained at 300°F. The wall is composed of nickel steel (40% Ni) with a diffusivity of D = 0.1ft2/hr. 
How will the temperature increase inside the wall?

It was required that the code works with Visual Studio, using no external libraries.

## What does it do

The program will generate .dat files inside the "datFiles" repository with the solutions for each time step. To display them, I advise using gnuplot as the code will also generate a "commands.txt" file with the gnuplot commands to do so. Here is an example of a graph you will get using these commands:

![Alt Text](https://image.ibb.co/gZ4hKG/Crank_Nicholson_t30_delta_T0_01.png)

# Binomial-Heterogenicity
Quick Numerical Simulations of Heterogenic/Heterozygote frequencies in a population using C++.

Short Introduction:

This is a short program I wrote alongside the HapHazard genomic ancestry simulator. Because junction formation depends on the frequency of heterogenic (mixed ancestry) genomic tracts, I wanted to understand the frequency distribution of heterogenic (aka heterozygotic) loci over many simulations and over time.

Dependencies: GNU Scientific Library

How to run:

This program has no user interface, and parameters/variables will have to be changed manually and compiled by the programmer.

To compile:

$ g++ -L/usr/local/lib main.cpp -o BinHet -lgsl -lgslcblas -lm -std=c++11

This will link the GNU scientific library, and create an executable file called 'BinHet'. It uses c++11 because that's what I was using when I wrote it.

Output:

A text file named 'totalHet.txt'. The first column labels the simulation number, the following columns list the heterogenic/heterozygote frequencies for each generation summarized.

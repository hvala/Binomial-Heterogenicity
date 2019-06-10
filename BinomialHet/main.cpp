#include <iostream>
#include <fstream>
#include <cmath>

#include "gsl/gsl_rng.h"
#include "gsl/gsl_randist.h"

using namespace std;

double start_freq = 0.5;     // the starting frequency of each population
int numGenerations = 1000;  // number of generations per simulation
int numSims = 1000;         // the number of simulations to run
double frequency;           // allele/ancestry frequency
int* population;            // a pointer to an array of populations
int populationSize = 100;   // the size of the population
double heteroFreq;          // the frequency of heterogenic individuals

// a list of generations to recorde the het frequency
int summaries[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

// the random number generator
gsl_rng * randNum;

int main()
{
    cout << "Heterogenicity!" << endl;

    // GSL RNG setup
    randNum = gsl_rng_alloc(gsl_rng_taus);
    int seed = time(0);
    gsl_rng_set(randNum, seed);

    // create an output file stream for the data
    ofstream totalHet;
    totalHet.open("totalHet.txt");
    totalHet << "TotalHet";

    // print a header row to the output file for each summary
    for( int i = 0 ; i < 10 ; i++ )
    {
        totalHet << "," << summaries[i];
    }
    totalHet << endl;

    // not sure what this is for
    double not_IBD = 1 - ( 1 / ( 2 * populationSize ) );
    double product_over_IBD = pow( not_IBD, numGenerations );
    double exp_Het = 0;

    for(int s = 0 ; s < numSims ; s++ )
    {
        //cout << "Sim: " << s << endl;
        //create a new population for the simulation
        int* population = new int[populationSize];
        frequency = start_freq;
        heteroFreq = 2 * start_freq * start_freq;
        double total_Heterogenicity = heteroFreq;

        // begin iterating through generations for the sim
        int sum = 0;
        totalHet << s ;
        for( int g = 0 ; g < numGenerations ; g++ )
        {
            // build a new population from the old generations
            // ancestry frequencies
            for( int i = 0 ; i < populationSize ; i++ )
            {
                // perform bernoulli trials to generate the alleles/ancestries
                int g1 = gsl_ran_bernoulli(randNum, frequency);
                int g2 = gsl_ran_bernoulli(randNum, frequency);
                population[i] = g1 + g2; // add new, replacing the old
            }

            // count up the heterogenic individuals
            int count = 0;
            int heterogenics = 0;
            for( int i = 0 ; i < populationSize ; i++ )
            {
                count += population[i];
                if( population[i] == 1 )
                {
                    heterogenics++;
                }
            }

            // calculate the new frequencies of ancestry and heterogenics
            frequency =  (double) count / (double) populationSize / 2;
            heteroFreq = (double) heterogenics /  (double) populationSize ;
            total_Heterogenicity += heteroFreq;

            // if we're in a summary generation, print the output to the file
            if(g == summaries[sum] - 1)
            {
                totalHet << "," << total_Heterogenicity;
                sum++;
            }
        }

        // when the sim is done, move to a new line of output and delete the population
        totalHet << endl;
        delete population;
    }

    // close the output file
    totalHet.close();


    return 0;
}

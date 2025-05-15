
#ifndef _HOPFNTLCP_H
#define _HOPFNTLCP_H

// This Hopfield network can recall at most three distinct patterns
// successfully. See the README.md file for details. 
// The patterns are stored in a 1D array of size N_HOPFIELD_NEURONS,
// are represented as 0s and 1s, where 0 represents an inactive neuron
// and 1 represents an active neuron.

#include <stdio.h>
#include <stdlib.h>

#define N_HOPFIELD_NEURONS 77

int refer_patt_Crc[] = {
                           0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0,
                           0, 0, 1, 1, 1, 0, 0,
                           0, 1, 0, 0, 0, 1, 0,
                           1, 0, 0, 0, 0, 0, 1,
                           1, 0, 0, 0, 0, 0, 1,
                           1, 0, 0, 0, 0, 0, 1,
                           0, 1, 0, 0, 0, 1, 0,
                           0, 0, 1, 1, 1, 0, 0,
                           0, 0, 0 ,0 ,0 ,0 ,0,
                           0, 0, 0, 0, 0, 0, 0
};
int test_patt_Crc[]  = {
                           0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0,
                           0, 0, 1, 0, 1, 0, 0,
                           0, 1, 0, 0, 0, 1, 0,
                           1, 0, 0, 1, 0, 0, 1,
                           0, 0, 1, 0, 0, 0, 0,
                           1, 0, 0, 0, 1, 0, 1,
                           0, 1, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 1, 0, 0,
                           0, 0, 0 ,0 ,0 ,0 ,0,
                           0, 0, 0, 0, 0, 0, 0
};

// Reference and distorted (test) patterns for a triangle
int refer_patt_Trg[] = {
                           0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 1, 0, 0,
                           0, 0, 0, 1, 1, 0, 0,
                           0, 0, 1, 0, 1, 0, 0,
                           0, 1, 0, 0, 1, 0, 0,
                           1, 0, 0, 0, 1, 0, 0,
                           0, 1, 0, 0, 1, 0, 0,
                           0, 0, 1, 0, 1, 0, 0,
                           0, 0, 0, 1, 1, 0, 0,
                           0, 0, 0 ,0, 1, 0, 0,
                           0, 0, 0, 0, 0, 0, 0
};
int test_patt_Trg[]  = {
                           0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 1, 0, 0,
                           0, 0, 0, 1, 1, 0, 0,
                           0, 0, 1, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0,
                           1, 0, 1, 0, 1, 0, 0,
                           0, 0, 0, 0, 1, 0, 0,
                           0, 0, 1, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 1, 0, 0,
                           0, 0, 0, 0, 0, 0, 0
};

// Reference and distorted (test) patterns for a '9'
int refer_patt_9[]   = {
                        0, 1, 1, 1, 1, 1, 0,
                        1, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 1,
                        0, 1, 1, 1, 1, 1, 0,
                        0, 0, 0, 0, 0, 0, 1,
                        0, 0, 0, 0, 0, 0, 1,
                        0, 0, 0, 0, 0, 0, 1,
                        0, 0, 0, 0, 0, 0, 1,
                        0, 1, 1, 1, 1, 1, 0 };
int test_patt_9[]    = {
                        0, 1, 0, 0, 1, 1, 0,
                        1, 0, 0, 0, 0, 0, 1,
                        1, 0, 1, 1, 0, 0, 1,
                        0, 0, 0, 0, 0, 0, 0,
                        1, 0, 0, 0, 0, 0, 1,
                        0, 0, 1, 0, 1, 1, 0,
                        0, 1, 0, 0, 0, 0, 0,
                        0, 0, 1, 0, 1, 0, 0,
                        0, 0, 0, 0, 0, 0, 1,
                        0, 0, 0, 0, 0, 0, 1,
                        0, 1, 0, 0, 1, 1, 0 };

// Reference and distorted (test) patterns for a '1'
int refer_patt_1[]   = {
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 1, 1, 0,
                         0, 0, 0, 1, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 1, 1, 1 };
int test_patt_1[]    = {
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 1, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 1,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 0, 1, 0,
                         0, 0, 0, 0, 1, 1, 1,
                         0, 0, 0, 0, 1, 1, 0,
                         0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 1 };

// Reference and distorted patterns for digit <4>.
int refer_patt_4[]   = {
                         1, 0, 0, 0, 0, 0, 0,
                         1, 0, 0, 0, 0, 0, 0,
                         1, 0, 0, 0, 1, 0, 0,
                         1, 0, 0, 0, 1, 0, 0,
                         1, 0, 0, 0, 1, 0, 0,
                         1, 0, 0, 0, 1, 0, 0,
                         1, 1, 1, 1, 1, 1, 1,
                         0, 0, 0, 0, 1, 0, 0,
                         0, 0, 0, 0, 1, 0, 0,
                         0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0 };
int test_patt_4[]    = {
                         1, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0,
                         1, 0, 0, 0, 1, 0, 0,
                         1, 0, 1, 0, 1, 0, 0,
                         1, 0, 0, 0, 1, 0, 0,
                         1, 1, 1, 1, 0, 1, 1,
                         0, 0, 0, 1, 1, 0, 0,
                         0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 1, 0, 0,
                         0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0 };

// Number of reference patterns
void
init_hebbian_weights(float weights[N_HOPFIELD_NEURONS][N_HOPFIELD_NEURONS]);

// Function to train the Hopfield network using Hebbian learning
void
hebbian_training(float weights[N_HOPFIELD_NEURONS][N_HOPFIELD_NEURONS],
                 int ref_pattern[N_HOPFIELD_NEURONS]
                );

// Function to update the Hopfield network synchronously
void
sync_update(float weights[N_HOPFIELD_NEURONS][N_HOPFIELD_NEURONS],
            int dist_pattern[N_HOPFIELD_NEURONS]
           );

// Function to render the reference or distorded patterns
void
render_pattern(int pattern[N_HOPFIELD_NEURONS]);

#endif



#include "hopfntlcp.h"

#define N_REFPATS     3 // Number of patterns to store
#define N_TESTPATS    3 // Number of distorted patterns to test
#define RECALL_ITER   3 // Number of iterations for recall

#define N_COL_NEURON  7 // Number of columns for nice printing of patterns
#define SPACE_CHAR   32 // Character representing the neuron state (off)  
#define SOLID_BLOCK 254 // Character representing the neuron state (on)


float weights[N_HOPFIELD_NEURONS][N_HOPFIELD_NEURONS];

int* ref_patterns[]  = {refer_patt_Crc, refer_patt_Trg, refer_patt_9,
                        refer_patt_4, refer_patt_1
                       };

int *test_patterns[] = {test_patt_Crc, test_patt_Trg, test_patt_9, 
                        test_patt_4, test_patt_1
                       };



//           Function prototype implementations 
//-------------------------------------------------------------------
void
init_hebbian_weights(float weights[N_HOPFIELD_NEURONS][N_HOPFIELD_NEURONS])
{
   // Initialize Hebbian weight matrix to zeros
   for (int i = 0; i < N_HOPFIELD_NEURONS; i++) {
      for (int j = 0; j < N_HOPFIELD_NEURONS; j++)
         weights[i][j] = 0.0f;
   }
}

void
hebbian_training(float weights[N_HOPFIELD_NEURONS][N_HOPFIELD_NEURONS],
                 int ref_pattern[N_HOPFIELD_NEURONS]
                )
{
   // Standard Hebbian learning rule for Hopfield networks
   for (int i = 0; i < N_HOPFIELD_NEURONS; i++) {
      for (int j = 0; j < N_HOPFIELD_NEURONS; j++) {
         if (i != j)
            weights[i][j] +=  (2 * ref_pattern[i] - 1) 
                            * (2 * ref_pattern[j] - 1);
      }
   }
}

void
sync_update(float weights[N_HOPFIELD_NEURONS][N_HOPFIELD_NEURONS],
            int test_pattern[N_HOPFIELD_NEURONS]
           )
{
   int next_neurons[N_HOPFIELD_NEURONS] = {0};

   for (int i = 0; i < N_HOPFIELD_NEURONS; i++) {
      float sum = 0.0f;
      for (int j = 0; j < N_HOPFIELD_NEURONS; j++) {
         // Convert current state of neuron x_j to bipolar (-1 or +1)
         float bipolar = (test_pattern[j] == 1) ? 1.0f : -1.0f;
         sum += weights[i][j] * bipolar; 
      }
      // Determine next state
      next_neurons[i] = (sum >= 0) ? 1 : 0;
   }
   
   // Update all neurons simultaneously
   for (int i = 0; i < N_HOPFIELD_NEURONS; i++) {
      test_pattern[i] = next_neurons[i];
   }
}


void
render_pattern(int pattern[N_HOPFIELD_NEURONS])
{
   for (int i = 0; i < N_HOPFIELD_NEURONS; i++) {
      printf("%c ", pattern[i] ? SOLID_BLOCK : SPACE_CHAR);
      if ((i + 1) % N_COL_NEURON == 0) {
         printf("\n");
      }
   }
   printf("\n");
}



//-------------------------------------------------------------------
int main() {

   // Initialize Hebbian Weight matrix
   init_hebbian_weights(weights);

   printf("\n    Training the Hebbian Weight matrix with %d patterns\n",
          N_REFPATS);

   for (int i = 0; i < N_REFPATS; i++)
      hebbian_training(weights, ref_patterns[i]);

   printf("\n---------- Training Hebbian Weight matrix complete -----------\n");

   printf("\nRecall process for each test pattern begins...\n");
   for (int i = 0; i < N_TESTPATS; i++) {
      printf("Test pattern %d:\n", i + 1);
      render_pattern(test_patterns[i]);

      printf("Recall process for this test pattern:\n\n");
      for (int itr = 0; itr < RECALL_ITER; itr++) {
         sync_update(weights, test_patterns[i]);

         printf("Iteration %d:\n", itr + 1);
         render_pattern(test_patterns[i]);
         (itr == RECALL_ITER - 1)
            ? printf("Recall process for this test pattern is complete.\n\n")
            : printf("Continuing recall process...\n\n");
      }
   }

   printf("\n------------------ Overall recall process complete ------------------\n\n");

   return 0;
}
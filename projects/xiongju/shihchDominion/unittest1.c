/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int j;
    int isEnd;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    printf ("TESTING isGameOver():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {

#if (NOISY_TEST == 1)
                printf("Test player %d with %d on-hand card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                
                //senerio 1: game is not over, since the stack of Province is non-empty, and less than 3 supply pile at 0
                isEnd=0;
                isGameOver(&G);
#if (NOISY_TEST == 1)
                printf("isGameOver = %d, expected = %d ", isGameOver(&G), isEnd);
#endif
                if(isGameOver(&G) == isEnd)// check if game is over
                {
                    printf("pass \n");
                } 
                else
                {
                    printf("FAIL \n");
                }

                //senerio 2: game is over, since the stack of Province is empty(but less than 3 supply pile are at 0)
                G.supplyCount[province] = 0;           //set stack of Province cards to be empty 
                isEnd=1;
                isGameOver(&G);
#if (NOISY_TEST == 1)
                printf("isGameOver = %d, expected = %d ", isGameOver(&G), isEnd);
#endif
                if(isGameOver(&G) == isEnd)// check if game is over
                {
                    printf("pass \n");
                } 
                else
                {
                    printf("FAIL \n");
                }

                //senerio3: game is over, since the stack of Province is empty & three supply pile are at 0
                G.supplyCount[0] = 0;
                G.supplyCount[1] = 0;
                G.supplyCount[2] = 0;
                isEnd=1;
                isGameOver(&G);
#if (NOISY_TEST == 1)
                printf("isGameOver = %d, expected = %d ", isGameOver(&G), isEnd);
#endif
                if(isGameOver(&G) == isEnd)// check if game is over
                {
                    printf("pass \n");
                } 
                else
                {
                    printf("FAIL \n");
                }

                //senerio4: game is over, since three supply pile are at 0 (but the stack of Province is non-empty)
                G.supplyCount[province] = 1;            
                G.supplyCount[0] = 0;
                G.supplyCount[1] = 0;
                G.supplyCount[2] = 0;
                isEnd=1;
                isGameOver(&G);
#if (NOISY_TEST == 1)
                printf("isGameOver = %d, expected = %d ", isGameOver(&G), isEnd);
#endif
                if(isGameOver(&G) == isEnd)// check if game is over
                {
                    printf("pass \n");
                } 
                else
                {
                    printf("FAIL \n");
                }

                //senerio5: game is NOT over, since two supply pile are at 0 (but the stack of Province is non-empty)
                G.supplyCount[province] = 1;            
                G.supplyCount[0] = 0;
                G.supplyCount[1] = 0;
                G.supplyCount[2] = 1;
                isEnd=0;
                isGameOver(&G);
#if (NOISY_TEST == 1)
                printf("isGameOver = %d, expected = %d ", isGameOver(&G), isEnd);
#endif
                if(isGameOver(&G) == isEnd)// check if game is over
                {
                    printf("pass \n");
                } 
                else
                {
                    printf("FAIL \n");
                }

                //senerio6: game is NOT over, since 1 supply pile are at 0 (but the stack of Province is non-empty)
                G.supplyCount[province] = 1;            
                G.supplyCount[0] = 0;
                G.supplyCount[1] = 1;
                G.supplyCount[2] = 1;
                isEnd=0;
                isGameOver(&G);
#if (NOISY_TEST == 1)
                printf("isGameOver = %d, expected = %d ", isGameOver(&G), isEnd);
#endif
                if(isGameOver(&G) == isEnd)// check if game is over
                {
                    printf("pass \n");
                } 
                else
                {
                    printf("FAIL \n");
                }
            
        }
    }

    printf("All tests passed!\n");

    return 0;
}
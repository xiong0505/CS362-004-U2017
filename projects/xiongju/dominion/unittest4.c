/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testendTurn: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
    int numPlayer = 3;
    int maxBonus = 10;
    int p, r;
    int handCount=5;
    int score;
    int scoreSum[MAX_PLAYERS];
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    // arrays of all coppers, silvers, and golds
    int estates[MAX_HAND];
    int duchys[MAX_HAND];
    int provinces[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        estates[i] = estate;
        duchys[i] = duchy;
        provinces[i] = province;
    }

    printf ("TESTING getWinners():\n");

    for(j=0;j<500;j++)
    {
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    for (p = 0; p < numPlayer; p++)
    {
        if(p == 0)
        {
            G.handCount[p]=handCount;
            memcpy(G.hand[p], estates, sizeof(int) * handCount); // set all the cards to estate
            score=scoreFor(p, &G);
            scoreSum[p]=score;
        }   
        if(p == 1)
        {
            G.handCount[p]=handCount;
            memcpy(G.hand[p], duchys, sizeof(int) * handCount); // set all the cards to dunchy
            score=scoreFor(p, &G);
            scoreSum[p]=score;
        }      
        else if(p == 2)
        {
            G.handCount[p]=handCount;
            memcpy(G.hand[p], provinces, sizeof(int) * handCount); // set all the cards to provinces
            score=scoreFor(p, &G);
            scoreSum[p]=score;
        }      
#if (NOISY_TEST == 1)
        printf("Test player %d has score = %d.\n", p,score);
#endif  
    }

    getWinners(scoreSum,&G);
     for (i = 0; i < MAX_PLAYERS; i++)
     {
        if(scoreSum[i]==1)
        {
            printf("The winner is player %d, and expected winner is player %d.\n",i,numPlayer-1);
            assert(i == numPlayer-1); // check if the winner is the right player
        }
     }

    }



     printf("All tests passed!\n");

    return 0;
}
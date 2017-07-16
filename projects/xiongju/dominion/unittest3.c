/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testendTurn: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
    int numPlayer = 4;
    int maxBonus = 10;
    int p, r, handCount;
    int score;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
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

   printf ("TESTING scoreFor():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {

#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], estates, sizeof(int) * handCount); // set all the cards to estate
                score=scoreFor(p, &G);
#if (NOISY_TEST == 1)
                printf("score = %d, expected = %d\n", score, handCount * 1);
#endif
                assert(score == handCount * 1); // check if the number of socre is correct
            
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], duchys, sizeof(int) * handCount); // set all the cards to estate
                score=scoreFor(p, &G);
#if (NOISY_TEST == 1)
                printf("score = %d, expected = %d\n", score, handCount * 3);
#endif
                assert(score == handCount * 3); // check if the number of socre is correct

#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], provinces, sizeof(int) * handCount); // set all the cards to estate
                score=scoreFor(p, &G);
#if (NOISY_TEST == 1)
                printf("score = %d, expected = %d\n", score, handCount * 6);
#endif
                assert(score == handCount * 6); // check if the number of socre is correct
        }
    }

    printf("All tests passed!\n");

    return 0;
}
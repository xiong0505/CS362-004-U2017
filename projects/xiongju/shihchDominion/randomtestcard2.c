/* -----------------------------------------------------------------------
 * Demonstration of how to write card tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testendTurn: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUMTEST 10000
#define SEED 100
#define NUMPLAYERS 2

int main (){
   struct gameState g;
   int testingPass = 0;
   int allPassFlag = 0;
   int currentPlayer = 0;
   int deckSize, handSize, previousHand, afterHand, previousAction, afterAction;
   int errorInHand = 0;
   int errorInAction = 0;
   int i = 0;
   int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
   int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
   srand(time(NULL));

   printf("Testing Village\n");

   for (i = 0; i < NUMTEST; i++) {

			//randomly intialize the game state. then make sure the needed variables are sane.
			initializeGame(NUMPLAYERS, cards, SEED, &g);

			deckSize = rand() % (MAX_DECK + 1);
			handSize = rand() % (deckSize + 1);

			g.deckCount[0] = deckSize - handSize;
			g.handCount[0] = handSize;
			g.numActions = rand() % 10;
			handPos = g.hand[currentPlayer][g.handCount[currentPlayer]-1];

			//Record hand card before calling card effect
			previousHand = g.handCount[0];
			previousAction = g.numActions;
			printf("village PRE: p %d HC %d Action %d \n",currentPlayer, previousHand, previousAction);
		
			cardEffect(village, choice1, choice2, choice3, &g, handPos, &bonus);

			//Record hand card after calling card effect
			afterHand = g.handCount[0];
			afterAction = g.numActions;
			printf("village POST: p %d HC %d Action %d \n",currentPlayer, afterHand, afterAction);

			allPassFlag = 1;

			if(afterHand==previousHand)
			{
			printf("handCount: pass\n");
			}
			else
			{
			printf("handCount: FAIL\n");
			}

			if(afterAction==previousAction+2)
			{
			printf("action: pass\n");
			}
			else
			{
			printf("action: FAIL\n");
			}

			if (allPassFlag == 1) {
			testingPass++;
			}

   }

   return 0;

}



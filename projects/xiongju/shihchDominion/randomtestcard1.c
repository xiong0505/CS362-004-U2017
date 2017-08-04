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

int main () {
	struct gameState g;

	int currentPlayer = 0;
	int errorInDeck = 0;
	int errorInHand = 0; 
	int errorInDiscard = 0;
	int deckSize, handSize, previousDeck, afterDeck, previousHand, afterHand, previousDiscard, afterDiscard;
	int i;
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int testingPass = 0;
	int allPassFlag = 0;

	printf("Testing Smithy\n");

	srand(time(NULL));

	for(i = 0; i < NUMTEST; i++) {
		initializeGame(NUMPLAYERS, cards, SEED, &g);
		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);
		g.deckCount[0] = deckSize - handSize;
		g.handCount[0] = handSize;
		handPos = g.hand[currentPlayer][g.handCount[currentPlayer]-1];

		//Record deck, hand and discard before calling card effect
		previousDeck = g.deckCount[0];
		previousHand = g.handCount[0];
		previousDiscard = g.playedCardCount;

		//Use smithy
		cardEffect(smithy, choice1, choice2, choice3, &g, handPos, &bonus);

		//Note the state after playing the card
      	afterDeck = g.deckCount[0];
      	afterHand = g.handCount[0];
      	afterDiscard = g.playedCardCount;

      	allPassFlag = 1;

      	//Testing 1: Deck decrease by 3
      	if(afterDeck != (previousDeck - 3)){
      		errorInDeck++;
      		allPassFlag = 0;
      	}
      	
      	//Testing 2: Hand increase by 2
      	if(afterHand != (previousHand + 2)){
      		errorInHand++;
      		allPassFlag=0;
      	}

      	//Testing 3: Discard increase by 1
      	if(afterDiscard != (previousDiscard + 1)){
      		errorInDiscard++;
      		allPassFlag = 0;
      	}

      	if (allPassFlag == 1)
      		testingPass++;
   }
	
	printf("-----Summary-----\nTotal %d random runs\nPass: %d\nFail: %d\n", NUMTEST, testingPass, (NUMTEST - testingPass));
	printf("Testing1 - Deck not decrease by 3: %d\n", errorInDeck);
	printf("Testing2 - Hand not increase by 2: %d\n", errorInHand);
	printf("Testing3 - Discard inot ncrease by 1: %d\n", errorInDiscard);
	return 0;
}
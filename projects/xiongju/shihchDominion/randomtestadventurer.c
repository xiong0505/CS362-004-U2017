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
	int errorTreasureCardsHand = 0;
	int errorTreasureCardsDiscard = 0;
	int errorCardsDeckAndDiscard = 0;
	int currentPlayer = 0;
	int deckSize, handSize, randCard, randomCardIdx;
	int discardCopper, discardSilver, discardGold;
	int previousTreasure = 0, afterTreasure = 0;
	int i, j, k, m;
	int choice1 = 0, choice2 = 0, choice3 = 0, handPos = 0, bonus = 0;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int testingPass = 0;
	int allPassFlag = 0;
	int newNumCards, oldNumCards;

	printf("Testing Adventurer\n");

	srand(time(NULL));
	
	for(i = 0; i < NUMTEST; i++) {
		
		//init the game
		initializeGame(NUMPLAYERS, cards, SEED, &g);
		
		//reset counter
		previousTreasure = 0;
		afterTreasure = 0;
		
		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);
		g.deckCount[0] = deckSize - handSize;
		g.handCount[0] = handSize;
		
		for(j = 0; j < NUMPLAYERS; j++){			
			for(k = 0; k < g.deckCount[j]; k++){
				randCard = rand() % 51;
				
				if (randCard == 1) g.deck[j][k] = copper;
				else if(randCard == 2) g.deck[j][k] = silver;
				else if(randCard == 3) g.deck[j][k] = gold;
				else{
					randomCardIdx = rand() % 10;
					g.deck[j][k] = cards[randomCardIdx];}
			}
		}

		//reset counter
		newNumCards=0; 
		oldNumCards=0;
		
		//Record deck and discard before calling card effect
		for(m = 0; m < g.deckCount[0]; m++)
			oldNumCards++;

		for (m = 0; m< g.discardCount[0]; m++)
			oldNumCards++;

		//Record treasure cards before calling card effect
		for(j = 0; j < g.handCount[currentPlayer]; j++)
			if(g.hand[currentPlayer][j] == copper || g.hand[currentPlayer][j] == silver || g.hand[currentPlayer][j] == gold) previousTreasure++;

		//Adventurer used
		cardEffect(adventurer, choice1, choice2, choice3, &g, handPos, &bonus);

		//Record treasure cards after calling card effect
		for(j = 0; j < g.handCount[currentPlayer]; j++) 
			if (g.hand[currentPlayer][j] == copper || g.hand[currentPlayer][j] == silver || g.hand[currentPlayer][j] == gold) afterTreasure++;

		//Record deck and discard after calling card effect
		for(m = 0; m < g.deckCount[0]; m++)
			newNumCards++;

		for (m = 0; m< g.discardCount[0]; m++)
			newNumCards++;

		//reset counter
		discardCopper = 0;
		discardSilver = 0;
		discardGold = 0;

		//Check if treasure cards being discarded
		for(j = 0; j < g.discardCount[currentPlayer]; j++){
			if (g.discard[currentPlayer][j] == copper) discardCopper++;
			else if (g.discard[currentPlayer][j] == silver) discardSilver++;
			else if (g.discard[currentPlayer][j] == gold) discardGold++;
		}

		//boolean flag: true if pass all testings
		allPassFlag = 1;
		
		//Testing 1: Treasure cards increase by 2
		if(afterTreasure != (previousTreasure + 2)){
			allPassFlag = 0;
			errorTreasureCardsHand++;
		}
		
		//Testing 2: No treasure cards being discard
		if(discardGold != 0 || discardSilver != 0 || discardCopper != 0){
			allPassFlag = 0;
			errorTreasureCardsDiscard++;
		}

		//Testing 3: Deck and discard decrease by 2
		if(newNumCards - oldNumCards == 2){
			allPassFlag = 0;
			errorCardsDeckAndDiscard++;
		}
		
		if(allPassFlag) testingPass++;

   }
	
	printf("-----Summary-----\nTotal %d random runs\nPass: %d\nFail %d\n", NUMTEST, testingPass, (NUMTEST-testingPass));
	printf("Testing1 - Treasure cards not increase by 2: %d\n", errorTreasureCardsHand);
	printf("Testing2 - Treasure card in discard: %d\n", errorTreasureCardsDiscard);
	printf("Testing3 - Deck and discard decrease by 2: %d\n", errorCardsDeckAndDiscard);
	return 0;
}
/* -----------------------------------------------------------------------
 * Demonstration of how to write card tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testendTurn: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

 int main(){
 	int i;
 	int r;
 	int p;
 	int handCountOld;
 	int deckCountOld;
 	int discardCountOld;
    int seed = 1000;
    int numPlayer = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING adventurer():\n");

    //scenario 1: first 2 cards on the deck are Treasure cards
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    p = whoseTurn(&G);							//get current player


    handCountOld=5;
	G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before adventurer, and whole hand pile to adventurer
	for(i=0;i<handCountOld;i++)  	 
	{
		G.hand[p][i]=adventurer;
	}

	deckCountOld=5;						
	G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before adventurer, and whole deck pile to cooper		
	for(i=0;i<deckCountOld;i++)
	{
		G.deck[p][i]=copper;
	}

	discardCountOld=10;
	G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before adventurer, and whole discard pile to cooper
	for(i=0;i<discardCountOld;i++)			
	{
		G.discard[p][i]=copper;
	}

	printf("Before adventurer: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,handCountOld,deckCountOld,discardCountOld);
	cardEffect(adventurer, 0, 0, 0, &G, 0, 0); 	//play adventurer card
	printf("After adeventurer: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,G.handCount[p],G.deckCount[p],G.discardCount[p]);
	if(G.handCount[p]==handCountOld+2)			//hand should have 2 more treasury cards
	{
		printf("handCount: pass\n");
	}
	else
	{
		printf("handCount: FAIL\n");
	}
	if(G.deckCount[p]+G.discardCount[p]==deckCountOld+discardCountOld-2)
	{
		printf("deckCount+discardCount: pass\n");
	}
	else
	{
		printf("deckCount+discardCount: FAIL\n");
	}

    //scenario 2: first card on deck is NON-Treasure card, and next 2 cards on the deck are Treasure cards
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    p = whoseTurn(&G);							//get current player


    handCountOld=5;
	G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before adventurer, and whole hand pile to adventurer
	for(i=0;i<handCountOld;i++)  	 
	{
		G.hand[p][i]=adventurer;
	}

	deckCountOld=5;						
	G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before adventurer, and whole deck pile to cooper		
	for(i=0;i<deckCountOld;i++)
	{
		G.deck[p][i]=copper;
	}
	G.deck[p][4]=estate;			//set the top card of current player's deck to non-Treasuer

	discardCountOld=10;
	G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before adventurer, and whole discard pile to cooper
	for(i=0;i<discardCountOld;i++)			
	{
		G.discard[p][i]=copper;
	}

	printf("Before adventurer: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,handCountOld,deckCountOld,discardCountOld);
	cardEffect(adventurer, 0, 0, 0, &G, 0, 0); 	//play adventurer card
	printf("After adeventurer: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,G.handCount[p],G.deckCount[p],G.discardCount[p]);
	if(G.handCount[p]==handCountOld+2)
	{
		printf("handCount: pass\n");
	}
	else
	{
		printf("handCount: FAIL\n");
	}
	if(G.deckCount[p]+G.discardCount[p]==deckCountOld+discardCountOld-2)
	{
		printf("deckCount+discardCount: pass\n");
	}
	else
	{
		printf("deckCount+discardCount: FAIL\n");
	}



    return 0;

 }
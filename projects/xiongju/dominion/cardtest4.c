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
 	int j;
 	int handCountOld;
 	int deckCountOld;
 	int discardCountOld;
 	int embargoTokensOld;
 	int coinsOld;
 	int choice1=7;
    int seed = 1000;
    int numPlayer = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, embargo};
    struct gameState G;

    printf ("TESTING embargo():\n");

    for(j=0;j<500;j++)
    {
	    memset(&G, 23, sizeof(struct gameState));   // clear the game state
	    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	    p = whoseTurn(&G);							//get current player


	    handCountOld=5;
		G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before embargo, and whole hand pile to embargo
		for(i=0;i<handCountOld;i++)  	 
		{
			G.hand[p][i]=embargo;
		}

		deckCountOld=5;						
		G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before embargo, and whole deck pile to cooper		
		for(i=0;i<deckCountOld;i++)
		{
			G.deck[p][i]=copper;
		}

		discardCountOld=10;
		G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before embargo, and whole discard pile to cooper
		for(i=0;i<discardCountOld;i++)			
		{
			G.discard[p][i]=copper;
		}

		embargoTokensOld=G.embargoTokens[choice1];			//get old embargo
		coinsOld=G.coins;									//get old coins
		printf("Before embargo: player=%d, handCount=%d, deckCout=%d, discardCount=%d, embargoTokensOld=%d, coinsOld=%d. \n",p,handCountOld,deckCountOld,discardCountOld,G.embargoTokens[choice1],G.coins);
		cardEffect(embargo, choice1, 0, 0, &G, 4, 0); 	//play embargo card
		printf("After embargo: player=%d, handCount=%d, deckCout=%d, discardCount=%d, embargoTokensOld=%d, coinsOld=%d. \n",p,G.handCount[p],G.deckCount[p],G.discardCount[p],G.embargoTokens[choice1],G.coins);
		if(G.handCount[p]==handCountOld-1)			//hand should have 2 more treasury cards
		{
			printf("handCount: pass\n");
		}
		else
		{
			printf("handCount: FAIL\n");
		}
		if(G.deckCount[p]+G.discardCount[p]==deckCountOld+discardCountOld)
		{
			printf("deckCount+discardCount: pass\n");
		}
		else
		{
			printf("deckCount+discardCount: FAIL\n");
		}
		if(G.embargoTokens[choice1]==embargoTokensOld+1)
		{
			printf("embargo: pass\n");
		}
		else
		{
			printf("embargo: FAIL\n");
		}
		if(G.coins==coinsOld+2)
		{
			printf("coins: pass\n");
		}
		else
		{
			printf("coins: FAIL\n");
		}
    }




    return 0;

 }
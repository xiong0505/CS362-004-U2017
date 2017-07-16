/* -----------------------------------------------------------------------
 * Demonstration of how to write card tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testendTurn: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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
 	int j;
 	int r;
 	int p;
 	int handCountOld;
 	int deckCountOld;
 	int discardCountOld;
 	int playedCardCountOld;
 	int numActionsOld;
    int seed = 1000;
    int numPlayer = 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING village():\n");

    for(j=0;j<500;j++)
    {
	    memset(&G, 23, sizeof(struct gameState));   // clear the game state
	    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	    p = whoseTurn(&G);							//get current player


	    handCountOld=5;
		G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before village, and whole hand pile to adventurer
		for(i=0;i<handCountOld;i++)  	 
		{
			G.hand[p][i]=village;
		}

		deckCountOld=5;						
		G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before village, and whole deck pile to cooper		
		for(i=0;i<deckCountOld;i++)
		{
			G.deck[p][i]=copper;
		}

		playedCardCountOld=0;
		G.playedCardCount=playedCardCountOld;

		discardCountOld=10;
		G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before village, and whole discard pile to cooper
		for(i=0;i<discardCountOld;i++)			
		{
			G.discard[p][i]=copper;
		}

		numActionsOld=1;
		G.numActions=numActionsOld;			//set current player's numActions to 1 before village

		printf("Before village: player=%d, handCount=%d, deckCout=%d, playedCardCount=%d, numActions=%d. \n",p,handCountOld,deckCountOld,playedCardCountOld,numActionsOld);
		cardEffect(village, 0, 0, 0, &G, 4, 0); 	//play village card
		printf("After village: player=%d, handCount=%d, deckCout=%d, playedCardCount=%d, numActions=%d. \n",p,G.handCount[p],G.deckCount[p],G.playedCardCount,G.numActions);
		//hand should remain the same, since draw one and discard one
		if(G.handCount[p]==handCountOld)			
		{
			printf("handCount: pass\n");
		}
		else
		{
			printf("handCount: FAIL\n");
		}
		//deck+playedCard shoudl remain the same, since draw one and played one
		if(G.deckCount[p]+G.playedCardCount==deckCountOld+playedCardCountOld)
		{
			printf("deckCount+discardCount: pass\n");
		}
		else
		{
			printf("deckCount+discardCount: FAIL\n");
		}
		//numActions should increase by 2
		if(G.numActions==numActionsOld+2)
		{
			printf("numActions: pass\n");
		}
		else
		{
			printf("numActions: FAIL\n");
		}
    }





    return 0;

 }
/* -----------------------------------------------------------------------
 * Demonstration of how to write card tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testendTurn: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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

    printf ("TESTING smithy():\n");

    //scenario 1: deckcount > 3
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    p = whoseTurn(&G);							//get current player


    handCountOld=5;
	G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before smith, and whole hand pile to smithy
	for(i=0;i<handCountOld;i++)  	 
	{
		G.hand[p][i]=smithy;
	}

	deckCountOld=5;						
	G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before smithy, and whole deck pile to cooper	for(i=0;i<10;i++)	
	for(i=0;i<deckCountOld;i++)
	{
		G.deck[p][i]=copper;
	}

	discardCountOld=10;
	G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before smithy, and whole discard pilr to cooper
	for(i=0;i<discardCountOld;i++)			
	{
		G.discard[p][i]=copper;
	}

	printf("Before smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,handCountOld,deckCountOld,discardCountOld);
	cardEffect(smithy, 0, 0, 0, &G, 0, 0); 	//play smithy card
	printf("After smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,G.handCount[p],G.deckCount[p],G.discardCount[p]);
	if(G.handCount[p]==handCountOld+3-1)
	{
		printf("handCount: pass\n");
	}
	else
	{
		printf("handCount: FAIL\n");
	}
	if(G.deckCount[p]+G.discardCount[p]==deckCountOld+discardCountOld-3+1)
	{
		printf("deckCount+discardCount: pass\n");
	}
	else
	{
		printf("deckCount+discardCount: FAIL\n");
	}


	//scenario 2: deckcount = 3
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    p = whoseTurn(&G);							//get current player


    handCountOld=5;
	G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before smith, and whole hand pile to smithy
	for(i=0;i<handCountOld;i++)  	 
	{
		G.hand[p][i]=smithy;
	}

	deckCountOld=3;						
	G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before smithy, and whole deck pile to cooper	for(i=0;i<10;i++)	
	for(i=0;i<deckCountOld;i++)
	{
		G.deck[p][i]=copper;
	}

	discardCountOld=10;
	G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before smithy, and whole discard pilr to cooper
	for(i=0;i<discardCountOld;i++)			
	{
		G.discard[p][i]=copper;
	}

	printf("Before smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,handCountOld,deckCountOld,discardCountOld);
	cardEffect(smithy, 0, 0, 0, &G, 0, 0); 	//play smithy card
	printf("After smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,G.handCount[p],G.deckCount[p],G.discardCount[p]);
	if(G.handCount[p]==handCountOld+3-1)
	{
		printf("handCount: pass\n");
	}
	else
	{
		printf("handCount: FAIL\n");
	}
	if(G.deckCount[p]+G.discardCount[p]==deckCountOld+discardCountOld-3+1)
	{
		printf("deckCount+discardCount: pass\n");
	}
	else
	{
		printf("deckCount+discardCount: FAIL\n");
	}

	//scenario 3: deckcount = 2
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    p = whoseTurn(&G);							//get current player


    handCountOld=5;
	G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before smith, and whole hand pile to smithy
	for(i=0;i<handCountOld;i++)  	 
	{
		G.hand[p][i]=smithy;
	}

	deckCountOld=2;						
	G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before smithy, and whole deck pile to cooper	for(i=0;i<10;i++)	
	for(i=0;i<deckCountOld;i++)
	{
		G.deck[p][i]=copper;
	}

	discardCountOld=10;
	G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before smithy, and whole discard pilr to cooper
	for(i=0;i<discardCountOld;i++)			
	{
		G.discard[p][i]=copper;
	}

	printf("Before smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,handCountOld,deckCountOld,discardCountOld);
	cardEffect(smithy, 0, 0, 0, &G, 0, 0); 	//play smithy card
	printf("After smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,G.handCount[p],G.deckCount[p],G.discardCount[p]);
	if(G.handCount[p]==handCountOld+3-1)
	{
		printf("handCount: pass\n");
	}
	else
	{
		printf("handCount: FAIL\n");
	}
	if(G.deckCount[p]+G.discardCount[p]==deckCountOld+discardCountOld-3+1)
	{
		printf("deckCount+discardCount: pass\n");
	}
	else
	{
		printf("deckCount+discardCount: FAIL\n");
	}


	//scenario 4: deckcount < 2
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    p = whoseTurn(&G);							//get current player


    handCountOld=5;
	G.handCount[p]=handCountOld; 	//set current turn player's hand count to 5 before smith, and whole hand pile to smithy
	for(i=0;i<handCountOld;i++)  	 
	{
		G.hand[p][i]=smithy;
	}

	deckCountOld=1;						
	G.deckCount[p]=deckCountOld;	//set current player's deck count to 5 before smithy, and whole deck pile to cooper	for(i=0;i<10;i++)	
	for(i=0;i<deckCountOld;i++)
	{
		G.deck[p][i]=copper;
	}

	discardCountOld=10;
	G.discardCount[p]=discardCountOld;			//set current player's discard pile to 10 before smithy, and whole discard pilr to cooper
	for(i=0;i<discardCountOld;i++)			
	{
		G.discard[p][i]=copper;
	}

	printf("Before smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,handCountOld,deckCountOld,discardCountOld);
	cardEffect(smithy, 0, 0, 0, &G, 0, 0); 	//play smithy card
	printf("After smithy: player=%d, handCount=%d, deckCout=%d, discardCount=%d. \n",p,G.handCount[p],G.deckCount[p],G.discardCount[p]);
	if(G.handCount[p]==handCountOld+3-1)
	{
		printf("handCount: pass\n");
	}
	else
	{
		printf("handCount: FAIL\n");
	}
	if(G.deckCount[p]+G.discardCount[p]==deckCountOld+discardCountOld-3+1)
	{
		printf("deckCount+discardCount: pass\n");
	}
	else
	{
		printf("deckCount+discardCount: FAIL\n");
	}

    return 0;

 }
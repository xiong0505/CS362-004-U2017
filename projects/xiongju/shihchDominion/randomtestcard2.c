/* -----------------------------------------------------------------------
 * Demonstration of how to write card tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testendTurn: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

 int main(){
	int i, n, r, p, deckCount, discardCount, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	printf("Testing village.\n");

	SelectStream(2);
	PutSeed(3);

	for(n=0;n<200000;n++){
		printf("round: %d\n",n);
		for(i=0;i<sizeof(struct gameState);i++){
			((char*)&G)[i]=floor(Random()*256);
		}
		p=floor(Random()*2);
		G.deckCount[p]=floor(Random()*MAX_DECK);
		G.discardCount[p]=floor(Random()*MAX_DECK);
		G.handCount[p]=floor(Random()*MAX_HAND)+1;     //at least have one card on hand to play
		checkVillageCard(p,&G);
	}

	printf("ALL TESTS OK\n");
	exit(0);
 }

 int checkVillageCard(int p,struct gameState *post){
 	int r;
 	int drawNum=1;
 	int actionNum=2;
 	struct gameState pre;
 	memcpy(&pre,post,sizeof(struct gameState));

 	printf("village PRE: p %d HC %d Dec %d DiC %d \n",p, pre.handCount[p],pre.deckCount[p],pre.discardCount[p]);
 	r=villageRef(p,post,0); 	//play village card
 	printf("village POST: p %d HC %d Dec %d DiC %d \n",p, post->handCount[p],post->deckCount[p],post->discardCount[p]);

	if(post->handCount[p]==pre.handCount[p]+drawNum)
	{
		printf("handCount: pass\n");
	}
	else
	{
		printf("handCount: FAIL\n");
	}
	if(post->deckCount[p]+post->discardCount[p]==pre.deckCount[p]+pre.discardCount[p]-drawNum)
	{
		printf("deckCount+discardCount: pass\n");
	}
	else
	{
		printf("deckCount+discardCount: FAIL\n");
	}
	if(post->numActions==pre.numActions+actionNum)
	{
		printf("action: pass\n");
	}
	else
	{
		printf("action: FAIL\n");
	}

 	assert(r==0);

 }
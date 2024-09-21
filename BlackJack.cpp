#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function prototypes
int dealfromdeck(bool b[52]);
int getcardvalue(int cardnumber);
void changefirstAce2one(int hand[7]);
int sumuphand(int hand[7]);
bool need2shuffle(bool deck[52]);
void shuffledeck(bool deck[52]);
void resethand(int hand[7], int v);
void displayhand(int hand[7], bool showfirstcardonly);
void getcardvaluesintoArray(int cardnumArray[7], int cardvalArray[7]);


// main()
int main(){
	srand(time(0));
	
	// Set up the "deck" of boolean array of 52 cards
	bool deck[52];
	// set to all true (available - not drawn).
	shuffledeck(deck);
	

	int playerhand[7];
	int dealerhand[7];
	resethand(playerhand,7);
	resethand(dealerhand,7);
	int playerhandvalue[7];
	int dealerhandvalue[7];
	
	int dealerscore, playerscore;
	// BlackJack game
	// 


	//
	// Reminder Cardnumber are indices from 0 to 51
	// 			CardValue are integers from 1 to 11
	
	char choice; // Hit or Stand choice
	char playagainchoice;
	// set playagain = true
	bool playagain = true;
	bool bust = false;
	// loop(while player wants to playagain):
	while(playagain == true){
		cout << "-----------------------------------------------" <<endl;
			int dCardcount = 0;
			int pCardcount = 0;
			dealerscore = 0;
			playerscore = 0;
			
	//		(reset both player's hand to -1s)
			resethand(playerhand, -1);
			resethand(dealerhand, -1);
			resethand(playerhandvalue, 0);
			resethand(dealerhandvalue, 0);
			
	//		(deal 2 "cards") to dealer and player
			dealerhand[dCardcount++] = dealfromdeck(deck);		
			dealerhand[dCardcount++] = dealfromdeck(deck);
			getcardvaluesintoArray(dealerhand,dealerhandvalue);
			
			playerhand[pCardcount++] = dealfromdeck(deck);
			playerhand[pCardcount++] = dealfromdeck(deck);
			getcardvaluesintoArray(playerhand,playerhandvalue);
			
			
	//			show 1 of the 2 cards for the dealer
	cout << "Dealer's hand:\n";
				displayhand(dealerhand , true); // display dealerhand, show only first is true
	cout << "\nPlayer's hand:\n";
				displayhand(playerhand, false); // display player's hand, show only first is false
				
	//			show both card for the player

	//		set stand to false
			bool stand = false;
			
	//		get or assign playerscore
			changefirstAce2one(playerhandvalue); // only happens if score is over 21 and there's an ace
			playerscore = sumuphand(playerhandvalue);
			cout << "Player's total: " << playerscore <<endl;
	
	//player's turn
	//	loop(while playerscore < 21 and not stand):
do{
	
			//	Ask the player "hit" or "stand" (input)
				cout << "Hit(H) or Stand(S)?" <<endl;;
				cin >> choice;
	          			
				if (choice == 'H' || choice == 'h'){
				cout << "----------------------------------------------------------------" <<endl;
				
				need2shuffle(deck);
				playerhand[pCardcount++] = dealfromdeck(deck);
				getcardvaluesintoArray(playerhand,playerhandvalue);
			
				
				cout << "Dealer's hand:\n";
				displayhand(dealerhand , true); // display dealerhand, show only first is true
            	cout << "\nPlayer's hand:\n";
				displayhand(playerhand, false); // display player's hand, show only first is false
				
				changefirstAce2one(playerhandvalue); // only happens if score is over 21 and there's an ace
			    playerscore = sumuphand(playerhandvalue);
			    cout << "Player's total: " << playerscore <<endl;
				
}
             
              else if (choice == 'S' || choice == 's'){
              	stand = true;
			  }
}while(!(playerscore > 21) && (stand != true));
if (playerscore > 21){
		bust = true;
		playagain = false;
		cout << "Sorry! You've Busted :(" <<endl;
		cout << "Would You like to play again? (y/n)" <<endl;
		cin >> playagainchoice;
		if(playagainchoice == 'Y' || playagainchoice =='y'){
		    playagain = true;
	}
}

//dealer's turn:
	do{
		dealerscore = sumuphand(dealerhandvalue);
		cout << "----------------------------------------------------------------" <<endl;
		need2shuffle(deck);
				dealerhand[dCardcount++] = dealfromdeck(deck);
		getcardvaluesintoArray(dealerhand,dealerhandvalue);
		
		cout << "Dealer's hand:\n";
        displayhand(dealerhand , false); // display dealerhand, show only first is false

        changefirstAce2one(dealerhandvalue);
        dealerscore = sumuphand(dealerhandvalue);
        cout << "Dealer's Score: " <<dealerscore << endl;

        cout << "\nPlayer's hand:\n";
        displayhand(playerhand, false); // display player's hand, show only first is false
		
        changefirstAce2one(playerhandvalue); 
        playerscore = sumuphand(playerhandvalue);
        cout << "Player's total: " << playerscore <<endl;
		changefirstAce2one(dealerhandvalue);
		dealerscore = sumuphand(dealerhandvalue);
		
		if (dealerscore > 21){
			bust = true;
			cout << "Congraulations! Dealer Busted! You've Won!" <<endl;
		}
		
		
}while((bust != true) && dealerscore < 17);

// compare the player's score and dealer's score

	if (playerscore > dealerscore && playerscore <=21){
		cout << "Congraulations! You Won!" <<endl; 
	}
	else if (playerscore < dealerscore && dealerscore <=21){
		cout << "Sorry, Dealer Won this time" <<endl;
	}	
	else if (dealerscore == playerscore){
		cout << "Oh, Looks Like You Tied. No Winners This Time!" <<endl;
	}
	

//ask the user to playagain (y/n)
	cout << "Would you like to play again?  (y/n)" <<endl;
	cin >> playagainchoice;
	
	if(playagainchoice == 'N' || playagainchoice =='n'){
		playagain = false;
	}
}
	
	
}// end of main()

// Function Definitions:

// getcardvaluesintoArray() gets the value of each cardnumber in cardnumArray[] and assigns it
// respectively to carvalArray[]
// cardnumArray[7] = {51, 13,-1,-1,-1,-1,-1};
// cardvalArray[7] = {10, 11, 0, 0, 0, 0, 0};
void getcardvaluesintoArray(int cardnumArray[7], int cardvalArray[7]){
	for(int i=0; i < 7; i++){
		if(cardnumArray[i] == -1)
			cardvalArray[i] = 0;
		else	
			cardvalArray[i] = getcardvalue(cardnumArray[i]);
	}
}


// cardnumber is from 0 - 51;

int getcardvalue(int cardnumber){
	int rankindex = cardnumber % 13; // rankindex 0 to 12
	if(rankindex == 0)
		return 11;
	else if(rankindex >=9)
		return 10;
	return rankindex + 1;
	
}

// displays the rank and suit of all the cards in the hand[]
// only show the first card if showfirstonly true
// display both if showfirstonly false;
// example of the handd:
// hand[7] = {51,13,-1,-1,-1,-1,-1}; (-1 means NO CARD PRESENT)

void displayhand(int hand[7], bool showfirstcardonly){
	// Arrays to represent the text for each card
	string rank[13] = {	"A-ace","2-two","3-three","4-four",
						"5-five","6-six","7-seven","8-eight","9-nine",
						"10-ten","J-Jack","Q-Queen", "K-King"};
						
	string suits[4] = {"spades", "hearts", "clubs", "diamonds"};
	
	
	int rankindex, suitindex, cardnum;
	if(showfirstcardonly == false){
		for(int i=0; i < 7; i++){
			if(hand[i] != -1){
				rankindex = hand[i] % 13;
				suitindex = hand[i] / 13;
				 cout << rank[rankindex]<< " of " << suits[suitindex] << "(" << getcardvalue(hand[i]) << ")"<<endl;
			}
		}
	}
	else{
		rankindex = hand[0] % 13;
		suitindex = hand[0] / 13;
		 cout << rank[rankindex]<< " of " << suits[suitindex] << "(" << getcardvalue(hand[0]) << ")"<<endl;
	}
}




// Assuming hand is of cardvalues:
// changes the First 11 in hand to a 1
// cardnumArray[7] = {0, 13,-1,-1,-1,-1,-1};
// cardvalArray[7] = {11, 11, 0, 0, 0, 0, 0};
// cardvalArray[7] = { 1, 11, 0, 0, 0, 0, 0};
void changefirstAce2one(int valhand[7]){
	if (sumuphand(valhand) > 21){
		for(int i=0; i < 7; i++){
			if(valhand[i] == 11){
				valhand[i] = 1;
				return;
			}
		}
	}
}




// Assuming the hand is of cardVALUEs
// returns the sum of the hand of values
int sumuphand(int hand[7]){
	int sum = 0;
	for(int i=0; i < 7; i++){
		sum = sum + hand[i];
	}
	return sum;
	
}

// returns false if there is at least 1 boolean element in deck that is true
// returns true if there are no more true values in deck[]
bool need2shuffle(bool deck[52]){
	for(int i=0; i<52; i++){
		if(deck[i] == true){
			return false;
		}
	}
	return true; // placeholder return
}

// changes all the values in deck[] to all true.
void shuffledeck(bool deck[52]){
	for(int i=0; i<52; i++){
		deck[i] = true;
	}
}

// sets the entire hand[] to all -1's
void resethand(int hand[7], int v){
	for(int i=0; i < 7; i++){
		hand[i] = v;
	}
}

//returns a cardnumber from 0-51 that is True in deck[]
int dealfromdeck(bool deck[52]){
	int cardnum;
	do{
		cardnum = rand() % 52; 
	}while(deck[cardnum] == false);
	deck[cardnum] = false;
	return cardnum;
}



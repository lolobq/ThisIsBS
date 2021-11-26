#include <iostream>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cstring>
#include <string>
#include <random>
#include <algorithm> //Used for random_shuffle method
using namespace std;

class Player
{
    public:
    //CONSTRUCTORS:
    Player() {};
    Player(string playerName)
    {
        name = playerName;
    };

    //VARIABLES:
    vector<int> cards; 
    string name;
    bool hasAceofSpades = false;
    bool isBot = false;

    //FUNCTIONS:
    //Removes a card from a player's hand
    void RemoveCard(int cardVal)
    {
        int size = cards.size();
        for(int i = 0; i < size; i++)
        {
            if(cards[i] == cardVal)
            {
                cards.erase(cards.begin()+i, cards.begin()+i+1);
                break;
            }
        }
    }

    //Adds a card to a player's hand
    void AddCard(int cardVal)
    {
        cards.push_back(cardVal);
    }

    //Sorts a player's hand in ascending order using built in algorithm
    void OrganizeHand()
    {
        sort(cards.begin(), cards.end());
    }

    //Algorithm to make a bot call BS
    bool BotCallBS()
    {
        int BSFRQ; //this will be the % for frequency of BS
        int handSize = cards.size();
        srand(time(0)); //put up here for randomization.
        
        if (handSize >=10)
        {
            BSFRQ = 60;
        }
        else if (handSize >=5 && handSize <=9)
        {
            BSFRQ = 20;
        }
        else
        {
            BSFRQ = 10;
        }

        int x = rand() % BSFRQ;
        
        if(x == 0 || x == 3 || x == 4 || 
           x == 7 || x == 8 || x == 12 || x == 18 || x == 25)
        {
            return true; 
        }
        
        return false;
    }

    //Returns the string representation of the card value
    string findCardVal(int cardVal)
    {
        if(cardVal == 1)
        {
            return "A";
        }
        else if(cardVal == 11)
        {
            return "J";
        }
        else if(cardVal == 12)
        {
            return "Q";
        }
        else if(cardVal == 13)
        {
            return "K";
        }
        else
        {
            return to_string(cardVal);
        }
    }
    
    //Algorithm that plays a bot's card if it has the desired card
    //Randomly selects a card if it doesn't have the desired cards
    //Returns card value that was played
    int BotPlays(int desiredCard)
    {
        int cardsLength = cards.size();
        int cardVal;
        
        //Searches to see if the person has the desired card
        for(int i = 0; i < cardsLength; i++)
        {
            cardVal = cards[i];
            
            if(cardVal == desiredCard)
            {
                return cardVal;
            }
        }

        //Randomly plays a card if the person doesn't have the desired card
        int ranIndex = rand() % cardsLength;
        return cards[ranIndex];
    }

    //Displays cards using ASCII characters
    void DisplayCards()
    {
        int vectorLength = cards.size();
        int i, r, numIterations;
        int vectorIndex = 0;
        string cardDisplay;

        //values that control how many times each loop runs
        int numCardsInRow = 8;
        int numRows = (vectorLength / numCardsInRow);
        int remain = (vectorLength % numCardsInRow);
        if(remain != 0)
        {
            numRows++;
        }
        
        //each loop iteration does one full row of cards
        for(r = 0; r < numRows; r++)
        {
            //determines how many cards are in the current row -> determines how many times to loop
            if(r == numRows-1 && remain != 0)
            {
                numIterations = remain;
            }
            else
            {
                numIterations = numCardsInRow;    
            }
            
            //upper border of each card
            for(i = 0 ; i < numIterations; i++)
            {
                cout << " _______" << "\t" ;
            }
            cout << endl;
            
            //first side border of each card -> includes card value
            for(i = 0; i < numIterations; i++)
            { 
                vectorIndex = (r*numCardsInRow) + i;
                int cardVal = cards.at(vectorIndex);
                cardDisplay = findCardVal(cardVal);
                
                // conditions for the cards in the players hand
                if(cardVal == 10)
                {
                    cout << "|" << cardDisplay << "     |" << "\t" ;
                }
                else
                {
                    cout << "|" << cardDisplay << "      |" << "\t" ;
                }
                
            }
            cout << endl;
            
            //adds 3 rows of borders to each card
            for(int rowCount = 0; rowCount < 3; rowCount++)
            {
                for(i = 0; i < numIterations; i++)
                {
                    cout << "|       |" << "\t";
                }
                cout << endl;
            }
            
            //last side border of each card -> includes card value
            for(i = 0; i < numIterations; i++)
            {
                vectorIndex = (r*numCardsInRow) + i;
                int cardVal = cards[vectorIndex];
                cardDisplay = findCardVal(cardVal);
                
                if(cardVal == 10)
                {
                    cout << "|     " << cardDisplay << "|" << "\t";
                }
                else
                {
                    cout << "|      " << cardDisplay << "|" << "\t";
                }
            }
            cout << endl;
            
            //Bottom border for each card
            for( i = 0; i < numIterations; i++)
            {
                cout << " ￣￣￣￣" << "\t";
            }
            cout << endl;
        }
    }
};

//GAME CLASS
class Game
{
    public:
    //CONSTRUCTOR:
    Game(int players, int bots)
    {
        numPlayers = players;
        numBots = bots;
    };

    //VARIABLES:
    int numPlayers;
    int numBots;
    vector<int> pile; //vector for pile in the middle                                                      
    vector<Player> players; //contains players
    
    //FUNCTIONS:
    //Fills the players vector with new players and bots
    void GeneratePlayers()
    {
        string playerName;                                                                      
        
        //loop for given number of players
        for(int i = 0; i < numPlayers; i++)                                                 
        {   
            //allows user to pick a name
            cout << "What's the player's name?" << endl;                                    
            cin >> playerName;

            //assign player to an index    
            players.push_back(Player(playerName));                                            
        }

        //add bots to the vector if needed
        if(numBots > 0)
        {
            int botNumber = 1;
            string botName;

            //loop for a given number of bots 
            for(int i = numPlayers; i < numPlayers + numBots; i++)
            {
                botName = "Bot " + to_string(botNumber);
                players.push_back(Player(botName));
                players[i].isBot = true;
                botNumber++;
            }
        }
    }

    //Create deck of cards
    void GenerateDeckOfCards()                                                      
    {   
        //creating variable for initializing vector starting point
        int vectorIndex = 0;
        
        //this for loop represents Ace (1) to King (13) cards
        for(int i = 1; i < 14; i++)
        {
            //this loop accounts for each of the four suits
            for(int j = 0; j < 4; j++)
            {
                pile.push_back(i);
                vectorIndex++;
            }
        }
    }

    //Shuffle cards
    void ShuffleCards()
    {
        random_device rd;
        default_random_engine rng(rd());

        shuffle(pile.begin(), pile.end(), rng);
    }

    //Deal cards
    void DealCards()
    {
        int cardValue;
        int playerIndex = 0;

        //Loop deals cards while there are still cards in the pile
        while(pile.size() != 0)
        {
            //Always take the front value in the pile 
            cardValue = pile[0];
            pile.erase(pile.begin(), pile.begin()+1);

            //Add the card value from the front of the pile to one of the player's hand
            players[playerIndex].cards.push_back(cardValue);
            int playersSize = players.size();
            if(playerIndex == playersSize-1) //Go back to the first player if we're at the end of the vector
            {
                playerIndex = 0;
            }
            else //Increment the index to deal to the next player
            {
                playerIndex++;
            }   
        }
    }

    //Assign Ace of Spades to a random player with a 1 
    //Returns the index of the player with the ace
    int AssignAce()
    {
        Player p = Player();
        vector<int> hasAce; //Holds the indexes of the players in the players vector that have an ace
        vector<int>::iterator aceIndex;
        int playersSize = players.size();

        //Loop through players 
        for(int i = 0; i < playersSize; i++)
        {
            p = players[i];

            //Searches through the player's cards and finds the index where an ace is
            aceIndex = find(p.cards.begin(), p.cards.end(), 1); 

            //Ace is in the the cards
            if(aceIndex < p.cards.end())
            {
                hasAce.push_back(i);
            }
        }

        //Selects a random value out of hasAce and assigns the ace of spades to the player from that index
        srand(1);
        int ranIndex = rand() % hasAce.size(); 
        int playerIndex = hasAce[ranIndex]; 
        players[playerIndex].hasAceofSpades = true;
        return playerIndex;
    }

    //Organizes each player's hand
    void OrganizeHands()
    {
        int playersSize = players.size();
        for(int i = 0; i < playersSize; i++)
        {
            players[i].OrganizeHand();
        }
    }

    //Check to make sure every player has at least one card - returns false if a player has 0 cards
    bool HasCard()
    {
        int playersSize = players.size();
        for(int i = 0; i < playersSize; i++)
        {
            if(players[i].cards.size() == 0)
            {
                return false;
            }
        }

        return true;
    }
    
    //Finds the winner -> returns the index of the winner
    int FindWinner()
    {
        int playersSize = players.size();
        int cardsSize = 0;
        for(int i = 0; i < playersSize; i++)
        {
            cardsSize = players[i].cards.size();
            if(cardsSize == 0)
            {
                return i;
            }
        }
    }

    //Adds a card to end of the pile
    void AddCard(int cardVal)
    {
        pile.push_back(cardVal);
    }

    //Removes a card from the given index
    void RemoveCard(int index)
    {
        pile.erase(pile.begin()+index, pile.begin()+index+1);
    }

    //Clears display - adds 10 or so newlines 
    void ClearDisplay()
    {
        for(int i = 0; i < 10; i++)
        {
            cout << "\n";
        }
    }

    //Function to play the game
    void PlayGame()
    {
        //Generate players
        GeneratePlayers();

        //Generate deck of cards
        GenerateDeckOfCards();

        //Shuffle cards
        ShuffleCards();

        //Deal cards
        DealCards();

        //Assign ace of spades and then set order based on who has the ace of spades
        int startPlayer = AssignAce();
        
        //Organize each player's hand
        OrganizeHands();

        bool playersHaveCards = true; //keeps track of when all players still have cards
        int playerIndex = startPlayer; //keeps track of which player's turn it is
        int cardValue = 0; //holds the numerical value of the card that the user wants to play
        string playerInput; //how we find out which card the user wants to play
        char playerInputChar;
        string emptyString;
        int playersSize = players.size(); //size of players vector
        int properCardVal = 0; //keeps track of which card should've been played if the player put the proper one down

        //Loop executes while each player still has at least 1 card
        while(playersHaveCards)
        {
            //Checks to see if the ace of spades has been played yet
            if(players[playerIndex].hasAceofSpades) 
            {
                players.at(playerIndex).DisplayCards(); //display cards
                cout << players[playerIndex].name << ", begin the game by playing an ace. Press any key to continue." << endl;
                cin >> emptyString;
                cout << players[playerIndex].name << " played an ace." << endl;

                AddCard(1); //add ace to the middle pile
                players[playerIndex].RemoveCard(1); //remove the ace from the user's hand
                players[playerIndex].hasAceofSpades = false; //indicate that the ace of spades has been played
                properCardVal = 1;
            }
            else
            {
                if(players[playerIndex].isBot == false) //routine for human player to play card
                {
                    //display the cards in the user's hand
                    players[playerIndex].DisplayCards();
    
                    cout << players.at(playerIndex).name << ", which card would you like to play?" << endl;
                    cin >> playerInput;
                    cout << endl;
                    
                    if(playerInput != "10")
                    {
                        playerInputChar = playerInput[0];
                        
                        if(isalpha(playerInputChar))
                        {
                            playerInputChar = tolower(playerInputChar);
                        }
                    
                        playerInput = playerInputChar;
                    }
                    
                    //finds out which character the user wants to play and makes sure it's valid
                    while(playerInput != "k" && playerInput != "q" 
                    && playerInput != "j" && playerInput != "a" && playerInput != "2" && playerInput != "3" 
                    && playerInput != "4" && playerInput != "5" && playerInput != "6" && playerInput != "7"
                    && playerInput != "8" && playerInput != "9" && playerInput != "10") 
                    {
                        cout << players[playerIndex].name << " please enter a single number or character (k, q, j, a)" << endl;
                        cin >> playerInput;
                        cout << endl;
                    }
                    
                    if(playerInput != "10")
                    {
                        playerInputChar = playerInput[0];
                        
                        if(isalpha(playerInputChar))
                        {
                            playerInputChar = tolower(playerInputChar);
                        }
                    
                        playerInput = playerInputChar;
                    }
                    
                    //Deals with face cards
                    switch(playerInputChar) 
                    {
                        case 'a'  :
                            cardValue = 1;
                            break; //optional
                        case 'j'  :
                            cardValue = 11;
                            break; //optional
                        case 'q'  :
                            cardValue = 12;
                            break; //optional
                        case 'k'  :
                            cardValue = 13;
                            break; //optional
                        default : 
                            cardValue = stoi(playerInput);
                    }
                }
                else //routine for bot to play card
                {
                    cardValue = players[playerIndex].BotPlays(properCardVal);
                }

                //Add the card to the pile and remove the card from the player's hand
                AddCard(cardValue);
                players[playerIndex].RemoveCard(cardValue);
                
                ClearDisplay();
                
                cout << players[playerIndex].name << " played a card." << endl;
                
                //Keeps track of what the actual played card value should be
                if(properCardVal == 13)
                {
                    properCardVal = 1;
                }
                else
                {
                    properCardVal++;
                }

                bool callBS = false;
                int callBSIndex = -1;
                string userInput;
                for(int i = 0; i < playersSize; i++)
                {
                    if(players[i].isBot && i != playerIndex) //bot call bs routine -> doesn't let the card player call BS
                    {
                        callBS = players[i].BotCallBS(); 
                        callBSIndex = i;
                        
                        if(callBS == true)
                        {
                            cout << players[i].name << " called BS." << endl;
                            i = playersSize; 
                        }
                    }
                    else //player call bs routine -> doesn't let the card player call BS
                    {
                        if(i != playerIndex)
                        {
                            cout << players[i].name << ", would you like to call bs? Type y for yes or n for no." << endl;
                            cin >> userInput;
    
                            if(userInput == "y" || userInput == "Y" || userInput == "yes" || userInput == "Yes")
                            {
                                callBS = true;
                                callBSIndex = i;
                                cout << players[i].name << " called BS." << endl;
                                i = playersSize; 
                            }
                            else
                            {
                                callBS = false;
                            }
                        }
                    }
                    
                    cout << endl;
                }

                if(callBS && pile.size() > 0)
                {
                    int pileSize = pile.size();
                    int card;
                    

                    //if someone calls bs and it is bs - give the cards in the pile to the person who just played
                    if(properCardVal != pile[pileSize - 1]) 
                    {
                        while(pileSize > 0)
                        {
                            card = pile[0];
                            players[playerIndex].AddCard(card);
                            RemoveCard(0);
                            pileSize--;
                        }
                        
                        cout << "It was BS!" << endl;
                    }
                    //if someone calls bs and it is not bs - give the cards in the pile to the caller
                    else if(properCardVal == pile[pileSize - 1]) 
                    {
                        while(pileSize > 0)
                        {
                            card = pile[0];
                            players[callBSIndex].AddCard(card);
                            RemoveCard(0);
                            pileSize--;
                        }
                        
                        cout << "It wasn't BS!" << endl;
                    }
                }
            }

            if(playerIndex == playersSize-1) //Bring back to the first index in players vector
            {
                playerIndex = 0;
            }
            else //Increment to next player in players vector
            {
                playerIndex++;
            }

            //Check to make sure every player has a card
            playersHaveCards = HasCard();
            
            //Gives the player time to see the results before clearing the display
            string fillerVar;
            cout << "Press any key to continue." << endl;
            cin >> fillerVar;
            
            //Returns newlines to "clear" the display before the next player
            ClearDisplay();

            //Organize each player's cards
            OrganizeHands();
        }
        
        //Returns the winner of the game
        int winnerIndex = FindWinner();
        cout << players[winnerIndex].name << " won the game!" << endl;
    }
};

//Where the game is played
int main()
{
    int numPlayers = 0;
    int numBots = 0;

    //game must have between 1 and 4 players
    while(numPlayers < 1 || numPlayers > 4)
    {         
        cout << "Please enter a number between 1 and 4." << endl;                               
        cout << "How many players are there?\n";
        cin >> numPlayers;
    }

    if(numPlayers < 3) //generate bots and players
    {
        numBots = 4-numPlayers;
    }
    else if(numPlayers >= 3 && numPlayers <=4) //generate just players
    {
        numBots = 0;
    }  

    //Create a game and play
    Game bs(numPlayers, numBots);
    bs.PlayGame();

    return 0;
}
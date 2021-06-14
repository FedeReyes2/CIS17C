
/* 
 * File:   main.cpp
 * Author: Federico Reyes
 *
 * This is project 2, I will develop a "Hanged" as my game.
 * 
 * I will use recursions, recursive sorts, hashing, trees and graphs to implement
 * the game and try different versions of it. 
 */

//directives
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <random>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <list>
#include <stack>

//My headers

#include "Player.hxx"
#include "node.hxx"

//Function prototypes

void menu();
void newGame();
void makeHang(const int& body);
void keyToC();
void fixQ(std::queue<std::string> &pos);
std::queue<std::string> getPlace(const std::vector<Player> &o);
std::queue<std::string> makeMap();
int fib(int n);
void bubbleSort(std::vector<char>& arr, int n);
node* newNode(std::string data);
void prntLev(node* root);
int height(node* node);
void prntLev(node* root, int level);

//This is function designed to clean the screen

void clean() { std::cout << "\033[2J\033[1;1H"; }


//Main function we will just execute one function

int main()
{
    menu();
    
    return 0;
}

// This is gonna be the main menu, we are gonna introduce the number of players
// and also the name of the players. 

void menu()
{
    
    //This is the main menu, we have the options to quit the game or just to 
    // start a new game. 
    
    int option;
    std::cout << std::setw(80) << std::setfill('-');
    std::cout << '\n';
    std::cout << std::setw(50) << std::setfill(' ') << "Welcome to Hanged" << '\n';
    std::cout << std::setw(80) << std::cout.fill('-') << '\n';
    std::cout << std::setw(45) << std::setfill(' ') << "1. New Game" << '\n';
    std::cout << std::setw(43) << std::setfill(' ') << "2. Quit" << '\n';
    std::cout << std::setw(80) << std::cout.fill('-') << '\n';
    std::cin >> option;
    
    //Here we see if the value is valid, we could have made a mistake 
    
    while(option < 1 || option > 2)
    {
        std::cout << " Enter a valid input" << std::endl;
        std::cin >> option;
    }
    
    switch (option)
    {
        case 1:
            newGame();
            break;
        case 2:
            break;
    }      
}

//This is the main menu for the new game
// Here we are going to recollect the number of players and the name of them.

void newGame()
{
    clean();
    makeHang(6);
    int numberPlayers;
    std::string line;
    std::vector<std::string> PlayerNames;
    std::vector<Player> myVecPlayers;
    
    //We ask for the number of players
    
    std::cout << "Enter the number of players(Max 2): ";
    std::cin >> numberPlayers;
    
    //Here we see if the value is valid, we could have made a mistake 
    
    while(numberPlayers < 2 || numberPlayers > 2)
    {
        std::cout << " Enter a valid input" << std::endl;
        std::cin >> numberPlayers;
    }
    
    std::cout << "Enter the name of the players separated by a comma: ";
    std::cin >> line;
    
    
    std::stringstream s(line);
    
    // here we stream the string where we entered the names
    
    while (s.good())
        {
          std::string subtr;
          std::getline(s, subtr, ',');
          if (subtr.find_first_not_of(' ') != std::string::npos) //Here I checked if the name is composed just of spaces.
            PlayerNames.push_back(subtr);
        }
    
    // In this part we do a loop if the number of names doesn't match with the 
    //number of players that we assigned before is gonna infinitely loop
    
    while (PlayerNames.size() != numberPlayers)
    {
        PlayerNames.clear();
        line.clear();
        std::cout << "Wrong!\nEnter the correct number of name of the players separated by a comma: (Enter slow)";
        std::cin >> line;
        std::stringstream s(line);
        while (s.good())
            {
                std::string subtr;
                std::getline(s, subtr, ',');
                if (subtr.find_first_not_of(' ') != std::string::npos) //Here I checked if the name is composed just of spaces.
                    PlayerNames.push_back(subtr);
            }
     }
    
    //Here I'm gonna create the objects for each player
    
    for(auto i : PlayerNames)
    {
        myVecPlayers.push_back(Player {i});
    }
    
    //This is the first part where we review the rules of the game.
    
    clean();
    std::cout << "Let review the rules! "  << std::endl;
    std::cout << " There are a lot of words to guess, who fails to find the word\n "
                << "loses, the one who survive, wins! \n" 
                << "Are you ready? " << std::endl;
                keyToC();
                clean();
                
    // This is the second part where we decide who is going first!
    
    std::cout << "Let see who is going first!\n"
              << "We are gonna give assign you a random number to decide who is going first!\n"
              << "We are gonna use fibonnaci using a random value!\n";
    
    
    // in this segment we stablish who is going first.
    
    std::queue<std::string> positions = getPlace(myVecPlayers);
    clean();
    std::cout << "The order is: \n";
    
    //we print out the positions here
    
    for(size_t i{}; i < positions.size(); i++)
    {
        std::cout << i+1 <<"- " << positions.front() << std::endl;
        fixQ(positions);
    }
    keyToC();
    
    //in this segment we get the map from an outside text where the words are 
    //placed
    
    auto mapWords = makeMap();
    
    bool gameOver;
    
    // we create the loop of our game
    
    while(!gameOver)
    {
        // we establish the amount of mistakes that we can do.
        
        int MaxwrongOptions{6};
        int PlayerIdx;
        int totalCountWords{};
        
        //we get the player first placed in the queue.
        
        for(auto i : myVecPlayers)
        {
            
            if(i.returnName() == positions.front())
            {
                break;
            }
            PlayerIdx++;
            
        }
        Player& temp = myVecPlayers[PlayerIdx];
        
        // this is where we have the words hidden, where we have the found words
        
        std::vector<char> wordHid;
        for(auto i : mapWords.front())
        {
            wordHid.push_back('_');
        }
        
        // we keep track of the words used
        
        std::vector<char> wordsUse;
        
        //to store the losers
        
        std::stack<std::string> losers;
        
        //This is the main loop
        
        while(MaxwrongOptions != temp.returnWrongChoices())
        {
            
            std::cin.clear();
            bool wordIsUse{};
            clean();
            
            //we let them know whos turn is 
            
            std::cout << "The turn of: " << positions.front() << '\n';
            std::string select;
            makeHang(temp.returnWrongChoices());

            std::cout << '\n' <<  std::setw(35) << std::setfill(' ');
            
            // here we print the word or just _ _ _ _ _ 
            
            for(auto i : wordHid)
            {
                std:: cout << i << " ";
            }
            
            std::cout << '\n';
            
            // Here is where i print all the words that u already used, so you 
            //don't make mistakes
            
            std::cout << "Letters already use: ";
            
            //Here is where I use bubblesort to sort the letters to make them 
            //look better 
            
            if(wordsUse.size()>1)
            {
                bubbleSort(wordsUse,wordsUse.size());
            }
            
            
            //I print each time the words that I used, so you can have a record
            //To avoid using the same word again and again
            
            for(auto i : wordsUse)
            {
                if(i == wordsUse.back())
                {
                    std::cout << i; 
                }
                else
                {
                    std::cout << i << ", ";
                }
            }
            std::cout << '\n';
            std::cout << "Try a letter : ";
            std::cin >> select;
                
            // Here we use it if they use the same letter, we will make them, type a new
            //letter
            
            
            
            if(wordsUse.size() != 0)
            {
                auto wordIs = std::count(wordHid.begin(), wordHid.end(), select.front()); 
                if(wordIs == 0)
                {
                    wordIsUse = false;
                }
                else
                    wordIsUse = true;
            }
            
            // Here is where we perfom it
            
            while(wordIsUse)
            {
                std::cout << "Try a letter : ";
                std::cin >> select;
                
                auto wordIs = std::count(wordHid.begin(), wordHid.end(), select.front()); 
                if(wordIs == 0)
                {
                    wordIsUse = false;
                }
                else
                    wordIsUse = true;
            }
            
            //Here we count the number of words with the same letter in the string
            
            auto count = std::count(mapWords.front().begin(),mapWords.front().end(), select.front());
            
            // if there are not words just add a new wrong choices
            if(count == 0)
            {
                temp.aumentWrongChoises();
                wordsUse.push_back(select.front());
            }
            else
            {
                // here we push the word and we add them to the number of total words
                // why total words? because we need to keep track when fully find out the 
                //word 
                
                wordsUse.push_back(select.front());
                totalCountWords+=count;
                for(size_t i{}; i < mapWords.front().size(); i++)
                {
                    if(select.front() == mapWords.front()[i])
                    {
                        wordHid[i] =  select.front();
                    }
                }
         
            }
            
            // this is where we are ready to switch user, and let the next player play
            if(totalCountWords == mapWords.front().size())
            {
                temp.aumentCorrectWords();
                temp.setWrongChoisesZero();
                break;               
            }        
            
        }
        
        // here we take out the player who gets hanged
        
        if(MaxwrongOptions == temp.returnWrongChoices())
        {
            losers.push(positions.front());
            positions.pop();
            temp.meOut();
        }
        
        //here we pop the word and we keep moving
        
        mapWords.pop();
        
        //What happen if the are not more words, there ford we are gonna get the
        //max number of words, it selects the player with more correct words.
        
        if(mapWords.empty())
        {
            std::map<int, std::string> vDice;
            for (auto i : myVecPlayers)
            {               
                vDice[i.returnCorrect()] = i.returnName();
            }
            
            //Im using a set here
            
            std::set<std::pair<int, std::string>, std::greater<std::pair<int, std::string>>> set(vDice.begin(), vDice.end());
            
            // we print the number of correct answers
             
            std::cout << "We run out of words!, the results are: \n";
            for (auto const &pair : set)
            {
              std::cout << pair.second << " got the # correct answers: " << pair.first << std::endl;    
            }
            keyToC();
        }
        
        
        
        // what happen if everyone is out and just one player is left
        //here we implement the winner of the game
        
        if(positions.size() == 1)
        {
            clean();
            int winnerId{};
            for(auto i : myVecPlayers)
            {
                if(i.returnName() == positions.front())
                {
                   break;
                }
            winnerId++;
            }
            
            //We stablish the winner here, depending who is left in the queue
            std::cout << "The winner is: " << positions.front();
            std::cout << " Congratulations, your score was: " << myVecPlayers[winnerId].returnCorrect() << '\n';
            
           //tree that I use to store the players.
    
     node *root = newNode(positions.front());
            while(!losers.empty())
            {
                if(losers.size() % 2 == 0)
                {
                    if(losers.size() % 2 == 0)
                    {
                        root->left = newNode(losers.top());
                    }
                    else
                        root->right = newNode(losers.top());
                    losers.pop();
                }
                else
                    if(losers.size() % 2 == 0)
                    {
                        root->right = newNode(losers.top());         
                    }
                    else
                        root->left = newNode(losers.top());
                    losers.pop();
            }
     
            std::cout << "Players: ";
            prntLev(root);
            std::cout << '\n';
            keyToC();
            break;
        }
        else
        {
            
            if(temp.returnWrongChoices() != MaxwrongOptions)
            {
                fixQ(positions); 
            }       
        }
        
    }
    
            
}

//This function is used to create the hanged man, body depends of the
//Wrong choices that he has already made.

void makeHang(const int& body)
{
    std::cout << std::setw(50) << std::setfill(' ') << "+---+" << '\n';
    std::cout << std::setw(50) << std::setfill(' ') << "|   |" << '\n';
    
    // in this part depending of how many wrong choices, the figure is gonna be 
    // different, I used a switch to easily change between them
    
    if (body >=1)
    {
        // This is all the process 
        
        switch (body)
        {
            case 1: {
                
                std::cout << std::setw(50) << std::setfill(' ') << "O   |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(53) << std::setfill(' ') << "============" << '\n';
                
                break;
                }
            case 2:{
                
                std::cout << std::setw(50) << std::setfill(' ') << "O   |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "|   |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(53) << std::setfill(' ') << "============" << '\n';
                
                break;
                }
            case 3:{
                
                std::cout << std::setw(50) << std::setfill(' ') << "O   |" << '\n';
                std::cout << std::setw(46) << std::setfill(' ') << "/|" << ' ' << "  |" <<  '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(53) << std::setfill(' ') << "============" << '\n';
                
                break;
                }
            case 4:{
                
                std::cout << std::setw(50) << std::setfill(' ') << "O   |" << '\n';
                std::cout << std::setw(46) << std::setfill(' ') << "/|" << '\\' << "  |" <<  '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(53) << std::setfill(' ') << "============" << '\n';
                
                break;
                }
            case 5:{
                
                std::cout << std::setw(50) << std::setfill(' ') << "O   |" << '\n';
                std::cout << std::setw(46) << std::setfill(' ') << "/|" << '\\' << "  |" <<  '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "/    |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(53) << std::setfill(' ') << "============" << '\n';
                
                break;
                }
            case 6:{
                
                std::cout << std::setw(50) << std::setfill(' ') << "O   |" << '\n';
                std::cout << std::setw(46) << std::setfill(' ') << "/|" << '\\' << "  |" <<  '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "/ \\  |" << '\n';
                std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
                std::cout << std::setw(53) << std::setfill(' ') << "============" << '\n';
                
                break;
                }
        }  
    }
    else
    {
        // here if it is zero 
        
        std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
        std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
        std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
        std::cout << std::setw(50) << std::setfill(' ') << "    |" << '\n';
        std::cout << std::setw(53) << std::setfill(' ') << "============" << '\n';
    }
    
    
    
}

//This functions is used for different parts of the game to stop and let the user
//read, and press to continue. 

void keyToC()
{
  std::cout << "Press any key to continue" << '\n';
  std::cin.ignore();
  std::cin.get();
}

//This function is used to fix the queue, who is going first, last

void fixQ(std::queue<std::string> &pos)
{
  auto first = pos.front();
  pos.pop();
  pos.push(first);
}

// This is the function use to assign a place to each player, who is going first
// and giving them a value.

std::queue<std::string> getPlace(const std::vector<Player> &o)
{
  std::queue<std::string> position;
  std::map<int, std::string> vDice;

  //here is where i create the random number.
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dist(0,30);
  
  //Here we will create the fibonnaci of the random number. 
  
  for (auto i : o)
  {
    int di{dist(mt)};
    vDice[fib(di)] = i.returnName();
  }
  //Im using a set here
  std::set<std::pair<int, std::string>, std::greater<std::pair<int, std::string>>> set(vDice.begin(), vDice.end());

  //I print each value for the players
  for (auto const &pair : set)
  {
    std::cout << pair.second << " got the value: " << pair.first << std::endl;
    position.push(pair.second);
  }
  keyToC();
  return position;
}

// this is the function that I use to create the map of the game, in this case the
// words in an array so I have them in a queue. 

std::queue<std::string> makeMap()
{
    
    // I get all the words from an external file called: xText.txt
    
    std::ifstream in("xText.txt");
    std::queue<std::string> objects;
    for (std::string line; std::getline(in, line);)
    {
        std::stringstream s(line);
        for (std::string temp; std::getline(s, temp, ',');)
        {
            objects.push(temp);
        }
    }
    
    return objects;
}

// This function we will use a recursive function to get the value.

int fib(int n)
{
    if (n <= 1)
        return n;
    
    // here we use recursion
    
    return fib(n-1) + fib(n-2);
}

//This the recursion sort used to order the characters that I used, so people can

void bubbleSort(std::vector<char>& arr, int n)
{
    // Base case
    if (n == 1)
        return;
  
    // One pass of bubble sort. After
    // this pass, the largest element
    // is moved (or bubbled) to end.
    for (int i=0; i<n-1; i++)
        if (arr[i] > arr[i+1])
            std::swap(arr[i], arr[i+1]);
  
    // Largest element is fixed,
    // recur for remaining array
    bubbleSort(arr, n-1);
}

node* newNode(std::string data){
     node *n;
     n=new node;
     n->data = data;
     n->left = NULL;
     n->right = NULL;
     return n;
}

void prntLev(node* root){  
    int h = height(root);
    for (int i=1;i<=h;i++)prntLev(root, i);  
}  

int height(node* node){  
    if (node == NULL)return 0; 
    //compute the height of each subtree
    int lheight = height(node->left);
    int rheight = height(node->right);
    //use the larger one
    if (lheight > rheight)return(lheight + 1);  
    else return(rheight + 1);
}
void prntLev(node* root, int level){  
    if (root == NULL)return;  
    if (level == 1)  
        std::cout << root->data << " ";  
    else if (level > 1){  
        prntLev(root->left, level-1);  
        prntLev(root->right, level-1);  
    }  
}  
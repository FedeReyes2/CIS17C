

/* 
 * File:   Player.hxx
 * Author: federico
 *
 
 * This is gonna be a class for player, that will include how many right answers
 * how many wrong answers, and if he is out. 
 */

#ifndef PLAYER_HXX
#define PLAYER_HXX

#include <string>

//This is the player class.
class Player
{
public:  
    //Constructor
    Player(const std::string& name) : myName{name} {}
    
    // this functions are use to change my variables
    void aumentCorrectWords(){correctWords++;}
    void aumentWrongChoises(){wrongChoices++;}
    void setWrongChoisesZero(){wrongChoices = 0;}
    void meOut(){iAmOut = true;}
    
    //Return functions
    std::string returnName(){return myName;}
    unsigned int returnCorrect(){return correctWords;}
    unsigned int returnWrongChoices(){return wrongChoices;}
    bool returnAmIO(){return iAmOut;}
    
private:  
    //This are all my variables
    std::string myName;
    unsigned int correctWords{};
    unsigned int wrongChoices{};
    bool iAmOut{};
};


#endif /* PLAYER_HXX */


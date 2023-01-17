#include <vector>
#include <iostream>

class Character{
    public:
        std::string name;
        int health,dmg;
        std::vector <std::string> voice_lines;
        Character(std::string,int,int,std::vector<std::string>);
        ~Character();
        void receiveDamage(int);
        void punch(Character &);
        void yell();

};
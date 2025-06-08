
#include "Pirate.h"



Pirate::Pirate(const string& name, DEVIL_FRUIT devilFruit, int bounty): name(name), devilFruit(devilFruit), bounty(bounty){}


void Pirate::setName(const string& name){
    this->name = name;
}


void Pirate::setDevilFruit(DEVIL_FRUIT devilFruit){
    this->devilFruit = devilFruit;
}


std::string Pirate::getName(){
    return name;
}


DEVIL_FRUIT Pirate::getDevilFruit(){
    return devilFruit;
}


const char* const devilFruitNames[] = {
    "Gum Gum",
    "Smoke Smoke",
    "Flame Flame",
    "Rumble Rumble",
    "String String",
    "Ice Ice",
    "None"
};

std::ostream &operator<<(std::ostream &os, const Pirate &pirate){
    os << pirate.name << " Bounty: " << pirate.bounty << " (Devil Fruit: " << devilFruitNames[pirate.devilFruit] << ")";
    return os;
}

void Pirate::setBounty(const int& bounty){
    this->bounty = bounty;
}


int Pirate::getBounty(void) const {
    return this->bounty;
}


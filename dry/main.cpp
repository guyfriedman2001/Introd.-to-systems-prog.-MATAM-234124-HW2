#include <iostream>
#include "Pirate.h"
#include <cstring>

using std::cout;
using std::endl;

int main() {

    Pirate luffy("Luffy");
    Pirate zoro("Zoro");

    const int crewSize = 2;
    
    Pirate* strawHatCrew[2];
    strawHatCrew[0] = &luffy;
    strawHatCrew[1] = &zoro;

    luffy.setBounty(1000000);
    zoro.setBounty(500000);
    
    cout << "Straw Hat crew contains:" << endl;
    for (int i = 0; i < crewSize; i++) {
        cout << *strawHatCrew[i] << endl;
    }

    return 0;
}

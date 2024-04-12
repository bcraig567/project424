#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <thread>
#include <mutex>
#include "Characters.h" // This includes the Character class and all derived classes.
#include "Monster.h"    // This includes the Monster class definition.

enum class EncounterType {
    Exploration,
    Combat
};

class Encounter {
public:
    virtual void Run(Character& player) = 0;
    virtual ~Encounter() {}
};

class ExplorationEncounterOne : public Encounter {
private:
    bool redKeyFound = false;
    bool blueKeyFound = false;
    bool doorKeyFound = false;
    bool puzzleSolved = false;
    bool mirrorExamined = false;
    bool mirrorFlipped = false;
    bool windowExamined = false;
    bool closetExamined = false;
    bool closetOpened = false;
    bool doorOpened = false;
    bool bedExamined = false;
    bool redCaseOpened = false;
    bool blueCaseOpened = false;
    bool caseExamined = false;
    // Additional puzzle states and variables as needed

public:
    void Run(Character& player) override {
        // Puzzle introduction and initial state setup
        std::cout << "\n\nDarkness. You awaken and you see nothing but darkness.\nYour arms ache in pain as you rise from the poorly\nmade bed, allowing for your eyes to adjust to the\ndarkness of the room.\n" << std::endl;
        std::cout << "TUTORIAL:\n You will be playing through this text RPG\nthrough several commands. Whenever a word is written\nlike **THIS**, it means you can type that word (all lowercase) to\nlook into it further. If you want to interact with the\nitem, type 'examine _____' to see what you can do!\nYou can only examine things which you've already\nlooked into using the word itself. For now, try using the\n**look** command!" << std::endl;
        while (!puzzleSolved) {
            std::string choice;
            std::cout << "**What do you want to do?**\n" << std::endl;
            std::getline(std::cin, choice);

            if (choice == "door") { // Door inspection logic
                if (doorKeyFound) {
                    std::cout << "Using the **BLACK KEY**, you unlock the door, revealing a new path.\n" << std::endl;
                    puzzleSolved = true; // This could also trigger the transition to a new game state or area
                }
                else {
                    std::cout << "You approach the door. The door is firmly\nlocked. There must be a key somewhere.\n" << std::endl;
                }
            }
            else if (choice == "admin")
                break;
            else if (choice == "look") {
                std::cout << "You glance around the room. A singular\n**WINDOW** illuminates the room with the faint light of the moon,\nand a **DOOR** stands across from it.\nYou see a small circular **MIRROR** hanging on the wall, with\na small **CLOSET** standing next to it. The **BED**\nyou were sleeping on appears to have been used for some\ntime, and is made of hay and linen.\n" << std::endl; 
            }
            else if (choice == "mirror") { // examines the mirror so it can be flipped
                std::cout << "You look into the mirror, darkness stares back\nat you. While you can't see yourself, you notice\nthe mirror is **flimsily hung**.\n" << std::endl;
                mirrorExamined = true;
            }
            else if (choice == "closet") {
                std::cout << "As you approach the closet, you notice its\nfine craftmanship. The closet is made out of a deep mahogany wood.\n" << std::endl;
                closetExamined = true;
            }
            else if (choice == "examine closet") {// examines the closet so it can be opened
                if (closetExamined && !closetOpened) {
                    std::cout << "You open the closet and find no clothing.\nHowever, you do see a small **BLUE KEY**\nsitting on one of the shelves. You pick\nup the **BLUE KEY**.\n" << std::endl;
                    blueKeyFound = true;
                    closetOpened = true;
                }
                else if (closetOpened) {
                    std::cout << "You've already got the **BLUE KEY**, let's move on.\n" << std::endl;
                }
                else {
                    std::cout << "You can't do this now.\n" << std::endl;
                }
            }
            else if (choice == "bed") {
                std::cout << "You look at the small bed you awoke on.\nIt's made of hay with a thin piece\nof white linen over it.\n" << std::endl;
                bedExamined = true;
            }
            else if (choice == "examine bed") { // allows for the briefcase to be examined for the final key
                if (bedExamined) {
                    std::cout << "You look under the bed. You see a small\n**BRIEFCASE** and pull it out.\n" << std::endl;
                    caseExamined = true;
                }
                else {
                    std::cout << "You can't do this now.\n" << std::endl;
                }
            }
            else if (choice == "examine mirror") { // flips the mirror and says the red key is found
                if (mirrorExamined && !mirrorFlipped) {
                    std::cout << "You carefully remove the mirror from its flimsy\nhook and see a **RED KEY**.\n You carefully remove the key from the back\nand put the mirror back up.\n" << std::endl;
                    redKeyFound = true;
                    mirrorFlipped = true;
                }
                else if (mirrorFlipped) {
                    std::cout << "You've already got the **RED KEY**, let's move on.\n" << std::endl;
                }
                else {
                    std::cout << "You can't do this now.\n" << std::endl;
                }
            }
            else if (choice == "briefcase") {// several cases based on whether you have one key, none, or both.
                if (caseExamined && redKeyFound && blueKeyFound) {
                    std::cout << "You look at the briefcase. There are\ntwo keyholes, one blue and one red.\nYou put the **RED KEY** and the **BLUE KEY**\ninto their respective sockets.\nThe briefcase opens up, revealing a **BLACK KEY**.\nYou pick up the **BLACK KEY**, knowing it\nmust be for the door.\n" << std::endl;
                    doorKeyFound = true;
                }
                else if (caseExamined && !redKeyFound && blueKeyFound) {
                    std::cout << "You look at the briefcase. There are\ntwo keyholes, one blue and one red.\nYou put the **BLUE KEY**\ninto its respective socket.\nThe briefcase does not open. It looks like\nyou'll need to find something else to open it...\n" << std::endl;
                }
                else if (caseExamined && redKeyFound && !blueKeyFound) {
                    std::cout << "You look at the briefcase. There are\ntwo keyholes, one blue and one red.\nYou put the **RED KEY**\ninto its respective socket.\nThe briefcase does not open. It looks like\nyou'll need to find something else to open it...\n" << std::endl;
                }
                else if (caseExamined && !redKeyFound && !blueKeyFound) {
                    std::cout << "You look at the briefcase. There are\ntwo keyholes, one blue and one red.\nIt looks like you'll need to find something to open it...\n" << std::endl;
                }
                else if (doorKeyFound) {
                    std::cout << "You've already got the **BLACK KEY**, let's move on.\n" << std::endl;
                }
                else {
                    std::cout << "You can't do this now.\n" << std::endl;
                }
            }
            else if (choice == "window") {
                std::cout << "You look out the window. It's a calm night, and\nthe window overlooks the ocean, which\nstretches for as far as the eye can see.\n" << std::endl;
            }       
         }
        std::cout << "You open the door, revealing a long hallway." << std::endl;
        // Additional logic to transition to the next part of the game after the puzzle is solved
    }
};

class MysteriousLibraryEncounter : public Encounter {
private:
    bool mapFound = false;
    bool secretPassageOpened = false;
    bool enchantmentBroken = false;

public:
    void Run(Character& player) override {
        std::cout << "\nYou enter a dusty library filled with ancient tomes. Some books float eerily above the shelves.\n";

        while (!enchantmentBroken) {
            std::cout << "\n**LOOK** around to find your way or **READ** a book that catches your eye.\n";
            std::string action;
            std::getline(std::cin, action);

            if (action == "look") {
                if (!mapFound) {
                    std::cout << "Among the books, you find a curious map detailing the library's layout with a hidden room marked.\n";
                    mapFound = true;
                }
                else {
                    std::cout << "The map reveals a switch hidden in a bookshelf that might open a secret passage.\n";
                }
            }
            else if (action == "read" && mapFound) {
                std::cout << "You pull a book titled 'The Enchanter's End' from the shelf, and the room begins to shift. A passage opens!\n";
                secretPassageOpened = true;
            }
            else if (action == "enter passage" && secretPassageOpened) {
                std::cout << "You enter the passage and find a room with a crystal emitting a strange light, binding the library under a spell.\n";
                std::cout << "**BREAK** the crystal to lift the enchantment.\n";
            }
            else if (action == "break" && secretPassageOpened) {
                std::cout << "You shatter the crystal. The floating books gently fall to the ground, and the library's magic is undone.\n";
                enchantmentBroken = true;
            }
            else {
                std::cout << "That action doesn't seem to have an effect right now.\n";
            }
        }

        std::cout << "With the enchantment broken, you find the exit to the library and continue on your quest.\n";
    }
};


class CombatEncounter : public Encounter {
public:
    // Constructor that initializes the monsters vector
    CombatEncounter(std::vector<std::unique_ptr<Monster>> monsters)
        : monsters(std::move(monsters)) {}

    void Run(Character& player) override {
        std::cout << "\nMonsters attack!" << std::endl;
        while (!player.IsDefeated() && !AllMonstersDefeated()) {
            PlayerTurn(player);
            if (!AllMonstersDefeated()) {
                std::cout << "\n\nMonsters turn!" << std::endl;
            }
            for (auto& monster : monsters) {
                if (!monster->IsDefeated()) {
                    MonsterTurn(player, *monster);
                }
            }

            RemoveDefeatedMonsters();  // Clean up any defeated monsters after the turn ends

         }
    }
    void PlayerTurn(Character& player) {
        std::cout << "\nYour turn! \nChoose an action: \n1.Attack\n2.Special Action\n\nEnter your action:";
        std::string input;
        std::cin >> input;

        if (input == "1") {
            player.Attack(monsters);
        }
        else if (input == "2") {
            player.SpecialAction(monsters);
        }
    }
    bool AllMonstersDefeated() {
        for (const auto& monster : monsters) {
            if (!monster->IsDefeated()) {
                return false; // If any monster is not defeated, return false immediately.
            }
        }
        return true; // If the loop completes without returning false, all monsters are defeated.
    }

    void RemoveDefeatedMonsters() {
        monsters.erase(
            std::remove_if(
                monsters.begin(),
                monsters.end(),
                [](const std::unique_ptr<Monster>& m) { return m->IsDefeated(); }
            ),
            monsters.end()
        );
    }
private:
    std::vector<std::unique_ptr<Monster>> monsters;

    void MonsterTurn(Character& target, Monster& monster) {
        monster.Attack(target);
    }
};


void GameLoop() {
    std::cout << "Welcome to the Dungeon!\n\nWho are you? \nEnter your name: ";
    std::string name; 
    std::cin >> name;

    std::cout << "\nWhat class do you wish to play?\n1. Fighter\n2. Mage\n3. Thief\n4. Cleric\n\n Enter class selection:";
    int playerClass; 
    std::cin >> playerClass;
    while (!(std::cin >> playerClass) || playerClass < 1 || playerClass > 4) {
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore wrong input
        std::cout << "Invalid. Choose again.\nEnter your class: ";
    }

    std::unique_ptr<Character> player; // Pointer to the base class

    if (playerClass == 1) {
        player = std::make_unique<Fighter>(name);
    }
    else if (playerClass == 2) {
        player = std::make_unique<Mage>(name);
    }
    else if (playerClass == 3) {
        player = std::make_unique<Thief>(name);
    }
    else if (playerClass == 4) {
        player = std::make_unique<Cleric>(name);
    }
    std::vector<std::unique_ptr<Encounter>> encounters;
    std::vector<std::unique_ptr<Monster>> monsters;

    monsters.push_back(std::make_unique<Monster>("Goblin1", "Humanoid", 1, 5, 10));
    
    encounters.push_back(std::make_unique<ExplorationEncounterOne>());
    encounters.push_back(std::make_unique<ExplorationEncounterOne>());

    // Pass the vector of monsters to the CombatEncounter
    encounters.push_back(std::make_unique<CombatEncounter>(std::move(monsters)));

    for (auto& encounter : encounters) {
        encounter->Run(*player);
        // Check if player wants to quit after each encounter
        std::cout << "Continue exploring? (y/n): ";
        char input;
        std::cin >> input;
        if (input == 'n') {
            std::cout << "You lie back down on the bed and crawl into a corner.\nYou accept your fate here and die of starvation.\nGame over!" << std::endl;
            break;
        }
    }
}

    int main() {
        GameLoop();
        return 0;
    };
#include "Characters.h"
#include <random>
#include <vector>
#include <string>

// Base Character class implementations
Character::Character(const std::string& name, int health, int AC, int damageDie, int damageBonus)
    : name(name), health(health), AC(AC), damageDie(damageDie), damageBonus(damageBonus), invisible(false) {}

void Character::DisplayTargets(const std::vector<std::unique_ptr<Monster>>& monsters) const {
    std::cout << "\nAvailable targets:\n";
    for (size_t i = 0; i < monsters.size(); ++i) {
        if (!monsters[i]->IsDefeated()) {
            std::cout << i + 1 << ": " << monsters[i]->getName() << "\n";
        }
    }
}
bool Character::AllMonstersDefeated(const std::vector<std::unique_ptr<Monster>>& monsters) {
    for (const auto& monster : monsters) {
        if (!monster->IsDefeated()) {
            return false; // If any monster is not defeated, return false immediately.
        }
    }
    return true; // If the loop completes without returning false, all monsters are defeated.
}

int Character::ChooseTarget(const std::vector<std::unique_ptr<Monster>>& monsters) const {
    int chosenIndex = 0;
    while (true) {
        std::cout << "\nEnter your target: ";
        std::cin >> chosenIndex;
        if (std::cin.fail() || chosenIndex < 1 || chosenIndex > monsters.size() || monsters[chosenIndex - 1]->IsDefeated()) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    return chosenIndex - 1; // Convert to 0-based index
}

int Character::RollDie(int sides) {
    return rand() % sides + 1;
}

int Character::getAC() const {
    return AC;
}

void Character::Attack(std::vector<std::unique_ptr<Monster>>& monsters) {
    DisplayTargets(monsters);
    int targetIndex = ChooseTarget(monsters);
    int AttackRoll = RollDie(20);
    if (AttackRoll >= monsters[targetIndex]->getAC()) {
        std::cout << "You roll a " << AttackRoll << " and hit " << monsters[targetIndex]->getName() << "!" << std::endl;
        int damage = RollDie(damageDie) + damageBonus;
        monsters[targetIndex]->TakeDamage(damage);
    }
    else {
        std::cout << "You roll a " << AttackRoll << " and miss " << monsters[targetIndex]->getName() << "!" << std::endl;
    }
}

void Character::TakeDamage(int damage) {
    std::cout << name << " takes " << damage << " points of damage." << std::endl;
    health -= damage;
}

std::string Character::getName() const {
    return name;
}

bool Character::IsDefeated() const {
    return  health  <= 0;
}

bool Character::IsInvisible() {
    return invisible;
}

void Character::BecomeInvisible() {
    invisible = true;
}

void Character::BecomeVisible() {
    invisible = false;
}

// Fighter implementations
Fighter::Fighter(const std::string& name) : Character(name, 120, 15, 12, 4) {}
void Fighter::SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters) {
    std::cout << "Choose your special action:\n1. Multiattack\n2. Break Armor\n\nEnter your Special Action:";
    int choice;
    std::cin >> choice;
    int targetIndex; // Declare targetIndex once, before the switch statement
    switch (choice) {
    case 1: // Multiattack

        Attack(monsters); // First attack
        if (monsters.size() > 0) {
            Attack(monsters); // Second attack
        }
        break;  // Make sure to add break after the attack to prevent fall-through

    case 2: // Break Armor
        DisplayTargets(monsters);  // Show the list of targets
        targetIndex = ChooseTarget(monsters);  // Let the player choose the target
        std::cout << "Break Armor! " << name << " attempts to lower " << monsters[targetIndex]->getName() << "'s AC!\n";
        monsters[targetIndex]->changeAC(-2); // Lower the monster's AC by 2
        break;
    default:
        std::cout << "Invalid action. Lost your turn!\n";
        break;
    }
}

// Mage implementations
Mage::Mage(const std::string& name) : Character(name, 80, 11, 4, 1) {}
void Mage::SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters) {
    std::cout << "Choose your special action:\n1. Firebolt\n2. Magic Missile\n3. Invisibility\n\nEnter your Special Action:";
    int choice;
    std::cin >> choice;

    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));
    
    switch (choice) {
    case 1: { // Firebolt
        std::cout << "Casting Firebolt!" << std::endl;
        DisplayTargets(monsters);
        int targetIndex = ChooseTarget(monsters);
        if (RollDie(20) >= monsters[targetIndex]->getAC()) {
            int damage = RollDie(12) + 2;
            std::cout << "Hit! You dealt " << damage << " damage to the target." << std::endl;
            monsters[targetIndex]->TakeDamage(damage);
        }
        else {
            std::cout << "Missed!" << std::endl;
        }
        break;
    }
    case 2: { // Magic Missile
        std::cout << "Casting Magic Missile!" << std::endl;
        for (int i = 0; i < 3; ++i) {
            if (!AllMonstersDefeated(monsters)) {
                DisplayTargets(monsters);
                int targetIndex = ChooseTarget(monsters);
                int damage = RollDie(4) + 1;
                std::cout << "Magic missile hits the target for " << damage << " damage!" << std::endl;
                monsters[targetIndex]->TakeDamage(damage);
            }
        }

        break;
    }
    case 3: {
        std::cout << "Casting Invisibility! You vanish from sight!" << std::endl;
        BecomeInvisible();
        break;
    }
    default:
        std::cout << "Invalid action. Lost your turn!\n";
        break;
    }
}

// Thief implementations
Thief::Thief(const std::string& name) : Character(name, 100, 13, 6, 2) {}
void Thief::SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters) {
    std::cout << "Choose your special action:\n1. Hide\n2. Sneak Attack\n\nEnter your Special Action:";
    int choice;
    std::cin >> choice;

    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    switch (choice) {
    case 1: // Hide
        std::cout << "You hide in the shadows, becoming invisible to your enemies.\n";
        BecomeInvisible();
        break;
    case 2: // Sneak Attack
        if (invisible) {
            std::cout << "Sneak Attack! While invisible, you attack with surprise!\n";
            DisplayTargets(monsters);
            int targetIndex = ChooseTarget(monsters);
            int damage = RollDie(6) + RollDie(6) + RollDie(6) + 3;
            std::cout << "You dealt " << damage << " damage to " << monsters[targetIndex]->getName() << " and reappear!.\n";
            monsters[targetIndex]->TakeDamage(damage);
            BecomeVisible(); // The thief becomes visible after attacking
        }
        else {
            std::cout << "You need to be hidden to use Sneak Attack!\n";
        }
        break;
    default:
        std::cout << "Invalid action. Lost your turn!\n";
        break;
    }
}

// Cleric implementations
Cleric::Cleric(const std::string& name) : Character(name, 100, 13, 8, 2) {}
void Cleric::SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters) {
    std::cout << "Choose your special action:\n1. Heal\n2. Smite\n3. Turn Undead\n\nEnter your Special Action:";
    int choice;
    std::cin >> choice;

    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    switch (choice) {
    case 1: {// Heal
        int addedHealth = RollDie(8) + RollDie(8) + 3;
        std::cout << "You heal yourself for " << addedHealth << " HP!";
        health += addedHealth;
        break;
    }
    case 2: {//Smite
        std::cout << "You emblazen your mace with Divine power!\n";
        DisplayTargets(monsters);
        int targetIndex = ChooseTarget(monsters);
        int damage = RollDie(6) + RollDie(6) + RollDie(6) + 3;
        std::cout << "You dealt " << damage << " damage to " << monsters[targetIndex]->getName() << " and reappear!.\n";
        monsters[targetIndex]->TakeDamage(damage);
        break;
    }
    case 3: {//Smite
        std::cout << "You channel the divine power of your god, unleashing a blast of holy energy!\n";
        for (auto& monster : monsters) {
            if (monster->getCreatureType() == "Undead") {
                std::cout << monster->getName() << " takes " << monster->getHealth() << " damage and explodes!" << std::endl;
                monster->TakeDamage(monster->getHealth());
            }
            else {
                std::cout << monster->getName() << " is not undead, it is unaffected." << std::endl;
            }
        }
        break;
    }
    default: {
        std::cout << "Invalid action. Lost your turn!\n";
        break;
    }
    }
}


#include "Monster.h"
#include "Characters.h" // Include the Character class definition.
#include <random>

Monster::Monster(const std::string& name, const std::string& creatureType, int health, int damage, int AC)
    : name(name), health(health), attackDamage(damage), AC(AC), creatureType(creatureType) {}

int Monster::RollDie(int sides) {
    return rand() % sides + 1;
}

void Monster::TakeDamage(int damage) {
    health -= damage;
    std::cout << name << " takes " << damage << " points of damage." << std::endl;
    if (health <= 0) {
        std::cout << name << " has been defeated." << std::endl;
    }
}

void Monster::Attack(Character& target) {
    if (!target.IsInvisible()) {
        int attackRoll = RollDie(20);
        if (attackRoll >= target.getAC()) {
            std::cout << name << " rolls a " << attackRoll << " and hits " << target.getName() << "!" << std::endl;
            target.TakeDamage(attackDamage);
        }
        else {
            std::cout << name << " rolls a " << attackRoll << " and misses " << target.getName() << "." << std::endl;
        }
    }
    else {
        std::cout << name << " cannot see " << target.getName() << "! Their attack misses!" << std::endl;
    }
}


void Monster::changeAC(int change) {
    AC -= change;
    if (AC < 0) {  // Ensure AC does not go below 0
        AC = 0;
    }
    std::cout << name << "'s armor class has been changed to " << AC << std::endl;
}


bool Monster::IsDefeated() const {
    return health <= 0;
}

std::string Monster::getName() const {
    return name;
}

int Monster::getHealth() const {
    return health;
}

int Monster::getAC() const {
    return AC;
}

int Monster::getAttackDamage() const {
    return attackDamage;
}

std::string Monster::getCreatureType() const {
    return creatureType;
}

Undead::Undead(const std::string& name) : Monster(name, "Undead", 20, 5, 8) {}

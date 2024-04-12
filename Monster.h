// Monster.h
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>
// Forward declaration of Character to avoid circular dependency.
class Character;

class Monster {
public:
    Monster(const std::string& name, const std::string& creatureType, int health, int damage, int AC);

    void TakeDamage(int damage);
    virtual void Attack(Character& target);
    void changeAC(int newAC);
    bool IsDefeated() const;

    std::string getName() const;
    int getHealth() const;
    int getAttackDamage() const;
    int getAC() const;
    std::string getCreatureType() const;
    int RollDie(int sides);

protected:
    std::string name;
    int health;
    int attackDamage;
    int AC;
    std::string creatureType;
};

class Undead : public Monster {
public:
    Undead(const std::string& name);
};

#endif // MONSTER_H

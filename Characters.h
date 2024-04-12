// Characters.h
#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "Monster.h"
#include <string>
#include <vector>

class Character {
public:
    Character(const std::string& name, int health, int AC, int damageDie, int damageBonus);
    virtual ~Character() = default;

    void Attack(std::vector<std::unique_ptr<Monster>>& monsters);    
    virtual void TakeDamage(int damage);
    int ChooseTarget(const std::vector<std::unique_ptr<Monster>>& monsters) const;
    void DisplayTargets(const std::vector<std::unique_ptr<Monster>>& monsters) const;
    virtual void SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters) = 0;
    int RollDie(int sides);
    bool AllMonstersDefeated(const std::vector<std::unique_ptr<Monster>>& monsters);



    std::string getName() const;
    int getAC() const;
    bool IsDefeated() const;
    bool IsInvisible();
    void BecomeInvisible();
    void BecomeVisible();

protected:
    std::string name;
    int health;
    int AC;
    bool invisible;
    int damageDie;
    int damageBonus;
};

class Fighter : public Character {
public:
    Fighter(const std::string& name);
    void SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters);
    // Fighter-specific functions...
};

class Mage : public Character {
public:
    Mage(const std::string& name);
    void SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters);
};

class Thief : public Character {
public:
    Thief(const std::string& name);
    void SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters);
};

class Cleric : public Character {
public:
    Cleric(const std::string& name);
    void SpecialAction(std::vector<std::unique_ptr<Monster>>& monsters);
    // Cleric-specific functions...
};
#endif // CHARACTERS_H


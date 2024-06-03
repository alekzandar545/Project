#pragma once
#include "entity.h"
#include "player.h"


/**
 * @class Monster
 * @brief Represents a monster entity in the game.
 * 
 * The Monster class is a derived class of the Entity class and represents a monster entity in the game.
 * It provides functionality for combat, including choosing attacks and performing attacks on other entities.
 */
/**
 * @class Monster
 * @brief Represents a monster entity in the game.
 * 
 * The Monster class is a derived class of the Entity class and represents a monster entity in the game.
 * It provides functionality for choosing and performing attacks on other entities.
 */
class Monster : public Entity{
public:
    /**
     * @enum Attacks
     * @brief Represents the types of attacks a monster can perform.
     */
    enum class Attacks{
        MeleeAttack, /**< Represents a melee attack. */
        SpellAttack /**< Represents a spell attack. */
    };
    
    /**
     * @brief Default constructor for the Monster class.
     */
    Monster();
    
    /**
     * @brief Constructor for the Monster class with specified level.
     * @param level The level of the monster.
     */
    Monster(unsigned level);
    
    /**
     * @brief Chooses an attack for the monster.
     * @param attack The chosen attack will be stored in this parameter.
     * @return The damage value of the chosen attack.
     */
    unsigned ChooseAttack(Attacks& attack) const;
    
    /**
     * @brief Performs an attack on another entity.
     * @param pl The entity to be attacked.
     * @param attack The chosen attack to be used.
     * @return True if the attack was successful, false otherwise.
     */
    bool Attack(Entity* pl, Attacks& attack) const;
    
private:
    unsigned level; /**< The level of the monster. */
};

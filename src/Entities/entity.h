#pragma once


/**
 * @class Entity
 * @brief Represents an entity in the game.
 * 
 * This class provides functionality for managing an entity's attributes such as strength, mana, health points, armor, and dexterity.
 * It also includes methods for taking hits, healing, and accessing the entity's attributes.
 */
class Entity {
public:
    /**
     * @brief Default constructor for Entity.
     */
    Entity();
    
    Entity(const Entity& other) = default;

    Entity& operator=(const Entity& other) = default;

    virtual ~Entity() = default;

    /**
     * @brief Takes a hit with the specified damage.
     * @param dmg The amount of damage to be taken.
     * @return True if the entity is still alive after taking the hit, false otherwise.
     */
    bool TakeHit(const unsigned dmg);
    
    /**
     * @brief Heals the entity by the specified value.
     * @param value The amount of healing to be applied.
     */
    void Heal(const unsigned value);
    
    // Getters
    
    /**
     * @brief Gets the strength attribute of the entity.
     * @return The strength attribute.
     */
    unsigned GetStrength() const;
    
    /**
     * @brief Gets the mana attribute of the entity.
     * @return The mana attribute.
     */
    unsigned GetMana() const;
    
    /**
     * @brief Gets the maximum health points attribute of the entity.
     * @return The maximum health points attribute.
     */
    unsigned GetMaxHP() const;
    
    /**
     * @brief Gets the current health points attribute of the entity.
     * @return The current health points attribute.
     */
    int GetHP() const;
    
    /**
     * @brief Gets the armor attribute of the entity.
     * @return The armor attribute.
     */
    unsigned GetArmor() const;
    
    /**
     * @brief Gets the dexterity attribute of the entity.
     * @return The dexterity attribute.
     */
    unsigned GetDexterity() const;
    
    // Setters
    
    /**
     * @brief Sets the strength attribute of the entity.
     * @param value The value to set.
     */
    void SetStrength(const unsigned value);
    
    /**
     * @brief Sets the mana attribute of the entity.
     * @param value The value to set.
     */
    void SetMana(const unsigned value);
    
    /**
     * @brief Sets the maximum health points attribute of the entity.
     * @param value The value to set.
     */
    void SetMaxHP(const unsigned value);
    
    /**
     * @brief Sets the current health points attribute of the entity.
     * @param value The value to set.
     */
    void SetHP(const int value);
    
    /**
     * @brief Sets the armor attribute of the entity.
     * @param value The value to set.
     */
    void SetArmor(const unsigned value);
    
    /**
     * @brief Sets the dexterity attribute of the entity.
     * @param value The value to set.
     */
    void SetDexterity(const unsigned value);
    
protected:
    unsigned str;       ///< The strength attribute of the entity.
    unsigned mana;      ///< The mana attribute of the entity.
    unsigned maxHP;     ///< The maximum health points attribute of the entity.
    int HP;             ///< The current health points attribute of the entity.
    unsigned armor;     ///< The armor attribute of the entity.
    unsigned dexterity; ///< The dexterity attribute of the entity.
};
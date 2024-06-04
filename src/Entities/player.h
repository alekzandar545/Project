#pragma once
#include "entity.h"
#include "monster.h"
#include "../Items/item.h"
#include <vector>
#include <stdexcept>

class Monster; //forward declaration

/**
 * @class Player
 * @brief Represents a player entity in the game.
 * 
 * The Player class inherits from the Entity class and provides functionality for managing a player's attributes, inventory, and combat actions.
 */
class Player : public Entity {
public:
    /**
     * @enum PlayerRace
     * @brief Represents the race of the player.
     */
    enum class PlayerRace {
        Human, /**< Human race */
        Berserk, /**< Berserk race */
        Sorcerer /**< Sorcerer race */
    };

    // Constructors
    Player(); /**< Default constructor */
    Player(PlayerRace race, const std::string name); /**< Constructor with race and name parameters */
    Player(const std::string name, const unsigned str, const unsigned mana, const unsigned maxHP, const int HP, const unsigned armor, const unsigned dexterity,
        const unsigned statPoints, const unsigned level, const unsigned xp, const unsigned requiredXp, const unsigned gold,
        const std::vector<Item> inventory, const Item& weapon, const Item& spell, const Item& armorPiece); /**< Constructor with all parameters */
    Player(const Player& other); /**< Copy constructor */
    Player& operator=(const Player& other); /**< Assignment operator */
    ~Player() override; /**< Destructor */

    // Leveling
    /**
     * @brief Increases the player's level and updates their attributes accordingly.
     */
    void LevelUp();
    
    /**
     * @brief Adds experience points to the player's current XP.
     * @param xp The amount of experience points to add.
     */
    void AddXP(unsigned xp);

    // Combat
    /**
     * @brief Performs a melee attack on a monster.
     * @param monster The monster to attack.
     * @return True if the attack is successful, false otherwise.
     */
    bool MeleeAttack(Monster& monster) const;
    
    /**
     * @brief Performs a spell attack on a monster.
     * @param monster The monster to attack.
     * @return True if the attack is successful, false otherwise.
     */
    bool SpellAttack(Monster& monster) const;

    // Item management
    /**
     * @brief Equips an item from the player's inventory.
     * @param index The index of the item to equip.
     */
    void EquipItem(const unsigned index);

    // Inventory
    /**
     * @brief Adds an item to the player's inventory.
     * @param item The item to add.
     * @return True if the item was successfully added, false otherwise.
     */
    bool AddItem(const Item& item);
    
    /**
     * @brief Sells an item from the player's inventory.
     * @param index The index of the item to sell.
     */
    void SellItem(const unsigned index);

    // Gold
    /**
     * @brief Adds gold to the player's current amount.
     * @param gold The amount of gold to add.
     */
    void AddGold(const unsigned gold);

    // Stats
    /**
     * @brief Increases the player's strength attribute.
     */
    void AddStrength();
    
    /**
     * @brief Increases the player's mana attribute.
     */
    void AddMana();
    
    /**
     * @brief Increases the player's maximum HP attribute.
     */
    void AddHP();
    
    /**
     * @brief Increases the player's dexterity attribute.
     */
    void AddDexterity();
    
    /**
     * @brief Adds a potion to the player's inventory.
     */
    void AddPotion();

    // Potion usage
    /**
     * @brief Uses a potion from the player's inventory.
     * @return True if a potion was successfully used, false otherwise.
     */
    bool UsePotion();
    
    /**
     * @brief Uses a potion from the player's inventory at a specific index.
     * @param index The index of the potion to use.
     */
    void UsePotion(unsigned index);

    // Getters
    /**
     * @brief Gets the name of the player.
     * @return The player's name.
     */
    std::string GetName() const;
    
    /**
     * @brief Gets the number of stat points the player has.
     * @return The number of stat points.
     */
    unsigned GetStatPoints() const;
    
    /**
     * @brief Gets the player's current level.
     * @return The player's level.
     */
    unsigned GetLevel() const;
    
    /**
     * @brief Gets the player's current XP.
     * @return The player's XP.
     */
    unsigned GetXP() const;
    
    /**
     * @brief Gets the required XP for the player to level up.
     * @return The required XP.
     */
    unsigned GetRequiredXP() const;
    
    /**
     * @brief Gets the amount of gold the player has.
     * @return The amount of gold.
     */
    unsigned GetGold() const;
    
    /**
     * @brief Gets the size of the player's inventory.
     * @return The inventory size.
     */
    unsigned GetInventorySize() const;
    
    /**
     * @brief Gets the player's inventory.
     * @return The inventory vector.
     */
    std::vector<Item> GetInventory() const;
    
    /**
     * @brief Gets the player's equipped weapon.
     * @return The weapon item.
     */
    Item GetWeapon() const;
    
    /**
     * @brief Gets the player's equipped spell.
     * @return The spell item.
     */
    Item GetSpell() const;
    
    /**
     * @brief Gets the player's equipped armor piece.
     * @return The armor piece item.
     */
    Item GetArmorPiece() const;
    
    /**
     * @brief Gets the capacity of the player's inventory.
     * @return The inventory capacity.
     */
    unsigned GetInventoryCapacity() const;

    // Setters
    /**
     * @brief Sets the name of the player.
     * @param name The player's name.
     */
    void SetName(const std::string& name);
    
    /**
     * @brief Sets the number of stat points the player has.
     * @param statPoints The number of stat points.
     */
    void SetStatPoints(const unsigned statPoints);
    
    /**
     * @brief Sets the player's current level.
     * @param level The player's level.
     */
    void SetLevel(const unsigned level);
    
    /**
     * @brief Sets the player's current XP.
     * @param xp The player's XP.
     */
    void SetXP(const unsigned xp);
    
    /**
     * @brief Sets the required XP for the player to level up.
     * @param requiredXp The required XP.
     */
    void SetRequiredXP(const unsigned requiredXp);
    
    /**
     * @brief Sets the amount of gold the player has.
     * @param gold The amount of gold.
     */
    void SetGold(const unsigned gold);
    
    /**
     * @brief Sets the player's inventory.
     * @param inventory The inventory vector.
     */
    void SetInventory(const std::vector<Item>& inventory);
    
    /**
     * @brief Sets the player's equipped weapon.
     * @param weapon The weapon item.
     */
    void SetWeapon(const Item& weapon);
    
    /**
     * @brief Sets the player's equipped spell.
     * @param spell The spell item.
     */
    void SetSpell(const Item& spell);
    
    /**
     * @brief Sets the player's equipped armor piece.
     * @param armorPiece The armor piece item.
     */
    void SetArmorPiece(const Item& armorPiece);

private:
    unsigned inventoryCapacity; /**< The capacity of the player's inventory */
    unsigned statPoints; /**< The number of stat points the player has */
    unsigned level; /**< The player's current level */
    unsigned xp; /**< The player's current XP */
    unsigned requiredXp; /**< The required XP for the player to level up */
    unsigned gold; /**< The amount of gold the player has */
    std::string name; /**< The player's name */
    std::vector<Item> inventory; /**< The player's inventory */
    Item weapon; /**< The player's equipped weapon */
    Item spell; /**< The player's equipped spell */
    Item armorPiece; /**< The player's equipped armor piece */

    /**
     * @brief Sets the default values for the player's attributes.
     */
    void SetDefaultValues();
    
    /**
     * @brief Copies the attributes of another player.
     * @param other The other player to copy from.
     */
    void copy(const Player& other);
};

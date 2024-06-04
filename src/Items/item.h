#pragma once
#include <string>

/**
 * @class Item
 * @brief Represents an item in the game.
 */
class Item
{
public:
    /**
     * @enum ItemType
     * @brief Represents the type of an item.
     */
    enum class ItemType
    {
        Weapon, /**< Represents a weapon item. */
        Spell, /**< Represents a spell item. */
        Armor, /**< Represents an armor item. */
        Potion /**< Represents a potion item. */
    };

    /**
     * @brief Default constructor for Item.
     */
    Item();

    /**
     * @brief Constructor for Item.
     * @param name The name of the item.
     * @param type The type of the item.
     * @param power The power of the item.
     */
    Item(const std::string &name, ItemType type, unsigned power);

    /**
     * @brief Copy constructor for Item.
     * @param other The item to be copied.
     */
    Item(const Item &other);

    /**
     * @brief Assignment operator for Item.
     * @param other The item to be assigned.
     * @return A reference to the assigned item.
     */
    Item& operator=(const Item &other);

    /**
     * @brief Destructor for Item.
     */
    ~Item();

    /**
     * @brief Static method to generate an item based on the given level.
     * @param level The level of the item to be generated.
     * @return The generated item.
     */
    static Item GenerateItem(unsigned level);

    /**
     * @brief Getter for the type of the item.
     * @return The type of the item.
     */
    ItemType GetType() const;

    /**
     * @brief Getter for the power of the item.
     * @return The power of the item.
     */
    unsigned GetPower() const;

    /**
     * @brief Getter for the name of the item.
     * @return The name of the item.
     */
    std::string GetName() const;

private:
    ItemType type; /**< The type of the item. */
    std::string name; /**< The name of the item. */
    unsigned power; /**< The power of the item. */
};

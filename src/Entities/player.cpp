#include "player.h"

// Constructors
Player::Player() {
    this->str = 30; // human class stats
    this->mana = 20;
    this->name = "Player";
    SetDefaultValues();
}

Player::Player(PlayerRace race, std::string name) {
    switch (race) {
    case PlayerRace::Human:
        this->str = 30;
        this->mana = 20;
        break;
    case PlayerRace::Berserk:
        this->str = 40;
        this->mana = 10;
        break;
    case PlayerRace::Sorcerer:
        this->str = 10;
        this->mana = 40;
        break;
    }
    SetDefaultValues();
}

Player::Player(const std::string name, const unsigned str, const unsigned mana, const unsigned maxHP, const int HP, const unsigned armor, const unsigned dexterity,
    const unsigned statPoints, const unsigned level, const unsigned xp, const unsigned requiredXp, const unsigned gold,
    const std::vector<Item> inventory, const Item& weapon, const Item& spell, const Item& armorPiece) {
    inventoryCapacity = 10;
    this->name = name;
    this->str = str;
    this->mana = mana;
    this->maxHP = maxHP;
    this->HP = HP;
    this->armor = armor;
    this->dexterity = dexterity;
    this->statPoints = statPoints;
    this->level = level;
    this->xp = xp;
    this->requiredXp = requiredXp;
    this->gold = gold;
    this->inventory = inventory;
    this->weapon = weapon;
    this->spell = spell;
    this->armorPiece = armorPiece;
}

Player::Player(const Player& other) {
    copy(other);
}

Player::~Player() = default;

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        copy(other);
    }
    return *this;
}

// Private support functionality
void Player::SetDefaultValues() {
    this->gold = 0;
    this->xp = 0;
    this->level = 1;
    this->requiredXp = 100;
    this->inventoryCapacity = 10;
    this->dexterity = 10;
    this->statPoints = 0;
    this->armor = 0;
    this->maxHP = 50;
    this->HP = 50;
    this->weapon = Item("Shortsword", Item::ItemType::Weapon, 20);
    this->spell = Item("Fireball", Item::ItemType::Spell, 20);
    this->armorPiece = Item("Old rags", Item::ItemType::Armor, 0);
    inventory.push_back(Item("Potion", Item::ItemType::Potion, 50));
}

void Player::copy(const Player& other) {
    this->gold = other.gold;
    this->xp = other.xp;
    this->level = other.level;
    this->requiredXp = other.requiredXp;
    this->str = other.str;
    this->mana = other.mana;
    this->inventoryCapacity = other.inventoryCapacity;
    this->dexterity = other.dexterity;
    this->statPoints = other.statPoints;
    this->armor = other.armor;
    this->maxHP = other.maxHP;
    this->HP = other.HP;
    this->weapon = other.weapon;
    this->spell = other.spell;
    this->armorPiece = other.armorPiece;
    this->name = other.name;
    this->inventory = other.inventory;
}

// Leveling
void Player::LevelUp() {
    level++;
    unsigned leftoverXP = this->xp % requiredXp;
    xp = leftoverXP;
    requiredXp += requiredXp / 10; // lets see if this progression is too slow
    HP = maxHP;
    statPoints += 30;
}

void Player::AddXP(unsigned xp) {
    this->xp += xp;
    if (this->xp >= requiredXp)
        LevelUp();
}

// Combat
bool Player::MeleeAttack(Monster& monster) const {
    return monster.TakeHit(str + str * weapon.GetPower() / 100);
}

bool Player::SpellAttack(Monster& monster) const {
    return monster.TakeHit(mana + mana * spell.GetPower() / 100);
}

// Item management
void Player::EquipItem(const unsigned index) {
    if (this->inventory.size() == 0)
        throw std::out_of_range("Cannot equip item: Inventory is empty.");
    if (index >= this->inventory.size())
        throw std::out_of_range("Cannot equip item: Index is out of range.");
    Item newItem = inventory[index]; // create a copy
    switch (inventory[index].GetType()) {
    case Item::ItemType::Weapon:
        inventory[index] = this->weapon;
        this->weapon = newItem;
        break;
    case Item::ItemType::Spell:
        inventory[index] = this->spell;
        this->spell = newItem;
        break;
    case Item::ItemType::Armor:
        this->armor -= this->armorPiece.GetPower();
        inventory[index] = this->armorPiece;
        this->armorPiece = newItem;
        this->armor += this->armorPiece.GetPower();
        break;
    case Item::ItemType::Potion:
        this->UsePotion(index);
    }
}

// Inventory
bool Player::AddItem(const Item& item) {
    if (this->inventory.size() < this->inventoryCapacity) {
        this->inventory.push_back(item);
        return true; // success
    }
    return false; // failed
}

void Player::SellItem(const unsigned index) {
    if (this->inventory.size() == 0)
        throw std::out_of_range("Cannot sell item: Inventory is empty.");
    if (index >= this->inventory.size())
        throw std::out_of_range("Cannot sell item: Index is out of range.");
    this->gold += inventory[index].GetPower() / 2;
    this->inventory.erase(this->inventory.begin() + index);
}

// Gold
void Player::AddGold(const unsigned gold) {
    this->gold += gold;
}

// Stats
void Player::AddStrength() {
    if (statPoints > 0) {
        str++;
        statPoints--;
    }
}

void Player::AddMana() {
    if (statPoints > 0) {
        mana++;
        statPoints--;
    }
}

void Player::AddHP() {
    if (statPoints > 0) {
        maxHP++;
        HP++;
        statPoints--;
    }
}

void Player::AddDexterity() {
    if (statPoints > 0) {
        dexterity++;
        statPoints--;
    }
}

void Player::AddPotion() {
    Item potion("Potion", Item::ItemType::Potion, 50); // potion restores 50% of hp
    inventory.push_back(potion);
}

// Potion usage
bool Player::UsePotion() {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i].GetType() == Item::ItemType::Potion) {
            Heal(maxHP / 2);
            inventory.erase(inventory.begin() + i);
            return true;
        }
    }
    return false;
}

void Player::UsePotion(unsigned index) {
    Heal(maxHP / 2);
    inventory.erase(inventory.begin() + index);
}

// Getters
std::string Player::GetName() const {
    return this->name;
}

unsigned Player::GetStatPoints() const {
    return this->statPoints;
}

unsigned Player::GetLevel() const {
    return this->level;
}

unsigned Player::GetXP() const {
    return this->xp;
}

unsigned Player::GetRequiredXP() const {
    return this->requiredXp;
}

unsigned Player::GetGold() const {
    return this->gold;
}

unsigned Player::GetInventorySize() const {
    return this->inventory.size();
}

std::vector<Item> Player::GetInventory() const {
    return this->inventory;
}

Item Player::GetWeapon() const {
    return this->weapon;
}

Item Player::GetSpell() const {
    return this->spell;
}

Item Player::GetArmorPiece() const {
    return this->armorPiece;
}

unsigned Player::GetInventoryCapacity() const {
    return this->inventoryCapacity;
}

// Setters
void Player::SetName(const std::string& name) {
    this->name = name;
}

void Player::SetStatPoints(unsigned statPoints) {
    this->statPoints = statPoints;
}

void Player::SetLevel(unsigned level) {
    this->level = level;
}

void Player::SetXP(unsigned xp) {
    this->xp = xp;
}

void Player::SetRequiredXP(unsigned requiredXp) {
    this->requiredXp = requiredXp;
}

void Player::SetGold(unsigned gold) {
    this->gold = gold;
}

void Player::SetInventory(const std::vector<Item>& inventory) {
    this->inventory = inventory;
}

void Player::SetWeapon(const Item& weapon) {
    this->weapon = weapon;
}

void Player::SetSpell(const Item& spell) {
    this->spell = spell;
}

void Player::SetArmorPiece(const Item& armorPiece) {
    this->armorPiece = armorPiece;
}

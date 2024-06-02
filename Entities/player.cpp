#include "player.h"

//constructors
Player::Player() = default;
Player::Player(PlayerRace race, std::string name) : gold(0), xp(0), level(1), requiredXp(100){
    switch (race)
    {
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
    this->inventoryCapacity = 10;
    this->dexterity = 10;
    this->statPoints = 0;
    this->armor = 0;
    this->maxHP = 50;
    this->HP = 50;
    this->weapon = Item("Shortsword", Item::ItemType::Weapon, 20);
    this->spell = Item("Fireball", Item::ItemType::Spell, 20);
    this->armorPiece = Item("Old rags", Item::ItemType::Armor, 0);
    this->name = name;
    inventory.push_back(Item("Potion",Item::ItemType::Potion, 50));
};
//leveling
void Player::LevelUp(){
    level++;
    unsigned leftoverXP = this->xp % requiredXp;
    xp = leftoverXP;
    requiredXp += requiredXp/10; //lets see if this progression is too slow
    HP = maxHP;
    statPoints+=30;
}

void Player::AddXP(unsigned xp){
    this->xp += xp;
    if(this->xp >= requiredXp)
        LevelUp();
}
//combat
bool Player::MeleeAttack(Monster& monster) const{
    return monster.TakeHit(str + str*weapon.GetPower()/100);
}
bool Player::SpellAttack(Monster& monster) const{
    return monster.TakeHit(mana + mana*spell.GetPower()/100);
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
unsigned Player::GetInventoryCapacity() const{
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

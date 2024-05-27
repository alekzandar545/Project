#pragma once
#include <string>

class Item{
public:
    enum class ItemType{
        Weapon,
        Spell,
        Armor
    };
    //getters
    ItemType GetType() const{
        return this->type;
    }
    unsigned GetPower() const{
        return this->power;
    }
    std::string GetName() const{
        return this->name;
    }
    //constructors
    Item() = default;
    Item(std::string name, ItemType type, unsigned power){
        this->name = name;
        this->type = type;
        this->power = power;
    }
    static Item GenerateItem(unsigned level){
        std::string weaponNames[] = {
            "Bloodthirster Blade", "Dragonfang Dagger", "Doomhammer", "Widowmaker Waraxe", 
            "Shadowstrike Scimitar", "Hellfire Halberd", "Frostbite Flail", "Stormbringer Sword", 
            "Grim Reaper's Glaive", "Bonecrusher Mace", "Blackguard's Blade", "Deathknell Dagger", 
            "Firestorm Flail", "Soulrender Scythe", "Darkbane Dagger", "Thunderfury Greatsword", 
            "Wraithslayer Warhammer", "Venomfang Voulge", "Ironclad Axe", "Nightstalker Knives", 
            "Skullsplitter Axe", "Lifedrinker Lance", "Blightbringer Blade", "Abyssal Axe", 
            "Frostwarden Warhammer", "Moonshadow Mace", "Emberblade Sword", "Bloodmoon Battleaxe", 
            "Runeblade Rapier", "Serpent's Fang Spear", "Voidreaver Scimitar", "Lightbringer Longsword", 
            "Searing Star Spear", "Soulforge Sword", "Dragon's Breath Battleaxe", "Nightfall Naginata", 
            "Ironheart Hammer", "Voidbane Voulge", "Dragonclaw Dagger", "Hellsguard Halberd", 
            "Stormforged Sword", "Icebreaker Axe", "Grimshadow Glaive", "Spiritbane Scepter", 
            "Emberfury Flail", "Shadowreaper Scythe", "Bloodseeker Blade", "Frostfang Falchion", 
            "Thunderstrike Trident"
        };
        std::string spellNames[] = {
            "Acid Arrow", "Blight", "Burning Hands", "Chain Lightning", "Chaos Bolt", "Chromatic Orb", 
            "Cloudkill", "Cone of Cold", "Crown of Stars", "Delayed Blast Fireball", "Destructive Wave", 
            "Disintegrate", "Divine Word", "Dragon's Breath", "Earthquake", "Eldritch Blast", 
            "Fire Bolt", "Fire Storm", "Fireball", "Flame Strike", "Frostbite", "Guiding Bolt", 
            "Hail of Thorns", "Harm", "Ice Knife", "Ice Storm", "Immolation", "Incendiary Cloud", 
            "Inflict Wounds", "Lightning Bolt", "Magic Missile", "Melf's Acid Arrow", "Meteor Swarm", 
            "Moonbeam", "Power Word Kill", "Power Word Stun", "Prismatic Spray", "Ray of Enfeeblement", 
            "Ray of Frost", "Scorching Ray", "Shatter", "Sickening Radiance", "Sleet Storm", 
            "Spirit Guardians", "Spirit Shroud", "Sunbeam", "Sunburst", "Thunderwave", "Vampiric Touch", 
            "Wall of Fire"
        };
        std::string armorNames[] = {
            "Padded Armor", "Leather Armor", "Studded Leather Armor", "Hide Armor", "Chain Shirt", 
            "Scale Mail", "Breastplate", "Half Plate", "Ring Mail", "Chain Mail", "Splint Armor", 
            "Plate Armor", "Shield", "Mithral Armor", "Adamantine Armor", "Elven Chain", 
            "Glamoured Studded Leather", "Mariner's Armor", "Armor of Invulnerability", 
            "Armor of Resistance", "Dwarven Plate", "Dragon Scale Mail", "Demon Armor", 
            "Celestial Armor", "Armor of Vulnerability", "Shield of Missile Attraction", 
            "Animated Shield", "Sentinel Shield", "Spellguard Shield", "Robe of the Archmagi", 
            "Robe of Scintillating Colors", "Robe of Stars", "Robe of the Magi", "Robe of Eyes", 
            "Bracers of Defense", "Cloak of Protection", "Cloak of Displacement", "Cloak of Elvenkind", 
            "Cloak of Invisibility", "Cloak of the Bat", "Cloak of the Manta Ray", "Boots of Elvenkind", 
            "Boots of Speed", "Boots of Striding and Springing", "Boots of Levitation", 
            "Boots of the Winterlands", "Armor of Gleaming", "Armor of Shadows", "Armor of the Dragon", 
            "Armor of the Celestial"
        };

        // Pick random type
        unsigned pickType = rand() % 3;
        unsigned bonus = rand() % 10;
        unsigned index = 0;

        switch (pickType){
            case 0:
                index = rand() % (sizeof(weaponNames) / sizeof(std::string));
                return Item(weaponNames[index], ItemType::Weapon, 20 + 5 * level + bonus);
            case 1:
                index = rand() % (sizeof(spellNames) / sizeof(std::string));
                return Item(spellNames[index], ItemType::Spell, 20 + 5 * level + bonus);
            case 2:
                index = rand() % (sizeof(armorNames) / sizeof(std::string));
                return Item(armorNames[index], ItemType::Armor, 10 + 5 * level + bonus);
        }
        return Item();
    }
private:
    ItemType type;
    std::string name;
    unsigned power;
};
#include "combatEvents.h"
#include "../MapGenerator/map.h"
#include "../Utils/constants.h"
#include "../UI/battleUI.h"
#include "../Entities/player.h"
#include "../Entities/monster.h"
#include "alerts.h"
#include "eventHandler.h"

//construction
CombatEvents::CombatEvents(Map* map) : map(map) {}

//handling cases
void CombatEvents::HandleMeleeAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead) {
    std::ostringstream msg;
    if (map->GetPlayer()->MeleeAttack(*ui.getMonster())) {
        ui.Render();
        msg << map->GetPlayer()->GetName() << " has slain the dragon and earned " << std::to_string(5 + map->GetFloor()) 
            << " gold and " << std::to_string(25 + map->GetFloor() * 3) << " xp";
        Alerts::Alert(msg);
        DropPotion(*map->GetPlayer());
        monsterIsDead = true;
    } 
    else {
        ui.Render();
        msg << map->GetPlayer()->GetName() << " hit the dragon with their " << map->GetPlayer()->GetWeapon().GetName();
        Alerts::BattleAlert(msg);
        Event event(map);
        event.MonsterAttack(map->GetPlayer(), ui.getMonster(), playerIsDead);
        system("cls");
        ui.RenderGraphics();
        ui.Render();
    }
}

void CombatEvents::HandleSpellAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead) {
    std::ostringstream msg;
    if (map->GetPlayer()->SpellAttack(*ui.getMonster())) {
        ui.Render();
        msg << map->GetPlayer()->GetName() << " has slain the dragon and earned " << std::to_string(5 + map->GetFloor()) 
            << " gold and " << std::to_string(25 + map->GetFloor() * 3) << " xp";
        Alerts::Alert(msg);
        DropPotion(*map->GetPlayer());
        monsterIsDead = true;
    } 
    else {
        ui.Render();
        msg << map->GetPlayer()->GetName() << " cast a " << map->GetPlayer()->GetSpell().GetName() << " on the dragon!";
        Alerts::BattleAlert(msg);
        Event event(map);
        event.MonsterAttack(map->GetPlayer(), ui.getMonster(), playerIsDead);
        system("cls");
        ui.RenderGraphics();
        ui.Render();
    }
}

void CombatEvents::HandlePotionUsage(BattleUI& ui) {
    std::ostringstream msg;
    if(!map->GetPlayer()->UsePotion()){
        msg << map->GetPlayer()->GetName() << " has no potions!";
        Alerts::Alert(msg);
    }
    else{
        msg << map->GetPlayer()->GetName() << "has used a potion to restore 50% HP";
        Alerts::Alert(msg);
    }
    system("cls");
    ui.RenderGraphics();
    ui.Render();
}

void CombatEvents::HandleFlee(BattleUI& ui, bool& fled) {
    fled = true;
    std::ostringstream msg;
    msg << map->GetPlayer()->GetName() << " has fled!";
    Alerts::Alert(msg);
}
//mob womp womp potion
void CombatEvents::DropPotion(Player& player){
    //50% chance for mob to drop potion
    bool dropped = rand() % 2;
    if(dropped){
        player.AddPotion();
        std::ostringstream msg;
        msg << player.GetName() << " has received a potion!";
        Alerts::Alert(msg);
    }
    else
        return;
}
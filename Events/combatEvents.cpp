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
    if (ui.getPlayer()->MeleeAttack(*ui.getMonster())) {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " has slain the dragon and earned " << std::to_string(5 + map->GetFloor()) 
            << " gold and " << std::to_string(25 + map->GetFloor() * 3) << " xp";
        Alerts::Alert(msg);
        DropPotion(*ui.getPlayer());
        monsterIsDead = true;
    } 
    else {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " hit the dragon with their " << ui.getPlayer()->GetWeapon().GetName();
        Alerts::BattleAlert(msg);
        Event event(map);
        event.MonsterAttack(ui.getPlayer(), ui.getMonster(), playerIsDead);
        system("cls");
        ui.RenderGraphics();
        ui.Render();
    }
}

void CombatEvents::HandleSpellAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead) {
    std::ostringstream msg;
    if (ui.getPlayer()->SpellAttack(*ui.getMonster())) {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " has slain the dragon and earned " << std::to_string(5 + map->GetFloor()) 
            << " gold and " << std::to_string(25 + map->GetFloor() * 3) << " xp";
        Alerts::Alert(msg);
        DropPotion(*ui.getPlayer());
        monsterIsDead = true;
    } 
    else {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " cast a " << ui.getPlayer()->GetSpell().GetName() << " on the dragon!";
        Alerts::BattleAlert(msg);
        Event event(map);
        event.MonsterAttack(ui.getPlayer(), ui.getMonster(), playerIsDead);
        system("cls");
        ui.RenderGraphics();
        ui.Render();
    }
}

void CombatEvents::HandlePotionUsage(BattleUI& ui) {
    std::ostringstream msg;
    if(!ui.getPlayer()->UsePotion()){
        msg << ui.getPlayer()->GetName() << " has no potions!";
        Alerts::Alert(msg);
    }
    else{
        msg << ui.getPlayer()->GetName() << "has used a potion to restore 50% HP";
        Alerts::Alert(msg);
    }
    system("cls");
    ui.RenderGraphics();
    ui.Render();
}

void CombatEvents::HandleFlee(BattleUI& ui, bool& fled) {
    fled = true;
    std::ostringstream msg;
    msg << ui.getPlayer()->GetName() << " has fled!";
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
#include "eventHandler.h"
#include "../UI/inputHandler.h"
#include "../Utils/gameState.h"
#include "alerts.h"
#include "../Utils/mathFunctions.h"


//events
void Event::TreasureEvent(Map* map) {
    map->GetPlayer()->AddGold(goldDrop);
    Item newItem = Item::GenerateItem(map->GetFloor());
    std::ostringstream msg;
    if (map->GetPlayer()->AddItem(newItem)) {
        msg << map->GetPlayer()->GetName() << " just acquired " << newItem.GetName();
        Alerts::Alert(msg);
    } 
    else {
        msg << "Inventory is full!";
        Alerts::Alert(msg);
    }
}

void Event::GameOver() const {
    system("cls");
    std::cout << "\nGAME OVER\n";
    std::cout << "Gold highscore: " << GameState::GetGamePlayer()->GetGold();
    GameState::EndGame();
}

void Event::MonsterAttack(Monster* monster, bool& playerIsDead) {
    Player* player = GameState::GetGamePlayer();
    std::ostringstream msg;
    Monster::Attacks attack;
    monster->Attack(player, attack);
    if (player->GetHP() == 0) {
        playerIsDead = true;
    }
    switch (attack) {
        case Monster::Attacks::MeleeAttack:
            msg << "The dragon hit " << player->GetName() << " with its claws!";
            Alerts::Alert(msg);
            break;
        case Monster::Attacks::SpellAttack:
            msg << "The dragon burned " << player->GetName() << " with fire breath!";
            Alerts::Alert(msg);
            break;
    }
}

void Event::MonsterEvent(Map* map) {
    system("cls");
    // monsters get stronger on each floor
    Monster* monster = new Monster(map->GetFloor()); 
    BattleUI battle(monster);
    battle.RenderGraphics();
    battle.Render();
    bool playerIsDead = 0;
    bool monsterIsDead = 0;
    bool evaded = 0;
    // initiative throw (based on dexterity):
    unsigned MonsterInitiative = rand() % (map->GetPlayer()->GetDexterity() + monster->GetDexterity());
    if (MonsterInitiative > map->GetPlayer()->GetDexterity()) { // monster gets the first hit
        std::cout << "Surprise attack! ";
        MonsterAttack(monster, playerIsDead);
        system("cls");
        battle.RenderGraphics();
        battle.Render();
    }
    // combat phase
    CombatEvents event;
    while (!playerIsDead && !monsterIsDead && !evaded) {
        InputHandler::BattleUserInput(&event, battle, playerIsDead, monsterIsDead, evaded); // Assuming BattleUserInput is part of InputHandler now
    }
    if (playerIsDead) {
        std::ostringstream msg;
        msg << map->GetPlayer()->GetName() << " has been slain.";
        Alerts::Alert(msg);
        GameOver();
        return;
    } 
    else if (monsterIsDead) {
        //heal player at end of combat if player is under 50%HP
        if (map->GetPlayer()->GetHP() < map->GetPlayer()->GetMaxHP() / 2)
            map->GetPlayer()->SetHP(map->GetPlayer()->GetMaxHP() / 2);
        map->GetPlayer()->AddGold(goldDrop); // more gold on each floor
        map->GetPlayer()->AddXP(XPDrop); // more xp on each floor
    }
    system("cls");
    map->RenderAll();
}

void Event::NextFloor(Map* map) {
    system("cls");
    *map = Map(MathFunctions::Fib(Constants::STARTING_WIDTH[0], Constants::STARTING_WIDTH[1], map->GetFloor()),
            MathFunctions::Fib(Constants::STARTING_HEIGHT[0], Constants::STARTING_HEIGHT[1], map->GetFloor()),
            MathFunctions::Fib(Constants::STARTING_MONSTERS[0], Constants::STARTING_MONSTERS[1], map->GetFloor()), 
            MathFunctions::Fib(Constants::STARTING_TREASURE[0], Constants::STARTING_TREASURE[1], map->GetFloor()), 
            map->GetFloor()+1, map->GetPlayer());
    map->GenerateMap();
    // hope this is balanced, will change later if need to;
    const unsigned baseXP = 70;
    const unsigned XPBonus = 10;
    const unsigned endOfLevelXP = baseXP + map->GetFloor() * XPBonus;
    map->GetPlayer()->AddXP(endOfLevelXP); 
    std::ostringstream msg;
    msg << "Floor " << (map->GetFloor()-1) << " passed! " << map->GetPlayer()->GetName() << " got " << baseXP + map->GetFloor() * XPBonus << " xp!";
    Alerts::Alert(msg);
    map->RenderAll();
}


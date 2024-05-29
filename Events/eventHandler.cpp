#include "eventHandler.h"
#include "../UI/inputHandler.h"
#include <sstream>
#include <thread>
#include <chrono>

//constructor
Event::Event(Map* map) {this->map=map;}

//handling cases
void Event::HandleMeleeAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead) {
    std::ostringstream msg;
    if (ui.getPlayer()->MeleeAttack(*ui.getMonster())) {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " has slain the dragon and earned " << std::to_string(5 + map->GetFloor()) 
            << " gold and " << std::to_string(25 + map->GetFloor() * 3) << " xp";
        Alert(msg);
        monsterIsDead = true;
    } 
    else {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " hit the dragon with their " << ui.getPlayer()->weapon.GetName();
        BattleAlert(msg);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        MonsterAttack(ui.getPlayer(), ui.getMonster(), playerIsDead);
        system("cls");
        ui.RenderGraphics();
        ui.Render();
    }
}

void Event::HandleSpellAttack(BattleUI& ui, bool& playerIsDead, bool& monsterIsDead) {
    std::ostringstream msg;
    if (ui.getPlayer()->SpellAttack(*ui.getMonster())) {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " has slain the dragon and earned " << std::to_string(5 + map->GetFloor()) 
            << " gold and " << std::to_string(25 + map->GetFloor() * 3) << " xp";
        Alert(msg);
        monsterIsDead = true;
    } 
    else {
        ui.Render();
        msg << ui.getPlayer()->GetName() << " cast a " << ui.getPlayer()->spell.GetName() << " on the dragon!";
        BattleAlert(msg);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        MonsterAttack(ui.getPlayer(), ui.getMonster(), playerIsDead);
        system("cls");
        ui.RenderGraphics();
        ui.Render();
    }
}

void Event::HandlePotionUsage(BattleUI& ui) {
    // Implement potion logic here
}

void Event::HandleFlee(BattleUI& ui, bool& fled) {
    fled = true;
    std::ostringstream msg;
    msg << ui.getPlayer()->GetName() << " has fled!";
    Alert(msg);
}


//events
void Event::TreasureEvent() {
    map->GetPlayer()->AddGold(3 + map->GetFloor());
    Item newItem = Item::GenerateItem(map->GetFloor());
    std::ostringstream msg;
    if (map->GetPlayer()->AddItem(newItem)) {
        msg << map->GetPlayer()->GetName() << " just acquired " << newItem.GetName();
        Alert(msg);
    } 
    else {
        msg << "Inventory is full!";
        Alert(msg);
    }
}

void Event::Alert(std::ostringstream& msg) const {
    std::cout << msg.str() << Constants::padding << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Event::BattleAlert(std::ostringstream& msg) const {
    std::cout << msg.str() << Constants::padding << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Event::GameOver() const {
    system("cls");
    std::cout << "\nGAME OVER\n";
    std::cout << "Gold highscore: " << map->GetPlayer()->gold;
    Constants::EndGame();
}

void Event::MonsterAttack(Player* player, Monster* monster, bool& playerIsDead) {
    std::ostringstream msg;
    Monster::Attacks attack;
    monster->Attack(player, attack);
    if (player->HP == 0) {
        playerIsDead = true;
    }
    switch (attack) {
        case Monster::Attacks::MeleeAttack:
            msg << "The dragon hit " << player->GetName() << " with its claws!";
            Alert(msg);
            break;
        case Monster::Attacks::SpellAttack:
            msg << "The dragon burned " << player->GetName() << " with fire breath!";
            Alert(msg);
            break;
    }
}

void Event::MonsterEvent() {
    system("cls");
    Monster* m = new Monster(map->GetFloor()); // monsters get stronger on each floor
    BattleUI battle(map->GetPlayer(), m);
    battle.RenderGraphics();
    battle.Render();
    bool playerIsDead = 0;
    bool monsterIsDead = 0;
    bool evaded = 0;
    // initiative throw (based on dexterity):
    unsigned MonsterInitiative = rand() % (map->GetPlayer()->dexterity + m->dexterity);
    if (MonsterInitiative > map->GetPlayer()->dexterity) { // monster gets the first hit
        std::cout << "Surprise attack! ";
        MonsterAttack(map->GetPlayer(), m, playerIsDead);
        system("cls");
        battle.RenderGraphics();
        battle.Render();
    }
    // combat phase
    while (!playerIsDead && !monsterIsDead && !evaded) {
        InputHandler inputHandler(this);
        inputHandler.BattleUserInput(battle, playerIsDead, monsterIsDead, evaded); // Assuming BattleUserInput is part of InputHandler now
    }
    if (playerIsDead) {
        std::ostringstream msg;
        msg << map->GetPlayer()->GetName() << " has been slain.";
        Alert(msg);
        GameOver();
        return;
    } 
    else if (monsterIsDead) {
        if (map->GetPlayer()->HP < map->GetPlayer()->maxHP / 2)
            map->GetPlayer()->HP = map->GetPlayer()->maxHP / 2;
        map->GetPlayer()->AddGold(5 + map->GetFloor()); // more gold on each floor
        map->GetPlayer()->AddXP(25 + map->GetFloor() * 3); // more xp on each floor
        // map->GetPlayer()->AddItem(GetRandomItem(map->GetFloor())); // stronger items on each floor
    }
    system("cls");
    map->RenderAll();
}

unsigned Fib(unsigned a, unsigned b, unsigned n){
    if (n == 0) return a;
    if (n == 1) return b;
    unsigned prev = a;
    unsigned curr = b;
    unsigned next;
    for (size_t i = 2; i <= n; ++i) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return next;
}
void Event::NextFloor() {
    system("cls");
    map->IncreaseFloor();
    Map newMap(Fib(Constants::STARTING_WIDTH[0], Constants::STARTING_WIDTH[1], map->GetFloor()),
               Fib(Constants::STARTING_HEIGHT[0], Constants::STARTING_HEIGHT[1], map->GetFloor()),
               Fib(Constants::STARTING_MONSTERS[0], Constants::STARTING_MONSTERS[1], map->GetFloor()), 
               Fib(Constants::STARTING_TREASURE[0], Constants::STARTING_TREASURE[1], map->GetFloor()), map->GetPlayer());
    newMap.GenerateMap();
    //maybe leakage later?
    //Map* oldMap = map;
    *map = newMap;
 
    //delete oldMap;
    map->GetPlayer()->AddXP(70 + map->GetFloor() * 10); // see if it is balanced
    std::ostringstream msg;
    msg << "Floor " << map->GetFloor() << " passed! " << map->GetPlayer()->GetName() << " got " << 70 + map->GetFloor() * 10 << " xp!";
    Alert(msg);
    map->SetPlayerX(0);
    map->SetPlayerY(0);
    map->GetRenderer().SetChunkX(0); // maybe problematic later
    map->GetRenderer().SetChunkY(0);
    map->RenderAll();
}
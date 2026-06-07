#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>   // min, max poradila ai - sorting
using namespace std;


int hracMaxHP, hracHP, hracUtok, hracMaxMana, hracMana;
int zlato = 0, levelHrace = 1, hracXP = 0;
int classaVolba = 1;   // 1=Paladin  2=Lovec  3=Mag  4=Warlockkl

// volani vsech funkci abzch na to pote neyapoměl
void navstivVesnici();
void souboj(int pocet, int monHP, int monAtk, bool jeBoss);
void soubojReckonus();
void zkontrolujLevelUp();
void zobrazStav();
void zobrazSchopnosti();

// stav hraace
void zobrazStav() {
    cout << "  HP: " << hracHP << "/" << hracMaxHP
         << " | Mana: " << hracMana << "/" << hracMaxMana
         << " | Utok: " << hracUtok
         << " | Zlato: " << zlato
         << " | Level: " << levelHrace
         << " | XP: " << hracXP << "/" << (levelHrace * 5) << "\n";
}


// schopnosti podle classy

void zobrazSchopnosti() {
    cout << "1) Zakladni utok (" << hracUtok << " dmg)\n";
    if (classaVolba == 1) {
        cout << "2) Uder svetlem  (1 dmg vsem, -2 mana)\n";
        cout << "3) Uzdraveni     (+1 HP, -1 mana)\n";
    } else if (classaVolba == 2) {
        cout << "2) Zamerena strela (" << (hracUtok * 2) << " dmg, -2 mana)\n";
        cout << "3) Prvni pomoc     (+2 HP, -2 mana)\n";
    } else if (classaVolba == 3) {
        cout << "2) Fireball   (" << (4 + hracUtok) << " dmg, -3 mana)\n";
        cout << "3) Leceni     (+3 HP, -3 mana)\n";
    } else {
        cout << "2) Shadow Bolt (" << (2 + hracUtok) << " dmg, -2 mana)\n";
        cout << "3) Drain Life  (" << (1 + hracUtok) << " dmg +2 HP, -3 mana)\n";
    }
    cout << "0) Vzdavam se\n";
}

// kontrola
void zkontrolujLevelUp() {
    while (hracXP >= levelHrace * 5) {
        hracXP -= levelHrace * 5;
        int staryMaxHP   = hracMaxHP;
        int staryUtok    = hracUtok;
        int staryMaxMana = hracMaxMana;
        levelHrace++;
        hracMaxHP   += 2;
        hracUtok    += 1;
        hracMaxMana += 1;
        cout << "\n========== NOVY LEVEL " << levelHrace << "! ==========\n";
        cout << "Max HP:   " << staryMaxHP   << " => " << hracMaxHP   << "\n";
        cout << "Utok:     " << staryUtok    << " => " << hracUtok    << "\n";
        cout << "Max Mana: " << staryMaxMana << " => " << hracMaxMana << "\n";
        cout << "==========================================\n";
    }
}

// snad fungujici souboj - potreba vyzkouset
void souboj(int monsterCount, int monsterHPMax, int monsterAtk, bool jeBoss) {
    vector<int> monHP(monsterCount, monsterHPMax);


    bool playerTurn = !jeBoss;

    cout << "\n=== SOUBOJ ZACINA ===\n";
    for (int i = 0; i < monsterCount; i++)
        cout << "  [" << (i + 1) << "] Monstrum | HP: " << monHP[i]
             << " | Utok: " << monsterAtk << "\n";

    while (true) {
        // konec boje kontrola
        if (hracHP <= 0) {
            cout << "\n*** PROHRAL JSI! GAME OVER :( ***\n";
            exit(0);
        }
        bool vseMrtva = true;
        for (int i = 0; i < monsterCount; i++)
            if (monHP[i] > 0) { vseMrtva = false; break; }

        if (vseMrtva) {
            cout << "\n*** VITEZSTVI! ***\n";
            int xp = monsterCount * 3 + (jeBoss ? 5 : 0);
            hracXP += xp;
            cout << "Ziskal jsi " << xp << " XP! (Celkem: "
                 << hracXP << "/" << (levelHrace * 5) << ")\n";
            if (jeBoss) {
                // Mini-boss ma zlato vzdy
                int drop = 10 + rand() % 11;
                zlato += drop;
                cout << "Mini-boss zanechal " << drop
                     << " zlata! (Celkem: " << zlato << ")\n";
            } else {
                // Monstra maji 50% sanci na zlato
                for (int i = 0; i < monsterCount; i++) {
                    if (rand() % 2 == 0) {
                        int drop = 1 + rand() % 5;
                        zlato += drop;
                        cout << "Monstrum " << (i + 1)
                             << " zanechalo " << drop << " zlata!\n";
                    }
                }
                cout << "Zlato celkem: " << zlato << "\n";
            }
            return;
        }

// co dela hrac
        if (playerTurn) {
            cout << "\n--- TVUJ TAH ---\n";
            zobrazStav();
            cout << "Ziva monstra:\n";
            for (int i = 0; i < monsterCount; i++)
                if (monHP[i] > 0)
                    cout << "  [" << (i + 1) << "] HP: " << monHP[i] << "\n";
            zobrazSchopnosti();
            cout << "Volba: ";
            int volba; cin >> volba;

            if (volba == 0) { cout << "Zbaběle jsi utekl...\n"; exit(0); }

            bool noTarget = false; // poradila ai bez toto to nefungovalo
            if (classaVolba == 1 && (volba == 2 || volba == 3)) noTarget = true;
            if (classaVolba == 2 && volba == 3)                 noTarget = true;
            if (classaVolba == 3 && volba == 3)                 noTarget = true;

            int cil = 0;
            if (!noTarget) {
                if (monsterCount > 1) {
                    cout << "Vyber cil (1-" << monsterCount << "): ";
                    cin >> cil;
                    cil--;
                    if (cil < 0 || cil >= monsterCount || monHP[cil] <= 0) {
                        cout << "Neplatny cil!\n"; continue;
                    }
                }

            }

            // akce
            if (volba == 1) {
                monHP[cil] = max(0, monHP[cil] - hracUtok);
                cout << "Zasahl jsi monstrum " << (cil + 1) << " za "
                     << hracUtok << " dmg! HP: " << monHP[cil] << "\n";

            } else if (volba == 2) {
                if (classaVolba == 1) {
                    // Paladin - Uder svtlem 1 dmg
                    if (hracMana < 2) { cout << "Malo many (potreba 2)!\n"; continue; }
                    hracMana -= 2;
                    cout << "Uder svetlem! 1 dmg vsem nepratelum!\n";
                    for (int i = 0; i < monsterCount; i++)
                        if (monHP[i] > 0) {
                            monHP[i] = max(0, monHP[i] - 1);
                            cout << "  Monstrum " << (i+1) << " HP: " << monHP[i] << "\n";
                        }
                } else if (classaVolba == 2) {
                    // Lovec - Zamerena strela
                    if (hracMana < 2) { cout << "Malo many (potreba 2)!\n"; continue; }
                    hracMana -= 2;
                    int dmg = hracUtok * 2;
                    monHP[cil] = max(0, monHP[cil] - dmg);
                    cout << "Zamerena strela za " << dmg << " dmg! "
                         << "Monstrum " << (cil+1) << " HP: " << monHP[cil] << "\n";
                } else if (classaVolba == 3) {
                    // Mag - Fireball
                    if (hracMana < 3) { cout << "Malo many (potreba 3)!\n"; continue; }
                    hracMana -= 3;
                    int dmg = 4 + hracUtok;
                    monHP[cil] = max(0, monHP[cil] - dmg);
                    cout << "Fireball za " << dmg << " dmg! "
                         << "Monstrum " << (cil+1) << " HP: " << monHP[cil] << "\n";
                } else {
                    // Warlock - Shadow Bolt
                    if (hracMana < 2) { cout << "Malo many (potreba 2)!\n"; continue; }
                    hracMana -= 2;
                    int dmg = 2 + hracUtok;
                    monHP[cil] = max(0, monHP[cil] - dmg);
                    cout << "Shadow Bolt za " << dmg << " dmg! "
                         << "Monstrum " << (cil+1) << " HP: " << monHP[cil] << "\n";
                }

            } else if (volba == 3) {
                if (classaVolba == 1) {
                    // Paladin - Uzdraveni (+5 HP)
                    if (hracMana < 1) { cout << "Malo many (potreba 1)!\n"; continue; }
                    if (hracHP >= hracMaxHP) { cout << "Jiz mas plne HP!\n"; continue; }
                    hracMana -= 1;
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Uzdraveni! HP: " << hracHP << "/" << hracMaxHP << "\n";
                } else if (classaVolba == 2) {
                    // Lovec - Prvni pomoc (+5 HP)
                    if (hracMana < 2) { cout << "Malo many (potreba 2)!\n"; continue; }
                    if (hracHP >= hracMaxHP) { cout << "Jiz mas plne HP!\n"; continue; }
                    hracMana -= 2;
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Prvni pomoc! HP: " << hracHP << "/" << hracMaxHP << "\n";
                } else if (classaVolba == 3) {
                    // Mag - Leceni (+5 HP)
                    if (hracMana < 3) { cout << "Malo many (potreba 3)!\n"; continue; }
                    if (hracHP >= hracMaxHP) { cout << "Jiz mas plne HP!\n"; continue; }
                    hracMana -= 3;
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Leceni! HP: " << hracHP << "/" << hracMaxHP << "\n";
                } else {
                    // Warlock - Drain Life (dmg + heal)
                    if (hracMana < 3) { cout << "Malo many (potreba 3)!\n"; continue; }
                    hracMana -= 3;
                    int dmg = 1 + hracUtok;
                    monHP[cil] = max(0, monHP[cil] - dmg);
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Drain Life! " << dmg << " dmg, +5 HP! "
                         << "Monstrum " << (cil+1) << " HP: " << monHP[cil]
                         << " | Tvoje HP: " << hracHP << "/" << hracMaxHP << "\n";
                }
            } else {
                cout << "Neplatna volba!\n"; continue;
            }

            playerTurn = false;

// tah monstra
        } else {
            cout << "\n--- TAH NEPRATEL ---\n";
            for (int i = 0; i < monsterCount; i++) {
                if (monHP[i] > 0) {
                    hracHP -= monsterAtk;
                    cout << "Monstrum " << (i + 1) << " utocilo za " << monsterAtk
                         << " dmg! Tvoje HP: " << max(0, hracHP)
                         << "/" << hracMaxHP << "\n";
                }
            }
            playerTurn = true;
        }

    }
}


void soubojReckonus() {
    const int RECK_MAX_HP   = 50;
    int       reckHP        = RECK_MAX_HP;
    const int RECK_BASE_ATK = 3;

    cout << "\n";
    cout << "+------------------------------------------+\n";
    cout << "|            BOSS:  RECKONUS               |\n";
    cout << "|   \"Cim vice krve, tim vice sily...\"      |\n";
    cout << "+------------------------------------------+\n\n";
    cout << "Reckonus HP: " << reckHP << "/" << RECK_MAX_HP
         << " | Zakladni utok: " << RECK_BASE_ATK << "\n";
    cout << "POZOR: Reckonus uderuje jako prvni!\n";

    bool playerTurn = false;   // Boss je na tahu prvy

    while (true) {
        // onec boje?
        if (reckHP <= 0) {
            cout << "\n+------------------------------------------+\n";
            cout << "|    RECKONUS PORAZEN! SLAVNE VITEZSTVI!   |\n";
            cout << "+------------------------------------------+\n";
            return;
        }
        if (hracHP <= 0) {
            cout << "\n*** RECKONUS TE ZNICIL! GAME OVER ***\n";
            exit(0);
        }

        // Vypocet aktualni faze boje - ai poradila - sorting
        float hpPct = (float)reckHP / (float)RECK_MAX_HP * 100.0f;

        int  currentAtk;
        int  odolnostFlat = 0;
        bool odolnostHalf = false;

        if      (hpPct > 80) { currentAtk = RECK_BASE_ATK * 1; odolnostFlat = 0; odolnostHalf = false; }
        else if (hpPct > 60) { currentAtk = RECK_BASE_ATK * 2; odolnostFlat = 1; odolnostHalf = false; }
        else if (hpPct > 40) { currentAtk = RECK_BASE_ATK * 3; odolnostFlat = 2; odolnostHalf = false; }
        else if (hpPct > 20) { currentAtk = RECK_BASE_ATK * 4; odolnostFlat = 3; odolnostHalf = false; }
        else                 { currentAtk = RECK_BASE_ATK * 5; odolnostFlat = 0; odolnostHalf = true;  }


        //  tAH REckonuse
        if (!playerTurn) {
            cout << "\n--- TAH RECKONUSE ---\n";
            cout << "Reckonus HP: " << reckHP << "/" << RECK_MAX_HP;
            if      (hpPct > 80) cout << "  [Faze 1 | Utok: "  << currentAtk << " | Odolnost: zadna]";
            else if (hpPct > 60) cout << "  [Faze 2 | Utok: "  << currentAtk << " | Odolnost: -1 dmg]";
            else if (hpPct > 40) cout << "  [Faze 3 | Utok: "  << currentAtk << " | Odolnost: -2 dmg]";
            else if (hpPct > 20) cout << "  [Faze 4 | Utok: "  << currentAtk << " | Odolnost: -3 dmg]";
            else                 cout << "  [FAZE 5! | Utok: " << currentAtk << " | Odolnost: 50%!]";
            cout << "\n";

            hracHP -= currentAtk;
            cout << "Reckonus te zasahl za " << currentAtk << " dmg!\n";
            cout << "Tvoje HP: " << max(0, hracHP) << "/" << hracMaxHP << "\n";

            // Heal Reckonuse jak HP hrace
            if (hracHP > 0) {
                float playerPct = (float)hracHP / (float)hracMaxHP * 100.0f;
                int heal = 0;

                if      (playerPct <= 5)  heal = 30;
                else if (playerPct <= 20) heal = 20;
                else if (playerPct <= 40) heal = 15;
                else if (playerPct <= 60) heal = 10;
                else if (playerPct <= 80) heal = 5;

                if (heal > 0) {
                    reckHP = min(reckHP + heal, RECK_MAX_HP);
                    cout << "Reckonus citi krev a uzdravuje se za " << heal
                         << " HP! (HP: " << reckHP << "/" << RECK_MAX_HP << ")\n";
                }
            }

            playerTurn = true;


        //  tah hrace proti Reckonusovi

        } else {
            cout << "\n--- TVUJ TAH ---\n";
            zobrazStav();
            cout << "Reckonus HP: " << reckHP << "/" << RECK_MAX_HP;
            if      (hpPct > 80) cout << "  [Odolnost: zadna]";
            else if (hpPct > 60) cout << "  [Odolnost: -1 dmg]";
            else if (hpPct > 40) cout << "  [Odolnost: -2 dmg]";
            else if (hpPct > 20) cout << "  [Odolnost: -3 dmg]";
            else                 cout << "  [Odolnost: 50% redukce!]";
            cout << "\n";
            zobrazSchopnosti();
            cout << "Volba: ";
            int volba; cin >> volba;

            if (volba == 0) { cout << "Utekl jsi pred Reckonusem...\n"; exit(0); }

            int  dmg     = 0;
            bool skipDmg = false;  // true = akce nedela dmg Reckonusovi

            if (volba == 1) {
                dmg = hracUtok;
                cout << "Zakladni utok za " << dmg << " dmg!\n";

            } else if (volba == 2) {
                if (classaVolba == 1) {
                    if (hracMana < 2) { cout << "Malo many!\n"; continue; }
                    hracMana -= 1; dmg = 8;
                    cout << "Uder svetlem za " << dmg << " dmg!\n";
                } else if (classaVolba == 2) {
                    if (hracMana < 2) { cout << "Malo many!\n"; continue; }
                    hracMana -= 1; dmg = hracUtok * 3;
                    cout << "Zamerena strela za " << dmg << " dmg!\n";
                } else if (classaVolba == 3) {
                    if (hracMana < 3) { cout << "Malo many!\n"; continue; }
                    hracMana -= 2; dmg = 10 + hracUtok;
                    cout << "Fireball za " << dmg << " dmg!\n";
                } else {
                    if (hracMana < 2) { cout << "Malo many!\n"; continue; }
                    hracMana -= 1; dmg = 12 + hracUtok;
                    cout << "Shadow Bolt za " << dmg << " dmg!\n";
                }

            } else if (volba == 3) {
                if (classaVolba == 1) {
                    if (hracMana < 1) { cout << "Malo many!\n"; continue; }
                    if (hracHP >= hracMaxHP) { cout << "Mas plne HP!\n"; continue; }
                    hracMana -= 1;
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Uzdraveni! HP: " << hracHP << "/" << hracMaxHP << "\n";
                    skipDmg = true;
                } else if (classaVolba == 2) {
                    if (hracMana < 2) { cout << "Malo many!\n"; continue; }
                    if (hracHP >= hracMaxHP) { cout << "Mas plne HP!\n"; continue; }
                    hracMana -= 2;
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Prvni pomoc! HP: " << hracHP << "/" << hracMaxHP << "\n";
                    skipDmg = true;
                } else if (classaVolba == 3) {
                    if (hracMana < 3) { cout << "Malo many!\n"; continue; }
                    if (hracHP >= hracMaxHP) { cout << "Mas plne HP!\n"; continue; }
                    hracMana -= 1;
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Leceni! HP: " << hracHP << "/" << hracMaxHP << "\n";
                    skipDmg = true;
                } else {
                    // Warlock - Drain Life
                    if (hracMana < 3) { cout << "Malo many!\n"; continue; }
                    hracMana -= 2;
                    dmg = 6 + hracUtok;
                    hracHP = min(hracHP + 5, hracMaxHP);
                    cout << "Drain Life! " << dmg << " dmg, +5 HP! "
                         << "HP: " << hracHP << "/" << hracMaxHP << "\n";
                }
            } else {
                cout << "Neplatna volba!\n"; continue;
            }

            // dani odolnosti a odpocteni dmg od Reckonuse - ai poradila
            if (!skipDmg && dmg > 0) {
                int finalDmg = dmg;
                if (odolnostHalf) {
                    finalDmg = max(1, finalDmg / 2);
                    cout << "Reckonusova odolnost! Dmg snizeno na polovinu -> "
                         << finalDmg << "\n";
                } else if (odolnostFlat > 0) {
                    finalDmg = max(0, finalDmg - odolnostFlat);
                    cout << "Reckonusova odolnost snizila dmg o " << odolnostFlat
                         << " -> " << finalDmg << "\n";
                }
                reckHP = max(0, reckHP - finalDmg);
                cout << "Zasahl jsi Reckonuse za " << finalDmg << " dmg! "
                     << "HP: " << reckHP << "/" << RECK_MAX_HP << "\n";
            }

            playerTurn = false;
        }

    }
}


void navstivVesnici() {
    cout << "\n+------------------------------+\n";
    cout << "|          VESNICE             |\n";
    cout << "+------------------------------+\n";
    while (true) {
        cout << "\nZlato: " << zlato
             << " | HP: " << hracHP << "/" << hracMaxHP << "\n";
        cout << "1) Lecivka - HP na max   (3 zlata)\n";
        cout << "2) Zvysit max HP +10      (5 zlata)\n";
        cout << "3) Zvysit max manu +30   (5 zlata)\n";
        cout << "4) Zvysit utok +5       (8 zlata)\n";
        cout << "0) Pokracovat\n";
        cout << "Volba: ";
        int volba; cin >> volba; // poradila ai na rovnou zapisovani do volby
        if (volba == 0) break;
        else if (volba == 1) {
            if (zlato >= 3) {
                zlato -= 3; hracHP = hracMaxHP;
                cout << "HP doplneny na " << hracHP << "!\n";
            } else cout << "Nemas dost zlata (potreba 3)!\n";
        } else if (volba == 2) {
            if (zlato >= 5) {
                zlato -= 5; hracMaxHP+=10;
                cout << "Max HP je ted " << hracMaxHP << "!\n";
            } else cout << "Nemas dost zlata (potreba 5)!\n";
        } else if (volba == 3) {
            if (zlato >= 5) {
                zlato -= 5; hracMaxMana+=30;
                cout << "Max Mana je ted " << hracMaxMana << "!\n";
            } else cout << "Nemas dost zlata (potreba 5)!\n";
        } else if (volba == 4) {
            if (zlato >= 8) {
                zlato -= 8; hracUtok+=8;
                cout << "Utok je ted " << hracUtok << "!\n";
            } else cout << "Nemas dost zlata (potreba 8)!\n";
        } else {
            cout << "Neplatna volba!\n";
        }
    }
}


int main() {
    srand(time(NULL));

    cout << R"(
              /\
             /  \
            |    |
          --:'''':--
            :'_' :
            _:"":\___
 ' '      ____.' :::     '._
. *=====<<=)           \    :
 .  '      '-'-'\_      /'._.'
                  \====:_ ""
                 .'     \\
                :       :
               /   :    \
              :   .      '.
              :  : :      :
              :__:-:__.;--'

DARK - LEGENDS OF THE DUNGEON

)";

    // vyber classy
    while (true) {
        cout << "\nVyberte si classu:\n";
        cout << "1) Paladin (HP 5, Utok 3, Mana 5)\n";
        cout << "2) Lovec   (HP 4, Utok 4, Mana 3)\n";
        cout << "3) Mag     (HP 3, Utok 2, Mana 7)\n";
        cout << "4) Warlock (HP 4, Utok 3, Mana 5)\n";
        cout << "Volba: ";
        cin >> classaVolba;

        if (classaVolba == 1) {
            hracMaxHP = 25; hracUtok = 7; hracMaxMana = 25;
            cout << "\nClass: Paladin\n";
            cout << "  Zivot: 5/5  |  Utok: 3  |  Mana: 5/5\n";
            cout << "Schopnosti:\n";
            cout << "  1) Zakladni uder  - 3 dmg\n";
            cout << "  2) Uder svetlem   - 1 dmg vsem nepratellum (-2 mana)\n";
            cout << "  3) Uzdraveni      - +5 HP (-1 mana)\n";
        } else if (classaVolba == 2) {
            hracMaxHP = 18; hracUtok = 4; hracMaxMana = 20;
            cout << "\nClass: Lovec\n";
            cout << "  Zivot: 4/4  |  Utok: 4  |  Mana: 3/3\n";
            cout << "Schopnosti:\n";
            cout << "  1) Zakladni uder    - 4 dmg\n";
            cout << "  2) Zamerena strela  - 8 dmg (-2 mana)\n";
            cout << "  3) Prvni pomoc      - +5 HP (-2 mana)\n";
        } else if (classaVolba == 3) {
            hracMaxHP = 15; hracUtok = 5; hracMaxMana = 40;
            cout << "\nClass: Mag\n";
            cout << "  Zivot: 3/3  |  Utok: 2  |  Mana: 7/7\n";
            cout << "Schopnosti:\n";
            cout << "  1) Zakladni uder - 2 dmg\n";
            cout << "  2) Fireball      - 6 dmg (-3 mana)\n";
            cout << "  3) Leceni        - +5 HP (-3 mana)\n";
        } else if (classaVolba == 4) {
            hracMaxHP = 20; hracUtok = 6; hracMaxMana = 25;
            cout << "\nClass: Warlock\n";
            cout << "  Zivot: 4/4  |  Utok: 3  |  Mana: 5/5\n";
            cout << "Schopnosti:\n";
            cout << "  1) Zakladni uder - 3 dmg\n";
            cout << "  2) Shadow Bolt   - 5 dmg (-2 mana)\n";
            cout << "  3) Drain Life    - 4 dmg +5 HP (-3 mana)\n";
        } else {
            cout << "Neplatna volba!\n";
            continue;
        }

        hracHP   = hracMaxHP;
        hracMana = hracMaxMana;
        cout << "\nPotvrdit vybir? (1 = Ano, 0 = Jina classa): ";
        int potvrzeni; cin >> potvrzeni;
        if (potvrzeni == 1) break;
    }

    cout << "\nDobrodruhu, tvoje quest zacina!\n";
    cout << "Vydej se do temnot a najdi sve destiny...\n\n";

    //  Mapa eventu od ai sam jsem nevedel jak na to
    vector<string> mapa = {
        "V",                       // Vesnice 1
        "M", "M", "2M", "MB",      // Zona 1
        "V",                       // Vesnice 2
        "M", "2M", "2M", "MB",     // Zona 2
        "V",                       // Vesnice 3
        "2M", "2M", "3M",          // Zona 3
        "V",                       // Vesnice 4
        "HB"                       // Hlavni boss
    };

    for (const string& event : mapa) {
        cout << "\n==========================================\n";

        if (event == "V") {
            navstivVesnici();

        } else if (event == "M") {
            cout << "! Potkal jsi MONSTRUM !\n";
            souboj(1, 10, 2, false);

        } else if (event == "2M") {
            cout << "!! Potkal jsi 2 MONSTRA !!\n";
            souboj(2, 8, 2, false);

        } else if (event == "3M") {
            cout << "!!! Potkal jsi 3 MONSTRA !!!\n";
            souboj(3, 6, 1, false);

        } else if (event == "MB") {
            cout << "!!! MINI-BOSS se priblizuje !!!\n";
            souboj(1, 20, 4, true);

        } else if (event == "HB") {
            cout << "!!!! HLAVNI BOSS - RECKONUS !!!!\n";
            soubojReckonus(); // art delala ai at to vypada pekne
            cout << "\n==========================================\n";
            cout << "  GRATULUJU HRDINO!\n";
            cout << "  Porazil jsi Reckonuse a zachranil kralovstvi!\n";
            cout << "  Zlaty Bludistak je tvuj navzdy!\n";
            cout << "==========================================\n";
            break;
        }

        // ontrola level-upu
        zkontrolujLevelUp();
    }

    return 0;
}
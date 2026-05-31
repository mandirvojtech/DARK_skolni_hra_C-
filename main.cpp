#include <iostream>
#include <ctime>
#include <vector> // pridani vektoru
#include <cstdlib> // nahodne generovani cisel
#include <ctime> // pridani casu pro nahodnost generovani
using namespace std;
// promene hrace
int hracmaxHP, hracHP, hracutok, hracmaxmana, hracmana;
int zlato = 0, levelhrace = 1, hracXP = 0;

// deklarace fuknci
void navstivVesnici();
void souboj(int pocet, int hp, int atk, bool jeBoss);

int main() {
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

██████╗  █████╗ ██████╗ ██╗  ██╗
██╔══██╗██╔══██╗██╔══██╗██║ ██╔╝
██║  ██║███████║██████╔╝█████╔╝
██║  ██║██╔══██║██╔══██╗██╔═██╗
██████╔╝██║  ██║██║  ██║██║  ██╗
╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝

         LEGENDS OF THE DUNGEON

)" << endl;

    srand(time(NULL)); // náhoda ve výběru

    // jak se vybere classa
    while (true) {
        cout << "Vyberte si postavu mlady pane:\n";
        cout << "1) Paladin (Zivot 5, Utok 3, Mana 5)\n";
        cout << "2) Lovec (Zivot 4. Utok 4, Mana 3)\n";
        cout << "3) Mag (Zivot 3, Utok 2, Mana 7) \n";
        cout << "4) Warlock (Zivot 4, Utok 3, Mana 5)\n";
        cout << "Volba: ";
        int volba; cin >> volba;
        if (volba == 1) {
            hracmaxHP = 5; hracutok = 3; hracmaxmana = 5;
            cout << "Class Paladin -> Zivot 5/5, Utok 3, Mana 5/5... \n";
            cout << "Schopnosti: Uder (3 dmg), Uder svetlem (1 vsem a -2 many), Uzdraveni (+1 HP a -1 mana) \n";
        }
        else if (volba == 2) {
            hracmaxHP = 4; hracutok = 4; hracmaxmana = 3;
            cout << "Class Lovec -> Zivot 4/4, Utok 4, Mana 3/3... \n";
            cout << "Schopnosti:  Zamerena strela (6 dmg, -2 mana), Salva (1 dmg, -2 mana), Prvni pomoc (+2 HP, -2 mana)\n";
        }
        else if (volba == 3) {
            hracmaxHP = 3; hracutok = 3; hracmaxmana = 7;
            cout << "Class Warlock. Zivot 4/4, Utok 3, Mana 5/5.\n";
            cout << "Schopnosti: Fireball (5 dmg, -3 mana), Storm (2 dmg , -2 mana), Leceni (+3 HP, -3 mana)\n";
        }
        else if (volba == 4) {
            hracmaxHP = 4; hracutok = 3; hracmaxmana = 2;
            cout << "Class Warlock. Zivot 4/4, Utok 3, Mana 5/5.\n";
            cout << "Schopnosti: Shadow bolt (4 dmg, -2 mana), Drain Life (3 dmg +3 HP, -3 mana)\n";
        }
        else {
            cout << "Neplatna volba :( \n";
            continue; // znamena preskoc interakci aby se smycka po spatnee volve ukoncila
        }
        hracHP = hracmaxHP;
        hracmana = hracmaxmana;
        cout << "Potrvrdti (1) nebo jimnak (0)? ";
        int jimnak; cin >> jimnak;
        if (jimnak == 1) break;
    }

    // Posloupnost podle toho jak to je v moodlu... lepší způsob mě nenapadl :(
    // použiju vektory jak mi ai poradila - je to pole textových hodnot a uchovává tu posloupnost jak chci je to také chytré pole xd
    vector<string> mapEvents = {
        "V","M","M","2M","MB","V","M","2M","2M","MB","V","2M","2M","3M","V","HB"
    };

    // ted bude smycka hry
    // event mi poradila ai na situace
    for (string event: mapEvents) {
        if (event == "V") {
            navstivVesnici(); // tu funkci nekdy napisu :)
        }
        else if (event == "M") {
            cout << "\n Souboj s monstrem \n";
            souboj(1, 10, 2, false); // podle funkce ktera je dole
        }
        else if (event == "2M") {
            cout << "\n Souboj s 2 monstry \n";
            souboj(2, 8, 1, false);
        }
        else if (event == "3M") {
            cout << "\n Souboj s 3 monstry \n";
            souboj(3, 6, 1, false);
        }
        else if (event == "MB") {
            cout << "\n Souboj s minibossem \n";
            souboj(1, 20, 4, true);
        }
        else if (event == "HB") {
            cout << "\n Souboj s final bossem\n";
            souboj(1, 30, 5, true);
            cout << "\n Souboj s final bossem ste vyhrali dostavate zlateho bludistaka\n";
            break;
        }
        // Kontrola po soubojich
        while (hracXP >= levelhrace * 5) {
            hracXP -= levelhrace * 5;
            levelhrace++;
            hracmaxHP++;
            hracutok++;
            hracmaxmana++;
            hracHP = hracmaxHP;
            hracmana = hracmaxmana;
            cout << "Novy level " << levelhrace;
            cout << "Max zivoty vracen! utok: " << hracutok << "\n";
        }
    }
    return 0;
}
void navstivVesnici() {
    cout << "\n ***** Vesnice ***** \n";
    while (true) {
        cout << "Zlato: " << zlato << "\n";
        cout << "1) Lecivka (doplni HP na max, 5 zlata)\n";
        cout << "2) Zvysit max HP +1 (10 zlata)\n";
        cout << "3) Zvysit max manu +1 (10 zlata)\n";
        cout << "4) Zvysit utok +1 (15 zlata)\n";
        cout << "0) Pokracovat\n";
        cout << "Tvoje volba: ";
        int volba; cin >> volba;
        if (volba == 0) break;
        if (volba == 1) {
            if(zlato >= 5) {
                zlato -= 5;
                hracHP = hracmaxHP;
                cout << "Zivot doplneny na: " << hracHP << "/" << hracmaxHP << ".\n";
            } else cout << "Nemas dost zlata.\n";
        }
        else if (volba == 2) {
            if(zlato>= 10) {
                zlato -= 10;
                hracmaxHP++;
                cout << "Max HP zvednuto na: " << hracmaxHP << ".\n";
            } else cout << "Nemas dost zlata.\n";
        }
        else if(volba == 3) {
            if(zlato >= 10) {
                zlato -= 10;
                hracmaxmana++;
                cout << "Max mana zvednuta na: " << hracmaxmana << ".\n";
            } else cout << "Nemas dost zlata.\n";
    }
        else if (volba == 4) {
            if(zlato >= 15) {
                zlato -= 15;
                hracutok++;
                cout << "Utok zvysen na: " << hracutok << ".\n";
            } else cout << "Nemas dost zlata.\n";
            }
        else {
            cout << "Neplatna volba \n";
        }
    }
}
// Souboj s monstry a hodnoty monster s radou od ai
void souboj(int monsterCount, int monsterHPMax, int monsterAttack, bool jeBoss) {
    vector<int> monsterHP(monsterCount, monsterHPMax);
    bool playerTurn = !jeBoss;
    while (true) {
        if (playerTurn) {
            // tady si hrac bude vybirat co chce udelat
            cout << "\nTahni - HP: " << hracHP << "/" << hracmana << "/" << hracmaxHP << ", Mana: " << hracmana << "/" << hracmaxmana << "\n";
            cout << "1) Zakladni utok (" << hracutok << "dmg)\n";
            cout << "2) Schopnost 1\n";
            cout << "3) Schopnost 2\n";
            cout << "4) Vzdavam se\n";
            cout << "Volba: ";
            int volba; cin >> volba;
            if (volba == 4) {
                cout << "Kapituloval si\n";
                exit(0);
            }
            int dmg = 0;
            if (volba == 1) {
                dmg = hracutok;
                // vyber jednoho monstra
                int cil = 0;
                if (monsterCount > 1) {
                    cout << "Cil je jake mostrum? (1-" << monsterCount << "): \n";
                    cil >> cil;
                    cil--;
                    if (cil < 0 || cil >= monsterCount || monsterHP[cil] <= 0) {
                        cout << "Neplatny cil... \n";
                        continue;
                    }
                }
                else cil = 0;
                monsterHP[cil] -= dmg;
                cout << "Uder za " << dmg << "monstru " << (cil + 1) << "\n";
            }
            else if (volba == 2) {} // omlouvam se pane uciteli ale nevim jak mam ty schopnosti udelat pro kazdou tridu
            else if (volba == 3) {}
            else {
                cout << "Neplatna volba :( \n";
                continue;
            }
        }
        else {
            // hra monster
            for (int i = 0; i < monsterCount; i++) {
                if (monsterHP[i] > 0) {
                    cout << "Monster" << i + 1 << " utok za: " << monsterAttack << "dmg \n";
                    hracHP -= monsterAttack;
                }
            }
        }
        bool mrtev = true;
        for (int i = 0; i < monsterCount; i++) {
            if (monsterHP[i] > 0) { mrtev = false; break; }
        }
        if (mrtev) {
            cout << "Vytezstvi gratuluju :)\n";
            if (jeBoss) {
                int drop = 10 + rand() % 11;
                zlato += drop;
                cout << "Po bossovi ti zbylo " << zlato << " zlata\n";
            }
        }
        break;
    }
    if(hracHP <= 0) {
        cout << "Prohral jsi :( \n";
        exit(0);
    }
    playerTurn = !playerTurn;
}
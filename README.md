# untitled1
# Terminálová RPG Hra v C++

**Popis:** Jedná se o textovou RPG hru napsanou v C++ (pouze s příkazy `goto`, bez OOP, spustitelná v příkazovém řádku **CMD**). Hráč si na začátku vybere třídu (např. Paladin, Lovec, Mág nebo Warlock), potvrdí volbu a následně prochází herní mapou složenou z vesnic a bojů s monstry a bossem. Hra obsahuje minimálně 16 různých monster, 2 mini-bossy, 1 hlavního bosse a 2 vesnice. Ve hře se přinejmenším jednou potkáš s bojem proti 1, 2 i 3 monsterům najednou.

**Hlavní vlastnosti hry:**
- **Výběr postavy:** Na začátku si vybereš jednu z předdefinovaných tříd. Statistika (životy, útok, mana) je pro každou třídu odlišná. Před potvrzením volby vidíš přehled stavu třídy i její schopnosti.
- **Souboje:** Boj je tahový. Proti běžným monsterům má první tah hráč, proti mini-bossům a bossovi mají tah první nepřátelé. Hra podporuje souboje s jedním, dvěma i třemi monstry současně. Cílem je zničit všechny nepřátele; pokud hráč ztratí všechny životy, hra končí prohrou. Po poražení hlavního bosse hráč vyhrává hru.
- **Zkušenosti a úrovně:** Za každé zabité monstrum/mini-bossa získáš zkušenosti a případně i zlato (monstra mají 50% šanci na nalezení zlata, mini-boss vždy). Po dosažení určitého počtu zkušeností postoupíš na další úroveň, která zvýší tvoje životy, manové body a útok. (Přesný systém úrovní je definován v kódu.)
- **Vesnice:** Vesnice slouží jako bezpečné útočiště. Tam si můžeš doplnit životy a manu nebo za utržené zlato vylepšit maximum životů, maximum many či útok. (Ceny jednotlivých akcí jsou pevně nastavené v kódu.)
- **Úsporné hodnoty:** Program kontroluje, aby životy nebo mana neklesly pod nulu a aby hráč měl dostatek zlata pro nákup. Nelze například dát hráči více životů, než jaké má stanovené maximum.
- **Textové rozhraní:** Hra komunikuje přes textový výstup. Hráč vybírá akce pomocí klávesnice zadáváním číselných voleb a potvrzuje stiskem ENTER.

## Jak hru spustit

1. Ujisti se, že máš nainstalovaný **C++ kompilátor** (např. GCC nebo MSVC). Kód lze kompilovat jako C++17.
2. Otevři příkazový řádek (CMD ve Windows).
3. Přejdi do složky s hlavním zdrojovým souborem hry (např. `main.cpp`).
4. Spusť kompilaci, například:
   ```bash
   g++ main.cpp -o hra.exe

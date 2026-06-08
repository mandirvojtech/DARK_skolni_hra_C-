# 🏰 DARK - Legends of the Dungeon

> Textové RPG vytvořené v jazyce C++, ve kterém se hráč vydává do temných dungeonů, bojuje s monstry, získává zkušenosti, nakupuje v obchodě a nakonec se utká s mocným bossem **Reckonusem**.

---

## 📖 O projektu

**DARK - Legends of the Dungeon** je konzolová RPG hra napsaná v C++, která využívá objektově jednodušší procedurální přístup.

Hráč si na začátku vybere jednu ze čtyř tříd a následně postupuje předem vytvořenou mapou plnou nepřátel, mini-bossů a vesnic.

Cílem hry je:

- ⚔️ Porazit všechny nepřátele
- 📈 Získávat zkušenosti a levelovat
- 💰 Sbírat zlato
- 🏘️ Vylepšovat postavu ve vesnicích
- 👑 Porazit finálního bosse Reckonuse

---

# 🎮 Herní třídy

## 🛡️ Paladin

Silný tank s vysokým zdravím.

### Schopnosti
| Schopnost | Efekt |
|------------|---------|
| Základní útok | Standardní poškození |
| Úder světlem | Poškození všech nepřátel |
| Uzdravení | Obnoví HP |

---

## 🏹 Lovec

Specialista na přesné útoky.

### Schopnosti
| Schopnost | Efekt |
|------------|---------|
| Základní útok | Standardní poškození |
| Zaměřená střela | Dvojnásobné poškození |
| První pomoc | Léčení |

---

## 🔥 Mag

Postava zaměřená na magické útoky.

### Schopnosti
| Schopnost | Efekt |
|------------|---------|
| Základní útok | Standardní poškození |
| Fireball | Silný magický útok |
| Léčení | Obnova zdraví |

---

## 🌑 Warlock

Temný mág využívající životní sílu nepřátel.

### Schopnosti
| Schopnost | Efekt |
|------------|---------|
| Základní útok | Standardní poškození |
| Shadow Bolt | Temná magie |
| Drain Life | Poškození + léčení |

---

# 🗺️ Herní mapa

Mapa je definována pomocí:

```cpp
vector<string> mapa
```

Každý symbol představuje událost:

| Symbol | Význam |
|----------|----------|
| V | Vesnice |
| M | 1 monstrum |
| 2M | 2 monstra |
| 3M | 3 monstra |
| MB | Mini-boss |
| HB | Hlavní boss |

Příklad:

```cpp
{
    "V",
    "M", "M", "2M", "MB",
    "V",
    "M", "2M", "2M", "MB",
    "V",
    "2M", "2M", "3M",
    "V",
    "HB"
};
```

---

# ⚔️ Soubojový systém

Hlavní souboje probíhají ve funkci:

```cpp
void souboj(...)
```

### Co systém umí

✅ Tahový souboj

✅ Více nepřátel najednou

✅ Výběr cíle

✅ Speciální schopnosti

✅ Spotřeba many

✅ Léčení

✅ Odměny za vítězství

✅ Drop zlata

✅ Získávání zkušeností

---

## Průběh boje

1. Hráč je na tahu
2. Vybere schopnost
3. Udělí poškození
4. Nepřátelé zaútočí
5. Cyklus se opakuje do smrti jedné strany

---

# 📈 Level systém

Levelování probíhá ve funkci:

```cpp
void zkontrolujLevelUp()
```

Potřebné XP:

```cpp
level * 5
```

Po získání levelu hráč dostane:

- ❤️ +2 Max HP
- ⚔️ +1 Attack
- 🔮 +1 Max Mana

---

# 💰 Ekonomika

Po vítězství mohou monstra zanechat zlato.

### Běžná monstra

- 50% šance na drop

```cpp
1 - 5 zlata
```

### Mini-boss

Garantovaný drop:

```cpp
10 - 20 zlata
```

---

# 🏘️ Vesnice

Vesnice slouží jako obchod a místo pro vylepšení postavy.

Funkce:

```cpp
void navstivVesnici()
```

---

## Dostupné upgrady

| Upgrade | Cena |
|----------|---------|
| Doplnění HP | 3 zlata |
| +10 Max HP | 5 zlata |
| +30 Mana | 5 zlata |
| +8 Attack | 8 zlata |

---

# 👑 Finální Boss - Reckonus

Nejtěžší protivník ve hře.

Souboj probíhá ve funkci:

```cpp
void soubojReckonus()
```

---

## Speciální mechaniky

### 🩸 Fázový systém

Boss sílí podle zbývajícího zdraví.

| HP | Fáze |
|------|------|
| 100-80% | Fáze 1 |
| 80-60% | Fáze 2 |
| 60-40% | Fáze 3 |
| 40-20% | Fáze 4 |
| 20-0% | Fáze 5 |

---

### 🛡️ Odolnost

V jednotlivých fázích získává:

- Redukci poškození
- Zvýšený útok
- 50% redukci poškození v poslední fázi

---

### ❤️ Regenerace

Čím méně HP má hráč, tím více se Reckonus léčí.

Příklad:

```cpp
Pokud má hráč méně než 5 % HP:
Reckonus se vyléčí o 30 HP.
```

---

# 🧠 Hlavní funkce programu

## `zobrazStav()`

Zobrazuje:

- HP
- Manu
- Útok
- Zlato
- Level
- XP

---

## `zobrazSchopnosti()`

Vypisuje schopnosti podle vybrané třídy.

---

## `souboj()`

Stará se o běžné souboje proti monstrům.

---

## `soubojReckonus()`

Speciální souboj s finálním bossem.

---

## `navstivVesnici()`

Obchod a vylepšování postavy.

---

## `zkontrolujLevelUp()`

Kontrola získaných zkušeností a levelování.

---

# 🧱 Použité knihovny

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
```

### Účel

| Knihovna | Použití |
|-----------|----------|
| iostream | Vstup a výstup |
| vector | Dynamická pole |
| cstdlib | Náhodná čísla |
| ctime | Seed pro rand() |
| algorithm | min() a max() |

---

# 🚀 Spuštění

## Kompilace

```bash
g++ main.cpp -o dungeon
```

## Spuštění

```bash
./dungeon
```

---

# 🎯 Budoucí vylepšení

- 🎒 Inventář
- 🧪 Lektvary
- ⚔️ Vybavení
- 🏹 Nové classy
- 🧟 Více nepřátel
- 🌍 Generovaná mapa
- 💾 Ukládání pozice
- 🎵 Zvuky
- 🎨 Barevný terminál

---

# 👨‍💻 Autor

Vytvořil **[Tvoje Jméno]**

Projekt vznikl jako studijní RPG hra v jazyce **C++** zaměřená na:

- Procedurální programování
- Práci s funkcemi
- Správu herních statistik
- Tahový soubojový systém
- Návrh RPG mechanik

---

⭐ Pokud se ti projekt líbí, dej repozitáři hvězdu!

# Mini-RPG-CPP-
This is a repo for modification for a mini rpg c++ project for BU Computer Science students.


# Mini RPG (C++) with a Browser Frontend

A turn-based console RPG written in C++, plus an optional localhost browser UI that runs the same program unchanged. The game is also a small showcase of C++ inheritance and polymorphism (see [OOP highlights](#oop-highlights)).

## Features

- 4 character classes (Fighter, Wizard, Cleric, Thief) and 4 races (Dragonborn, Demi-God, Vampire, Human)
- Turn-based combat: attack, cast spells, use items, or run
- Random monster encounters, XP and leveling
- A shop, **Merlin's Surplus**, at map position (2, 4) where you can buy and sell
- Two-slot inventory with potions and attack items
- Browser UI with a game log, HP/MP bars, enemy card, map and clickable buttons

## Requirements

- A C++ compiler with C++17 support (`g++` 7 or newer)
- [Node.js](https://nodejs.org) 16 or newer, only for the browser UI (the console game doesn't need it)

## Build

From the repository root:

```bash
g++ -std=c++17 src/main.cpp src/Player.cpp src/Monster.cpp src/Map.cpp src/Store.cpp src/Item.cpp -o rpg
```

Or, if you have npm: `npm run build`. On Windows this creates `rpg.exe`.

## Run

**In the browser (recommended for demos):**

```bash
node frontend/server.js
```

Then open http://localhost:3000. Use `node frontend/server.js path/to/rpg` if your executable lives elsewhere, or set the `PORT` environment variable to change the port.

**In the console:**

```bash
./rpg          # Windows: .\rpg.exe
```

## How to play

1. Enter a name, then pick a class and a race.
2. On the main menu you can **Move**, **Rest**, open your **Inventory**, **View Stats** or **Quit**.
3. Move around the map with North, East, South and West. Walk to **(2, 4)** to enter the shop. Moving can trigger a monster fight.
4. In combat choose Attack, Cast Spell, Use Item or Run. Winning gives XP and gold, and enough XP levels you up.
5. Resting restores HP and MP, but there is a 1-in-4 chance of being ambushed.

## Project structure

```
src/        C++ game source (Player, Monster, Map, Store, Item, helpers)
frontend/   Node server (server.js) and browser UI (index.html)
```

## OOP highlights

- `Item` is an abstract base class with pure virtual `use()` and `clone()` functions and a virtual destructor.
- `PotionItem` and `AttackItem` inherit from `Item` and `override` both functions.
- `Player` calls `mInventory[slot]->use(...)` without knowing the item's real type. This is runtime polymorphism.
- `clone()` copies the real derived object from a base pointer, so buying an item never slices it.
- The `Player` and `Store` classes manage heap-allocated items with `new` and `delete`.

## How the browser frontend works

`frontend/server.js` starts the compiled game as a child process. Its output is streamed to the browser, and button clicks are sent back as keyboard input. The page reads the game's own prompts (like `[1] Move || [2] Rest`) and turns them into buttons, so the C++ code needs no changes. The side panel updates HP and MP every turn, and the other stats when you open **View Stats**.

## Troubleshooting

- **`g++` is not recognized:** install a C++ compiler (MSYS2 or WinLibs on Windows, `build-essential` on Linux, Xcode command line tools on macOS) and reopen your terminal.
- **`no match for operator=` errors:** you are compiling with an old standard. Use `-std=c++17`.
- **Port 3000 is in use:** run with `PORT=3001 node frontend/server.js` (Windows PowerShell: `$env:PORT=3001; node frontend/server.js`).
- **Browser shows an error about starting the game:** build the game first and run the server from the repository root.

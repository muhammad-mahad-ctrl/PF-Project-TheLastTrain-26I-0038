# The Last Train

CS-1002: Programming Fundamentals (AI & DS) — Semester Project
Name: Muhammad Mahad | Roll No: 26I-0038 | Solo project

## About the game

The Last Train is a text-based rescue game written in C++17. The player explores a building with 5 floors and 4 rooms on each floor. The goal is to rescue an injured passenger and a stranded cat, find the three hidden clue digits (4, 2, 7), open the cabinet with the code to get the Train Key, and board the train at F5-R2 before Energy or Time reaches 0.

Neighbouring rooms on a floor are joined by a door, a window, a locked door (needs the Master Key) or a solid wall. Stairs join the first rooms of neighbouring floors, Lift 1 joins rooms 2 and 3 of Floors 1 and 2, and Lift 2 joins the fourth rooms of Floors 2, 4 and 5.

## Project structure

- `include/` – header files
- `src/core/` – source files
- `data/` – `building.txt` (map), `initial-state.txt` (starting values) and `test.txt` (sample run)
- `out/` – `savegame.txt` and `game_summary.txt`
- `docs/` – architecture diagram, flowchart and console screenshot

The project is purely procedural: no structs or classes, only `int`, `char`, `bool` and arrays.

## Build

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/core/*.cpp -o last_train
```

The program compiles with no warnings.

## Run

Run the game from the project folder, because the file paths are relative (`data/...`, `out/...`).

```bash
./last_train          # Linux / Mac / PowerShell: .\last_train
```

1. The game asks whether to load a saved game: `1` loads `out/savegame.txt`, `0` starts a new game. If `1` is chosen and no valid save exists, a new game starts.
2. For a new game, enter the starting floor and room.
3. Each turn, choose an action from the menu:

| Choice | Action         | What it asks for                         |
|--------|----------------|------------------------------------------|
| 1      | Move           | target floor and room                    |
| 2      | Inspect        | nothing; reveals clue digits in the room |
| 3      | Collect        | the item symbol, e.g. `<`                |
| 4      | Use            | the item symbol, e.g. `%`                |
| 5      | Unlock cabinet | the three code digits (in F5-R1)         |
| 6      | Save           | nothing; writes `out/savegame.txt`       |
| 7 	 | Quit           | nothing                                  |

To win: rescue the passenger (use the Medical Kit `%` in F4-R1), secure the cat (use the Cat Carrier `@` in F3-R3), unlock the cabinet with 427 in F5-R1, then go to F5-R2 and use the Train Key `^`.

## Costs

| Action 			| Energy | Time |
|-------------------------------|--------|------|
| Move (door, stairs) 		| -2     | -1   |
| Move (window)                 | -3 	 | -2   |
| Lift journey                  | -4 	 | -3   |
| Inspect, collect, use, unlock | -1 	 | -1   |

Energy Pack +25 Energy, Emergency Toolkit +15 Energy, Observation Token +15 Time. Energy and Time stay between 0 and 100. The player starts with Energy 100 and Time 50. A rejected action costs nothing.

## Sample run and determinism check

`data/test.txt` is a winning run that starts in F4-R2. The game reads its commands instead of the keyboard. Expected result: Victory, Score 480, Energy 15, Time 8.

To check that the game is deterministic, play the same run twice and compare the results. In Command Prompt (cmd), from the project folder:

```
last_train.exe < data\test.txt > out\run1.txt
copy out\game_summary.txt out\summary1.txt
last_train.exe < data\test.txt > out\run2.txt
copy out\game_summary.txt out\summary2.txt
fc out\run1.txt out\run2.txt
fc out\summary1.txt out\summary2.txt
```

Both `fc` commands print `FC: no differences encountered`, so the same commands always give the same output and the same summary. On Linux/Mac, use `./last_train < data/test.txt > out/run1.txt` and compare with `diff`.

## Output files

- `out/savegame.txt` – the saved game, overwritten each time the player saves
- `out/game_summary.txt` – the final report (result, score, remaining Energy and Time, objective checklist), written when the game ends

## Choices and assumptions

- The map has two Energy Packs in F1-R4, as instructed by the TA. Collecting one removes only that pack.
- Clue digits are not shown in the room list; they appear only after Inspect.
- Energy Packs, the Toolkit and the Token are used up immediately when picked up. The normal pickup cost applies first.
- The Train Key is tracked as an objective, not as an inventory item.
- Lift 2 works after the Fuse is installed in F3-R4 and the Lift Pass is collected. Before that, the Emergency Access Card gives 3 trips.
- There is no direct door between rooms 2 and 3 on Floors 1 and 2; the player crosses using Lift 1.
- Because Time starts at 50, the game can only be won from six starting rooms: F4-R1, F4-R2 and the four rooms on Floor 5.
- The sample run scores 480, not 520, because the Fuse and Lift Pass (+40) do not fit in the available Time.
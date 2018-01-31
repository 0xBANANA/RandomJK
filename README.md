# OpenJK - now with even moar randomness

This version of OpenJK has some additional single player features implemented:

* The missions of each tier will be randomized on every start of the single player game (after creating a character)
* The randomized level pattern will be saved to a file called `pattern_file.txt` which you can edit and share
* Random patterns will be restored from the last sessions as long as you don't start a new run of the story mode.
* Randomized force levels: For each level, you can edit the file `randomizerOptions.json` to specify the minimum force level required for each force power and level.

# You can haz randomization too!

* Download the latest release from the releases tab. Please never just git clone, compile and complain about the game not running.
* Place all the files of the specific archive you downloaded into your existing OpenJK folder - Keep backups in case you need them. The `.json` and `.txt` files have to be in the same folder as your JKA executable.

## Troubleshooting on first runs

For initial troubleshooting, please verify that OpenJK runs without using my modifications. If this is true and it however fails with the binaries and configuration files supplied in the latest release of this project, feel free to file an issue on GitHub.

## Basic usage

On initial SP game start, after creating your character, your first randomized mission pattern will be generated in the same folder your JKA executables are. This gets randomized each time you start a new story playthrough.

To use you own pattern file without it being overwritten on SP game startup, edit the pattern file as you please, e.g.:

```
t1_surprise t2_trip t2_dpred t1_danger t1_sour t3_hevil t2_wedge t3_stamp t3_byss t2_rogue t2_rancor t3_rift t1_fatal t1_rail t3_bounty
```

After that, add `NO_OVERWRITE` at the start of the line:

```
NO_OVERWRITE t1_surprise t2_trip t2_dpred t1_danger t1_sour t3_hevil t2_wedge t3_stamp t3_byss t2_rogue t2_rancor t3_rift t1_fatal t1_rail t3_bounty
```

For additional configuration, check out the following sections and the supplied configuration file `randomizerOptions.json`.

# Seed values

You can specify the seed value you want for your next run in `randomizerOptions.json` via `PRNGSeed`. Please only use unsigned values (>= 0). If you want the randomizer to generate a new seed value for each start of JKA and for each start of a new story playthrough, just leave it at `0`. Each time a new seed value gets calculated/used, it will be written to `seedValue.txt`, so it's possible to recover the state of a previous run using the configuration file. Also, a file called `seedLog.txt` will be created to map seed dates to seed values of previous runs in case your `seedValue.txt` file gets overwritten by accident.

In case you define your own seed, you don't need to provide the `pattern_file.txt` because this file will be re-generated using the user supplied PRNG seed.

Note: Only the seed value of the `.json` configuration file will be used, don't edit `seedValue.txt` and expect it to be used.

# Force randomization
In the file `randomizerOptions.json` you can choose the following force modes with `forceRandomizationMode`:
- `0`: Progression mode: As you complete missions, you gain additional force points. You can spend exactly one force point for each mission - the rest will be randomized, including the core force powers like force jump. As you progress, the maximum points that can be spent randomly increase. However, RNG decides whether all points actually will be used.
- `1`: Chaos mode: Every force power will be randomized, you can gain from zero to the maximum amount of force points. One user selectable force power can be chosen freely.

Additionally, the required force *levels* can be selected for each map and force power in the settings file. In there you can select the level from 0 to 3. This value will be guaranteed to be satisfied.

# Weapons randomization

This works comparable to the force randomization. The values in `randomizerOptions.json` range from 0 (weapon not required) to 1 (weapon required). The amount of ammo will always be random for weapons you didn't choose via the selection menu.

In the file `randomizerOptions.json` you can choose the weapon modes with `weaponRandomizationMode`:
- `0`: You can choose two shootable weapons and one throwable weapon from a random pool
- `1`: Chaos mode: Like mode `0` but on top of that, random weapons will be added

# Randomization sets

For each map, it's possible to define multiple possible minimal force/weapon sets, e.g.

```
    "t1_surprise_0": {
      "FP_JUMP": 0,
      "FP_PUSH": 0,
      "FP_PULL": 1,
      "FP_SABERTHROW": 0,
      "FP_SABER_DEFENSE": 0,
      "FP_SABER_OFFENSE": 0,
      "FP_SENSE": 0,
      "FP_SPEED": 0,
      "FP_HEAL": 0,
      "FP_MINDTRICK": 0,
      "FP_GRIP": 0,
      "FP_LIGHTNING": 0,
      "FP_RAGE": 0,
      "FP_PROTECT": 0,
      "FP_ABSORB": 0,
      "FP_DRAIN": 0
    },

    "t1_surprise_1": {
      "FP_JUMP": 1,
      "FP_PUSH": 1,
      "FP_PULL": 0,
      "FP_SABERTHROW": 0,
      "FP_SABER_DEFENSE": 0,
      "FP_SABER_OFFENSE": 0,
      "FP_SENSE": 0,
      "FP_SPEED": 0,
      "FP_HEAL": 0,
      "FP_MINDTRICK": 0,
      "FP_GRIP": 0,
      "FP_LIGHTNING": 0,
      "FP_RAGE": 0,
      "FP_PROTECT": 0,
      "FP_ABSORB": 0,
      "FP_DRAIN": 0
    },
```

For each possible strategy, one set can be defined. The used set will be determined randomly at runtime.
Currently, there is a limit of 100 possible sets per map, which should be enough <:

If you add a set, make sure you use a unique index in the range of 0-99.

# Additional Notes
* Considering map loading: If you load from a previous save game, **NO** randomization will be performed as the savegame will be treated as is. Quicksaves will be treated the same.
* Please note that for yavin1b, the force powers currently won't get randomized. Starting from yavin2, randomizations kicks in.
* It's intended that sometimes no information on force powers and/or available weapons will be displayed upon map loading. This simplifies randomization at some points in the game.

# Building

Please refer to the original notes on the build process of OpenJK. I added an option to the CMake project which allows you to pass the installation directory with an environment variable. Check the `CMakeList` files for additional info.

**After compiling this project, copy the files of the** `files` **folder into the same directory your JKA executable lives in. If you don't do this, the game will crash as intended.** Please refer to the troubleshooting sections in case of problems.

# Credits
Thanks go out to Raven, the JACoders and the JKA speedrunning community.
Additionally, to nlohmann for the great JSON library.

~ Joe Bananas (@JoeBananas1337_)

# Todos
* Clean this project from MP files and folders
* Add CVar for `NO_OVERWRITE`, `forceRandomizationMode` and `weaponRandomizationMode`
* Make suggestions :)

--------------------------
OpenJK is an effort by the JACoders group to maintain and improve the game engines on which the Jedi Academy (JA) and Jedi Outcast (JO) games run on, while maintaining *full backwards compatibility* with the existing games. *This project does not attempt to rebalance or otherwise modify core gameplay*.

Our aims are to:
* Improve the stability of the engine by fixing bugs and improving performance.
* Provide a clean base from which new JO and JA code modifications can be made.
* Make available this engine to more operating systems. To date, we have ports on Linux and OS X.

Currently, the most stable portion of this project is the Jedi Academy multiplayer code, with the single player code in a reasonable state.

Rough support for Jedi Outcast single player is also available, however this should be considered heavily work in progress. This is not currently actively worked on or tested. OpenJK does not have Jedi Outcast multiplayer support.

Please use discretion when making issue requests on GitHub. The [JKHub sub-forum](http://jkhub.org/forum/51-discussion/) is a better place for support queries, discussions, and feature requests.

[![IRC](https://img.shields.io/badge/irc-%23JACoders-brightgreen.svg)](http://unic0rn.github.io/tiramisu/jacoders/)
[![Forum](https://img.shields.io/badge/forum-JKHub.org%20OpenJK-brightgreen.svg)](http://jkhub.org/forum/51-discussion/)

[![Coverity Scan Build Status](https://scan.coverity.com/projects/1153/badge.svg)](https://scan.coverity.com/projects/1153)

| Windows | OSX | Linux x86 | Linux x64 |
|---------|-----|-----------|-----------|
| [![Windows Build Status](http://jk.xd.cm/badge.svg?builder=windows)](http://jk.xd.cm/builders/windows) | [ ![OSX Build Status](http://jk.xd.cm/badge.svg?builder=osx)](http://jk.xd.cm/builders/osx) | [ ![Linux x86 Build Status](http://jk.xd.cm/badge.svg?builder=linux)](http://jk.xd.cm/builders/linux) | [ ![Linux x64 Build Status](http://jk.xd.cm/badge.svg?builder=linux-64)](http://jk.xd.cm/builders/linux-64) |

## License

[![License](https://img.shields.io/github/license/JACoders/OpenJK.svg)](https://github.com/JACoders/OpenJK/blob/master/LICENSE.txt)

OpenJK is licensed under GPLv2 as free software. You are free to use, modify and redistribute OpenJK following the terms in LICENSE.txt.

## For players

To install OpenJK, you will first need Jedi Academy installed. If you don't already own the game you can buy it from online stores such as [Steam](http://store.steampowered.com/app/6020/), [Amazon](http://www.amazon.com/Star-Wars-Jedi-Knight-Academy-Pc/dp/B0000A2MCN) or [GOG](https://www.gog.com/game/star_wars_jedi_knight_jedi_academy).

Installing and running OpenJK:

1. [Download the latest build](http://builds.openjk.org) for your operating system.
2. Extract the contents of the file into the Jedi Academy `GameData/` folder. For Steam users, this will be in `<Steam Folder>/steamapps/common/Jedi Academy/GameData`.
3. Run `openjk.x86.exe` (Windows), `openjk.i386` (Linux 32-bit), `openjk.x86_64` (Linux 64-bit) or the `OpenJK` application (OS X), depending on your operating system.

**Linux Instructions**

If you do not have a windows partition and need to download the game base.

1. Download  and Install SteamCMD [SteamCMD](https://developer.valvesoftware.com/wiki/SteamCMD#Linux) .
2. Set the download path using steamCMD, force_install_dir <path> .
3. Using SteamCMD Set the platform to windows to download any windows game on steam. @sSteamCmdForcePlatformType "windows"
4. Using SteamCMD download the game,  app_update 6020.
5. [Download the latest build](http://builds.openjk.org) for your operating system.
6. Extract the contents of the file into the Jedi Academy `GameData/` folder. For Steam users, this will be in `<Steam Folder>/steamapps/common/Jedi Academy/GameData`.


**OS X Instructions**

If you have the Mac App Store Version of Jedi Academy, follow these steps to get OpenJK runnning under OS X:

1. Install [Homebrew](http://brew.sh/) if you don't have it.
2. Open the Terminal app, and enter the command `brew install sdl2`.
3. Extract the contents of the OpenJK DMG ([Download the latest build](http://builds.openjk.org)) into the game directory `/Applications/Star Wars Jedi Knight: Jedi Academy.app/Contents/`
4. Run `openJK.app` or `openJK SP.app`
5. Savegames, Config Files and Log Files are stored in `/Users/<USER>/Library/Application Support/OpenJK/`


## For Developers

### Building OpenJK
* [Compilation guide](https://github.com/JACoders/OpenJK/wiki/Compilation-guide)
* [Debugging guide](https://github.com/JACoders/OpenJK/wiki/Debugging)

### Contributing to OpenJK
* [Fork](https://github.com/JACoders/OpenJK/fork) the project on GitHub
* Create a new branch and make your changes
* Send a [pull request](https://help.github.com/articles/creating-a-pull-request) to upstream (JACoders/OpenJK)

### Using OpenJK as a base for a new mod
* [Fork](https://github.com/JACoders/OpenJK/fork) the project on GitHub
* Change the GAMEVERSION define in codemp/game/g_local.h from "OpenJK" to your project name
* If you make a nice change, please consider back-porting to upstream via pull request as described above. This is so everyone benefits without having to reinvent the wheel for every project.

### Deciphering buildbot's output
* Pick the build from the operating system builder you're interested in at the [builders](https://jk.xd.cm/builders) page.
* Click on stdio for the Steps to see the command executed and the result.
* The command is at the very top, the output starts below.

## Maintainers (in alphabetical order)

* Ensiform
* Razish
* Xycaleth

## Significant contributors (in alphabetical order)

* eezstreet
* exidl
* ImperatorPrime
* mrwonko
* redsaurus
* Scooper
* Sil
* smcv

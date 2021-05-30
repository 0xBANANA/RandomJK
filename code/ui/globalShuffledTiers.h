//
// Created by ps on 18.01.18.
//

#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <iostream>
#include <fstream>
#include <regex>
#include <random>
#include <ctime>
#include <iomanip>

#include "../qcommon/qcommon.h"

#include "../game/weapons.h"
#include "../game/statindex.h"


#include "json.h"
#include "ui_local.h"

using json = nlohmann::json;

#ifndef OPENJK_GLOBALSHUFFLEDTIERS_H
#define OPENJK_GLOBALSHUFFLEDTIERS_H

// to track if we already randomized the weapons because
// this can happen mutliple times for one run
// true: already randomized -- do nothing
// false: randomize
extern bool randomizeWeaponsDoOnce;

// to track if we already randomized the force powers because
// this can happen mutliple times for one run
// true: already randomized -- do nothing
// false: randomize
extern bool randomizeForcePowersDoOnce;

// 0 = Progression mode - 1 additional power per completed mission
// 1 = Chaos mode aka yolo mode
extern int forceRandomizationMode;

// 0 = PRNG using the provided seed
// 1 = Randomization using secure random numbers
static int RNGMode;

// 0 = Choose weapons from a random pool
// 1 = Chaos mode aka yolo mode
extern int weaponRandomizationMode;

// How many levels the player has completed --> amount of force points available
extern int TIER_MISSIONS_COMPLETED;

// mersienne twister --> PRNG
extern std::mt19937 _rng;
extern bool _seeded;

// to track if we quickloaded or did a full load
// --> don't randomize for quickloads
extern bool WAS_QUICKLOAD;

extern int CURRENT_KNOWN_FORCE_POWERS;
extern std::vector<int> CURRENT_FORCE_LEVELS;

// if the user specified pattern file is allowed to be overwritten
// on SP game startup
extern bool OVERWRITE_ALLOWED;

// the filename of the pattern file to save
static std::string PATTERN_FILE_NAME = "pattern_file.txt";
static std::string MISSION_TEMPLATE_FILE_NAME = "mission_template_file.txt";
static std::string WEAPON_TEMPLATE_FILE_NAME = "weapon_template_file.txt";
static std::string SETTINGS_FILE_NAME = "randomizerOptions.json";
static std::string SEED_FILE_NAME = "seedValue.txt";
static std::string SEED_LOG_FILE_NAME = "seedLog.txt";


// if you edit these, change them in `cg_info.cpp` too!
static std::string KNOWN_FORCE_POWERS_FILE_NAME = "tmp_knownForcePowers.txt";
static std::string FORCE_POWER_LEVELS_FILE_NAME = "tmp_forcePowerLevels.txt";

// JSON object storing the user supplied settings via `SETTINGS_FILE_NAME`
extern json SETTINGS_JSON;

// name of the loaded map
extern std::string UPCOMING_MAP_NAME;

// to make e.g. force jump level 3 more unlikely
// 75 percent
static int _forceJumpOneProbability = 75;
static int _forceJumpTwoProbability = 15;
static int _forceJumpThreeProbability = 5;

// the maps we will use to randomize tiers
static std::vector<std::string> TIER_MAP_NAMES = {
    "t1_sour",
    "t1_surprise",
    "t1_fatal",
    "t1_danger",
    "t1_rail",
    "t2_rancor",
    "t2_trip",
    "t2_wedge",
    "t2_rogue",
    "t2_dpred",
    "t3_rift",
    "t3_stamp",
    "t3_hevil",
    "t3_byss",
    "t3_bounty"
};

// every SP map
static std::vector<std::string> ALL_MAP_NAMES = {
    "t1_sour",
    "t1_surprise",
    "t1_fatal",
    "t1_danger",
    "t1_rail",
    "t2_rancor",
    "t2_trip",
    "t2_wedge",
    "t2_rogue",
    "t2_dpred",
    "t3_rift",
    "t3_stamp",
    "t3_hevil",
    "t3_byss",
    "t3_bounty",
    "yavin1",
    "yavin1b",
    "yavin2",
    "hoth2",
    "hoth3",
    "taspir1",
    "taspir2",
    "kor1",
    "kor2",
    "vjun1",
    "vjun2",
    "vjun3"
};

// every randomized SP map
// e.g. no hoth3 is included to preserve weapons at some points
static std::vector<std::string> RANDOMIZED_MAP_NAMES = {
        "t1_sour",
        "t1_surprise",
        "t1_fatal",
        "t1_danger",
        "t1_rail",
        "t2_rancor",
        "t2_trip",
        "t2_wedge",
        "t2_rogue",
        "t2_dpred",
        "t3_rift",
        "t3_stamp",
        "t3_hevil",
        "t3_byss",
        "t3_bounty",
        "yavin1b",
        "yavin2",
        "hoth2",
        "taspir1",
        "kor1",
        "vjun1",
};

static std::map<std::string, std::string> MAP_TITLE_NAME_CONVERSION = {
    {"t1_sour", "tatooine"},
    {"t1_surprise", "tatooine"},
    {"t1_danger", "blenjeel"},
    {"t1_rail", "corellia"},
    {"t1_fatal", "bakura"},

    {"t2_wedge", "krildor"},
    {"t2_trip", "zonju"},
    {"t2_rogue", "coruscant"},
    {"t2_dpred", "dosuun"},
    {"t2_rancor", "narkreeta"},

    {"t3_rift", "chandrila"},
    {"t3_stamp", "tanaab"},
    {"t3_hevil", "yalara"},
    {"t3_byss", "byss"},
    {"t3_bounty", "ordman"},
};

const static std::vector<int> FORCE_POWERS_ALL = {
    FP_HEAL,
    FP_LEVITATION,
    FP_SPEED,
    FP_PUSH,
    FP_PULL,
    FP_TELEPATHY,
    FP_GRIP,
    FP_LIGHTNING,
    FP_SABERTHROW,
    FP_SABER_DEFENSE,
    FP_SABER_OFFENSE,
    FP_RAGE,
    FP_PROTECT,
    FP_ABSORB,
    FP_DRAIN,
    FP_SEE
};

const static std::vector<int> FORCE_POWERS_PLAYER = {
    FP_HEAL,
    FP_TELEPATHY,
    FP_GRIP,
    FP_LIGHTNING,
    FP_RAGE,
    FP_PROTECT,
    FP_ABSORB,
    FP_DRAIN,
};

const static std::vector<int> FORCE_POWERS_CORE = {
    FP_LEVITATION,
    FP_PUSH,
    FP_PULL,
    FP_SABERTHROW,
    FP_SABER_DEFENSE,
    FP_SABER_OFFENSE,
    FP_SEE,
    FP_SPEED,
};


const static std::vector<int> ALL_WEAPONS = {
    WP_SABER,

    WP_BLASTER_PISTOL,
    WP_BLASTER,
    WP_DISRUPTOR,
    WP_BOWCASTER,
    WP_REPEATER,
    WP_DEMP2,
    WP_FLECHETTE,
    WP_ROCKET_LAUNCHER,
    WP_THERMAL,
    WP_TRIP_MINE,
    WP_DET_PACK,
    WP_CONCUSSION,

    //extras
    WP_MELEE,
    WP_STUN_BATON,
};

// contains the shuffled tier menus which will be hot-patched at runtime
extern std::string SHUFFLED_TIER_1;
extern std::string SHUFFLED_TIER_2;
extern std::string SHUFFLED_TIER_3;

// the modified menu to choose weapons
static std::string CURRENT_WEAPON_MENU;

// the modified main menu
extern std::string MAIN_MENU;

// template for the generated menu files
// will be set on startup
static std::string MISSION_TMPLT;

// template for the generated weapon menu files
// will be set on startup
extern std::string WEAPON_TMPLT;


static std::string tierMenuNamePlaceholder = "ingameMissionSelectX";

// will be replaced with e.g. t1_surprise
static std::vector<std::string> PLACEHOLDERS_MAP_NAMES = {
    "XX_MAP1_XX",
    "XX_MAP2_XX",
    "XX_MAP3_XX",
    "XX_MAP4_XX",
    "XX_MAP5_XX",
};

// will be replaced with e.g. T1_SURPRISE
static std::vector<std::string> PLACEHOLDERS_TITLES_BRIEFINGS = {
    "XX_MAP1_TB_XX",
    "XX_MAP2_TB_XX",
    "XX_MAP3_TB_XX",
    "XX_MAP4_TB_XX",
    "XX_MAP5_TB_XX",
};

// will be replaced with e.g. tatooine
static std::vector<std::string> PLACEHOLDERS_LONG_NAMES_LOWER = {
    "XX_MAP_1_LONG_NAME_LOWER_XX",
    "XX_MAP_2_LONG_NAME_LOWER_XX",
    "XX_MAP_3_LONG_NAME_LOWER_XX",
    "XX_MAP_4_LONG_NAME_LOWER_XX",
    "XX_MAP_5_LONG_NAME_LOWER_XX",
};


// will be replaced with e.g. TATOOINE
// used for setitemtext planet_name @MENUS_...
static std::vector<std::string> PLACEHOLDERS_LONG_NAMES_UPPER = {
    "XX_MAP_1_LONG_NAME_UPPER_XX",
    "XX_MAP_2_LONG_NAME_UPPER_XX",
    "XX_MAP_3_LONG_NAME_UPPER_XX",
    "XX_MAP_4_LONG_NAME_UPPER_XX",
    "XX_MAP_5_LONG_NAME_UPPER_XX",
};

// transform long lowercase names to long uppercase names (see the special cases with "_")
static std::map<std::string, std::string> MAP_ITEMTEXT_NAMES = {
    {"tatooine", "TATOOINE"},
    {"blenjeel", "BLENJEEL"},
    {"corellia", "CORELLIA"},
    {"bakura", "BAKURA"},

    {"krildor", "KRIL_DOR"},
    {"zonju", "ZONJU_V"},
    {"coruscant", "CORUSCANT"},
    {"dosuun", "DOSUUN"},
    {"narkreeta", "NAR_KREETA"},

    {"chandrila", "CHANDRILA"},
    {"tanaab", "TANAAB"},
    {"yalara", "YALARA"},
    {"byss", "BYSS"},
    {"ordman", "ORD_MANTELL"},
};


// to generate random weapon select menus
// all shootable weapons
static std::vector<std::string> PLACEHOLDERS_WEAPON_SELECT_PEWPEW = {
    "XX_WEAPON_PLACEHOLDER_1_XX",
    "XX_WEAPON_PLACEHOLDER_2_XX",
    "XX_WEAPON_PLACEHOLDER_3_XX",
    "XX_WEAPON_PLACEHOLDER_4_XX",
    "XX_WEAPON_PLACEHOLDER_5_XX",
    "XX_WEAPON_PLACEHOLDER_6_XX",
    "XX_WEAPON_PLACEHOLDER_7_XX",
    "XX_WEAPON_PLACEHOLDER_8_XX",
};

// all throwable weapons
static std::vector<std::string> PLACEHOLDERS_WEAPON_SELECT_THROW = {
    "XX_WEAPON_PLACEHOLDER_9_XX",
    "XX_WEAPON_PLACEHOLDER_10_XX",
    "XX_WEAPON_PLACEHOLDER_11_XX",
};

static void INIT_PRNG() {

    unsigned int seed = SETTINGS_JSON.at("PRNGSeed");

    if (seed == 0) {
        // get seed and write it to a file
        auto time = std::time(nullptr);
        seed = time;

        // write `seedValue.txt`
        std::ofstream seedValueFile;
        seedValueFile.open(SEED_FILE_NAME);
        seedValueFile << std::to_string(seed);
        seedValueFile.close();

        // append to `seedLog.txt`
        auto tm = *std::localtime(&time);

        std::ofstream seedLogFile;
        seedLogFile.open(SEED_LOG_FILE_NAME, std::ios_base::app);
        seedLogFile << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        seedLogFile << ": " << std::to_string(seed) << std::endl;
        seedLogFile.close();
    }

    _rng = std::mt19937(seed);
    _seeded = true;
}

// from <= x <= to (--> inclusive)
static int GET_RANDOM(int from, int to) {
    assert(_seeded);
    // define the range
    std::uniform_int_distribution<> distr(from, to);

    return distr(_rng);
}

// inclusive max
static int GET_RANDOM_MAX(int max) {
    assert(_seeded);
    // define the range
    std::uniform_int_distribution<> distr(0, max);

    return distr(_rng);
}

static std::string _getMenuFileFromTier(std::vector<std::string> tier, int tierIndex) {

    assert(tierIndex >= 1 && tierIndex <= 3);

    // initialize the menu string with the template
    std::string menu_result = MISSION_TMPLT;

    // set the correct menu name for the current tier
    size_t start_pos = 0;

    std::string currentTierMenuName;
    if (tierIndex == 1) {
        currentTierMenuName = "ingameMissionSelect1";
    }
    else if (tierIndex == 2) {

        currentTierMenuName = "ingameMissionSelect2";
    }
    else {

        currentTierMenuName = "ingameMissionSelect3";
    }

    while ((start_pos = menu_result.find(tierMenuNamePlaceholder, start_pos)) != std::string::npos) {
        menu_result.replace(start_pos, tierMenuNamePlaceholder.length(), currentTierMenuName);
        start_pos += currentTierMenuName.length();
    }

    // Just use a fixed value here - the asserts of the caller have checked for possible errors anyway
    for (int i = 0; i < 5; i++) {

        // map names
        size_t start_pos = 0;
        // Replace e.g. XX_MAP1_XX with t1_sour
        while ((start_pos = menu_result.find(PLACEHOLDERS_MAP_NAMES[i], start_pos)) != std::string::npos) {
            menu_result.replace(start_pos, PLACEHOLDERS_MAP_NAMES[i].length(), tier[i]);
            start_pos += tier[i].length();
        }

        // title and briefing placeholders
        start_pos = 0;
        while ((start_pos = menu_result.find(PLACEHOLDERS_TITLES_BRIEFINGS[i], start_pos)) != std::string::npos) {

            // convert mapname to uppercase
            std::string mapNameUpper = tier[i];
            std::transform(mapNameUpper.begin(), mapNameUpper.end(), mapNameUpper.begin(), ::toupper);

            // of course the briefing title for t3_stamp is called T3_STAMPEDE :D
            if (mapNameUpper == "T3_STAMP") {
                mapNameUpper = "T3_STAMPEDE";
            }

            // Replace e.g. XX_MAP1_TB_XX with T1_SOUR
            menu_result.replace(start_pos, PLACEHOLDERS_TITLES_BRIEFINGS[i].length(), mapNameUpper);
            start_pos += mapNameUpper.length();
        }

        // long names lower
        start_pos = 0;

        // to track how many times the placeholder has been replaced because for t1_rail we have to inject
        // a different string the first time it will be replaced :S
        int timesReplaced = 0;
        // Replace e.g. XX_MAP_1_LONG_NAME_LOWER_XX with tatooine
        while ((start_pos = menu_result.find(PLACEHOLDERS_LONG_NAMES_LOWER[i], start_pos)) != std::string::npos) {

            if (tier[i] == "t1_rail" && timesReplaced == 0) {
                menu_result.replace(start_pos, PLACEHOLDERS_LONG_NAMES_LOWER[i].length(), "core");
                start_pos += 4;
                timesReplaced++;
            }
            else {
                menu_result.replace(start_pos, PLACEHOLDERS_LONG_NAMES_LOWER[i].length(), MAP_TITLE_NAME_CONVERSION[tier[i]]);
                start_pos += tier[i].length();
                timesReplaced++;
            }


        }

        // long names upper
        start_pos = 0;
        // Replace e.g. XX_MAP_1_LONG_NAME_UPPER_XX with TATOOINE
        while ((start_pos = menu_result.find(PLACEHOLDERS_LONG_NAMES_UPPER[i], start_pos)) != std::string::npos) {

            // e.g. get long name of t2_wedge --> krildor
            std::string longNameLower = MAP_TITLE_NAME_CONVERSION[tier[i]];
            // krildor --> KRIL_DOR
            std::string longNameUpper = MAP_ITEMTEXT_NAMES[longNameLower];

            menu_result.replace(start_pos, PLACEHOLDERS_LONG_NAMES_UPPER[i].length(), longNameUpper);
            start_pos += tier[i].length();
        }
    }

    return menu_result;
}

// generate the .menu files using the template - quick and dirty implementation in header file <:
static void generateShuffledMenusFromTiers(std::vector<std::string> t1, std::vector<std::string> t2, std::vector<std::string> t3) {

    assert(PLACEHOLDERS_MAP_NAMES.size() == 5);
    assert(PLACEHOLDERS_TITLES_BRIEFINGS.size() == 5);
    assert(PLACEHOLDERS_TITLES_BRIEFINGS.size() == PLACEHOLDERS_TITLES_BRIEFINGS.size());
    assert(PLACEHOLDERS_MAP_NAMES.size() == t1.size());
    assert(PLACEHOLDERS_MAP_NAMES.size() == t2.size());
    assert(PLACEHOLDERS_MAP_NAMES.size() == t3.size());


    SHUFFLED_TIER_1 = _getMenuFileFromTier(t1, 1);
    SHUFFLED_TIER_2 = _getMenuFileFromTier(t2, 2);
    SHUFFLED_TIER_3 = _getMenuFileFromTier(t3, 3);

    assert(SHUFFLED_TIER_1.length() > 0);
    assert(SHUFFLED_TIER_2.length() > 0);
    assert(SHUFFLED_TIER_3.length() > 0);
}

// e.g. get either t1_surprise_0 or t1_surprise_1 force configuration
static json getRandomSetForMap(std::string parentKey, std::string mapname) {

    // constant value for now
    int setsPerMap = 100;

    json parentJSON = SETTINGS_JSON.at(parentKey);

    std::vector<json> sets;

    for(int i = 0; i < setsPerMap; i++) {
        std::string mapSetName = mapname + "_" + std::to_string(i);
        if (parentJSON.find(mapSetName) != parentJSON.end()) {
            sets.push_back(parentJSON.at(mapSetName));
        }
    }

    // return a random set
    assert(sets.size() > 0);
    return sets[GET_RANDOM_MAX(sets.size()-1)];

}

// Helper method to set force powers with error checking
static void _setRandomForcePower(playerState_t* pState, json forcePowersUpcomingLevel, int FP_enumType, std::string FP_string) {

    int newLevel = forcePowersUpcomingLevel.at(FP_string);
    // if we need to modify it
    if (pState->forcePowerLevel[FP_enumType] < newLevel) {

        if (newLevel < 0) { newLevel = 0; }
        if (newLevel > 3) { newLevel = 3; }

        pState->forcePowerLevel[FP_enumType] = newLevel;
    }

    // always learn the force power if points > 0
    if (newLevel > 0) {
        pState->forcePowersKnown |= (1 << FP_enumType);
    }
}

// write the current force configuration to file and cvars
// to display it on the loading screen (if possible)
static void _updateForceData(playerState_t *pState) {

    CURRENT_KNOWN_FORCE_POWERS = pState->forcePowersKnown;

    CURRENT_FORCE_LEVELS.clear();
    for (int i = 0; i < FORCE_POWERS_ALL.size(); i++) {
        CURRENT_FORCE_LEVELS.push_back(pState->forcePowerLevel[i]);
    }

    char buf[3000];
    DC->getCVarString("playersave", buf, sizeof(buf));
    std::string playersaveString(buf);

    std::stringstream ps_ss(playersaveString);
    std::istream_iterator<std::string> ps_begin(ps_ss);
    std::istream_iterator<std::string> ps_end;
    std::vector<std::string> splittedVar(ps_begin, ps_end);

    std::string newState = "";
    for (int i = 0; i < splittedVar.size(); i++) {

        if (i == 10) {
            newState += std::to_string(pState->forcePowersKnown) + " ";
        }

        else {
            newState += splittedVar[i] + " ";
        }

    }

    Cvar_Set( sCVARNAME_PLAYERSAVE, newState.c_str() );

    // write to file to let jagame pick it up
    std::ofstream forcePowersKnownFile;
    forcePowersKnownFile.open(KNOWN_FORCE_POWERS_FILE_NAME);
    forcePowersKnownFile << std::to_string(pState->forcePowersKnown);
    forcePowersKnownFile.close();

    std::string resultString = "";
    if (CURRENT_FORCE_LEVELS.size() == 16) {
        // e.g. " 0 1 0 1 3 0 0 0 0 0 0 0 0 0 0 3"
        for (int i = 0; i < FORCE_POWERS_ALL.size(); i++) {
            resultString += std::to_string(pState->forcePowerLevel[i]) + " ";
        }
        Cvar_Set( "playerfplvl", resultString.c_str() );

        // write to file to let jagame pick it up
        std::ofstream forcePowerLevelsFile;
        forcePowerLevelsFile.open(FORCE_POWER_LEVELS_FILE_NAME);
        forcePowerLevelsFile << resultString;
        forcePowerLevelsFile.close();
    }
}

static double getProb(int fp, int lvl) {

    std::string lvlstr = "LVL1";
    switch (lvl) {
    case 1:
        lvlstr = "LVL1";
        break;
    case 2:
        lvlstr = "LVL2";
        break;
    case 3:
        lvlstr = "LVL3";

    default:
        break;
    }

    std::string fpstr = "FP_JUMP";
    switch (fp) {
    case FP_LEVITATION:
        fpstr = "FP_JUMP";
        break;
    case FP_PUSH:
        fpstr = "FP_PUSH";
        break;
    case FP_PULL:
        fpstr = "FP_PULL";
        break;
    case FP_SABERTHROW:
        fpstr = "FP_SABERTHROW";
        break;
    case FP_SABER_DEFENSE:
        fpstr = "FP_SABER_DEFENSE";
        break;
    case FP_SABER_OFFENSE:
        fpstr = "FP_SABER_OFFENSE";
        break;
    case FP_SEE:
        fpstr = "FP_SENSE";
        break;
    case FP_SPEED:
        fpstr = "FP_SPEED";
        break;
    case FP_HEAL:
        fpstr = "FP_HEAL";
        break;
    case FP_TELEPATHY:
        fpstr = "FP_MINDTRICK";
        break;
    case FP_GRIP:
        fpstr = "FP_GRIP";
        break;
    case FP_LIGHTNING:
        fpstr = "FP_LIGHTNING";
        break;
    case FP_RAGE:
        fpstr = "FP_RAGE";
        break;
    case FP_PROTECT:
        fpstr = "FP_PROTECT";
        break;
    case FP_ABSORB:
        fpstr = "FP_ABSORB";
        break;
    case FP_DRAIN:
        fpstr = "FP_DRAIN";
        break;

    default:
        break;
    }

    return SETTINGS_JSON.at("probability").at(fpstr).at(lvlstr);
}

// returns the known force powers
static void randomizeForcePowers(playerState_t* pState, std::string mapname = "") {

    // if the optional parameter is not specified, use the (hopefully) previously set global variable instead
    if (mapname.length() == 0) { mapname = UPCOMING_MAP_NAME; }

    // has to be a valid mapname
    if (std::find(ALL_MAP_NAMES.begin(), ALL_MAP_NAMES.end(), mapname) == ALL_MAP_NAMES.end()) {
        return;
    }

    // only check user specified mandatory force powers for e.g. hoth3 --> keep old force powers
    bool preserveForcePowers = false;

    // it's a valid mapname but not a randomized one --> don't randomize and only check required force powers
    if (std::find(RANDOMIZED_MAP_NAMES.begin(), RANDOMIZED_MAP_NAMES.end(), mapname) == RANDOMIZED_MAP_NAMES.end()) {
        preserveForcePowers = true;
    }

    if(!preserveForcePowers) {
        // get amount of missions completed
        // check how many missions we have completed
        char completedMapsString[2048];
        ui.Cvar_VariableStringBuffer("tiers_complete", completedMapsString, sizeof(completedMapsString));

        // split it by spaces
        std::stringstream ss(completedMapsString);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> completedMapsVector(begin, end);

        TIER_MISSIONS_COMPLETED = 0;
        for (auto cm : completedMapsVector) {
            if (std::find(TIER_MAP_NAMES.begin(), TIER_MAP_NAMES.end(), cm) != TIER_MAP_NAMES.end()) {
                TIER_MISSIONS_COMPLETED++;
            }
        }

        // core powers - player can't choose these
        std::vector<int> fps_core_shuffled = FORCE_POWERS_CORE;
        std::shuffle(fps_core_shuffled.begin(), fps_core_shuffled.end(), _rng);

        // the force powers the player can choose
        std::vector<int> fps_player_shuffled = FORCE_POWERS_PLAYER;
        std::shuffle(fps_player_shuffled.begin(), fps_player_shuffled.end(), _rng);

        // reset the force powers to zero first
        for (auto fp : FORCE_POWERS_ALL) {
            pState->forcePowersKnown &= ~( 1 << fp );
            pState->forcePowerLevel[fp] = 0;
        }

        forceRandomizationMode = SETTINGS_JSON.at("forceRandomizationMode");

        // only two modes for now
        if (forceRandomizationMode < 0) { forceRandomizationMode = 0; }
        if (forceRandomizationMode > 1) { forceRandomizationMode = 0; }

        // progression mode
        if (forceRandomizationMode == 0) {
            int playerPointsToSpend = TIER_MISSIONS_COMPLETED > 0 ? TIER_MISSIONS_COMPLETED : 0;

            int corePointsToSpend = 0;
            if (TIER_MISSIONS_COMPLETED < 5) { corePointsToSpend = fps_core_shuffled.size(); }
            if (TIER_MISSIONS_COMPLETED >= 5 && TIER_MISSIONS_COMPLETED < 10) { corePointsToSpend = fps_core_shuffled.size() * 2; }
            if (TIER_MISSIONS_COMPLETED >= 10) { corePointsToSpend = fps_core_shuffled.size() *  3; }

            // core
            for (auto fp : fps_core_shuffled) {

                // finished
                if (corePointsToSpend <= 0) { break; }

                int randomLevel = 0;
                int randNo = GET_RANDOM(0, 100);

                if (randNo <= (getProb(fp, 1))) {
                    randomLevel = 1;
                }

                if (randNo > (getProb(fp, 1))) {
                    randomLevel = 2;
                }

                if (randomLevel > (getProb(fp, 1) + getProb(fp, 2))) {
                    randomLevel = 3;
                }

                corePointsToSpend -= randomLevel;

                pState->forcePowerLevel[fp] = randomLevel;

                // enable or disable the force power
                if (randomLevel > 0) {
                    pState->forcePowersKnown |= (1 << fp);
                }

                    // disable of level is zero
                else {
                    pState->forcePowersKnown &= ~( 1 << fp );
                }
            }

            // player
            for (auto fp : fps_player_shuffled) {

                // finished
                if (playerPointsToSpend <= 0) { break; }

                int randomLevel = 0;
                int randNo = GET_RANDOM(0, 100);

                if (randNo <= (getProb(fp, 1))) {
                    randomLevel = 1;
                }

                if (randNo > (getProb(fp, 1))) {
                    randomLevel = 2;
                }

                if (randomLevel > (getProb(fp, 1) + getProb(fp, 2))) {
                    randomLevel = 3;
                }
                playerPointsToSpend -= randomLevel;

                pState->forcePowerLevel[fp] = randomLevel;

                // enable or disable the force power
                if (randomLevel > 0) {
                    pState->forcePowersKnown |= (1 << fp);
                }

                    // disable of level is zero
                else {
                    pState->forcePowersKnown &= ~( 1 << fp );
                }
            }

        }

        // chaos mode
        if (forceRandomizationMode == 1) {
            // allocate random core powers first
            for (auto fp : fps_core_shuffled) {

                if (GET_RANDOM_MAX(100) > 60) { continue; }

                int randomLevel = 0;
                int randNo = GET_RANDOM(0, 100);

                if (randNo <= (getProb(fp, 1))) {
                    randomLevel = 1;
                }

                if (randNo > (getProb(fp, 1))) {
                    randomLevel = 2;
                }

                if (randomLevel > (getProb(fp, 1) + getProb(fp, 2))) {
                    randomLevel = 3;
                }

                pState->forcePowerLevel[fp] = randomLevel;

                // enable or disable the force power
                if (randomLevel > 0) {
                    pState->forcePowersKnown |= (1 << fp);
                }

                    // disable of level is zero
                else {
                    pState->forcePowersKnown &= ~( 1 << fp );
                }
            }

            // allocate random force powers for the player powers
            // Max points to spend so we don't soft block
            auto maxPoints_bkp = ((fps_player_shuffled.size() * 3) - 1);

            // don't use all possible points all the time
            auto maxPoints = Q_min((maxPoints_bkp - (GET_RANDOM(0, maxPoints_bkp)) + 8), maxPoints_bkp);

            for (auto fp : fps_player_shuffled) {
                if (maxPoints == 0) { break; }

                int randomLevel = 0;
                int randNo = GET_RANDOM(0, 100);

                if (randNo <= (getProb(fp, 1))) {
                    randomLevel = 1;
                }

                if (randNo > (getProb(fp, 1))) {
                    randomLevel = 2;
                }

                if (randomLevel > (getProb(fp, 1) + getProb(fp, 2))) {
                    randomLevel = 3;
                }

                maxPoints -= randomLevel;

                pState->forcePowerLevel[fp] = randomLevel;

                // enable or disable the force power
                if (randomLevel > 0) {
                    pState->forcePowersKnown |= (1 << fp);
                }

                    // disable if level is zero
                else {
                    pState->forcePowersKnown &= ~( 1 << fp );
                }

            }

        }
    }


    // assure all user specified force levels are OK
    // if its a valid mapname, not like t1_inter
    if (std::find(ALL_MAP_NAMES.begin(), ALL_MAP_NAMES.end(), mapname) != ALL_MAP_NAMES.end()) {

        json forcePowersUpcomingLevel = getRandomSetForMap("forcePowers", mapname);

        // for each force power
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_LEVITATION, "FP_JUMP");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_PUSH, "FP_PUSH");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_PULL, "FP_PULL");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_SABERTHROW, "FP_SABERTHROW");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_SABER_DEFENSE, "FP_SABER_DEFENSE");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_SABER_OFFENSE, "FP_SABER_OFFENSE");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_SEE, "FP_SENSE");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_SPEED, "FP_SPEED");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_HEAL, "FP_HEAL");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_TELEPATHY, "FP_MINDTRICK");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_GRIP, "FP_GRIP");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_LIGHTNING, "FP_LIGHTNING");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_RAGE, "FP_RAGE");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_PROTECT, "FP_PROTECT");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_ABSORB, "FP_ABSORB");
        _setRandomForcePower(pState, forcePowersUpcomingLevel, FP_DRAIN, "FP_DRAIN");
    }

    // re-check all if at least one point is unused -- avoid soft block
    int scoreEnd = 0;
    for (auto fp : FORCE_POWERS_PLAYER) {
        int lvl = pState->forcePowerLevel[fp];
        scoreEnd += lvl;
    }

    // if blocked
    if (scoreEnd == (FORCE_POWERS_PLAYER.size()) * 3) {
        // remove random point from player force level
        auto randomFP = FORCE_POWERS_PLAYER[GET_RANDOM(0, FORCE_POWERS_PLAYER.size() - 1)];
        pState->forcePowerLevel[randomFP] = pState->forcePowerLevel[randomFP] - 1;
    }

    _updateForceData(pState);

    // debugging
    /*std::cout << "RND_FP:" << std::endl;
    std::cout << "KNOWN " << pState->forcePowersKnown << std::endl;
    std::cout << "FP_HEAL " << pState->forcePowerLevel[FP_HEAL] << std::endl;
    std::cout << "FP_LEVITATION " << pState->forcePowerLevel[FP_LEVITATION] << std::endl;
    std::cout << "FP_SPEED " << pState->forcePowerLevel[FP_SPEED] << std::endl;
    std::cout << "FP_PUSH " << pState->forcePowerLevel[FP_PUSH] << std::endl;
    std::cout << "FP_PULL " << pState->forcePowerLevel[FP_PULL] << std::endl;
    std::cout << "FP_TELEPATHY " << pState->forcePowerLevel[FP_TELEPATHY] << std::endl;
    std::cout << "FP_GRIP " << pState->forcePowerLevel[FP_GRIP] << std::endl;
    std::cout << "FP_LIGHTNING " << pState->forcePowerLevel[FP_LIGHTNING] << std::endl;
    std::cout << "FP_SABERTHROW " << pState->forcePowerLevel[FP_SABERTHROW] << std::endl;
    std::cout << "FP_SABER_DEFENSE " << pState->forcePowerLevel[FP_SABER_DEFENSE] << std::endl;
    std::cout << "FP_SABER_OFFENSE " << pState->forcePowerLevel[FP_SABER_OFFENSE] << std::endl;
    std::cout << "FP_RAGE " << pState->forcePowerLevel[FP_RAGE] << std::endl;
    std::cout << "FP_PROTECT " << pState->forcePowerLevel[FP_PROTECT] << std::endl;
    std::cout << "FP_ABSORB " << pState->forcePowerLevel[FP_ABSORB] << std::endl;
    std::cout << "FP_DRAIN " << pState->forcePowerLevel[FP_DRAIN] << std::endl;
    std::cout << "FP_SEE " << pState->forcePowerLevel[FP_SEE] << std::endl;*/

}

// Helper method to set weapons with error checking
static void _setRandomWeapon(playerState_t* pState, json weaponsUpcomingLevel, int WP_enumType, const std::string WP_string) {

    int setting = weaponsUpcomingLevel.at(WP_string);
    if (setting < 0) { setting = 0; }
    if (setting > 1) { setting = 0; }
    // apply the setting with OR
    // if it was 1 it will remain 1
    // if it was 0 it will be 1
    pState->stats[ STAT_WEAPONS ] |= ( setting << WP_enumType );

    // ammo should be already applied
}

static void randomizeWeapons(playerState_t* pState, std::string mapname = "") {

    // if the optional parameter is not specified, use the (hopefully) previously set global variable instead
    if (mapname.length() == 0) { mapname = UPCOMING_MAP_NAME; }

    // has to be a valid mapname
    if (std::find(ALL_MAP_NAMES.begin(), ALL_MAP_NAMES.end(), mapname) == ALL_MAP_NAMES.end()) {
        return;
    }

    // only check user specified mandatory weapons for e.g. hoth3 --> keep old weapons
    bool preserveWeapons = false;

    // it's a valid mapname but not a randomized one --> don't randomize and only check required weapons
    if (std::find(RANDOMIZED_MAP_NAMES.begin(), RANDOMIZED_MAP_NAMES.end(), mapname) == RANDOMIZED_MAP_NAMES.end()) {
        preserveWeapons = true;
    }

    if(!preserveWeapons) {
        // Clear out any weapons for the player
        pState->stats[ STAT_WEAPONS ] = 0;
        pState->weapon = WP_NONE;

        weaponRandomizationMode = SETTINGS_JSON.at("weaponRandomizationMode");

        if (weaponRandomizationMode == 0) {


            // Give random ammo
            for (auto i = 0; i < AMMO_MAX; i++) {

                // don't get like 500 rockets
                if (i == AMMO_ROCKETS || i == AMMO_EMPLACED || i == AMMO_THERMAL || i == AMMO_TRIPMINE || i == AMMO_DETPACK) {
                    pState->ammo[i] = GET_RANDOM(0, 20);
                }
                else {
                    pState->ammo[i] = GET_RANDOM(1, GET_RANDOM(100, 500));
                }
            }
        }

        // chaos mode
        if (weaponRandomizationMode == 1) {
            // get random amount of weapons
            // this doesn't mean 3 added weapons max - e.g. there's a chance WP_SABER gets picked again
            // with no effect in the end
            for (int i = 0; i < GET_RANDOM(1, 3); i++) {

                if (GET_RANDOM_MAX(100) > 70) { continue; }

                auto randomWeapon = ALL_WEAPONS[GET_RANDOM(0, ALL_WEAPONS.size() - 1)];

                if (randomWeapon < WP_NUM_WEAPONS)
                {
                    pState->stats[ STAT_WEAPONS ] |= ( 1 << randomWeapon );

                }
            }

            // Give random ammo
            for (auto i = 0; i < AMMO_MAX; i++) {

                // dont get like 500 rockets
                if (i == AMMO_ROCKETS || i == AMMO_EMPLACED || i == AMMO_THERMAL || i == AMMO_TRIPMINE || i == AMMO_DETPACK) {
                    pState->ammo[i] = GET_RANDOM(1, 20);
                }
                else {
                    pState->ammo[i] = GET_RANDOM(1, GET_RANDOM(100, 500));
                }
            }

        }
    }


    // assure all user specified weapons are OK
    // if its a valid mapname, not like t1_inter
    if (std::find(ALL_MAP_NAMES.begin(), ALL_MAP_NAMES.end(), mapname) != ALL_MAP_NAMES.end()) {

        json weaponsUpcomingLevel = getRandomSetForMap("weapons", mapname);

        // for each weapon
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_SABER, "WP_SABER");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_BLASTER_PISTOL, "WP_BLASTER_PISTOL");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_BLASTER, "WP_BLASTER");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_DISRUPTOR, "WP_DISRUPTOR");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_BOWCASTER, "WP_BOWCASTER");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_REPEATER, "WP_REPEATER");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_DEMP2, "WP_DEMP2");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_FLECHETTE, "WP_FLECHETTE");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_ROCKET_LAUNCHER, "WP_ROCKET_LAUNCHER");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_THERMAL, "WP_THERMAL");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_TRIP_MINE, "WP_TRIP_MINE");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_DET_PACK, "WP_DET_PACK");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_CONCUSSION, "WP_CONCUSSION");

    }
}

// if this works without ever blocking someone call me jesus
static void generateRandomWeaponMenu() {

    // get the template
    CURRENT_WEAPON_MENU = WEAPON_TMPLT;

    // set a pattern for each weapon
    std::vector<std::string> patternsShootable;
    // one pattern for each shootable weapon
    for (int i = 0; i < PLACEHOLDERS_WEAPON_SELECT_PEWPEW.size(); i++) {
        patternsShootable.push_back("");
    }

    std::vector<std::string> patternsThrowable;
    // one pattern for each throwable weapon
    for (int i = 0; i < PLACEHOLDERS_WEAPON_SELECT_THROW.size(); i++) {
        patternsThrowable.push_back("\"0\"; ");
    }


    // for shootable weapons first
    // for each level: choose 2 shootable weapons (at least) and add them
    for (int level = 0; level < 20; level++) {

        // choose 2 random weapons (or more)
        int amountOfWeapons = GET_RANDOM(2, GET_RANDOM(2, 4));

        // keep track which weapons we added to prevent duplicates and therefore blocks
        std::vector<int> affectedWeapons;
        // for each weapon
        for (int weaponCount = 0; weaponCount < amountOfWeapons; weaponCount++) {

            int randomWeaponIndex = 0;
            while (true) {
                // get the random weapon
                randomWeaponIndex = GET_RANDOM(0, patternsShootable.size() - 1);
                // only if we haven't added it yet
                if (std::find(affectedWeapons.begin(), affectedWeapons.end(), randomWeaponIndex) == affectedWeapons.end()) {
                    break;
                }
                // else try again
            }

            affectedWeapons.push_back(randomWeaponIndex);
            // add the level to the weapon
            std::string stringToAdd = "\"";
            stringToAdd += std::to_string(level);
            stringToAdd += "\"; ";
            patternsShootable[randomWeaponIndex] = patternsShootable[randomWeaponIndex] + stringToAdd;

        }
    }

    // write the pattern for each level
    for (int i = 0; i < PLACEHOLDERS_WEAPON_SELECT_PEWPEW.size(); i++) {
        std::string currentPlaceholder = PLACEHOLDERS_WEAPON_SELECT_PEWPEW[i];

        // replace the current placeholder with the random pattern we generated
        for ( size_t pos = 0; ; pos += patternsShootable[i].length() ) {
            // Locate the substring to replace
            pos = CURRENT_WEAPON_MENU.find( currentPlaceholder, pos );
            if ( pos == std::string::npos ) break;
            // Replace by erasing and inserting
            CURRENT_WEAPON_MENU.erase( pos, currentPlaceholder.length() );
            CURRENT_WEAPON_MENU.insert( pos, patternsShootable[i] );
        }

    }


    // do the same for throwable weapons (we need at least one)
    for (int level = 0; level < 20; level++) {

        // choose 1 random throwable weapons (or more)
        int amountOfWeapons = GET_RANDOM(1, GET_RANDOM(2, 3));

        // keep track which weapons we added to prevent duplicates and therefore blocks
        std::vector<int> affectedWeapons;
        // for each weapon
        for (int weaponCount = 0; weaponCount < amountOfWeapons; weaponCount++) {

            int randomWeaponIndex = 0;
            while (true) {
                // get the random weapon
                randomWeaponIndex = GET_RANDOM(0, patternsThrowable.size() - 1);
                // only if we haven't added it yet
                if (std::find(affectedWeapons.begin(), affectedWeapons.end(), randomWeaponIndex) == affectedWeapons.end()) {
                    break;
                }
                // else try again
            }

            affectedWeapons.push_back(randomWeaponIndex);
            // add the level to the weapon
            std::string stringToAdd = "\"";
            stringToAdd += std::to_string(level);
            stringToAdd += "\"; ";
            patternsThrowable[randomWeaponIndex] = patternsThrowable[randomWeaponIndex] + stringToAdd;

        }
    }

    // write the pattern for each level
    for (int i = 0; i < PLACEHOLDERS_WEAPON_SELECT_THROW.size(); i++) {
        std::string currentPlaceholder = PLACEHOLDERS_WEAPON_SELECT_THROW[i];

        // replace the current placeholder with the random pattern we generated
        for ( size_t pos = 0; ; pos += patternsThrowable[i].length() ) {
            // Locate the substring to replace
            pos = CURRENT_WEAPON_MENU.find( currentPlaceholder, pos );
            if ( pos == std::string::npos ) break;
            // Replace by erasing and inserting
            CURRENT_WEAPON_MENU.erase( pos, currentPlaceholder.length() );
            CURRENT_WEAPON_MENU.insert( pos, patternsThrowable[i] );
        }

    }

}

#endif //OPENJK_GLOBALSHUFFLEDTIERS_H

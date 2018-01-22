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
#include <regex>

#include "../qcommon/qcommon.h"

#include "../game/weapons.h"
#include "../game/statindex.h"


#include "json.h"
using json = nlohmann::json;

#ifndef OPENJK_GLOBALSHUFFLEDTIERS_H
#define OPENJK_GLOBALSHUFFLEDTIERS_H

// obtain a random number from hardware
extern std::random_device _random_device;
// mersienne twister --> PRNG
extern std::mt19937 _rng;
extern bool _seeded;

// if the user specified pattern file is allowed to be overwritten
// on SP game startup
extern bool OVERWRITE_ALLOWED;

// the filename of the pattern file to save
static std::string PATTERN_FILE_NAME = "pattern_file.txt";
static std::string MISSION_TEMPLATE_FILE_NAME = "mission_template_file.txt";
static std::string WEAPON_TEMPLATE_FILE_NAME = "weapon_template_file.txt";
static std::string SETTINGS_FILE_NAME = "randomizerOptions.json";

// JSON object storing the user supplied settings via `SETTINGS_FILE_NAME`
extern json SETTINGS_JSON;

// name of the loaded map
extern std::string UPCOMING_MAP_NAME;

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
static std::vector<std::string> PLACEHOLDERS_WEAPON_SELECT = {
        "XX_WEAPON_PLACEHOLDER_1_XX",
        "XX_WEAPON_PLACEHOLDER_2_XX",
        "XX_WEAPON_PLACEHOLDER_3_XX",
        "XX_WEAPON_PLACEHOLDER_4_XX",
};


static void INIT_PRNG() {
    // seed the mersienne twister
    _rng = std::mt19937(_random_device());
    _seeded = true;
}

static int GET_RANDOM(int from, int to) {
    assert(_seeded);
    // define the range
    std::uniform_int_distribution<> distr(from, to);

    return distr(_rng);
}

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
    if(tierIndex == 1) {
        currentTierMenuName = "ingameMissionSelect1";
    }
    else if(tierIndex == 2) {

        currentTierMenuName = "ingameMissionSelect2";
    }
    else {

        currentTierMenuName = "ingameMissionSelect3";
    }

    while((start_pos = menu_result.find(tierMenuNamePlaceholder, start_pos)) != std::string::npos) {
        menu_result.replace(start_pos, tierMenuNamePlaceholder.length(), currentTierMenuName);
        start_pos += currentTierMenuName.length();
    }

    // Just use a fixed value here - the asserts of the caller have checked for possible errors anyway
    for(int i = 0; i < 5; i++) {

        // map names
        size_t start_pos = 0;
        // Replace e.g. XX_MAP1_XX with t1_sour
        while((start_pos = menu_result.find(PLACEHOLDERS_MAP_NAMES[i], start_pos)) != std::string::npos) {
            menu_result.replace(start_pos, PLACEHOLDERS_MAP_NAMES[i].length(), tier[i]);
            start_pos += tier[i].length();
        }

        // title and briefing placeholders
        start_pos = 0;
        while((start_pos = menu_result.find(PLACEHOLDERS_TITLES_BRIEFINGS[i], start_pos)) != std::string::npos) {

            // convert mapname to uppercase
            std::string mapNameUpper = tier[i];
            std::transform(mapNameUpper.begin(), mapNameUpper.end(),mapNameUpper.begin(), ::toupper);

            // of course the briefing title for t3_stamp is called T3_STAMPEDE :D
            if(mapNameUpper == "T3_STAMP") {
                mapNameUpper = "T3_STAMPEDE";
            }

            // Replace e.g. XX_MAP1_TB_XX with T1_SOUR
            menu_result.replace(start_pos, PLACEHOLDERS_TITLES_BRIEFINGS[i].length(), mapNameUpper);
            start_pos += mapNameUpper.length();
        }

        // long names lower
        start_pos = 0;
        // Replace e.g. XX_MAP_1_LONG_NAME_LOWER_XX with tatooine
        while((start_pos = menu_result.find(PLACEHOLDERS_LONG_NAMES_LOWER[i], start_pos)) != std::string::npos) {
            menu_result.replace(start_pos, PLACEHOLDERS_LONG_NAMES_LOWER[i].length(), MAP_TITLE_NAME_CONVERSION[tier[i]]);
            start_pos += tier[i].length();
        }

        // long names upper
        start_pos = 0;
        // Replace e.g. XX_MAP_1_LONG_NAME_UPPER_XX with TATOOINE
        while((start_pos = menu_result.find(PLACEHOLDERS_LONG_NAMES_UPPER[i], start_pos)) != std::string::npos) {

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

// 0 = Choose two weapons from a random pool
// 1 = Chaos mode aka yolo mode
extern int weaponRandomizationMode;

// How many levels the player has completed --> amount of force points available
extern int TIER_MISSIONS_COMPLETED;


// We will push the passed map strings in here
// this currently ignores maps where no force points will be achieved
extern std::vector<std::string> PASSED_LEVELS;

// Helper method to set force powers with error checking
static void _setRandomForcePower(playerState_t* pState, json forcePowersUpcomingLevel, int FP_enumType, std::string FP_string) {

    int newLevel = forcePowersUpcomingLevel.at(FP_string);
    // if we need to modify it
    if (pState->forcePowerLevel[FP_enumType] < forcePowersUpcomingLevel.at(FP_string)) {

        if(newLevel < 0) { newLevel = 0; }
        if(newLevel > 3) { newLevel = 3; }

        pState->forcePowerLevel[FP_enumType] = newLevel;
    }

    if (newLevel > 0) {
        // learn
        pState->forcePowersKnown |= (1 << FP_enumType);
    } else {
        // forget
        pState->forcePowersKnown |= (0 << FP_enumType);
    }
}

static void randomizeForcePowers(playerState_t* pState, const std::string mapname) {

    // core powers - player can't choose these
    std::vector<int> fps_core = {
            FP_LEVITATION,
            FP_PUSH,
            FP_PULL,
            FP_SABERTHROW,
            FP_SABER_DEFENSE,
            FP_SABER_OFFENSE,
            FP_SEE,
            FP_SPEED,
    };


    // the force powers the player can choose
    std::vector<int> fps_player = {
            FP_HEAL,
            FP_TELEPATHY,
            FP_GRIP,
            FP_LIGHTNING,
            FP_RAGE,
            FP_PROTECT,
            FP_ABSORB,
            FP_DRAIN,
    };

    // reset the force powers to zero first
    for(auto fp: fps_core) {
        pState->forcePowerLevel[fp] = 0;
        pState->forcePowersKnown &= (0 << fp);
    }
    for(auto fp: fps_player) {
        pState->forcePowerLevel[fp] = 0;
        pState->forcePowersKnown &= (0 << fp);
    }

    srand(unsigned(time(NULL)));

    forceRandomizationMode = SETTINGS_JSON.at("forceRandomizationMode");

    // only two modes for now
    if(forceRandomizationMode < 0) { forceRandomizationMode = 0; }
    if(forceRandomizationMode > 1) { forceRandomizationMode = 0; }

    // progression mode
    if(forceRandomizationMode == 0) {
        int playerPointsToSpend = TIER_MISSIONS_COMPLETED > 0 ? TIER_MISSIONS_COMPLETED : 0;

        int corePointsToSpend = 0;
        if(TIER_MISSIONS_COMPLETED < 5) { corePointsToSpend = fps_core.size(); }
        if(TIER_MISSIONS_COMPLETED >= 5 && TIER_MISSIONS_COMPLETED < 10) { corePointsToSpend = fps_core.size() * 2; }
        if(TIER_MISSIONS_COMPLETED >= 10) { corePointsToSpend = fps_core.size() *  3; }

        for(auto fp: fps_core) {

            // finished
            if(corePointsToSpend <= 0) { break; }

            int randomLevel = Q_min(GET_RANDOM(0, 3), corePointsToSpend);

            // don't make it too easy ;)
            if (fp == FP_LEVITATION) {
                int randNo = GET_RANDOM(0, 100);

                if (randNo > 25) {
                    randomLevel = 1;
                }

                if (randNo > 85) {
                    randomLevel = 2;
                }

                if (randomLevel > 95) {
                    randomLevel = 3;
                }

            }

            corePointsToSpend -= randomLevel;


            pState->forcePowerLevel[fp] = randomLevel;

            // enable or disable the force power
            if (randomLevel > 0) {
                pState->forcePowersKnown |= (1 << fp);
            }

                // disable of level is zero
            else {
                pState->forcePowersKnown &= (0 << fp);
            }
        }

        for(auto fp: fps_player) {

            // finished
            if(playerPointsToSpend <= 0) { break; }

            int randomLevel = Q_min(GET_RANDOM(0, 3), playerPointsToSpend);
            playerPointsToSpend -= randomLevel;

            pState->forcePowerLevel[fp] = randomLevel;

            // enable or disable the force power
            if (randomLevel > 0) {
                pState->forcePowersKnown |= (1 << fp);
            }

                // disable of level is zero
            else {
                pState->forcePowersKnown &= (0 << fp);
            }
        }

    }

    // chaos mode
    if(forceRandomizationMode == 1) {
        // allocate random core powers first
        for (auto fp : fps_core) {

            int randomLevel = 0;
            // don't make it too easy ;)
            if (fp == FP_LEVITATION) {
                int randNo = GET_RANDOM(0, 100);

                // todo make these global

                if (randNo > 25) {
                    randomLevel = 1;
                }

                if (randNo > 80) {
                    randomLevel = 2;
                }

                if (randomLevel > 95) {
                    randomLevel = 3;
                }

            } else {


                // from 0..3
                randomLevel = GET_RANDOM(0, GET_RANDOM(1, 3));
            }

            pState->forcePowerLevel[fp] = randomLevel;

            // enable or disable the force power
            if (randomLevel > 0) {
                pState->forcePowersKnown |= (1 << fp);
            }

                // disable of level is zero
            else {
                pState->forcePowersKnown &= (0 << fp);
            }
        }

        // allocate random force powers for the player powers
        // Max points to spend so we don't soft block
        auto maxPoints_bkp = ((fps_player.size() * 3) - 1);

        // don't use all possible points all the time
        auto maxPoints = Q_min((maxPoints_bkp - (GET_RANDOM(0, maxPoints_bkp)) + 8), maxPoints_bkp);

        for (auto fp : fps_player) {
            if (maxPoints == 0) { break; }

            int randomLevel = Q_min(GET_RANDOM(0, 3), maxPoints);

            maxPoints -= randomLevel;

            pState->forcePowerLevel[fp] = randomLevel;

            // enable or disable the force power
            if (randomLevel > 0) {
                pState->forcePowersKnown |= (1 << fp);
            }

                // disable if level is zero
            else {
                pState->forcePowersKnown &= (0 << fp);
            }

        }

    }

    // assure all user specified force levels are OK
    // if its a valid mapname, not like t1_inter
    if (std::find(ALL_MAP_NAMES.begin(), ALL_MAP_NAMES.end(), mapname) != ALL_MAP_NAMES.end()) {

        json forcePowersJSON = SETTINGS_JSON.at("forcePowers");
        json forcePowersUpcomingLevel = forcePowersJSON.at(mapname);

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
    for (auto fp : fps_player) {
        scoreEnd += pState->forcePowerLevel[fp];
    }

    // if blocked
    if (scoreEnd == (fps_player.size()) * 3) {
        // remove random point from player force level
        auto randomFP = fps_player[GET_RANDOM(0, fps_player.size() - 1)];
        pState->forcePowerLevel[randomFP] = pState->forcePowerLevel[randomFP] - 1;
    }

}

// Helper method to set weapons with error checking
static void _setRandomWeapon(playerState_t* pState, json weaponsUpcomingLevel, int WP_enumType, const std::string WP_string) {

    int setting = weaponsUpcomingLevel.at(WP_string);
    if(setting < 0) { setting = 0; }
    if(setting > 1) { setting = 0; }
    // apply the setting with OR
    // if it was 1 it will remain 1
    // if it was 0 it will be 1
    pState->stats[ STAT_WEAPONS ] |= ( setting << WP_enumType );

    // ammo should be already applied
}

static void randomizeWeapons(playerState_t* pState, const std::string mapname) {

    std::vector<int> allWeapons = {
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

    // Clear out any weapons for the player
    pState->stats[ STAT_WEAPONS ] = 0;
    pState->weapon = WP_NONE;

    weaponRandomizationMode = SETTINGS_JSON.at("weaponRandomizationMode");
    // get random amount of weapons
    // this doesn't mean 3 added weapons max - e.g. there's a chance WP_SABER gets picked again
    // with no effect in the end
    for(int i = 0; i < GET_RANDOM(1, 3); i++) {

        auto randomWeapon = allWeapons[GET_RANDOM(0, allWeapons.size()-1)];

        if (randomWeapon<WP_NUM_WEAPONS)
        {
            pState->stats[ STAT_WEAPONS ] |= ( 1 << randomWeapon );

        }
    }

    // Give random ammo
    for(auto i = 0; i < AMMO_MAX; i++) {

        // dont get like 500 rockets
        if(i == AMMO_ROCKETS || i == AMMO_EMPLACED || i == AMMO_THERMAL || i == AMMO_TRIPMINE || i == AMMO_DETPACK) {
            pState->ammo[i] = GET_RANDOM(0, 20);
        }
        else {
            pState->ammo[i] = GET_RANDOM(1, GET_RANDOM(100, 500));
        }
    }

    // assure all user specified weapons are OK
    // if its a valid mapname, not like t1_inter
    if (std::find(ALL_MAP_NAMES.begin(), ALL_MAP_NAMES.end(), mapname) != ALL_MAP_NAMES.end()) {

        json weaponsJSON = SETTINGS_JSON.at("weapons");
        json weaponsUpcomingLevel = weaponsJSON.at(mapname);

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
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_MELEE, "WP_MELEE");
        _setRandomWeapon(pState, weaponsUpcomingLevel, WP_STUN_BATON, "WP_STUN_BATON");

    }
}

static void generateRandomWeaponMenu() {
    CURRENT_WEAPON_MENU = WEAPON_TMPLT;

    std::cout << CURRENT_WEAPON_MENU << std::endl;

    for(int i = 0; i < PLACEHOLDERS_WEAPON_SELECT.size(); i++) {

        // todo generate a new menu string pattern
        // e.g. "7"; "8"; "9"; "10"; "11"; "12"; "13"; "14"; "15"; "16"; "17"; "18"; "19";
        std::string newMenuString = "\"1\"; \"2\"; \"3\"; \"4\"; \"5\"; \"6\"; \"7\"; \"8\"; \"9\"; \"10\"; \"11\"; \"12\"; \"13\"; \"14\"; \"15\"; \"16\"; \"17\"; \"18\"; \"19\";";

        std::string currentPlaceholder = PLACEHOLDERS_WEAPON_SELECT[i];

        for( size_t pos = 0; ; pos += newMenuString.length() ) {
            // Locate the substring to replace
            pos = CURRENT_WEAPON_MENU.find( currentPlaceholder, pos );
            if( pos == std::string::npos ) break;
            // Replace by erasing and inserting
            CURRENT_WEAPON_MENU.erase( pos, currentPlaceholder.length() );
            CURRENT_WEAPON_MENU.insert( pos, newMenuString );
        }


        std::cout << CURRENT_WEAPON_MENU << std::endl;
    }
}

#endif //OPENJK_GLOBALSHUFFLEDTIERS_H

//
// Created by ps on 18.01.18.
//

#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>

#include "../qcommon/q_shared.h"

#include "json.h"
using json = nlohmann::json;

#ifndef OPENJK_GLOBALSHUFFLEDTIERS_H
#define OPENJK_GLOBALSHUFFLEDTIERS_H

// the filename of the pattern file to save
static std::string PATTERN_FILE_NAME = "pattern_file.txt";
static std::string TEMPLATE_FILE_NAME = "template_file.txt";
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

// the modified main menu
extern std::string MAIN_MENU;

// template for the generated menu files
// will be set on startup
static std::string TMPLT;

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


static std::string _getMenuFileFromTier(std::vector<std::string> tier, int tierIndex) {

    assert(tierIndex >= 1 && tierIndex <= 3);

    // initialize the menu string with the template
    std::string menu_result = TMPLT;

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

// to track if we already randomized the force powers because
// this can happen mutliple times for one run
// true: already randomize -- do nothing
// false: randomize
extern bool randomizeForcePowersDoOnce;

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


    srand(unsigned(time(NULL)));

    // allocate random core powers first
    for(auto fp : fps_core) {
        // from 0..3
        int randomLevel = rand() % 4;

        pState->forcePowerLevel[fp] = randomLevel;

        // enable or disable the force power
        if(randomLevel > 0) {
            pState->forcePowersKnown |= ( 1 << fp );
        }

            // disable of level is zero
        else {
            pState->forcePowersKnown |= ( 0 << fp );
        }
    }

    // allocate random force powers for the player powers
    // Max points to spend so we don't soft block
    auto maxPoints_bkp = ((fps_player.size()*3) - 1);

    // don't use all possible points all the time
    auto maxPoints = Q_min((maxPoints_bkp - (rand() % maxPoints_bkp) + 8), maxPoints_bkp);

    for(auto fp : fps_player) {
        if(maxPoints == 0) { break; }

        int randomLevel = 0;
        // don't make it too easy ;)
        if(fp == FP_LEVITATION) {
            int randNo = rand() % 100;

            if(randNo > 25) {
                randomLevel = 1;
            }

            if(randNo > 60) {
                randomLevel = 2;
            }

            if(randomLevel > 90) {
                randomLevel = 3;
            }

        }
        else {


            // from 0..3
            randomLevel = rand() % 4;
        }

        // spend the rest
        if(maxPoints <= 3) { randomLevel = 3; }

        maxPoints -= randomLevel;

        pState->forcePowerLevel[fp] = randomLevel;

        // enable or disable the force power
        if(randomLevel > 0) {
            pState->forcePowersKnown |= ( 1 << fp );
        }

            // disable if level is zero
        else {
            pState->forcePowersKnown |= ( 0 << fp );
        }

    }

    // assure all user specified force levels are OK
    // if its a valid mapname, not like t1_inter
    if(std::find(ALL_MAP_NAMES.begin(), ALL_MAP_NAMES.end(), mapname) != ALL_MAP_NAMES.end()) {

        json forcePowersJSON = SETTINGS_JSON.at("forcePowers");
        json forcePowersUpcomingLevel = forcePowersJSON.at(mapname);

        // for each force power
        if(pState->forcePowerLevel[FP_LEVITATION] < forcePowersUpcomingLevel.at("FP_JUMP")) {
            pState->forcePowerLevel[FP_LEVITATION] = forcePowersUpcomingLevel.at("FP_JUMP");
        }
        if(forcePowersUpcomingLevel.at("FP_JUMP") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_LEVITATION );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_LEVITATION );
        }

        if(pState->forcePowerLevel[FP_PUSH] < forcePowersUpcomingLevel.at("FP_PUSH")) {
            pState->forcePowerLevel[FP_PUSH] = forcePowersUpcomingLevel.at("FP_PUSH");
        }
        if(forcePowersUpcomingLevel.at("FP_PUSH") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_PUSH );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_PUSH );
        }

        if(pState->forcePowerLevel[FP_PULL] < forcePowersUpcomingLevel.at("FP_PULL")) {
            pState->forcePowerLevel[FP_PULL] = forcePowersUpcomingLevel.at("FP_PULL");
        }
        if(forcePowersUpcomingLevel.at("FP_PULL") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_PULL );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_PULL );
        }

        if(pState->forcePowerLevel[FP_SABERTHROW] < forcePowersUpcomingLevel.at("FP_SABERTHROW")) {
            pState->forcePowerLevel[FP_SABERTHROW] = forcePowersUpcomingLevel.at("FP_SABERTHROW");
        }
        if(forcePowersUpcomingLevel.at("FP_SABERTHROW") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_SABERTHROW );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_SABERTHROW );
        }

        if(pState->forcePowerLevel[FP_SABER_DEFENSE] < forcePowersUpcomingLevel.at("FP_SABER_DEFENSE")) {
            pState->forcePowerLevel[FP_SABER_DEFENSE] = forcePowersUpcomingLevel.at("FP_SABER_DEFENSE");
        }
        if(forcePowersUpcomingLevel.at("FP_SABER_DEFENSE") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_SABER_DEFENSE );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_SABER_DEFENSE );
        }

        if(pState->forcePowerLevel[FP_SABER_OFFENSE] < forcePowersUpcomingLevel.at("FP_SABER_OFFENSE")) {
            pState->forcePowerLevel[FP_SABER_OFFENSE] = forcePowersUpcomingLevel.at("FP_SABER_OFFENSE");
        }
        if(forcePowersUpcomingLevel.at("FP_SABER_OFFENSE") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_SABER_OFFENSE );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_SABER_OFFENSE );
        }

        if(pState->forcePowerLevel[FP_SEE] < forcePowersUpcomingLevel.at("FP_SENSE")) {
            pState->forcePowerLevel[FP_SEE] = forcePowersUpcomingLevel.at("FP_SENSE");
        }
        if(forcePowersUpcomingLevel.at("FP_SENSE") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_SEE );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_SEE );
        }

        if(pState->forcePowerLevel[FP_SPEED] < forcePowersUpcomingLevel.at("FP_SPEED")) {
            pState->forcePowerLevel[FP_SPEED] = forcePowersUpcomingLevel.at("FP_SPEED");
        }
        if(forcePowersUpcomingLevel.at("FP_SPEED") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_SPEED );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_SPEED );
        }

        if(pState->forcePowerLevel[FP_HEAL] < forcePowersUpcomingLevel.at("FP_HEAL")) {
            pState->forcePowerLevel[FP_HEAL] = forcePowersUpcomingLevel.at("FP_HEAL");
        }
        if(forcePowersUpcomingLevel.at("FP_HEAL") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_HEAL );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_HEAL );
        }

        if(pState->forcePowerLevel[FP_TELEPATHY] < forcePowersUpcomingLevel.at("FP_MINDTRICK")) {
            pState->forcePowerLevel[FP_TELEPATHY] = forcePowersUpcomingLevel.at("FP_MINDTRICK");
        }
        if(forcePowersUpcomingLevel.at("FP_MINDTRICK") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_TELEPATHY );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_TELEPATHY );
        }

        if(pState->forcePowerLevel[FP_GRIP] < forcePowersUpcomingLevel.at("FP_GRIP")) {
            pState->forcePowerLevel[FP_GRIP] = forcePowersUpcomingLevel.at("FP_GRIP");
        }
        if(forcePowersUpcomingLevel.at("FP_GRIP") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_GRIP );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_GRIP );
        }

        if(pState->forcePowerLevel[FP_LIGHTNING] < forcePowersUpcomingLevel.at("FP_LIGHTNING")) {
            pState->forcePowerLevel[FP_LIGHTNING] = forcePowersUpcomingLevel.at("FP_LIGHTNING");
        }
        if(forcePowersUpcomingLevel.at("FP_LIGHTNING") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_LIGHTNING );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_LIGHTNING );
        }

        if(pState->forcePowerLevel[FP_RAGE] < forcePowersUpcomingLevel.at("FP_RAGE")) {
            pState->forcePowerLevel[FP_RAGE] = forcePowersUpcomingLevel.at("FP_RAGE");
        }
        if(forcePowersUpcomingLevel.at("FP_RAGE") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_RAGE );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_RAGE );
        }

        if(pState->forcePowerLevel[FP_PROTECT] < forcePowersUpcomingLevel.at("FP_PROTECT")) {
            pState->forcePowerLevel[FP_PROTECT] = forcePowersUpcomingLevel.at("FP_PROTECT");
        }
        if(forcePowersUpcomingLevel.at("FP_PROTECT") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_PROTECT );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_PROTECT );
        }

        if(pState->forcePowerLevel[FP_ABSORB] < forcePowersUpcomingLevel.at("FP_ABSORB")) {
            pState->forcePowerLevel[FP_ABSORB] = forcePowersUpcomingLevel.at("FP_ABSORB");
        }
        if(forcePowersUpcomingLevel.at("FP_ABSORB") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_ABSORB );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_ABSORB );
        }

        if(pState->forcePowerLevel[FP_DRAIN] < forcePowersUpcomingLevel.at("FP_DRAIN")) {
            pState->forcePowerLevel[FP_DRAIN] = forcePowersUpcomingLevel.at("FP_DRAIN");
        }
        if(forcePowersUpcomingLevel.at("FP_DRAIN") > 0) {
            // learn
            pState->forcePowersKnown |= ( 1 << FP_DRAIN );
        }
        else {
            // forget
            pState->forcePowersKnown |= ( 0 << FP_DRAIN );
        }


    }

    // re-check all if at least one point is unused -- avoid soft block
    int scoreEnd = 0;
    for(auto fp : fps_player) {
        scoreEnd += pState->forcePowerLevel[fp];
    }

    // if blocked
    if(scoreEnd == (fps_player.size()) * 3) {
        // remove random point from player force level
        auto randomFP = fps_player[rand() % (fps_player.size() - 1)];
        pState->forcePowerLevel[randomFP] = pState->forcePowerLevel[randomFP] - 1;
    }
}


#endif //OPENJK_GLOBALSHUFFLEDTIERS_H

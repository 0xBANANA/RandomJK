//
// Created by ps on 18.01.18.
//

#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>

#ifndef OPENJK_GLOBALSHUFFLEDTIERS_H
#define OPENJK_GLOBALSHUFFLEDTIERS_H

// the filename of the pattern file to save
static std::string PATTERN_FILE_NAME = "pattern_file.txt";
static std::string TEMPLATE_FILE_NAME = "template_file.txt";

// the maps we will use
static std::vector<std::string> MAP_NAMES = {
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


#endif //OPENJK_GLOBALSHUFFLEDTIERS_H

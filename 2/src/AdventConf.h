#ifndef ADVENTCONF_H
#define ADVENTCONF_H

#include <string>

// ***
// Player Settings
// ***
static const unsigned s_confInventorySize = 5;

// ***
// Output and UI-settings
// ***
static const unsigned s_confTerminalLineSpacing = 2;

static const std::string s_confTerminalIndicator = "> ";

// Commands, Syntax & Help
static const std::string s_confMessageInvalidCommand 	= "That's not a verb I recognise.";
static const std::string s_confMessageInvalidTravel 	= "I understand you as far as that you wish to travel, but you have specified too many destinations.";
static const std::string s_confMessageInvalidInteract 	= "I understand you as far as that you would like to interact with something. However, you have specified too many actions and/or objects.";
static const std::string s_confMessageInvalidGame 		= "I understand you as far as that you have specified a special game-command. However, you have specified too many game-commands.";

// Inventory and objects:
static const std::string s_confMessageObjectTaken 		= "Taken.";
static const std::string s_confMessageObjectDropped		= "Dropped.";
static const std::string s_confMessageObjectNoDescription = ">$<";
static const std::string s_confMessageObjectNotFound	= "You can't see any such thing.";
static const std::string s_confMessageInventoryEmpty 	= "You are carrying nothing.";
static const std::string s_confMessageInventoryHeader 	= "You are carrying:";
static const std::string s_confMessageObjectNotOpenable = "That is no object you may unlock or open.";
static const std::string s_confMessageObjectOpened = "Opened.";

// ***
// Commands & Interpretation
// ***
enum VerbIds {
	VerbIds_TAKE 	= 2001,
	VerbIds_DROP 	= 2002,
	VerbIds_SAY		= 2003,
	VerbIds_OPEN 	= 2004,
	VerbIds_NOTHING = 2005,
	VerbIds_CLOSE 	= 2006,
	VerbIds_ON 		= 2007,
	VerbIds_OFF 	= 2008,
	VerbIds_WAVE 	= 2009,
	VerbIds_CALM 	= 2010,
	VerbIds_WALK 	= 2011,
	VerbIds_FIGHT 	= 2012,
	VerbIds_POUR 	= 2013,
	VerbIds_EAT 	= 2014,
	VerbIds_DRINK 	= 2015,
	VerbIds_RUB 	= 2016,
	VerbIds_THROW 	= 2017,
	VerbIds_QUIT 	= 2018,
	VerbIds_FIND	= 2019,	
	VerbIds_INVEN	= 2020,
	VerbIds_FEED	= 2021,
	VerbIds_FILL	= 2022,
	VerbIds_BLAST	= 2023,
	VerbIds_SCORE	= 2024,
	VerbIds_FEE		= 2025,
	VerbIds_FIE		= 2025,
	VerbIds_BRIEF	= 2026,
	VerbIds_READ	= 2027,
	VerbIds_BREAK	= 2028,
	VerbIds_WAKE	= 2029,
	VerbIds_SUSPE	= 2030,
	VerbIds_HOURS	= 2031,
};

// Structured this way so that one may loop through ids that may be opened.
enum ObjectsOpenableIds {
	ObjectsOpenableIds_GRATE = 3
};
static const unsigned s_objectsOpenableSize = 1; // INCREASE ME
static const unsigned ObjectsOpenable[] = { 
	ObjectsOpenableIds_GRATE
};

/*
enum ObjectsLighteable { ??
	...	
};
*/

#endif // ADVENTCONF_H
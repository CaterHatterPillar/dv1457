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
static const std::string s_confMessageObjectNotOpenable = "You cannot open that item. Are you missing something?";
static const std::string s_confMessageObjectOpened		= "Opened.";
static const std::string s_confMessageObjectOn 			= "Item activated.";

static const std::string s_confDescShortDarkness = "\tDARKNESS";
static const std::string s_confDescLongDarkness = "\tIT IS PITCH DARK, AND YOU CAN'T SEE A THING.";

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

enum MeaningfulWords
{
	MeaningfulWords_XYZZY = 62,
	MeaningfulWords_PLUGH = 65,
	MeaningfulWords_PLOVE = 71,

	MeaningfulWords_FEE = 3001,
	MeaningfulWords_FIE = 3002,
	MeaningfulWords_FOE = 3003,
	MeaningfulWords_FOO = 3004,
	MeaningfulWords_FUM = 3005,
};

enum MagicWordLocations
{
	MagicWordLocations_XYZZY = 11,
	MagicWordLocations_PLUGH = 33,
	MagicWordLocations_PLOVER = 100,
	MagicWordLocations_FEE = 92,
};

enum LiquidAssets {
	LiquidAssets_LIT 					= 0,
	LiquidAssets_LIQUID_TYPE 			= 1,
	LiquidAssets_LIQUID 				= 2,
	LiquidAssets_NO_PIRATES_ALLOWED 	= 3,
	LiquidAssets_TRYING_INTO_CAVE 		= 4,
	LiquidAssets_TRYING_CATCH_BIRD 		= 5,
	LiquidAssets_TRYING_DEAL_WITH_SNAKE = 6,
	LiquidAssets_LOST_IN_MAZE 			= 7,
	LiquidAssets_PONDERING_DARK_ROOM 	= 8,
	LiquidAssets_AT_WITTS_END 			= 9
};

/*
The cond bits currently assigned are:
	0	light
	1	if bit 2 is on: on for oil, off for water
	2	liquid asset, see bit 1
	3	pirate doesn't go here unless following player
Other bits are used to indicate areas of interest to "hint" routines:
	4	trying to get into cave
	5	trying to catch bird
	6	trying to deal with snake
	7	lost in maze
	8	pondering dark room
	9	at witt's end
*/

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
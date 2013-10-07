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
enum VerbIdsMotion {
	VerbIdsMotion_LOOK = 57
};
enum VerbIdsAction {
	VerbIdsAction_TAKE 		= 2001,
	VerbIdsAction_DROP 		= 2002,
	VerbIdsAction_SAY		= 2003,
	VerbIdsAction_OPEN 		= 2004,
	VerbIdsAction_NOTHING 	= 2005,
	VerbIdsAction_CLOSE 	= 2006,
	VerbIdsAction_ON 		= 2007,
	VerbIdsAction_OFF 		= 2008,
	VerbIdsAction_WAVE 		= 2009,
	VerbIdsAction_CALM 		= 2010,
	VerbIdsAction_WALK 		= 2011,
	VerbIdsAction_FIGHT 	= 2012,
	VerbIdsAction_POUR 		= 2013,
	VerbIdsAction_EAT 		= 2014,
	VerbIdsAction_DRINK 	= 2015,
	VerbIdsAction_RUB 		= 2016,
	VerbIdsAction_THROW 	= 2017,
	VerbIdsAction_QUIT 		= 2018,
	VerbIdsAction_FIND		= 2019,	
	VerbIdsAction_INVEN		= 2020,
	VerbIdsAction_FEED		= 2021,
	VerbIdsAction_FILL		= 2022,
	VerbIdsAction_BLAST		= 2023,
	VerbIdsAction_SCORE		= 2024,
	VerbIdsAction_FEE		= 2025,
	VerbIdsAction_FIE		= 2025,
	VerbIdsAction_BRIEF		= 2026,
	VerbIdsAction_READ		= 2027,
	VerbIdsAction_BREAK		= 2028,
	VerbIdsAction_WAKE		= 2029,
	VerbIdsAction_SUSPE		= 2030,
	VerbIdsAction_HOURS		= 2031,
};

enum ObjectIds
{
	ObjectIds_CAGE = 4,
	ObjectIds_ROD  = 5,
	ObjectIds_BIRD = 8,
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
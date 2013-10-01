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
static const std::string s_confMessageObjectNotFound	= "You can't see any such thing.";
static const std::string s_confMessageInventoryEmpty 	= "You are carrying nothing.";
static const std::string s_confMessageInventoryHeader 	= "You are carrying:";

#endif // ADVENTCONF_H
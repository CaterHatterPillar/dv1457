#include "Common.h"
#include "AdventData.h"

AdventData::AdventData() {
}
AdventData::~AdventData() {
	// Do nothing.
}

bool AdventData::isOnSite( Object p_object ) {
	bool onSite = false;
	unsigned objectId = p_object.getId();

	Location& loc = map[ adventurer.getIdLocation() ];
	if( adventurer.getInventory().carriesItem( objectId )==true ||
		loc.objectAtLocation( objectId )==true ) {
		onSite = true;
	}
	return onSite;
};
bool AdventData::locationIsIlluminated() {
	// Whether or not current location is illuminated. That is:
	// Either player has the lamp lit, or the location has sufficient light form the start.
	bool illuminated = false;
	
	// Lamp
	const unsigned LAMP_HACK = 2;
	if( adventurer.getInventory().carriesItem( LAMP_HACK ) ) {
		unsigned lampPropVal = map.getObject( LAMP_HACK ).getPropertyValue();
		if( lampPropVal!=0 ) {
			illuminated = true;
		}
	}

	// Sunlight
	Location& location = map[ adventurer.getIdLocation() ];
	if( location.isLit()==true ) {
		illuminated = true;
	}

	return illuminated;
}
void AdventData::discoverMagicWords() {
    int locationId = adventurer.getIdLocation();
    if( locationIsIlluminated()==true ) {
    	switch(locationId) {
    	case MagicWordLocations_XYZZY:
    		magic.setXyzzy( true );
    	    break;
    	case MagicWordLocations_PLUGH:
    	    magic.setPlugh( true );
    	    break;
    	case MagicWordLocations_PLOVER:
    	    magic.setPlover( true );
    	    break;
    	case MagicWordLocations_FEE:
    	    magic.setFee( true );
    	    break;
    	default:
    		// Do nothing.
    		break;
    	}
    }
}
#include <stddef.h>
#include "Market.h"


Market* Market::singleton_instance = NULL;

Market* Market::instance() {
	if (!singleton_instance)
		singleton_instance = new Market;

	return singleton_instance;
}


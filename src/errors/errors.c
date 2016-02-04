#include "./../../headers/errors.h"

void setError(errorMessage message) {
	error = message;
}

char* getError() {
	switch (error) {
	case INVALID_ARGUMENTS:
		return "INVALID ARGUMENTS";
	case INVALID_PATH:
		return "NO DATASET FOUND";	
	case NODE_FROM_NOT_FOUND:
		return "\"FROM\" NODE NOT FOUND";
	case NODE_TO_NOT_FOUND:
		return "\"TO\" NODE NOT FOUND";
	}
}

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
	}
}

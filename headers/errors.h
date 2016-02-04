#pragma once

typedef enum Error errorMessage;

static enum Error {
	INVALID_ARGUMENTS = 0,
	INVALID_PATH,
	NODE_FROM_NOT_FOUND,
	NODE_TO_NOT_FOUND
} error;

void setError(errorMessage);
char* getError();

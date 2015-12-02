#pragma once

typedef enum Error errorMessage;

static enum Error {
	INVALID_ARGUMENTS = 0,
	INVALID_PATH
} error;

void setError(errorMessage);
char* getError();

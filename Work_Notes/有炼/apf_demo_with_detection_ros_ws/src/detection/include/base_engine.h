
#ifndef BASE_ENGINE_H
#define BASE_ENGINE_H
#include "common.h"

class BaseEngine{
public:
	BaseEngine(const char*, const char*,const string&);
	~BaseEngine();
	IExecutionContext *context;
	const char* INPUT_BLOB_NAME;
	const char* OUTPUT_BLOB_NAME;

};
#endif

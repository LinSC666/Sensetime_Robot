#include "base_engine.h"

BaseEngine::BaseEngine(const char* input_name, const char* output_name, const string& engine_file_path):
	INPUT_BLOB_NAME(input_name),OUTPUT_BLOB_NAME(output_name)
{
    std::ifstream engine_file_stream;
    gLogInfo<<"loading engine filename from:" <<engine_file_path <<endl;
    engine_file_stream.open(engine_file_path,std::ios::binary);
    vector<char> trtModelStream;
    if (engine_file_stream.good()){
         engine_file_stream.seekg(0, std::ios::end);
         int length = engine_file_stream.tellg();
         gLogInfo<<"Engine file with:" <<length <<" bytes "<<endl;
	 trtModelStream.resize(length);
         engine_file_stream.seekg(0, std::ios::beg);
	 engine_file_stream.read(trtModelStream.data(),length);
	 engine_file_stream.close();

         IRuntime* trtRuntime = createInferRuntime(gLogger);
	 assert(trtRuntime != nullptr);
         ICudaEngine *trtEngine = trtRuntime->deserializeCudaEngine(trtModelStream.data(),length,nullptr);		 
	 assert(trtEngine);
	 context = trtEngine->createExecutionContext();
    }
    else{
	    gLogError<<"Error reading file "<<engine_file_path<<endl;
    }
}

BaseEngine::~BaseEngine()
{
    context->destroy();
}

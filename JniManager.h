#pragma once
#include <map>
#include "TypeConverter.h"
#include <iostream>

using namespace std;
using namespace rapidjson;

class JniManager
{
private:
    TypeConverter* typeConverter;
   
    // Mono Methods
    MonoMethod* processMethod;
    MonoMethod* setAssemblyPathField;
    MonoMethod* setMethodNameField;
    MonoMethod* setAssemblyNameField;
    MonoMethod* setFullTrustField;
    MonoMethod* setIsSingletonField;
    MonoMethod* setLogField;
    MonoMethod* setNotifyEventsField;
    MonoMethod* addMethodArgumentsProperty;
    MonoMethod* addOutboundProperty;
    MonoMethod* addInboundProperty;
    MonoMethod* addInvocationProperty;
    MonoMethod* addSessionProperty;
    MonoMethod* getOutboundProperty;
    MonoMethod* getInvocationProperty;
    MonoMethod* getSessionProperty;
    MonoMethod* getOutboundPropertySize;
    MonoMethod* getInvocationPropertySize;
    MonoMethod* getSessionPropertySize;
    MonoMethod* getOutboundPropertyKey;
    MonoMethod* getInvocationPropertyKey;
    MonoMethod* getSessionPropertyKey;
    MonoMethod* getResult;

    MonoMethod* getMonoInvocationProperties;
    MonoMethod* getMonoOutboundProperties;

    MonoClass* processRequestClass;
    MonoMethod* getItem;
    MonoMethod* addItem;
    MonoMethod* createDictionary;

public:
    void setMono(MonoImage*);
    string toResponse(MonoObject*);
    void toProcessRequest(string, MonoObject*);
    string toException(const char*);
};


#include "JniManager.h"
#include <iostream>

void JniManager::setMono(MonoImage* monoImage)
{
    processRequestClass = mono_class_from_name(monoImage, "Org.Mule.Api.Routing", "ProcessRequest");
    setAssemblyNameField = mono_class_get_method_from_name(processRequestClass, "set_AssemblyName", 1);
    setMethodNameField = mono_class_get_method_from_name(processRequestClass, "set_MethodName", 1);
    setAssemblyPathField = mono_class_get_method_from_name(processRequestClass, "set_AssemblyPath", 1);
    setFullTrustField = mono_class_get_method_from_name(processRequestClass, "set_FullTrust", 1);
    setIsSingletonField = mono_class_get_method_from_name(processRequestClass, "set_IsSingleton", 1);
    setLogField = mono_class_get_method_from_name(processRequestClass, "set_Log", 1);
    getResult = mono_class_get_method_from_name(processRequestClass, "get_Result", 0);
    setNotifyEventsField = mono_class_get_method_from_name(processRequestClass, "set_NotifyEvents", 1);
    addMethodArgumentsProperty = mono_class_get_method_from_name(processRequestClass, "AddMethodArgumentProperty", 2);
    addInboundProperty = mono_class_get_method_from_name(processRequestClass, "AddInboundProperty", 2);
    addInvocationProperty = mono_class_get_method_from_name(processRequestClass, "AddInvocationProperty", 2);
    addSessionProperty = mono_class_get_method_from_name(processRequestClass, "AddSessionProperty", 2);
    addOutboundProperty = mono_class_get_method_from_name(processRequestClass, "AddOutboundProperty", 2);
    getInvocationProperty = mono_class_get_method_from_name(processRequestClass, "GetInvocationProperty", 1);
    getSessionProperty = mono_class_get_method_from_name(processRequestClass, "GetSessionProperty", 1);
    getOutboundProperty = mono_class_get_method_from_name(processRequestClass, "GetOutboundProperty", 1);
    getInvocationPropertySize = mono_class_get_method_from_name(processRequestClass, "GetInvocationPropertySize", 0);
    getSessionPropertySize = mono_class_get_method_from_name(processRequestClass, "GetSessionPropertySize", 0);
    getOutboundPropertySize = mono_class_get_method_from_name(processRequestClass, "GetOutboundPropertySize", 0);
    getInvocationPropertyKey = mono_class_get_method_from_name(processRequestClass, "GetInvocationPropertyKey", 1);
    getSessionPropertyKey = mono_class_get_method_from_name(processRequestClass, "GetSessionPropertyKey", 1);
    getOutboundPropertyKey = mono_class_get_method_from_name(processRequestClass, "GetOutboundPropertyKey", 1);
    
    getMonoInvocationProperties = mono_class_get_method_from_name(processRequestClass, "set_InvocationProperties", 1);
    getMonoOutboundProperties = mono_class_get_method_from_name(processRequestClass, "set_IOutboundProperties", 1);
    
     // Get class for generic Dictionary<string, object> 
    createDictionary = mono_class_get_method_from_name(processRequestClass, "CreateDictionary", 0);
        
    MonoObject* dictInstance = mono_runtime_invoke(createDictionary, NULL, NULL, NULL);

    MonoClass* dictionaryClass = mono_object_get_class (dictInstance);
    
    dictInstance = NULL;
    
    getItem = mono_class_get_method_from_name(dictionaryClass, "get_Item", 1);
    addItem = mono_class_get_method_from_name(dictionaryClass, "Add", 2);
    
    typeConverter = new TypeConverter();
    typeConverter->init(processRequestClass);
}

void JniManager::toProcessRequest(string input, MonoObject* processRequest)
{
    Document d;
    d.Parse<0>(input.c_str());
    
    if(d.HasParseError())
    {
        string error = d.GetParseError();
        //toException(errorMessage)
        //return NULL;
        printf("SERVER PARSE ERROR: %s\n", error.c_str());
        printf("INPUT: %s\n", input.c_str());
        return;
    }

    MonoDomain* monoDomain = typeConverter->getMonoDomain();

    MonoString* assemblyName = mono_string_new(monoDomain, d["assemblyName"].GetString());
    MonoString* assemblyPath = mono_string_new(monoDomain, d["assemblyPath"].GetString());
    MonoString* methodName = mono_string_new(monoDomain, d["methodName"].GetString());
    bool fullTrust = true;
    bool notifyEvents = d["notifyEvents"].GetBool();

    MonoObject* exception = NULL;

    void* args[1];
    args[0] = assemblyName;
    mono_runtime_invoke(setAssemblyNameField, processRequest, args, &exception);

    args[0] = assemblyPath;
    mono_runtime_invoke(setAssemblyPathField, processRequest, args, &exception);

    args[0] = methodName;
    mono_runtime_invoke(setMethodNameField, processRequest, args, &exception);

    args[0] = &fullTrust;
    mono_runtime_invoke(setFullTrustField, processRequest, args, &exception);

    bool log = d["log"].GetBool();
    args[0] = &log;
    mono_runtime_invoke(setLogField, processRequest, args, &exception);

    bool isSingleton = d["isSingleton"].GetBool();
    args[0] = &isSingleton;
    mono_runtime_invoke(setIsSingletonField, processRequest, args, &exception);

    args[0] = &notifyEvents;
    mono_runtime_invoke(setNotifyEventsField, processRequest, args, &exception);

    if (exception)
    {
        const char* message = mono_string_to_utf8(mono_object_to_string(exception, NULL));
        //throwException(message);
    }
    
    /* Fill method arguments */
    if(d.HasMember("methodArguments") && d["methodArguments"].IsObject())
    {
        for (Value::ConstMemberIterator itr = d["methodArguments"].MemberBegin(); itr != d["methodArguments"].MemberEnd(); ++itr)
        {
            string keyName = string(itr->name.GetString());
            const GenericValue<UTF8<> >& value = itr->value;

            MonoObject* exc = NULL;

            void* args[] = { mono_string_new(monoDomain, keyName.c_str()), typeConverter->toMonoObject(value) };

            mono_runtime_invoke(addMethodArgumentsProperty, processRequest, args, &exc);

            if (exc)
            {
                const char* message = mono_string_to_utf8(mono_object_to_string(exc, NULL));
                return;
            }
        }
    }
    
    /* Fill invocation properties */
    if(d.HasMember("invocationProperties") && d["invocationProperties"].IsObject())
    {
        for (Value::ConstMemberIterator itr = d["invocationProperties"].MemberBegin(); itr != d["invocationProperties"].MemberEnd(); ++itr)
        {
            string keyName = string(itr->name.GetString());
            const GenericValue<UTF8<> >& value = itr->value;

            MonoObject* exc = NULL;

            void* args[] = { mono_string_new(monoDomain, keyName.c_str()), typeConverter->toMonoObject(value) };

            mono_runtime_invoke(addInvocationProperty, processRequest, args, &exc);

            if (exc)
            {
                const char* message = mono_string_to_utf8(mono_object_to_string(exc, NULL));
                return;
            }
        }
    }
    
    /* Fill inbound properties */
    if(d.HasMember("inboundProperties") && d["inboundProperties"].IsObject())
    {
        for (Value::ConstMemberIterator itr = d["inboundProperties"].MemberBegin(); itr != d["inboundProperties"].MemberEnd(); ++itr)
        {
            string keyName = string(itr->name.GetString());
            const GenericValue<UTF8<> >& value = itr->value;

            MonoObject* exc = NULL;

            void* args[] = { mono_string_new(monoDomain, keyName.c_str()), typeConverter->toMonoObject(value) };

            mono_runtime_invoke(addInboundProperty, processRequest, args, &exc);

            if (exc)
            {
                const char* message = mono_string_to_utf8(mono_object_to_string(exc, NULL));
                return;
            }
        }
    }
    
    /* Fill outbound properties */
    if(d.HasMember("outboundProperties") && d["outboundProperties"].IsObject())
    {
        for (Value::ConstMemberIterator itr = d["outboundProperties"].MemberBegin(); itr != d["outboundProperties"].MemberEnd(); ++itr)
        {
            string keyName = string(itr->name.GetString());
            const GenericValue<UTF8<> >& value = itr->value;

            MonoObject* exc = NULL;

            void* args[] = { mono_string_new(monoDomain, keyName.c_str()), typeConverter->toMonoObject(value) };

            mono_runtime_invoke(addOutboundProperty, processRequest, args, &exc);

            if (exc)
            {
                const char* message = mono_string_to_utf8(mono_object_to_string(exc, NULL));
                return;
            }
        }
    }
    
    /* Fill session properties */
    if(d.HasMember("sessionProperties") && d["sessionProperties"].IsObject())
    {
        for (Value::ConstMemberIterator itr = d["sessionProperties"].MemberBegin(); itr != d["sessionProperties"].MemberEnd(); ++itr)
        {
            string keyName = string(itr->name.GetString());
            const GenericValue<UTF8<> >& value = itr->value;

            MonoObject* exc = NULL;

            void* args[] = { mono_string_new(monoDomain, keyName.c_str()), typeConverter->toMonoObject(value) };

            mono_runtime_invoke(addSessionProperty, processRequest, args, &exc);

            if (exc)
            {
                const char* message = mono_string_to_utf8(mono_object_to_string(exc, NULL));
                return;
            }
        }
    }
}

string JniManager::toException(const char* errorMessage)
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    
    writer.StartObject();
    
    writer.String("exception");
    writer.String(errorMessage);
    
    writer.EndObject();
    
    return sb.GetString();
}

string JniManager::toResponse(MonoObject* monoObject)
{
    assert(monoObject);

    MonoObject* exc = NULL;

    MonoObject* result = mono_runtime_invoke(getResult, monoObject, NULL, &exc);

    if (exc)
    {
        const char* message = mono_string_to_utf8(mono_object_to_string(exc, NULL));
        return toException(message);
    }
    
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    
    // set Mule Message properties
    writer.StartObject();

    if (result != NULL)
    {
        writer.String("payload");
        typeConverter->toJson(result, writer);
    }

    writer.String("invocationProperties");
    typeConverter->convertToJsonMap(monoObject, getInvocationPropertySize, getInvocationProperty, getInvocationPropertyKey, writer);
    
    writer.String("sessionProperties");
    typeConverter->convertToJsonMap(monoObject, getSessionPropertySize, getSessionProperty, getSessionPropertyKey, writer);
    
    writer.String("outboundProperties");
    typeConverter->convertToJsonMap(monoObject, getOutboundPropertySize, getOutboundProperty, getOutboundPropertyKey, writer);
    
    writer.EndObject();
    return sb.GetString();
}
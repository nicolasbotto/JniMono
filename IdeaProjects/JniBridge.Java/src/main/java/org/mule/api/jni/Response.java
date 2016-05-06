package org.mule.api.jni;

import java.util.Map;

public class Response {
    private Object payload;

    public Map<String, Object> getMethodArguments() {
        return methodArguments;
    }

    public void setMethodArguments(Map<String, Object> methodArguments) {
        this.methodArguments = methodArguments;
    }

    public Map<String, Object> getInvocationProperties() {
        return invocationProperties;
    }

    public void setInvocationProperties(Map<String, Object> invocationProperties) {
        this.invocationProperties = invocationProperties;
    }

    public Map<String, Object> getSessionProperties() {
        return sessionProperties;
    }

    public void setSessionProperties(Map<String, Object> sessionProperties) {
        this.sessionProperties = sessionProperties;
    }

    public Map<String, Object> getOutboundProperties() {
        return outboundProperties;
    }

    public void setOutboundProperties(Map<String, Object> outboundProperties) {
        this.outboundProperties = outboundProperties;
    }

    private Map<String, Object> methodArguments;
    private Map<String, Object> invocationProperties;
    private Map<String, Object> sessionProperties;
    private Map<String, Object> outboundProperties;

    public Object getPayload() {
        return payload;
    }

    public void setPayload(Object payload) {
       this.payload = payload;
    }
}
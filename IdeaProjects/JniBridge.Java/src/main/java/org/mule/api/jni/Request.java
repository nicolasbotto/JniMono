package org.mule.api.jni;

import java.util.Map;

public class Request {
    private String assemblyName;
    private String assemblyPath;
    private String methodName;
    private boolean log;
    private boolean notifyEvents;
    private boolean fullTrust;
    private boolean isSingleton;
    private Object result;
    private Map<String, Object> methodArguments;
    private Map<String, Object> invocationProperties;
    private Map<String, Object> sessionProperties;
    private Map<String, Object> outboundProperties;
    private Map<String, String> inboundProperties;

    public String getAssemblyName() {
        return assemblyName;
    }

    public void setAssemblyName(String assemblyName) {
        this.assemblyName = assemblyName;
    }

    public String getAssemblyPath() {
        return assemblyPath;
    }

    public void setAssemblyPath(String assemblyPath) {
        this.assemblyPath = assemblyPath;
    }

    public String getMethodName() {
        return methodName;
    }

    public void setMethodName(String methodName) {
        this.methodName = methodName;
    }

    public boolean getLog() {
        return log;
    }

    public void setLog(Boolean log) {
        this.log = log;
    }

    public boolean getNotifyEvents() {
        return notifyEvents;
    }

    public void setNotifyEvents(Boolean notifyEvents) {
        this.notifyEvents = notifyEvents;
    }

    public boolean getFullTrust() {
        return fullTrust;
    }

    public void setFullTrust(Boolean fullTrust) {
        this.fullTrust = fullTrust;
    }

    public boolean getIsSingleton() {
        return isSingleton;
    }

    public void setIsSingleton(Boolean isSingleton) {
        this.isSingleton = isSingleton;
    }

    public Object getResult() {
        return result;
    }

    public void setResult(Object result) {
        this.result = result;
    }

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

    public Map<String, String> getInboundProperties() {
        return inboundProperties;
    }

    public void setInboundProperties(Map<String, String> inboundProperties) {
        this.inboundProperties = inboundProperties;
    }
}
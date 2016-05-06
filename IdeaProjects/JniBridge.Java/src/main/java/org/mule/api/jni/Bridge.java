package org.mule.api.jni;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Bridge
{
	private JniLogger logger;
	private Object instrumentationManager;
	private Method fireEventMethod = null;
	private final String DLLNAME = "JniBridge";

	// Native methods
	public native void init(String path);
	public native Response invokegitNetMethod(Request request);

	public void initJni(String path)
	{
		// Do version check to load 32 or 64 bit version
		//String finalPath = path + File.separator + DLLNAME + getRuntime() + ".dll";
		//String finalPath = "/home/test/Documents/JniBridge.C/JniBridge.so";
		System.load(path);
	}

	public void setInstrumentationManager(Object instrumentationManager) throws IOException, NoSuchMethodException
	{
		if(instrumentationManager != null) {
			this.instrumentationManager = instrumentationManager;

			if(fireEventMethod == null) {
				fireEventMethod = this.instrumentationManager.getClass().getMethod("fireEvent", new Class[] { String.class, Integer.class });
			}
		}
	}

	public void setLogger(JniLogger logger)
	{
	    this.logger = logger;
	}
	public void log(String message)
	{
		if(this.logger != null) {
			this.logger.debug(message);
		}
	}

	public void instrument(String message, int id) throws InterruptedException, SecurityException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {

		if(fireEventMethod != null)
		{
			fireEventMethod.invoke(this.instrumentationManager, new Object[] { message, id});
		}
	}

	private String getRuntime()
	{
		return System.getProperty("sun.arch.data.model");
	}
}
package org.mule.api.jni;

public class JniLogger {
	private org.apache.log4j.Logger log4j;

	public JniLogger(org.apache.log4j.Logger log4j)
	{
		this.log4j = log4j;
	}

	public void debug(String message)
	{
		if(log4j.isDebugEnabled())
		{
			log4j.debug(message);
		}
	}

	public void info(String message)
	{
		if(log4j.isInfoEnabled())
		{
			log4j.info(message);
		}
	}

	public void trace(String message)
	{
		if(log4j.isTraceEnabled())
		{
			log4j.trace(message);
		}
	}

	public void error(String message)
	{
		log4j.error(message);
	}

}

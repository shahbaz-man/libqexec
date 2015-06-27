package com.asdev.libqexec;

public class QExec {

	private static final String NULL_EXT;

	public static final static int DEFAULT_BUFFER_SIZE = 512;	

	static {
		System.loadLibrary("qexec");
		if(System.getProperty("os.name").toLowerCase().contains("windows")){
			NULL_EXT = " > NUL";
		} else {
			NULL_EXT = " > /dev/null";
		}
	}
	
	public static void main(String[] args) throws Exception {
		// convert args to string
		StringBuilder cmd = new StringBuilder();
		for(String s : args){
			cmd.append(s);
			cmd.append(" ");
		}
		
		// exec
		long start = System.nanoTime();
		exec(cmd.toString(), DEFAULT_BUFFER_SIZE);
		System.out.println("EXEC TOOK: " + ((System.nanoTime() - start) / 1000000.0) + "ms");
		start = System.nanoTime();
		Runtime.getRuntime().exec(args);
		System.out.println("RUNTIME EXEC TOOK: " + ((System.nanoTime() - start) / 1000000.0) + "ms");
		start = System.nanoTime();
		execToNull(cmd.toString());
		System.out.println("EXEC TO NULL TOOK: " + ((System.nanoTime() - start) / 1000000.0) + "ms");
	}
	
	private static native String exec0(String cmd, int bufSize);
	
	public static String exec(String cmd, int bufSize){
		return exec0(cmd, bufSize).trim();
	}
	
	public static native int execToConsole(String cmd);
	
	public static int execToNull(String cmd){
		return execToConsole(cmd + NULL_EXT);
	}
}

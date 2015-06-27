#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "com_asdev_libqexec_QExec.h"

static int const ERROR_CMD_NULL = 3945;

JNIEXPORT jstring JNICALL Java_com_asdev_libqexec_QExec_exec0(JNIEnv *env, jclass class, jstring cmdStr, jint jBufSize){
	const char *cmd = (*env)->GetStringUTFChars(env, cmdStr, NULL);
	int bufSize = (int) jBufSize;
	// check for cmd null
	if(cmd == NULL) return NULL;
	
	char buf[bufSize];
	char *str = NULL;
	char *temp = NULL;
	unsigned int size = 1;
	unsigned int strlength;
	
	FILE *fp;
	
	if((fp = popen(cmd, "r") == NULL){
		return NULL;
	}
	
	// release the cmd
	(*env)->ReleaseStringUTFChars(env, cmdStr, cmd);
	
	while (fgets(buf, bufSize, fp) != NULL) {
		// append it to master
		strlength = strlen(buf);
		temp = realloc(str, size + strlength);
		if(temp == NULL){
		    // alloc error
		} else {
			str = temp;
		}
		strcpy(str + size - 1, buf);
		size += strlength;
	}
	
	// close
	pclose(fp);
	
	return (*env)->NewStringUTF(env, str);
}

JNIEXPORT jint JNICALL Java_com_asdev_libqexec_QExec_execToConsole
  (JNIEnv *env, jclass class, jstring cmdStr){
	const char *cmd = (*env)->GetStringUTFChars(env, cmdStr, NULL);
	// check for null cmd
	if(cmd == NULL) return (jint) ERROR_CMD_NULL;
	// exec
	int res = system(cmd);
	// release
	(*env)->ReleaseStringUTFChars(env, cmdStr, cmd);
	// return
	return (jint) res;
  }
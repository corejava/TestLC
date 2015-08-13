/*
 * test.c
 *
 *  Created on: Jul 29, 2015
 *      Author: jon
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}

int test1() {
	int a = 1;
	a = write(1, "Here is some data\n", 19);
	printf("write size=%d\n", a);
	a = write(2, "A write error has occurred on file description 1\n", 46);
	printf("error size=%d\n", a);
	return 0;
}

int test2() {
	char buffer[128];
	int nread;

	nread = read(0, buffer, 128);
	if (nread == -1) {
		const char* err_string = "A read error has occurred\n";
		int len;
		GET_ARRAY_LEN(err_string, len);
		write(2, err_string, len);
	}
	if (write(1, buffer, nread) != nread) {
		const char* err_string = "A write error has occurred\n";
		int len;
		GET_ARRAY_LEN(err_string, len);
		write(2, err_string, len);
	}
	return 0;
}

void test3() {
	open("testFile", O_CREAT, S_IRUSR | S_IXOTH);
}

/**
 * Test dir filesystem on Linux&MacOS
 */
void test4() {
	char buf[255];
	char* pwd = getcwd(buf, 255);
	printf("Your are in the %s\n", pwd);
	const char* cwd = "/usr";
	chdir(cwd);
	pwd = getcwd(buf, 255);
	printf("Your are in the %s\n", pwd);
}

/**
 * Test print dir
 */
void test5(char *dir, int depth) {
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "cannot open directory: s%\n", dir);
		return;
	}

	chdir(dir);
	while((entry=readdir(dp))!=NULL){
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			//
			if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0){
				continue;
			}
			printf("%*s%s/\n",depth,"",entry->d_name);
			test5(entry->d_name,depth+4);
		}else{
			printf("%*s%s\n",depth,"",entry->d_name);
		}
	}
	chdir("..");
	closedir(dp);
}

int main() {
	test5("/Users/jon/work/testLC",0);
	return 0;
}

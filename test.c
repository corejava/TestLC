/*
 * test.c
 *
 *  Created on: Jul 29, 2015
 *      Author: jon
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


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

void test3(){
	open("testFile",O_CREAT,S_IRUSR|S_IXOTH);
}


void test4(){

}

int main() {
	test3();
	return 0;
}

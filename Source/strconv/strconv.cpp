#include <iostream>
#include <string.h>
#include <limits.h>
#include "strconv.h"
using namespace std;

// returns false if successful
// returns true if not successful
bool overflow(const char* s, int len, int& returnVal, int pos){
	bool overIntMax = false;
	if(pos == -1){
		pos = len-1;
	}
	if(pos == 0){
		returnVal = s[0]-'0'; // converting from ascii to an int
	}
	else {
		
		int prevVal; // = (( ... ((s[0])*10 + s[1]) ... )*10 + s[pos-1])
		
		int newVal = s[pos]-'0'; // converting from ascii to an int
		if(overflow(s, len, prevVal, pos-1))
			overIntMax = true;
		else {
			if((INT_MAX - newVal) / 10 < prevVal)
				overIntMax = true;
			else
				returnVal = prevVal * 10 + newVal;
		}
	}
	return overIntMax;
}
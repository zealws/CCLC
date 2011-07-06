#ifndef _STRING_CONVERSION_H_
#define _STRING_CONVERSION_H_

// returns false if successful
// returns true if not successful
bool overflow(const char* s, int len, int& val, int pos = -1);

#endif

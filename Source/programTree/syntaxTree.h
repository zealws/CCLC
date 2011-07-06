#ifndef _SYNTAX_TREE_DECLARATION_
#define _SYNTAX_TREE_DECLARATION_

#include <vector>
#include "programTree.h"
#include "../typeTree/typeTree.h"
#include "../Library/orderedPair.h"

using namespace std;

typedef orderedPair<programTree*, typeTree*> programTypePair;

typedef orderedPair<vector<programTree*>, typeTree*> programListTypePair;

extern programTypePair syntaxTree;

#endif

// copied for the most part from sampleVisitors.h

#ifndef _TYPE_TREE_VISITORS_H_
#define _TYPE_TREE_VISITORS_H_

#include <string>
#include "typeTree.h"
#include "abstractTypeTreeVisitors.h"
using namespace std;

// frontend for subtypeVisitor
bool subtype(typeTree* tree1, typeTree* tree2);

// frontend for subtype()
bool supertype(typeTree* tree1, typeTree* tree2);

// frontend for subtype() and supertype()
bool compatible(typeTree* tree1, typeTree* tree2);
bool combinable(typeTree* tree1, typeTree* tree2);

// frontends for dsupVisitor
typeTree* combine(typeTree* tree1, typeTree* tree2);
typeTree* dsup(typeTree* tree1, typeTree* tree2);

// frontend for csubVisitor
typeTree* csub(typeTree* tree1, typeTree* tree2);

// frontend for deepCopyVisitor
typeTree* deepCopy(typeTree* tree1);

// frontend for toStrVisitor
string toStr(typeTree* tree1);

// frontend for mutableVisitor
bool isMutable(typeTree* tree1);

// frontend for isFunctionVisitor
bool isFun(typeTree* tree1);

// frontend for extractReturnTypeVisitor
typeTree* returnType(typeTree* tree1);

// frontend for extractParameterTypesVisitor
vector<typeTree*> parameterTypes(typeTree* tree1);

// frontend for isIntVisitor
bool isInt(typeTree* tree1);

// frontend for isTrivVisitor
bool isTriv(typeTree* tree1);

// frontend for isConVisitor
bool isCon(typeTree* tree1);

// frontend for unConVisitor
typeTree* unCon(typeTree* tree1);

// frontend for isRefVisitor
bool isRef(typeTree* tree1);

// frontend for unRefVisitor
typeTree* unRef(typeTree* tree1);

// frontend for isRefvecVisitor
bool isRefvec(typeTree* tree1);

// frontend for unRefvecVisitor
typeTree* unRefvec(typeTree* tree1);

// returns the size in bytes of a type
int sizeOf(typeTree* tree1);

// returns the dimension of a type
// simple types are dimension 0
// dimension( refvec T )  = 1 + dimension( T )
int dimension(typeTree* tree);

/*
 * deepCopyVisitor Class Definition
 */
class deepCopyVisitor : public singleDispatchTypeTreeVisitor<typeTree*> {
private:

protected:

public:
    deepCopyVisitor();

    static typeTree* visitIntTypeTreeNode(thisVisitorType& thisVisitor, intTypeTreeNode* visitedNodePtr);
    static typeTree* visitTrivTypeTreeNode(thisVisitorType& thisVisitor, trivTypeTreeNode* visitedNodePtr);
    static typeTree* visitImmutTypeTreeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
    static typeTree* visitConTypeTreeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr);
    static typeTree* visitRefTypeTreeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr);
    static typeTree* visitRefvecTypeTreeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode* visitedNodePtr);
    static typeTree* visitFunTypeTreeNode(thisVisitorType& thisVisitor, funTypeTreeNode* visitedNodePtr);

    virtual typeTree* defaultCase(typeTreeNode* visitedNodePtr);
};

/*
 * toStrVisitor
 *
 * Returns the string format for a type tree.
 */
class toStrVisitor : public singleDispatchTypeTreeVisitor< string > {
private:
    toStrVisitor(const toStrVisitor& other);
        // leave unimplemented
    toStrVisitor& operator=(const toStrVisitor& other);
        // leave unimplemented

protected:
    // nothing
    
public:
    toStrVisitor();

    virtual string defaultCase(typeTreeNode* visitedNodePtr);

    static string toStringIntTreeNode(
        thisVisitorType& thisVisitor,
        intTypeTreeNode* visitedNodePtr);

    static string toStringTrivTreeNode(
        thisVisitorType& thisVisitor,
        trivTypeTreeNode* visitedNodePtr);

    static string toStringImmutTreeNode(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr);

    static string toStringConTreeNode(
        thisVisitorType& thisVisitor,
        conTypeTreeNode* visitedNodePtr);

    static string toStringRefTreeNode(
        thisVisitorType& thisVisitor,
        refTypeTreeNode* visitedNodePtr);

    static string toStringRefvecTreeNode(
        thisVisitorType& thisVisitor,
        refvecTypeTreeNode* visitedNodePtr);

    static string toStringFunTreeNode(
        thisVisitorType& thisVisitor,
        funTypeTreeNode* visitedNodePtr);
};

/*
 * subtypeVisitor
 *
 * Visits two typeTrees, returning true if the first is a subtype of the second.
 */
class subtypeVisitor : public predicateDoubleDispatchTypeTreeVisitor {
private:
    subtypeVisitor(const subtypeVisitor& other);
        // leave unimplemented

    subtypeVisitor& operator=(const subtypeVisitor& other);
        // leave unimplemented

protected:
    // nothing
    
public:

    subtypeVisitor();

    static bool subtypeIntIntTreeNodePair(
        thisVisitorType& thisVisitor,
        intTypeTreeNode* visitedNodePtr01,
        intTypeTreeNode* visitedNodePtr02);
    static bool subtypeTrivTrivTreeNodePair(
        thisVisitorType& thisVisitor,
        trivTypeTreeNode* visitedNodePtr01,
        trivTypeTreeNode* visitedNodePtr02);
    static bool subtypeImmutImmutTreeNodePair(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr01,
        immutTypeTreeNode* visitedNodePtr02);
    // <frustration>
    static bool subtypeImmutIntTreeNodePair(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr01,
        intTypeTreeNode* visitedNodePtr02);
    static bool subtypeImmutTrivTreeNodePair(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr01,
        trivTypeTreeNode* visitedNodePtr02);
    static bool subtypeImmutConTreeNodePair(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr01,
        conTypeTreeNode* visitedNodePtr02);
    static bool subtypeImmutRefTreeNodePair(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr01,
        refTypeTreeNode* visitedNodePtr02);
    static bool subtypeImmutRefvecTreeNodePair(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr01,
        refvecTypeTreeNode* visitedNodePtr02);
    static bool subtypeImmutFunTreeNodePair(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr01,
        funTypeTreeNode* visitedNodePtr02);
    // -- break --
    static bool subtypeIntImmutTreeNodePair(
        thisVisitorType& thisVisitor,
        intTypeTreeNode* visitedNodePtr01,
        immutTypeTreeNode* visitedNodePtr02);
    static bool subtypeTrivImmutTreeNodePair(
        thisVisitorType& thisVisitor,
        trivTypeTreeNode* visitedNodePtr01,
        immutTypeTreeNode* visitedNodePtr02);
    static bool subtypeConImmutTreeNodePair(
        thisVisitorType& thisVisitor,
        conTypeTreeNode* visitedNodePtr01,
        immutTypeTreeNode* visitedNodePtr02);
    static bool subtypeRefImmutTreeNodePair(
        thisVisitorType& thisVisitor,
        refTypeTreeNode* visitedNodePtr01,
        immutTypeTreeNode* visitedNodePtr02);
    static bool subtypeRefvecImmutTreeNodePair(
        thisVisitorType& thisVisitor,
        refvecTypeTreeNode* visitedNodePtr01,
        immutTypeTreeNode* visitedNodePtr02);
    static bool subtypeFunImmutTreeNodePair(
        thisVisitorType& thisVisitor,
        funTypeTreeNode* visitedNodePtr01,
        immutTypeTreeNode* visitedNodePtr02);
    // </frustration>
    static bool subtypeConConTreeNodePair(
        thisVisitorType& thisVisitor,
        conTypeTreeNode* visitedNodePtr01,
        conTypeTreeNode* visitedNodePtr02);
    static bool subtypeRefRefTreeNodePair(
        thisVisitorType& thisVisitor,
        refTypeTreeNode* visitedNodePtr01,
        refTypeTreeNode* visitedNodePtr02);
    static bool subtypeRefvecRefvecTreeNodePair(
        thisVisitorType& thisVisitor,
        refvecTypeTreeNode* visitedNodePtr01,
        refvecTypeTreeNode* visitedNodePtr02);
    static bool subtypeFunFunTreeNodePair(
        thisVisitorType& thisVisitor,
        funTypeTreeNode* visitedNodePtr01,
        funTypeTreeNode* visitedNodePtr02);
};

/*
 * mutableVisitor
 *
 * visites a typeTree and returns true if it is not an immut typeTree
 */
class mutableVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:
    mutableVisitor(const mutableVisitor& other);
    // leave unimplemented
    mutableVisitor& operator=(const mutableVisitor& other);
    // leave unimplemented
    
protected:
    // nothing
    
public:
    mutableVisitor();
    
    virtual bool defaultCase(typeTreeNode* visitedNodePtr);
    
    static bool mutableImmutTreeNode(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr);
};

/*
 * immutableVisitor
 *
 * visites a typeTree and returns true if it is an immut typeTree
 */
class immutableVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:
    immutableVisitor(const immutableVisitor& other);
    // leave unimplemented
    immutableVisitor& operator=(const immutableVisitor& other);
    // leave unimplemented
    
protected:
    // nothing
    
public:
    immutableVisitor();
    
    virtual bool defaultCase(typeTreeNode* visitedNodePtr);
    
    static bool immutableImmutTreeNode(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr);
};

/*
 * dsupVisitor Class Definition
 */
class dsupVisitor : public doubleDispatchTypeTreeVisitor <typeTree*> {
private:
    
protected:
    
public:
    dsupVisitor();

    // <-- int -->
    static typeTree* dsupIntInt(
        thisVisitorType& thisVisitor,
        intTypeTreeNode* visitedNodePtr1,
        intTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupIntImmut(
        thisVisitorType& thisVisitor,
        intTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    // <-- triv -->
    static typeTree* dsupTrivTriv(
        thisVisitorType& thisVisitor,
        trivTypeTreeNode* visitedNodePtr1,
        trivTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupTrivImmut(
        thisVisitorType& thisVisitor,
        trivTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    // <-- immut -->
    static typeTree* dsupImmutInt(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        intTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupImmutTriv(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        trivTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupImmutImmut(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupImmutCon(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        conTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupImmutRef(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        refTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupImmutRefvec(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        refvecTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupImmutFun(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        funTypeTreeNode* visitedNodePtr2
    );
    // <-- con -->
    static typeTree* dsupConImmut(
        thisVisitorType& thisVisitor,
        conTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupConCon(
        thisVisitorType& thisVisitor,
        conTypeTreeNode* visitedNodePtr1,
        conTypeTreeNode* visitedNodePtr2
    );
    // <-- ref -->
    static typeTree* dsupRefImmut(
        thisVisitorType& thisVisitor,
        refTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupRefRef(
        thisVisitorType& thisVisitor,
        refTypeTreeNode* visitedNodePtr1,
        refTypeTreeNode* visitedNodePtr2
    );
    // <-- refvec -->
    static typeTree* dsupRefvecImmut(
        thisVisitorType& thisVisitor,
        refvecTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupRefvecRefvec(
        thisVisitorType& thisVisitor,
        refvecTypeTreeNode* visitedNodePtr1,
        refvecTypeTreeNode* visitedNodePtr2
    );
    // <-- fun -->
    static typeTree* dsupFunImmut(
        thisVisitorType& thisVisitor,
        funTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* dsupFunFun(
        thisVisitorType& thisVisitor,
        funTypeTreeNode* visitedNodePtr1,
        funTypeTreeNode* visitedNodePtr2
    );

    virtual typeTree* defaultCase(
        typeTreeNode * visitedNodePtr1,
        typeTreeNode * visitedNodePtr2);
};

/*
 * csubVisitor Class Definition
 */
class csubVisitor : public doubleDispatchTypeTreeVisitor <typeTree*> {
private:

protected:

public:
    csubVisitor();

    // <-- int -->
    static typeTree* csubIntInt(
        thisVisitorType& thisVisitor,
        intTypeTreeNode* visitedNodePtr1,
        intTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubIntImmut(
        thisVisitorType& thisVisitor,
        intTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    // <-- triv -->
    static typeTree* csubTrivTriv(
        thisVisitorType& thisVisitor,
        trivTypeTreeNode* visitedNodePtr1,
        trivTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubTrivImmut(
        thisVisitorType& thisVisitor,
        trivTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    // <-- immut -->
    static typeTree* csubImmutInt(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        intTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubImmutTriv(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        trivTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubImmutImmut(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubImmutCon(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        conTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubImmutRef(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        refTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubImmutRefvec(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        refvecTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubImmutFun(
        thisVisitorType& thisVisitor,
        immutTypeTreeNode* visitedNodePtr1,
        funTypeTreeNode* visitedNodePtr2
    );
    // <-- con -->
    static typeTree* csubConImmut(
        thisVisitorType& thisVisitor,
        conTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubConCon(
        thisVisitorType& thisVisitor,
        conTypeTreeNode* visitedNodePtr1,
        conTypeTreeNode* visitedNodePtr2
    );
    // <-- ref -->
    static typeTree* csubRefImmut(
        thisVisitorType& thisVisitor,
        refTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubRefRef(
        thisVisitorType& thisVisitor,
        refTypeTreeNode* visitedNodePtr1,
        refTypeTreeNode* visitedNodePtr2
    );
    // <-- refvec -->
    static typeTree* csubRefvecImmut(
        thisVisitorType& thisVisitor,
        refvecTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubRefvecRefvec(
        thisVisitorType& thisVisitor,
        refvecTypeTreeNode* visitedNodePtr1,
        refvecTypeTreeNode* visitedNodePtr2
    );
    // <-- fun -->
    static typeTree* csubFunImmut(
        thisVisitorType& thisVisitor,
        funTypeTreeNode* visitedNodePtr1,
        immutTypeTreeNode* visitedNodePtr2
    );
    static typeTree* csubFunFun(
        thisVisitorType& thisVisitor,
        funTypeTreeNode* visitedNodePtr1,
        funTypeTreeNode* visitedNodePtr2
    );

    virtual typeTree* defaultCase(
        typeTreeNode * visitedNodePtr1,
        typeTreeNode * visitedNodePtr2);
};

/*
 * extractReturnTypeVisitor Class Definition
 */
class extractReturnTypeVisitor : public singleDispatchTypeTreeVisitor<typeTree*> {
private:
    
protected:
    
public:
    extractReturnTypeVisitor();

    virtual typeTree* defaultCase(typeTreeNode* visitedNodePtr);

    static typeTree* extractReturnFunTypeTreeNode(thisVisitorType& thisVisitor,
                                                  funTypeTreeNode* visitedNodePtr);

    static typeTree* extractReturnImmutTypeTreeNode(thisVisitorType& thisVisitor,
                                                    immutTypeTreeNode* visitedNodePtr);
};

/*
 * extractParameterTypesVisitor Class Definition
 */
class extractParameterTypesVisitor : public singleDispatchTypeTreeVisitor<vector<typeTree*> > {
private:

protected:

public:
    extractParameterTypesVisitor();

    virtual vector<typeTree*> defaultCase(typeTreeNode* visitedNodePtr);

    static vector<typeTree*> extractParameterTypesFunTypeNode(thisVisitorType& thisVisitor,
                                                              funTypeTreeNode* visitedNodePtr);

    static vector<typeTree*> extractParameterTypesImmutTypeNode(thisVisitorType& thisVisitor,
                                                                immutTypeTreeNode* visitedNodePtr);
};

/*
 * getVectorTypeVisitor Class Definition
 */
class getVectorTypeVisitor : public singleDispatchTypeTreeVisitor<typeTree*> {
private:

protected:

public:
    getVectorTypeVisitor();

    virtual typeTree* defaultCase(typeTreeNode* visitedNodePtr);

    static typeTree* getVectorTypeRefvecTreeNode(thisVisitorType& thisVisitor,
                                                 refvecTypeTreeNode* visitedNodePtr);
};

/*
 * unContinueVisitor Class Definition
 */
class unContinueVisitor : public singleDispatchTypeTreeVisitor<typeTree*> {
private:

protected:

public:
    unContinueVisitor();

    virtual typeTree* defaultCase(typeTreeNode* visitedNodePtr);

    static typeTree* unContinueConTypeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr);

    static typeTree* unContinueImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * isFunctionVisitor Class Definition
 */
class isFunctionVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:

protected:

public:
    isFunctionVisitor();
    
    static bool isFunFunTypeNode(thisVisitorType& thisVisitor, funTypeTreeNode* visitedNodePtr);
    
    static bool isFunImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * isIntVisitor Class Definition
 */
class isIntVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:

protected:

public:
	isIntVisitor();

	static bool isIntIntTypeNode(thisVisitorType& thisVisitor, intTypeTreeNode* visitedNodePtr);

	static bool isIntImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 *
 */
class isTrivVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:

protected:

public:
	isTrivVisitor();

	static bool isTrivTrivTypeNode(thisVisitorType& thisVisitor, trivTypeTreeNode* visitedNodePtr);

	static bool isTrivImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * isConVisitor Class Definition
 */
class isConVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:

protected:

public:
	isConVisitor();

	static bool isConConTypeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr);

	static bool isConImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * unConVisitor Class Definition
 */
class unConVisitor : public singleDispatchTypeTreeVisitor<typeTree*> {
private:

protected:

public:
	unConVisitor();

	typeTree* defaultCase(typeTreeNode* visitedNodePtr);

	static typeTree* unConConTypeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr);
};

/*
 * isRefVisitor Class Definition
 */
class isRefVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:

protected:

public:
	isRefVisitor();

	static bool isRefRefTypeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr);

	static bool isRefImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * unReVisitor Class Definition
 */
class unRefVisitor : public singleDispatchTypeTreeVisitor<typeTree*> {
private:

protected:

public:
	unRefVisitor();

	typeTree* defaultCase(typeTreeNode* visitedNodePtr);

	static typeTree* unRefRefTypeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr);

	static typeTree* unRefImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * isRefvecVisitor Class Definition
 */
class isRefvecVisitor : public predicateSingleDispatchTypeTreeVisitor {
private:

protected:

public:
	isRefvecVisitor();

	static bool isRefvecRefvecTypeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode*  visitedNodePtr);

	static bool isRefvecImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * unRefvecVisitor Class Definition
 */
class unRefvecVisitor : public singleDispatchTypeTreeVisitor<typeTree*> {
private:

protected:

public:
    unRefvecVisitor();

    typeTree* defaultCase(typeTreeNode* visitedNodePtr);

    static typeTree* unRefvecRefvecTypeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode* visitedNodePtr);

    static typeTree* unRefvecImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
};

/*
 * sizeOfTypeVisitor Class Definition
 */
class sizeOfTypeVisitor : public singleDispatchTypeTreeVisitor<int> {
private:

protected:

public:
    sizeOfTypeVisitor();

    int defaultCase(typeTreeNode* visitedNodePtr);

    static int sizeOfIntTypeTreeNode(thisVisitorType& thisVisitor, intTypeTreeNode* visitedNodePtr);
    static int sizeOfTrivTypeTreeNode(thisVisitorType& thisVisitor, trivTypeTreeNode* visitedNodePtr);
    static int sizeOfImmutTypeTreeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr);
    static int sizeOfConTypeTreeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr);
    static int sizeOfRefTypeTreeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr);
    static int sizeOfRefvecTypeTreeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode* visitedNodePtr);
    static int sizeOfFunTypeTreeNode(thisVisitorType& thisVisitor, funTypeTreeNode* visitedNodePtr);
};

#endif

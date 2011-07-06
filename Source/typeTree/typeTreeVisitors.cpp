#include <string>
#include <iostream>
#include "abstractTypeTreeVisitors.h"
#include "typeTree.h"
#include "../error/error.h"
#include "typeTreeVisitors.h"
using namespace std;

// frontend for subtypeVisitor
bool subtype(typeTree* tree1, typeTree* tree2) {
    if(tree1 == NULL || tree2 == NULL)
        return false;
    else {
//         debugMessage("subtype:");
//         debugMessage(toStr(tree1));
//         debugMessage(toStr(tree2));
        subtypeVisitor v;
        return v.visit(*tree1, *tree2);
    }
}

// frontend for subtype()
bool supertype(typeTree* tree1, typeTree* tree2) {
    if(tree1 == NULL || tree2 == NULL)
        return false;
    else {
        return subtype(tree2, tree1);
    }
}

// frontend for subtype() and supertype()
bool compatible(typeTree* tree1, typeTree* tree2) {
    if(tree1 == NULL || tree2 == NULL)
        return false;
    else {
        return subtype(tree1, tree2) or supertype(tree1, tree2);
    }
}
bool combinable(typeTree* tree1, typeTree* tree2) {
    return compatible(tree1, tree2);
}

// frontends for dsupVisitor
typeTree* combine(typeTree* tree1, typeTree* tree2) {
    if(tree1 == NULL || tree2 == NULL)
        return NULL;
    else {
        dsupVisitor v;
        return v.visit(*tree1, *tree2);
    }
}
typeTree* dsup(typeTree* tree1, typeTree* tree2) {
    return combine(tree1, tree2);
}

// frontend for csubVisitor
typeTree* csub(typeTree* tree1, typeTree* tree2) {
    if(tree1 == NULL || tree2 == NULL)
        return NULL;
    else {
        csubVisitor v;
        return v.visit(*tree1, *tree2);
    }
}

// frontend for deepCopyVisitor
typeTree* deepCopy(typeTree* tree1) {
    if(tree1 == NULL)
        return NULL;
    else {
        deepCopyVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for toStrVisitor
string toStr(typeTree* tree1) {
    if(tree1 == NULL)
        return "errorType";
    else {
        toStrVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for mutableVisitor
bool isMutable(typeTree* tree1) {
    if(tree1 == NULL)
        return false;
    else {
        mutableVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for isFunctionVisitor
bool isFun(typeTree* tree1) {
    if(tree1 == NULL)
        return false;
    else {
        isFunctionVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for extractReturnTypeVisitor
typeTree* returnType(typeTree* tree1) {
    if(tree1 == NULL)
        return NULL;
    else {
        extractReturnTypeVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for extractParameterTypesVisitor
vector<typeTree*> parameterTypes(typeTree* tree1) {
    if(tree1 == NULL)
        return vector<typeTree*>();
    else {
        extractParameterTypesVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for isIntVisitor
bool isInt(typeTree* tree1) {
    if(tree1 == NULL)
        return false;
    else {
        isIntVisitor v;
        return v.visit(*tree1);
    }
}

// frontend  for isTrivVisitor
bool isTriv(typeTree* tree1) {
    if(tree1 == NULL)
        return false;
    else {
        isTrivVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for isConVisitor
bool isCon(typeTree* tree1) {
    if(tree1 == NULL)
        return false;
    else {
        isConVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for unConVisitor
typeTree* unCon(typeTree* tree1) {
    if(tree1 == NULL)
        return NULL;
    else {
        unConVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for isRefVisitor
bool isRef(typeTree* tree1) {
    if(tree1 == NULL)
        return false;
    else {
        isRefVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for unRefVisitor
typeTree* unRef(typeTree* tree1) {
    if(tree1 == NULL)
        return NULL;
    else {
        unRefVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for isRefvecVisitor
bool isRefvec(typeTree* tree1) {
    if(tree1 == NULL)
        return false;
    else {
        isRefvecVisitor v;
        return v.visit(*tree1);
    }
}

// frontend for unRefvecVisitor
typeTree* unRefvec(typeTree* tree1) {
    if(tree1 == NULL)
        return NULL;
    else {
        unRefvecVisitor v;
        return v.visit(*tree1);
    }
}

// returns the size in bytes of a type
int sizeOf(typeTree* tree1) {
    if(tree1 == NULL)
        return -1;
    else {
        sizeOfTypeVisitor v;
        return v.visit(*tree1);
    }
}

// returns the dimension of a type
// simple types are dimension 0
// dimension( refvec T )  = 1 + dimension( T )
int dimension(typeTree* tree) {
    if(tree == NULL)
        return -1;
    else {
        if(isRefvec(tree))
            return 1 + dimension(unRefvec(tree));
        else
            return 0;
    }
}

/*
 * Class deepCopyVisitor
 */
deepCopyVisitor::deepCopyVisitor()
    : singleDispatchTypeTreeVisitor<typeTree*>() {
    add< intTypeTreeNode >(visitIntTypeTreeNode);
    add< trivTypeTreeNode >(visitTrivTypeTreeNode);
    add< immutTypeTreeNode >(visitImmutTypeTreeNode);
    add< conTypeTreeNode >(visitConTypeTreeNode);
    add< refTypeTreeNode >(visitRefTypeTreeNode);
    add< refvecTypeTreeNode >(visitRefvecTypeTreeNode);
    add< funTypeTreeNode >(visitFunTypeTreeNode);
}

typeTree* deepCopyVisitor::visitIntTypeTreeNode(thisVisitorType& thisVisitor, intTypeTreeNode* visitedNodePtr) {
    return new intTypeTree();
}

typeTree* deepCopyVisitor::visitTrivTypeTreeNode(thisVisitorType& thisVisitor, trivTypeTreeNode* visitedNodePtr) {
    return new trivTypeTree();
}

typeTree* deepCopyVisitor::visitImmutTypeTreeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return new immutTypeTree(deepCopy(visitedNodePtr->subTreeRef()));
}

typeTree* deepCopyVisitor::visitConTypeTreeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr) {
    return new conTypeTree(deepCopy(visitedNodePtr->subTreeRef()));
}

typeTree* deepCopyVisitor::visitRefTypeTreeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr) {
    return new refTypeTree(deepCopy(visitedNodePtr->subTreeRef()));
}

typeTree* deepCopyVisitor::visitRefvecTypeTreeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode* visitedNodePtr) {
    return new refvecTypeTree(deepCopy(visitedNodePtr->subTreeRef()));
}

typeTree* deepCopyVisitor::visitFunTypeTreeNode(thisVisitorType& thisVisitor, funTypeTreeNode* visitedNodePtr) {
    vector<typeTree*> params;
    for(int i = 0; i < visitedNodePtr->numParameters(); i++){
        params.push_back(deepCopy(visitedNodePtr->parameterTypeRef(i)));
    }
    return new funTypeTree(deepCopy(visitedNodePtr->returnTypeRef()),
                           params);
}


typeTree* deepCopyVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return new intTypeTree();
}


/*
 * Class toStrVisitor
 */

/* Private Members */

// nothing

/* Protected Members */

// nothing

/* Public Members */

toStrVisitor::toStrVisitor()
    : singleDispatchTypeTreeVisitor< string >() {

    add< intTypeTreeNode >(toStringIntTreeNode);
    add< trivTypeTreeNode >(toStringTrivTreeNode);
    add< immutTypeTreeNode >(toStringImmutTreeNode);
    add< conTypeTreeNode >(toStringConTreeNode);
    add< refTypeTreeNode >(toStringRefTreeNode);
    add< refvecTypeTreeNode >(toStringRefvecTreeNode);
    add< funTypeTreeNode >(toStringFunTreeNode);

}

string toStrVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return "";
}

string toStrVisitor::toStringIntTreeNode(
    thisVisitorType& thisVisitor,
    intTypeTreeNode* visitedNodePtr) {

    return "int";
}

string toStrVisitor::toStringTrivTreeNode(
    thisVisitorType& thisVisitor,
    trivTypeTreeNode* visitedNodePtr) {

    return "triv";
}

string toStrVisitor::toStringImmutTreeNode(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr) {

    return "immut " + toStr(visitedNodePtr -> subTreeRef());
}

string toStrVisitor::toStringConTreeNode(
    thisVisitorType& thisVisitor,
    conTypeTreeNode* visitedNodePtr){
    
    return "con " + toStr(visitedNodePtr -> subTreeRef());
}

string toStrVisitor::toStringRefTreeNode(
    thisVisitorType& thisVisitor,
    refTypeTreeNode* visitedNodePtr){
    
    return "ref " + toStr(visitedNodePtr -> subTreeRef());
}

string toStrVisitor::toStringRefvecTreeNode(
    thisVisitorType& thisVisitor,
    refvecTypeTreeNode* visitedNodePtr){
    
    return "ref vec " + toStr(visitedNodePtr -> subTreeRef());
}

string toStrVisitor::toStringFunTreeNode(
    thisVisitorType& thisVisitor,
    funTypeTreeNode* visitedNodePtr){

    string result = "fun ( ";

    for(int i = 0; i < visitedNodePtr->numParameters(); i++) {
        result += toStr(visitedNodePtr -> parameterTypeRef(i));
        if(i < visitedNodePtr->numParameters()-1)
            result += ", ";
    }

    result += " ) " + toStr(visitedNodePtr -> returnTypeRef());
    
    return result;
}

/*
 * Class subtypeVisitor
 */

/* Private Members */

// nothing

/* Protected Members */

// nothing

/* Public Members */

subtypeVisitor::subtypeVisitor()
    : predicateDoubleDispatchTypeTreeVisitor() {
    add < intTypeTreeNode, intTypeTreeNode >(subtypeIntIntTreeNodePair);
    add < trivTypeTreeNode, trivTypeTreeNode >(subtypeTrivTrivTreeNodePair);
    add < immutTypeTreeNode, immutTypeTreeNode >(subtypeImmutImmutTreeNodePair);

    add < immutTypeTreeNode, intTypeTreeNode >(subtypeImmutIntTreeNodePair);
    add < immutTypeTreeNode, trivTypeTreeNode >(subtypeImmutTrivTreeNodePair);
    add < immutTypeTreeNode, conTypeTreeNode >(subtypeImmutConTreeNodePair);
    add < immutTypeTreeNode, refTypeTreeNode >(subtypeImmutRefTreeNodePair);
    add < immutTypeTreeNode, refvecTypeTreeNode >(subtypeImmutRefvecTreeNodePair);
    add < immutTypeTreeNode, funTypeTreeNode >(subtypeImmutFunTreeNodePair);

    add < intTypeTreeNode, immutTypeTreeNode >(subtypeIntImmutTreeNodePair);
    add < trivTypeTreeNode, immutTypeTreeNode >(subtypeTrivImmutTreeNodePair);
    add < conTypeTreeNode, immutTypeTreeNode >(subtypeConImmutTreeNodePair);
    add < refTypeTreeNode, immutTypeTreeNode >(subtypeRefImmutTreeNodePair);
    add < refvecTypeTreeNode, immutTypeTreeNode >(subtypeRefvecImmutTreeNodePair);
    add < funTypeTreeNode, immutTypeTreeNode >(subtypeFunImmutTreeNodePair);
    
    add < conTypeTreeNode, conTypeTreeNode >(subtypeConConTreeNodePair);
    add < refTypeTreeNode, refTypeTreeNode >(subtypeRefRefTreeNodePair);
    add < refvecTypeTreeNode, refvecTypeTreeNode >(subtypeRefvecRefvecTreeNodePair);
    add < funTypeTreeNode, funTypeTreeNode >(subtypeFunFunTreeNodePair);
}

bool subtypeVisitor::subtypeIntIntTreeNodePair(
    thisVisitorType& thisVisitor,
    intTypeTreeNode* visitedNodePtr01,
    intTypeTreeNode* visitedNodePtr02) {
    return true;
}

bool subtypeVisitor::subtypeTrivTrivTreeNodePair(
    thisVisitorType& thisVisitor,
    trivTypeTreeNode* visitedNodePtr01,
    trivTypeTreeNode* visitedNodePtr02) {
    return true;
}

bool subtypeVisitor::subtypeImmutImmutTreeNodePair(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr01,
    immutTypeTreeNode* visitedNodePtr02) {
    return subtype(visitedNodePtr01->subTreeRef(),
                             visitedNodePtr02->subTreeRef());
}

bool subtypeVisitor::subtypeImmutIntTreeNodePair(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr01,
    intTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitIntTypeTreeNode(v, visitedNodePtr02);
    bool res = subtype(visitedNodePtr01->subTreeRef(),
                       t);
    delete t;
    return res;
}

bool subtypeVisitor::subtypeImmutTrivTreeNodePair(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr01,
    trivTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitTrivTypeTreeNode(v, visitedNodePtr02);
    bool res = subtype(visitedNodePtr01->subTreeRef(),
                       t);
    delete t;
    return res;
}

bool subtypeVisitor::subtypeImmutConTreeNodePair(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr01,
    conTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitConTypeTreeNode(v, visitedNodePtr02);
    bool res = subtype(visitedNodePtr01->subTreeRef(),
                                 t);
    delete t;
    return res;
}

bool subtypeVisitor::subtypeImmutRefTreeNodePair(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr01,
    refTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitRefTypeTreeNode(v, visitedNodePtr02);
    bool res = subtype(visitedNodePtr01->subTreeRef(),
                       t);
    delete t;
    return res;
}

bool subtypeVisitor::subtypeImmutRefvecTreeNodePair(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr01,
    refvecTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitRefvecTypeTreeNode(v, visitedNodePtr02);
    bool res = subtype(visitedNodePtr01->subTreeRef(),
                       t);
    delete t;
    return res;
}

bool subtypeVisitor::subtypeImmutFunTreeNodePair(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr01,
    funTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitFunTypeTreeNode(v, visitedNodePtr02);
    bool res = subtype(visitedNodePtr01->subTreeRef(),
                       t);
    delete t;
    return res;
}

bool subtypeVisitor::subtypeIntImmutTreeNodePair(
    thisVisitorType& thisVisitor,
    intTypeTreeNode* visitedNodePtr01,
    immutTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitIntTypeTreeNode(v, visitedNodePtr01);
    bool res = subtype(t,
                                 visitedNodePtr02->subTreeRef());
    delete t;
    return res;
}

bool subtypeVisitor::subtypeTrivImmutTreeNodePair(
    thisVisitorType& thisVisitor,
    trivTypeTreeNode* visitedNodePtr01,
    immutTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitTrivTypeTreeNode(v, visitedNodePtr01);
    bool res = subtype(t,
                       visitedNodePtr02->subTreeRef());
    delete t;
    return res;
}

bool subtypeVisitor::subtypeConImmutTreeNodePair(
    thisVisitorType& thisVisitor,
    conTypeTreeNode* visitedNodePtr01,
    immutTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitConTypeTreeNode(v, visitedNodePtr01);
    bool res = subtype(t,
                       visitedNodePtr02->subTreeRef());
    delete t;
    return res;
}

bool subtypeVisitor::subtypeRefImmutTreeNodePair(
    thisVisitorType& thisVisitor,
    refTypeTreeNode* visitedNodePtr01,
    immutTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitRefTypeTreeNode(v, visitedNodePtr01);
    bool res = subtype(t,
                       visitedNodePtr02->subTreeRef());
    delete t;
    return res;
}

bool subtypeVisitor::subtypeRefvecImmutTreeNodePair(
    thisVisitorType& thisVisitor,
    refvecTypeTreeNode* visitedNodePtr01,
    immutTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitRefvecTypeTreeNode(v, visitedNodePtr01);
    bool res = subtype(t,
                       visitedNodePtr02->subTreeRef());
    delete t;
    return res;
}

bool subtypeVisitor::subtypeFunImmutTreeNodePair(
    thisVisitorType& thisVisitor,
    funTypeTreeNode* visitedNodePtr01,
    immutTypeTreeNode* visitedNodePtr02) {
    deepCopyVisitor v;
    typeTree* t = v.visitFunTypeTreeNode(v, visitedNodePtr01);
    bool res = subtype(t,
                       visitedNodePtr02->subTreeRef());
    delete t;
    return res;
}

bool subtypeVisitor::subtypeConConTreeNodePair(
    thisVisitorType& thisVisitor,
    conTypeTreeNode* visitedNodePtr01,
    conTypeTreeNode* visitedNodePtr02) {
    return subtype(visitedNodePtr01->subTreeRef(),
                   visitedNodePtr02->subTreeRef());
}

bool subtypeVisitor::subtypeRefRefTreeNodePair(
    thisVisitorType& thisVisitor,
    refTypeTreeNode* visitedNodePtr01,
    refTypeTreeNode* visitedNodePtr02) {
    mutableVisitor mutV;
    immutableVisitor immutV;
    bool recursiveSubtypeResult =
        subtype(visitedNodePtr01->subTreeRef(),
                visitedNodePtr02->subTreeRef());
    bool result =
        recursiveSubtypeResult
        && isMutable(visitedNodePtr01->subTreeRef())
        && mutV.visit(*(visitedNodePtr02->subTreeRef()));
    result = result ||
        recursiveSubtypeResult
        && immutV.visit(*(visitedNodePtr02->subTreeRef()));
    return result;
}

bool subtypeVisitor::subtypeRefvecRefvecTreeNodePair(
    thisVisitorType& thisVisitor,
    refvecTypeTreeNode* visitedNodePtr01,
    refvecTypeTreeNode* visitedNodePtr02) {
    mutableVisitor mutV;
    immutableVisitor immutV;
    bool recursiveSubtypeResult =
        subtype(visitedNodePtr01->subTreeRef(),
                visitedNodePtr02->subTreeRef());
    bool result =
    recursiveSubtypeResult
    && mutV.visit(*(visitedNodePtr01->subTreeRef()))
    && mutV.visit(*(visitedNodePtr02->subTreeRef()));
    result = result ||
    recursiveSubtypeResult
    && immutV.visit(*(visitedNodePtr02->subTreeRef()));
    return result;
}

bool subtypeVisitor::subtypeFunFunTreeNodePair(
    thisVisitorType& thisVisitor,
    funTypeTreeNode* visitedNodePtr01,
    funTypeTreeNode* visitedNodePtr02) {
    
    bool isSubtype = true;
    if(visitedNodePtr01->numParameters() != visitedNodePtr02->numParameters())
        isSubtype = false;
    else {
        for(int i = 0; isSubtype && i < visitedNodePtr01->numParameters(); i++){
            isSubtype = subtype(visitedNodePtr02 -> parameterTypeRef(i),
                                visitedNodePtr01 -> parameterTypeRef(i));
        }
        if(isSubtype)
            isSubtype = subtype(visitedNodePtr01 -> returnTypeRef(),
                                visitedNodePtr02 -> returnTypeRef());
    }
    return isSubtype;
}

/*
 * Class mutableVisitor
 */

/* Private Members */

// nothing

/* Protected Members */

// nothing

/* Public Members */

mutableVisitor::mutableVisitor()
    : predicateSingleDispatchTypeTreeVisitor() {
    add< immutTypeTreeNode >(mutableImmutTreeNode);
}

bool mutableVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return true;
}

bool mutableVisitor::mutableImmutTreeNode(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr) {

    return false;
}

/*
 * Class immutableVisitor
 */

/* Private Members */

// nothing

/* Protected Members */

// nothing

/* Public Members */

immutableVisitor::immutableVisitor()
: predicateSingleDispatchTypeTreeVisitor() {
	
    add< immutTypeTreeNode >(immutableImmutTreeNode);
    
}

bool immutableVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return false;
}

bool immutableVisitor::immutableImmutTreeNode(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr) {

    return true;
}

/*
 * dsupVisitor Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

dsupVisitor::dsupVisitor()
    : doubleDispatchTypeTreeVisitor<typeTree*>() {
    // <-- int -->
    add < intTypeTreeNode, intTypeTreeNode >(dsupIntInt);
    add < intTypeTreeNode, immutTypeTreeNode >(dsupIntImmut);
    // <-- triv -->
    add < trivTypeTreeNode, trivTypeTreeNode >(dsupTrivTriv);
    add < trivTypeTreeNode, immutTypeTreeNode >(dsupTrivImmut);
    // <-- immut -->
    add < immutTypeTreeNode, intTypeTreeNode >(dsupImmutInt);
    add < immutTypeTreeNode, trivTypeTreeNode >(dsupImmutTriv);
    add < immutTypeTreeNode, immutTypeTreeNode >(dsupImmutImmut);
    add < immutTypeTreeNode, conTypeTreeNode >(dsupImmutCon);
    add < immutTypeTreeNode, refTypeTreeNode >(dsupImmutRef);
    add < immutTypeTreeNode, refvecTypeTreeNode >(dsupImmutRefvec);
    add < immutTypeTreeNode, funTypeTreeNode >(dsupImmutFun);
    // <-- con -->
    add < conTypeTreeNode, immutTypeTreeNode >(dsupConImmut);
    add < conTypeTreeNode, conTypeTreeNode >(dsupConCon);
    // <-- ref -->
    add < refTypeTreeNode, immutTypeTreeNode >(dsupRefImmut);
    add < refTypeTreeNode, refTypeTreeNode >(dsupRefRef);
    // <-- refvec -->
    add < refvecTypeTreeNode, immutTypeTreeNode >(dsupRefvecImmut);
    add < refvecTypeTreeNode, refvecTypeTreeNode >(dsupRefvecRefvec);
    // <-- fun -->
    add < funTypeTreeNode, immutTypeTreeNode >(dsupFunImmut);
    add < funTypeTreeNode, funTypeTreeNode >(dsupFunFun);
}

// <-- int -->
typeTree* dsupVisitor::dsupIntInt(
    thisVisitorType& thisVisitor,
    intTypeTreeNode* visitedNodePtr1,
    intTypeTreeNode* visitedNodePtr2) {
    return new intTypeTree;
}
typeTree* dsupVisitor::dsupIntImmut(
    thisVisitorType& thisVisitor,
    intTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        new immutTypeTree(dsup(t,
                               visitedNodePtr2->subTreeRef()));
    return result;
}
// <-- triv -->
typeTree* dsupVisitor::dsupTrivTriv(
    thisVisitorType& thisVisitor,
    trivTypeTreeNode* visitedNodePtr1,
    trivTypeTreeNode* visitedNodePtr2) {
    return new trivTypeTree;
}
typeTree* dsupVisitor::dsupTrivImmut(
    thisVisitorType& thisVisitor,
    trivTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        new immutTypeTree(dsup(t,
                               visitedNodePtr2->subTreeRef()));
    return result;
}
// <-- immut -->
typeTree* dsupVisitor::dsupImmutInt(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    intTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        new immutTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                           t));
    delete t;
    return result;
}
typeTree* dsupVisitor::dsupImmutTriv(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    trivTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        new immutTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                               t));
    return result;
}
typeTree* dsupVisitor::dsupImmutImmut(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    return new immutTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                                  visitedNodePtr2->subTreeRef()));
}
typeTree* dsupVisitor::dsupImmutCon(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    conTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        new immutTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                           t));
    return result;
}
typeTree* dsupVisitor::dsupImmutRef(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    refTypeTreeNode* visitedNodePtr2){
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        new immutTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                           t));
    return result;
}
typeTree* dsupVisitor::dsupImmutRefvec(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    refvecTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        new immutTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                           t));
    return result;
}
typeTree* dsupVisitor::dsupImmutFun(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    funTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        new immutTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                           t));
    return result;
}
// <-- con -->
typeTree* dsupVisitor::dsupConImmut(
    thisVisitorType& thisVisitor,
    conTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        new immutTypeTree(dsup(t,
                           visitedNodePtr2->subTreeRef()));
    return result;
}
typeTree* dsupVisitor::dsupConCon(
    thisVisitorType& thisVisitor,
    conTypeTreeNode* visitedNodePtr1,
    conTypeTreeNode* visitedNodePtr2) {
    return new conTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                                visitedNodePtr2->subTreeRef()));
}
// <-- ref -->
typeTree* dsupVisitor::dsupRefImmut(
    thisVisitorType& thisVisitor,
    refTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        new immutTypeTree(dsup(t,
                           visitedNodePtr2->subTreeRef()));
    return result;
}
typeTree* dsupVisitor::dsupRefRef(
    thisVisitorType& thisVisitor,
    refTypeTreeNode* visitedNodePtr1,
    refTypeTreeNode* visitedNodePtr2) {
    return new refTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                                visitedNodePtr2->subTreeRef()));
}
// <-- refvec -->
typeTree* dsupVisitor::dsupRefvecImmut(
    thisVisitorType& thisVisitor,
    refvecTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        new immutTypeTree(dsup(t,
                           visitedNodePtr2->subTreeRef()));
    return result;
}
typeTree* dsupVisitor::dsupRefvecRefvec(
    thisVisitorType& thisVisitor,
    refvecTypeTreeNode* visitedNodePtr1,
    refvecTypeTreeNode* visitedNodePtr2) {
    return new refvecTypeTree(dsup(visitedNodePtr1->subTreeRef(),
                                   visitedNodePtr2->subTreeRef()));
}
// <-- fun -->
typeTree* dsupVisitor::dsupFunImmut(
    thisVisitorType& thisVisitor,
    funTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        new immutTypeTree(dsup(t,
                           visitedNodePtr2->subTreeRef()));
    return result;
}
typeTree* dsupVisitor::dsupFunFun(
    thisVisitorType& thisVisitor,
    funTypeTreeNode* visitedNodePtr1,
    funTypeTreeNode* visitedNodePtr2) {
    vector<typeTree*> operands;
    for(int i = 0; i < visitedNodePtr1->numParameters(); i++){
        operands.push_back(csub(visitedNodePtr1->parameterTypeRef(i),
                                visitedNodePtr2->parameterTypeRef(i)));
    }
    return new funTypeTree(dsup(visitedNodePtr1->returnTypeRef(),
                                visitedNodePtr2->returnTypeRef()),
                           operands);
}

typeTree* dsupVisitor::defaultCase(
    typeTreeNode* visitedNodePtr1,
    typeTreeNode* visitedNodePtr2) {
    return NULL;
}

/*
 * csubVisitor Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

csubVisitor::csubVisitor()
    : doubleDispatchTypeTreeVisitor<typeTree*>() {
    // <-- int -->
    add < intTypeTreeNode, intTypeTreeNode >(csubIntInt);
    add < intTypeTreeNode, immutTypeTreeNode >(csubIntImmut);
    // <-- triv -->
    add < trivTypeTreeNode, trivTypeTreeNode >(csubTrivTriv);
    add < trivTypeTreeNode, immutTypeTreeNode >(csubTrivImmut);
    // <-- immut -->
    add < immutTypeTreeNode, intTypeTreeNode >(csubImmutInt);
    add < immutTypeTreeNode, trivTypeTreeNode >(csubImmutTriv);
    add < immutTypeTreeNode, immutTypeTreeNode >(csubImmutImmut);
    add < immutTypeTreeNode, conTypeTreeNode >(csubImmutCon);
    add < immutTypeTreeNode, refTypeTreeNode >(csubImmutRef);
    add < immutTypeTreeNode, refvecTypeTreeNode >(csubImmutRefvec);
    add < immutTypeTreeNode, funTypeTreeNode >(csubImmutFun);
    // <-- con -->
    add < conTypeTreeNode, immutTypeTreeNode >(csubConImmut);
    add < conTypeTreeNode, conTypeTreeNode >(csubConCon);
    // <-- ref -->
    add < refTypeTreeNode, immutTypeTreeNode >(csubRefImmut);
    add < refTypeTreeNode, refTypeTreeNode >(csubRefRef);
    // <-- refvec -->
    add < refvecTypeTreeNode, immutTypeTreeNode >(csubRefvecImmut);
    add < refvecTypeTreeNode, refvecTypeTreeNode >(csubRefvecRefvec);
    // <-- fun -->
    add < funTypeTreeNode, immutTypeTreeNode >(csubFunImmut);
    add < funTypeTreeNode, funTypeTreeNode >(csubFunFun);
}

// <-- int -->
typeTree* csubVisitor::csubIntInt(
    thisVisitorType& thisVisitor,
    intTypeTreeNode* visitedNodePtr1,
    intTypeTreeNode* visitedNodePtr2) {
    return new intTypeTree;
}
typeTree* csubVisitor::csubIntImmut(
    thisVisitorType& thisVisitor,
    intTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        csub(t,
             visitedNodePtr2->subTreeRef());
    return result;
}
// <-- triv -->
typeTree* csubVisitor::csubTrivTriv(
    thisVisitorType& thisVisitor,
    trivTypeTreeNode* visitedNodePtr1,
    trivTypeTreeNode* visitedNodePtr2) {
    return new trivTypeTree;
}
typeTree* csubVisitor::csubTrivImmut(
    thisVisitorType& thisVisitor,
    trivTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        csub(t,
             visitedNodePtr2->subTreeRef());
    return result;
}
// <-- immut -->
typeTree* csubVisitor::csubImmutInt(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    intTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        csub(visitedNodePtr1->subTreeRef(),
             t);
    return result;
}
typeTree* csubVisitor::csubImmutTriv(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    trivTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        csub(visitedNodePtr1->subTreeRef(),
             t);
    return result;
}
typeTree* csubVisitor::csubImmutImmut(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    return new immutTypeTree(csub(visitedNodePtr1->subTreeRef(),
                                  visitedNodePtr2->subTreeRef()));
}
typeTree* csubVisitor::csubImmutCon(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    conTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        csub(visitedNodePtr1->subTreeRef(),
             t);
    return result;
}
typeTree* csubVisitor::csubImmutRef(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    refTypeTreeNode* visitedNodePtr2){
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        csub(visitedNodePtr1->subTreeRef(),
             t);
    return result;
}
typeTree* csubVisitor::csubImmutRefvec(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    refvecTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        csub(visitedNodePtr1->subTreeRef(),
             t);
    return result;
}
typeTree* csubVisitor::csubImmutFun(
    thisVisitorType& thisVisitor,
    immutTypeTreeNode* visitedNodePtr1,
    funTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr2);
    typeTree* result =
        csub(visitedNodePtr1->subTreeRef(),
             t);
    return result;
}
// <-- con -->
typeTree* csubVisitor::csubConImmut(
    thisVisitorType& thisVisitor,
    conTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        csub(t,
             visitedNodePtr2->subTreeRef());
    return result;
}
typeTree* csubVisitor::csubConCon(
    thisVisitorType& thisVisitor,
    conTypeTreeNode* visitedNodePtr1,
    conTypeTreeNode* visitedNodePtr2) {
    return new conTypeTree(csub(visitedNodePtr1->subTreeRef(),
                                visitedNodePtr2->subTreeRef()));
}
// <-- ref -->
typeTree* csubVisitor::csubRefImmut(
    thisVisitorType& thisVisitor,
    refTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        csub(t,
             visitedNodePtr2->subTreeRef());
    return result;
}
typeTree* csubVisitor::csubRefRef(
    thisVisitorType& thisVisitor,
    refTypeTreeNode* visitedNodePtr1,
    refTypeTreeNode* visitedNodePtr2) {
    return new refTypeTree(csub(visitedNodePtr1->subTreeRef(),
                                visitedNodePtr2->subTreeRef()));
}
// <-- refvec -->
typeTree* csubVisitor::csubRefvecImmut(
    thisVisitorType& thisVisitor,
    refvecTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        csub(t,
             visitedNodePtr2->subTreeRef());
    return result;
}
typeTree* csubVisitor::csubRefvecRefvec(
    thisVisitorType& thisVisitor,
    refvecTypeTreeNode* visitedNodePtr1,
    refvecTypeTreeNode* visitedNodePtr2) {
    return new refvecTypeTree(csub(visitedNodePtr1->subTreeRef(),
                                   visitedNodePtr2->subTreeRef()));
}
// <-- fun -->
typeTree* csubVisitor::csubFunImmut(
    thisVisitorType& thisVisitor,
    funTypeTreeNode* visitedNodePtr1,
    immutTypeTreeNode* visitedNodePtr2) {
    typeTree* t = new typeTree(visitedNodePtr1);
    typeTree* result =
        csub(t,
             visitedNodePtr2->subTreeRef());
    return result;
}
typeTree* csubVisitor::csubFunFun(
    thisVisitorType& thisVisitor,
    funTypeTreeNode* visitedNodePtr1,
    funTypeTreeNode* visitedNodePtr2) {
    vector<typeTree*> operands;
    for(int i = 0; i < visitedNodePtr1->numParameters(); i++){
        operands.push_back(dsup(visitedNodePtr1->parameterTypeRef(i),
                                visitedNodePtr2->parameterTypeRef(i)));
    }
    return new funTypeTree(csub(visitedNodePtr1->returnTypeRef(),
                                visitedNodePtr2->returnTypeRef()),
                            operands);
}

typeTree* csubVisitor::defaultCase(
    typeTreeNode* visitedNodePtr1,
    typeTreeNode* visitedNodePtr2) {
    return new intTypeTree();
}

/*
 * extractReturnTypeVisitor Class Function Definitions
 */

extractReturnTypeVisitor::extractReturnTypeVisitor()
    : singleDispatchTypeTreeVisitor<typeTree*>() {
    add < funTypeTreeNode > (extractReturnFunTypeTreeNode);
    add < immutTypeTreeNode > (extractReturnImmutTypeTreeNode);
}

typeTree* extractReturnTypeVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return (typeTree*)NULL;
}

typeTree* extractReturnTypeVisitor::extractReturnFunTypeTreeNode(thisVisitorType& thisVisitor,
                                                                 funTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->returnTypeRef();
}

typeTree* extractReturnTypeVisitor::extractReturnImmutTypeTreeNode(thisVisitorType& thisVisitor,
                                                                   immutTypeTreeNode* visitedNodePtr) {
    return thisVisitor.visit(*visitedNodePtr->subTreeRef());
}

/*
 * extractParameterTypesVisitor Class: Function Definitions
 */

extractParameterTypesVisitor::extractParameterTypesVisitor()
    : singleDispatchTypeTreeVisitor<vector<typeTree*> >() {
    add < funTypeTreeNode > (extractParameterTypesFunTypeNode);
    add < immutTypeTreeNode > (extractParameterTypesImmutTypeNode);
}

vector<typeTree*> extractParameterTypesVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return vector<typeTree*>();
}

vector<typeTree*> extractParameterTypesVisitor::extractParameterTypesFunTypeNode(thisVisitorType& thisVisitor,
                                                                                 funTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->parameterTypeVec();
}

vector<typeTree*> extractParameterTypesVisitor::extractParameterTypesImmutTypeNode(thisVisitorType& thisVisitor,
                                                                                   immutTypeTreeNode* visitedNodePtr) {
    return thisVisitor.visit(*visitedNodePtr->subTreeRef());
}

/*
 * getVectorTypeVisitor Class Function Definitions
 */

getVectorTypeVisitor::getVectorTypeVisitor()
    : singleDispatchTypeTreeVisitor<typeTree*>() {
    add < refvecTypeTreeNode > (getVectorTypeRefvecTreeNode);
}

typeTree* getVectorTypeVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return NULL;
}

typeTree* getVectorTypeVisitor::getVectorTypeRefvecTreeNode(thisVisitorType& thisVisitor,
                                             refvecTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->subTreeRef();
}

/*
 * unContinueVisitor Class: Function Definitions
 */
unContinueVisitor::unContinueVisitor()
    : singleDispatchTypeTreeVisitor<typeTree*>() {
    add < conTypeTreeNode > (unContinueConTypeNode);
    add < immutTypeTreeNode > (unContinueImmutTypeNode);
    
}

typeTree* unContinueVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return NULL;
}

typeTree* unContinueVisitor::unContinueConTypeNode(thisVisitorType& thisVisitor,
                                                   conTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->subTreeRef();
}

typeTree* unContinueVisitor::unContinueImmutTypeNode(thisVisitorType& thisVisitor,
                                                     immutTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->subTreeRef();
}

/*
 * isFunctionVisitor Class: Function Definitions
 */

isFunctionVisitor::isFunctionVisitor()
    : predicateSingleDispatchTypeTreeVisitor() {
    add < funTypeTreeNode > (isFunFunTypeNode);
    add < immutTypeTreeNode > (isFunImmutTypeNode);
}

bool isFunctionVisitor::isFunFunTypeNode(thisVisitorType& thisVisitor, funTypeTreeNode* visitedNodePtr) {
    return true;
}

bool isFunctionVisitor::isFunImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return isFun(visitedNodePtr->subTreeRef());
}

/*
 * isIntVisitor Class: Function Definitions
 */
isIntVisitor::isIntVisitor()
    : predicateSingleDispatchTypeTreeVisitor() {
    add < intTypeTreeNode > (isIntIntTypeNode);
    add < immutTypeTreeNode > (isIntImmutTypeNode);
}

bool isIntVisitor::isIntIntTypeNode(thisVisitorType& thisVisitor, intTypeTreeNode* visitedNodePtr) {
    return true;
}

bool isIntVisitor::isIntImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return isInt(visitedNodePtr->subTreeRef());
}

/*
 * isTrivVisitor Class: Function Definitions
 */
isTrivVisitor::isTrivVisitor()
    : predicateSingleDispatchTypeTreeVisitor() {
    add < trivTypeTreeNode > (isTrivTrivTypeNode);
    add < immutTypeTreeNode > (isTrivImmutTypeNode);
}

bool isTrivVisitor::isTrivTrivTypeNode(thisVisitorType& thisVisitor, trivTypeTreeNode* visitedNodePtr) {
    return true;
}

bool isTrivVisitor::isTrivImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return isTriv(visitedNodePtr->subTreeRef());
}

/*
 * isConVisitor Class: Function Definitions
 */
isConVisitor::isConVisitor()
    : predicateSingleDispatchTypeTreeVisitor() {
    add < conTypeTreeNode > (isConConTypeNode);
    add < immutTypeTreeNode > (isConImmutTypeNode);
}

bool isConVisitor::isConConTypeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr) {
    return true;
}

bool isConVisitor::isConImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return isCon(visitedNodePtr->subTreeRef());
}

/*
 * unConVisitor Class: Function Definitions
 */
unConVisitor::unConVisitor()
    : singleDispatchTypeTreeVisitor<typeTree*>() {
    add < conTypeTreeNode > (unConConTypeNode);
}

typeTree* unConVisitor::defaultCase(typeTreeNode* visitedNodePtr){
    return NULL;
}

typeTree* unConVisitor::unConConTypeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->subTreeRef();
}

/*
 * isRefVisitor Class: Function Definitions
 */
isRefVisitor::isRefVisitor()
    : predicateSingleDispatchTypeTreeVisitor() {
    add < refTypeTreeNode > (isRefRefTypeNode);
    add < immutTypeTreeNode > (isRefImmutTypeNode);
}

bool isRefVisitor::isRefRefTypeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr) {
    return true;
}

bool isRefVisitor::isRefImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return isRef(visitedNodePtr->subTreeRef());
}

/*
 * unRefVisitor Class: Function Definitions
 */
unRefVisitor::unRefVisitor()
    : singleDispatchTypeTreeVisitor<typeTree*>() {
    add < refTypeTreeNode > (unRefRefTypeNode);
    add < immutTypeTreeNode > (unRefImmutTypeNode);
}

typeTree* unRefVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return NULL;
}

typeTree* unRefVisitor::unRefRefTypeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->subTreeRef();
}

typeTree* unRefVisitor::unRefImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr){
    return unRef(visitedNodePtr->subTreeRef());
}

/*
 * isRefvecVisitor Class: Function Definitions
 */
isRefvecVisitor::isRefvecVisitor()
    : predicateSingleDispatchTypeTreeVisitor() {
    add < refvecTypeTreeNode > (isRefvecRefvecTypeNode);
    add < immutTypeTreeNode > (isRefvecImmutTypeNode);
}

bool isRefvecVisitor::isRefvecRefvecTypeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode* visitedNodePtr) {
    return true;
}

bool isRefvecVisitor::isRefvecImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return isRefvec(visitedNodePtr->subTreeRef());
}

/*
 * unRefvecVisitor Class: Function Definitions
 */
unRefvecVisitor::unRefvecVisitor()
    : singleDispatchTypeTreeVisitor<typeTree*>() {
    add < refvecTypeTreeNode > (unRefvecRefvecTypeNode);
    add < immutTypeTreeNode > (unRefvecImmutTypeNode);
}

typeTree* unRefvecVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return NULL;
}

typeTree* unRefvecVisitor::unRefvecRefvecTypeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode* visitedNodePtr) {
    return visitedNodePtr->subTreeRef();
}

typeTree* unRefvecVisitor::unRefvecImmutTypeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return unRefvec(visitedNodePtr->subTreeRef());
}

/*
 * sizeOfTypeVisitor Class: Function Definitions
 */
sizeOfTypeVisitor::sizeOfTypeVisitor() {
    add < intTypeTreeNode > (sizeOfIntTypeTreeNode);
    add < trivTypeTreeNode > (sizeOfTrivTypeTreeNode);
    add < immutTypeTreeNode > (sizeOfImmutTypeTreeNode);
    add < conTypeTreeNode > (sizeOfConTypeTreeNode);
    add < refTypeTreeNode > (sizeOfRefTypeTreeNode);
    add < refvecTypeTreeNode > (sizeOfRefvecTypeTreeNode);
    add < funTypeTreeNode > (sizeOfFunTypeTreeNode);
}

int sizeOfTypeVisitor::defaultCase(typeTreeNode* visitedNodePtr) {
    return -1;
}

int sizeOfTypeVisitor::sizeOfIntTypeTreeNode(thisVisitorType& thisVisitor, intTypeTreeNode* visitedNodePtr) {
    return 4; // standard ia32 integer size
}
int sizeOfTypeVisitor::sizeOfTrivTypeTreeNode(thisVisitorType& thisVisitor, trivTypeTreeNode* visitedNodePtr) {
    return 4; // by choice
}
int sizeOfTypeVisitor::sizeOfImmutTypeTreeNode(thisVisitorType& thisVisitor, immutTypeTreeNode* visitedNodePtr) {
    return sizeOf(visitedNodePtr->subTreeRef());
}
int sizeOfTypeVisitor::sizeOfConTypeTreeNode(thisVisitorType& thisVisitor, conTypeTreeNode* visitedNodePtr) {
    // TODO i'm not sure exactly why
    return 12;
}
int sizeOfTypeVisitor::sizeOfRefTypeTreeNode(thisVisitorType& thisVisitor, refTypeTreeNode* visitedNodePtr) {
    return 4; // standard ia32 integer size
}
int sizeOfTypeVisitor::sizeOfRefvecTypeTreeNode(thisVisitorType& thisVisitor, refvecTypeTreeNode* visitedNodePtr) {
    return 8;
}
int sizeOfTypeVisitor::sizeOfFunTypeTreeNode(thisVisitorType& thisVisitor, funTypeTreeNode* visitedNodePtr) {
    return 8; // (ep ip) pair, each of which is 4 bytes
}

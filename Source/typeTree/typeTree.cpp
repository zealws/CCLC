#include "typeTree.h"
#include "typeTreeVisitors.h"
#include <vector>
using namespace std;

/*
 * typeTree Class: Function Definitions
 */

/* public: */

// default copy constructor
typeTree::typeTree()
    : rootNode(NULL) {
    // Do Nothing
}

// copy constructor (creates a deep copy)
typeTree::typeTree(const typeTree& other)
: rootNode(other.rootNode) {
    // Do Nothing
}

// explicit constructor
typeTree::typeTree(typeTreeNode* initRootNode)
    : rootNode(initRootNode) {
    // Do Nothing
}

// destructor
typeTree::~typeTree() {
    delete rootNode;
}

// callback for visitors
void typeTree::accept(abstractTypeTreeVisitor* treeVisitor) const {
    rootNode->accept(treeVisitor);
}

void typeTree::accept(abstractTypeTreeVisitor& treeVisitor) const {
    rootNode->accept(&treeVisitor);
}

/*
 * typeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// default constructor
typeTreeNode::typeTreeNode() {
    // Do Nothing
}

// copy constructor
typeTreeNode::typeTreeNode(const typeTreeNode& other) {
    // Do Nothing
}

// destructor
typeTreeNode::~typeTreeNode() {
    // Do Nothing
}

/*
 * intTypeTree Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// constructor
intTypeTree::intTypeTree()
    : typeTree(new intTypeTreeNode()) {
    // Do Nothing
}

// destructor
intTypeTree::~intTypeTree() {
    // Do Nothing
}

/*
 * intTypeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

void intTypeTreeNode::accept(abstractTypeTreeVisitor* treeVisitor) {
    treeVisitor->visitIntTypeTreeNode(this);
}

/*
 * trivTypeTree Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// constructor
trivTypeTree::trivTypeTree()
    : typeTree(new trivTypeTreeNode()) {
    // Do Nothing
}

// destructor
trivTypeTree::~trivTypeTree() {
    // Do Nothing
}

/*
 * trivTypeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

void trivTypeTreeNode::accept(abstractTypeTreeVisitor* treeVisitor) {
    treeVisitor->visitTrivTypeTreeNode(this);
}

/*
 * immutTypeTree Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
immutTypeTree::immutTypeTree(typeTree* initSubTree)
    : typeTree(new immutTypeTreeNode(initSubTree)) {
    // Do Nothing
}

// destructor
immutTypeTree::~immutTypeTree() {
    // Do Nothing
}

/*
 * immutTypeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
immutTypeTreeNode::immutTypeTreeNode(typeTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

// destructor
immutTypeTreeNode::~immutTypeTreeNode() {
    delete subTree;
}

// accepts a visitor
void immutTypeTreeNode::accept(abstractTypeTreeVisitor* treeVisitor) {
    treeVisitor->visitImmutTypeTreeNode(this);
}

// returns a constant reference to our subtree
typeTree* immutTypeTreeNode::subTreeRef() {
    return subTree;
}


/*
 * conTypeTree Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
conTypeTree::conTypeTree(typeTree* initSubTree)
    : typeTree(new conTypeTreeNode(initSubTree)) {
    // Do Nothing
}

// destructor
conTypeTree::~conTypeTree() {
    // Do Nothing
}

/*
 * conTypeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
conTypeTreeNode::conTypeTreeNode(typeTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

// destructor
conTypeTreeNode::~conTypeTreeNode() {
    delete subTree;
}

// accepts a visitor
void conTypeTreeNode::accept(abstractTypeTreeVisitor* treeVisitor) {
    treeVisitor->visitConTypeTreeNode(this);
}

// returns a constant reference to our subtree
typeTree* conTypeTreeNode::subTreeRef() {
    return subTree;
}

/*
 * refTypeTree Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
refTypeTree::refTypeTree(typeTree* initSubTree)
    : typeTree(new refTypeTreeNode(initSubTree)) {
    // Do Nothing
}

// destructor
refTypeTree::~refTypeTree() {
    // Do Nothing
}

/*
 * refTypeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
refTypeTreeNode::refTypeTreeNode(typeTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

// destructor
refTypeTreeNode::~refTypeTreeNode() {
    delete subTree;
}

// accepts a visitor
void refTypeTreeNode::accept(abstractTypeTreeVisitor* treeVisitor) {
    treeVisitor->visitRefTypeTreeNode(this);
}

// returns a constant reference to our subtree
typeTree* refTypeTreeNode::subTreeRef() {
    return subTree;
}

/*
 * refvecTypeTree Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
refvecTypeTree::refvecTypeTree(typeTree* initSubTree)
    : typeTree(new refvecTypeTreeNode(initSubTree)) {
    // Do Nothing
}

// destructor
refvecTypeTree::~refvecTypeTree() {
    // Do Nothing
}

/*
 * refvecTypeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
refvecTypeTreeNode::refvecTypeTreeNode(typeTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

// destructor
refvecTypeTreeNode::~refvecTypeTreeNode() {
    delete subTree;
}

// accepts a visitor
void refvecTypeTreeNode::accept(abstractTypeTreeVisitor* treeVisitor) {
    treeVisitor->visitRefvecTypeTreeNode(this);
}

// returns a constant reference to our subtree
typeTree* refvecTypeTreeNode::subTreeRef() {
    return subTree;
}

/*
 * funTypeTree Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
funTypeTree::funTypeTree(typeTree* initReturnType, vector<typeTree*> initParameterTypes)
    : typeTree(new funTypeTreeNode(initReturnType, initParameterTypes)) {
    // Do Nothing
}

// destructor
funTypeTree::~funTypeTree() {
    // Do Nothing
}

/*
 * funTypeTreeNode Class: Function Definitions
 */

/* private: */

// nothing

/* protected: */

// nothing

/* public: */

// explicit constructor
funTypeTreeNode::funTypeTreeNode(typeTree* initReturnType, vector<typeTree*> initParameterTypes)
    : returnType(initReturnType), parameterTypes(initParameterTypes) {
    // Do Nothing
}

// destructor
funTypeTreeNode::~funTypeTreeNode() {
    for(int i = 0; i < parameterTypes.size(); i++){
        delete parameterTypes[i];
    }
    delete returnType;
    
}

// accepts a visitor
void funTypeTreeNode::accept(abstractTypeTreeVisitor* treeVisitor) {
    treeVisitor->visitFunTypeTreeNode(this);
}

// returns a constant reference to our subtree
typeTree* funTypeTreeNode::returnTypeRef() {
    return returnType;
}

// returns the number of parameters
int funTypeTreeNode::numParameters() const {
    return parameterTypes.size();
}

// returns one of the parameter type subtrees
typeTree* funTypeTreeNode::parameterTypeRef(int position) {
    return parameterTypes[position];
}

vector<typeTree*>& funTypeTreeNode::parameterTypeVec() {
    return parameterTypes;
}
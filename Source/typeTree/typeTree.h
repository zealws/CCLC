#ifndef _TYPE_TREE_
#define _TYPE_TREE_

#include "typeTreeForwards.h"
#include "typeTreeVisitorsForwards.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//
// typeTree Class Definition
//
// Base Class for Type Expression Trees
//
class typeTree {
private:
    // pointer to our root node
    typeTreeNode* rootNode;

public:
    // default constructor
    typeTree();

    // copy constructor (creates a deep copy)
    typeTree(const typeTree& other);

    // explicit constructor
    // TODO this should be protected;
    // it isn't because of a strange error in the visitors
    // by which we have to create a typeTree from a node
    typeTree(typeTreeNode* initRootNode);

    // destructor
    virtual ~typeTree();

    // callback for visitors
    virtual void accept(abstractTypeTreeVisitor* treeVisitor) const;

    virtual void accept(abstractTypeTreeVisitor& treeVisitor) const;
};

//
// typeTreeNode Class Definition
//
// Base Class for Type Expression Tree Nodes
//
class typeTreeNode {
private:
    // nothing

protected:
    // nothing

public:
    // default constructor
    typeTreeNode();

    // copy constructor (deep copy)
    typeTreeNode(const typeTreeNode& other);

    // destructor
    virtual ~typeTreeNode();

    // callback for visitors
    virtual void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
};

//
// Class Defintions for the Int Type Trees
//

class intTypeTree : public typeTree {
private:
    // nothing

protected:
    // from typeTree:
    //
    // typeTreeNode* rootNode;
    //

public:
    // from typeTree:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor);
    //

    // constructor
    intTypeTree();

    // destructor
    virtual ~intTypeTree();

    // typeTree's version of accept is fine as well
};

class intTypeTreeNode : public typeTreeNode {
private:
    // nothing

protected:
    // nothing

public:
    // from typeTreeNode:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
    //

    // compiler-generated default and copy c'tors are fine

    // compiler-generated d'tor is also fine

    void accept(abstractTypeTreeVisitor* treeVisitor);
};

//
// Class Defintions for the Int Type Trees
//

class trivTypeTree : public typeTree {
private:
    // nothing

protected:
    // nothing

public:
    // from typeTree:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor);
    //

    // constructor
    trivTypeTree();

    // destructor
    ~trivTypeTree();

    // typeTree's version of accept is fine as well
};

class trivTypeTreeNode : public typeTreeNode {
private:
    // nothing

protected:
    // nothing

public:
    // from typeTreeNode:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
    //

    // compiler-generated default and copy c'tors are fine

    // compiler-generated d'tor is also fine

    // callback for single

    void accept(abstractTypeTreeVisitor* treeVisitor);
};

//
// Class Definitions for the Immut Type Trees
//
class immutTypeTree : public typeTree {
private:
    // nothing

protected:
    // nothing

public:
    // from typeTree:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor);
    //

    // explicit constructor
    immutTypeTree(typeTree* initSubTree);

    // destructor
    ~immutTypeTree();

    // typeTree's version of accept is fine
};

class immutTypeTreeNode : public typeTreeNode {
private:
    typeTree* subTree;

protected:
    // nothing

public:
    // from typeTreeNode:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
    //

    // explicit constructor
    immutTypeTreeNode(typeTree* initSubTree);

    // destructor
    ~immutTypeTreeNode();

    // accepts a visitor
    void accept(abstractTypeTreeVisitor* treeVisitor);

    // returns a constant reference to our subtree
    typeTree* subTreeRef();
};

//
// Class Definitions for the Con Type Trees
//

class conTypeTree : public typeTree {
private:
    // nothing

protected:
    // from typeTree:
    //
    // typeTreeNode* rootNode;
    //

public:
    // from typeTree:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor);
    //

    // explicit constructor
    conTypeTree(typeTree* initSubTree);

    // destructor
    ~conTypeTree();

    // typeTree's version of accept is fine
};

class conTypeTreeNode : public typeTreeNode {
private:
    typeTree* subTree;

protected:
    // nothing

public:
    // from typeTreeNode:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
    //

    // explicit constructor
    conTypeTreeNode(typeTree* initSubTree);

    // destructor
    ~conTypeTreeNode();

    // accepts a visitor
    void accept(abstractTypeTreeVisitor* treeVisitor);

    // returns a constant reference to our subtree
    typeTree* subTreeRef();
};

//
// Class Defintions for the Ref Type Trees
//

class refTypeTree : public typeTree {
private:
    // nothing

protected:
    // from typeTree:
    //
    // typeTreeNode* rootNode;
    //

public:
    // from typeTree:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor);
    //

    // explicit constructor
    refTypeTree(typeTree* initSubTree);

    // destructor
    ~refTypeTree();

    // typeTree's version of accept is fine as well
};

class refTypeTreeNode : public typeTreeNode {
private:
    typeTree* subTree;

protected:
    // nothing

public:
    // from typeTreeNode:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
    //

    // explicit constructor
    refTypeTreeNode(typeTree* initSubTree);

    // destructor
    ~refTypeTreeNode();

    // accepts a visitor
    void accept(abstractTypeTreeVisitor* treeVisitor);

    // returns a constant reference to our subtree
    typeTree* subTreeRef();
};

//
// Class Defintions for the Refvec Type Trees
//

class refvecTypeTree : public typeTree {
private:
    // nothing

protected:
    // from typeTree:
    //
    // typeTreeNode* rootNode;
    //

public:
    // from typeTree:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor);
    //

    // explicit constructor
    refvecTypeTree(typeTree* initSubTree);

    // destructor
    ~refvecTypeTree();

    // typeTree's version of accept is fine as well
};

class refvecTypeTreeNode : public typeTreeNode {
private:
    typeTree* subTree;

protected:
    // nothing

public:
    // from typeTreeNode:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
    //

    // explicit constructor
    refvecTypeTreeNode(typeTree* initSubTree);

    // destructor
    ~refvecTypeTreeNode();

    // accepts a visitor
    void accept(abstractTypeTreeVisitor* treeVisitor);

    // returns a constant reference to our subtree
    typeTree* subTreeRef();
};

//
// Class Defintions for the Function Type Trees
//

class funTypeTree : public typeTree {
private:
    // nothing

protected:
    // from typeTree:
    //
    // typeTreeNode* rootNode;
    //

public:
    // from typeTree:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor);
    //

    // explicit constructor
    funTypeTree(typeTree* initReturnType, vector<typeTree*> initParameterTypes);

    // destructor
    ~funTypeTree();

    // typeTree's version of accept is fine as well
};

class funTypeTreeNode : public typeTreeNode {
private:
    typeTree* returnType;
    vector<typeTree*> parameterTypes;

protected:
    // nothing

public:
    // from typeTreeNode:
    //
    // void accept(abstractTypeTreeVisitor* treeVisitor) = 0;
    //

    // explicit constructor
    funTypeTreeNode(typeTree* initReturnType, vector<typeTree*> initParameterTypes);

    // destructor
    ~funTypeTreeNode();

    // accepts a visitor
    void accept(abstractTypeTreeVisitor* treeVisitor);

    // returns a constant reference to our subtree
    typeTree* returnTypeRef();

    // returns the number of parameters
    int numParameters() const;

    // returns one of the parameter type subtrees
    typeTree* parameterTypeRef(int position);

    // returns the vector of parameter types
    // it is preferred to use the two functions above when accessing individual elements
    vector<typeTree*>& parameterTypeVec();
};

#endif
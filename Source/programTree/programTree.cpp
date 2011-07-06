#include <cstdlib>
#include "programTree.h"
#include "abstractProgramTreeVisitors.h"
#include "programTreeVisitors.h"
#include "../typeTree/typeTree.h"
#include "../typeTree/typeTreeVisitors.h"
using namespace std;

//
// programTree Class: Function Definitions
//

// private: */

// nothing

// protected: */

// explicit constructor with root node
programTree::programTree(programTreeNode* initRootNode)
    : rootNode(initRootNode) {
    // Do Nothing
}

// public: */

// default constructor
programTree::programTree()
	: rootNode(NULL)
	{}

// destructor
programTree::~programTree() {
	delete rootNode;
}

// callback for visitors
void programTree::accept(abstractProgramTreeVisitor* treeVisitor) const  {
    rootNode->accept(treeVisitor);
}

void programTree::accept(abstractProgramTreeVisitor& treeVisitor) const  {
    rootNode->accept(&treeVisitor);
}

//
// programTreeNode Class: Function Definitions
//

// private: */

// nothing

// protected: */

// nothing

// public: */

programTreeNode::programTreeNode() {
    // Do Nothing
}

programTreeNode::~programTreeNode() {
    // Do Nothing
}

//
// functionConstant Class: Function Definitions
//

// private: */

// protected: */

// public: */

// constructor
functionConstant::functionConstant(vector<programTree*> initParamList, vector<programTree*> initExprList)
    : programTree(new functionConstantNode(initParamList, initExprList)) {
    // Do Nothing
}

// destructor
functionConstant::~functionConstant() {
    delete rootNode;
}

//
// functionConstantNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

// constructor
functionConstantNode::functionConstantNode(vector<programTree*> initParamList, vector<programTree*> initExprList)
    : paramList(initParamList), exprList(initExprList) {
    // Do Nothing
}

// destructor
functionConstantNode::~functionConstantNode() {
    for(int i = 0; i < exprList.size(); i++)
        delete exprList[i];
    for(int i = 0; i < paramList.size(); i++)
        delete paramList[i];
}

int functionConstantNode::numParams() const {
    return paramList.size();
}

programTree* functionConstantNode::paramRef(int ref) {
    return paramList[ref];
}

int functionConstantNode::totalSizeOfParameters() const {
    int total = 0;
    for(int i = 0; i < paramList.size(); i++) {
        total += sizeOf(typeOf(paramList[i]));
    }
    return total;
}

void functionConstantNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitFunctionConstantNode(this);
}

//
// parameterDeclaration Class: Function Definitions
//

// private: */

// protected: */

// public: */

parameterDeclaration::parameterDeclaration(typeTree* initType, string initId)
    : programTree(new parameterDeclarationNode(initType, initId)) {
    // Do Nothing
}

parameterDeclaration::~parameterDeclaration() {
    delete rootNode;
}

//
// parameterDeclarationNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

parameterDeclarationNode::parameterDeclarationNode(typeTree* initType, string initId)
    : type(initType), id(initId) {
    // Do Nothing
}

parameterDeclarationNode::~parameterDeclarationNode() {
    delete type;
}

void parameterDeclarationNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    return treeVisitor->visitParameterDeclarationNode(this);
}

//
// variableDeclaration Class: Function Definitions
//

// private: */

// protected: */

// public: */

variableDeclaration::variableDeclaration(typeTree* initType,
                                         string initId)
    : programTree(new variableDeclarationNode(initType, initId)) {
    // Do Nothing
}

variableDeclaration::~variableDeclaration() {
    delete rootNode;
}

//
// variableDeclarationNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

variableDeclarationNode::variableDeclarationNode(typeTree* initType,
                                                 string initId)
    : myType(initType), myId(initId) {
    // Do Nothing
}

variableDeclarationNode::~variableDeclarationNode() {
    delete myType;
}

typeTree* variableDeclarationNode::type() {
    return myType;
}

string& variableDeclarationNode::id() {
    return myId;
}

void variableDeclarationNode::accept(abstractProgramTreeVisitor* visitor) {
    visitor->visitVariableDeclarationNode(this);
}

//
// vectorDeclaration Class Definition
//
vectorDeclaration::vectorDeclaration(string initId,
                                     programTree* initVectorSubtype,
                                     vector<programTree*> initSizeExpression)
    : programTree(new vectorDeclarationNode(initId, initVectorSubtype, initSizeExpression)) {
    // Do Nothing
}

vectorDeclaration::~vectorDeclaration() {
    delete rootNode;
}

//
// vectorDeclarationNode Class Definition
//
vectorDeclarationNode::vectorDeclarationNode(string initId,
                                             programTree* initSubtype,
                                             vector<programTree*> initSizeExpression)
    : myId(initId), myVectorSubtype(initSubtype), mySizeExpression(initSizeExpression) {
    // Do Nothing
}

string& vectorDeclarationNode::id() {
    return myId;
}

programTree* vectorDeclarationNode::vectorSubtype() {
    return myVectorSubtype;
}

vector<programTree*>& vectorDeclarationNode::sizeExpression() {
    return mySizeExpression;
}

void vectorDeclarationNode::accept(abstractProgramTreeVisitor* visitor) {
    visitor->visitVectorDeclarationNode(this);
}

//
// continuesExpression Class: Function Definitions
//
continuesExpression::continuesExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new continuesExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

continuesExpression::~continuesExpression() {
    delete rootNode;
}

//
// continuesExpressionNode Class: Function Definitions
//
continuesExpressionNode::continuesExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

continuesExpressionNode::~continuesExpressionNode() {
    delete lhs;
    delete rhs;
}

void continuesExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitContinuesExpressionNode(this);
}

//
// assignmentExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */
assignmentExpression::assignmentExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new assignmentExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

assignmentExpression::~assignmentExpression() {
    delete rootNode;
}

//
// assignmentExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

assignmentExpressionNode::assignmentExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

assignmentExpressionNode::~assignmentExpressionNode() {
    delete lhs;
    delete rhs;
}

void assignmentExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitAssignmentExpressionNode(this);
}

//
// eqExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

eqExpression::eqExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new eqExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

eqExpression::~eqExpression() {
    delete rootNode;
}

//
// eqExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

eqExpressionNode::eqExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

eqExpressionNode::~eqExpressionNode() {
    delete lhs; delete rhs;
}

void eqExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitEqExpressionNode(this);
}

//
// neqExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

neqExpression::neqExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new neqExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

neqExpression::~neqExpression() {
    delete rootNode;
}

//
// neqExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

neqExpressionNode::neqExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

neqExpressionNode::~neqExpressionNode() {
    delete rhs;
    delete lhs;
}

void neqExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitNeqExpressionNode(this);
}

//
// lessExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

lessExpression::lessExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new lessExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

lessExpression::~lessExpression() {
    delete rootNode;
}

//
// lessExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

lessExpressionNode::lessExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

lessExpressionNode::~lessExpressionNode() {
    delete lhs;
    delete rhs;
}

void lessExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitLessExpressionNode(this);
}

//
// leqExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

leqExpression::leqExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new leqExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

leqExpression::~leqExpression() {
    delete rootNode;
}

//
// leqExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

leqExpressionNode::leqExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

leqExpressionNode::~leqExpressionNode() {
    delete lhs;
    delete rhs;
}

void leqExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitLeqExpressionNode(this);
}

//
// greaterExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

greaterExpression::greaterExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new greaterExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

greaterExpression::~greaterExpression() {
    delete rootNode;
}

//
// greaterExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

greaterExpressionNode::greaterExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

greaterExpressionNode::~greaterExpressionNode() {
    delete lhs;
    delete rhs;
}

void greaterExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitGreaterExpressionNode(this);
}

//
// geqExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

geqExpression::geqExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new geqExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

geqExpression::~geqExpression() {
    delete rootNode;
}

//
// geqExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

geqExpressionNode::geqExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

geqExpressionNode::~geqExpressionNode() {
    delete lhs;
    delete rhs;
}

void geqExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitGeqExpressionNode(this);
}

//
// sumExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

sumExpression::sumExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new sumExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

sumExpression::~sumExpression() {
    delete rootNode;
}

//
// sumExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

sumExpressionNode::sumExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

sumExpressionNode::~sumExpressionNode() {
    delete lhs;
    delete rhs;
}

void sumExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitSumExpressionNode(this);
}

//
// diffExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

diffExpression::diffExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new diffExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

diffExpression::~diffExpression() {
    delete rootNode;
}

//
// diffExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

diffExpressionNode::diffExpressionNode(programTree* initLhs, programTree* initRhs)
    : rhs(initRhs), lhs(initLhs) {
    // Do Nothing
}

diffExpressionNode::~diffExpressionNode() {
    delete lhs;
    delete rhs;
}

void diffExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitDiffExpressionNode(this);
}

//
// productExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

productExpression::productExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new productExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

productExpression::~productExpression() {
    delete rootNode;
}

//
// productExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

productExpressionNode::productExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

productExpressionNode::~productExpressionNode() {
    delete lhs;
    delete rhs;
}

void productExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitProductExpressionNode(this);
}

//
// quotientExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

quotientExpression::quotientExpression(programTree* initLhs, programTree* initRhs)
    : programTree(new quotientExpressionNode(initLhs, initRhs)) {
    // Do Nothing
}

quotientExpression::~quotientExpression() {
    delete rootNode;
}

//
// quotientExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */
quotientExpressionNode::quotientExpressionNode(programTree* initLhs, programTree* initRhs)
    : lhs(initLhs), rhs(initRhs) {
    // Do Nothing
}

quotientExpressionNode::~quotientExpressionNode() {
    delete lhs;
    delete rhs;
}

void quotientExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitQuotientExpressionNode(this);
}

//
// inputExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

inputExpression::inputExpression(programTree* initSubTree)
    : programTree(new inputExpressionNode(initSubTree)) {
    // Do Nothing
}

inputExpression::~inputExpression() {
    delete rootNode;
}

//
// inputExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

inputExpressionNode::inputExpressionNode(programTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

inputExpressionNode::~inputExpressionNode() {
    delete subTree;
}

void inputExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitInputExpressionNode(this);
}

//
// outputExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

outputExpression::outputExpression(programTree* initSubTree)
    : programTree(new outputExpressionNode(initSubTree)) {
    // Do Nothing
}

outputExpression::~outputExpression() {
    delete rootNode;
}

//
// outputExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

outputExpressionNode::outputExpressionNode(programTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

outputExpressionNode::~outputExpressionNode() {
    delete subTree;
}

void outputExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor -> visitOutputExpressionNode(this);
}

//
// plusExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

plusExpression::plusExpression(programTree* initSubTree)
    : programTree(new plusExpressionNode(initSubTree)) {
    // Do Nothing
}

plusExpression::~plusExpression() {
    delete rootNode;
}

//
// plusExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

plusExpressionNode::plusExpressionNode(programTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

plusExpressionNode::~plusExpressionNode() {
    delete subTree;
}

void plusExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitPlusExpressionNode(this);
}

//
// negationExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

negationExpression::negationExpression(programTree* initSubTree)
    : programTree(new negationExpressionNode(initSubTree)) {
    // Do Nothing
}

negationExpression::~negationExpression() {
    delete rootNode;
}

//
// negationExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

negationExpressionNode::negationExpressionNode(programTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

negationExpressionNode::~negationExpressionNode() {
    delete subTree;
}

void negationExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitNegationExpressionNode(this);
}

//
// vecSizeExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

vecSizeExpression::vecSizeExpression(programTree* initSubTree)
    : programTree(new vecSizeExpressionNode(initSubTree)) {
    // Do Nothing
}

vecSizeExpression::~vecSizeExpression() {
    delete rootNode;
}

//
// vecSizeExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

vecSizeExpressionNode::vecSizeExpressionNode(programTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

vecSizeExpressionNode::~vecSizeExpressionNode() {
    delete subTree;
}

void vecSizeExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitVecSizeExpressionNode(this);
}

//
// referenceExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

referenceExpression::referenceExpression(programTree* initSubTree)
    : programTree(new referenceExpressionNode(initSubTree)) {
    // Do Nothing
}

referenceExpression::~referenceExpression() {
    delete rootNode;
}

//
// referenceExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

referenceExpressionNode::referenceExpressionNode(programTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

referenceExpressionNode::~referenceExpressionNode() {
    delete subTree;
}

void referenceExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitReferenceExpressionNode(this);
}

//
// parenExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

parenExpression::parenExpression(vector<programTree*> initSubTree)
    : programTree(new parenExpressionNode(initSubTree)) {
    // Do Nothing
}

parenExpression::~parenExpression() {
    delete rootNode;
}

//
// parenExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

parenExpressionNode::parenExpressionNode(vector<programTree*> initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

parenExpressionNode::~parenExpressionNode() {
    for(int i = 0; i < subTree.size(); i++)
        delete subTree[i];
}

void parenExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitParenExpressionNode(this);
}

//
// whileBlock Class: Function Definitions
//

// private: */

// protected: */

// public: */

whileBlock::whileBlock(vector<programTree*> initTest, vector<programTree*> initExprSeq)
    : programTree(new whileBlockNode(initTest, initExprSeq)) {
    // Do Nothing
}

whileBlock::~whileBlock() {
    delete rootNode;
}

//
// whileBlockNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

whileBlockNode::whileBlockNode(vector<programTree*> initTest, vector<programTree*> initExprSeq)
    : test(initTest), exprSeq(initExprSeq) {
    // Do Nothing
}

whileBlockNode::~whileBlockNode() {
    for(int i = 0; i < test.size(); i++)
        delete test[i];
    for(int i = 0; i < exprSeq.size(); i++)
        delete exprSeq[i];
}

void whileBlockNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitWhileBlockNode(this);
}

//
// ifBlock Class: Function Definitions
//

// private: */

// protected: */

// public: */

ifBlock::ifBlock(vector<programTree*> initTest, vector<programTree*> initTrue, vector<programTree*> initFalse)
    : programTree(new ifBlockNode(initTest, initTrue, initFalse)) {
    // Do Nothing
}

ifBlock::~ifBlock() {
    delete rootNode;
}

//
// ifBlockNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

ifBlockNode::ifBlockNode(vector<programTree*> initTest, vector<programTree*> initTrue, vector<programTree*> initFalse)
    : test(initTest), trueClause(initTrue), falseClause(initFalse) {
    // Do Nothing
}

ifBlockNode::~ifBlockNode() {
    for(int i = 0; i < test.size(); i++)
        delete test[i];
    for(int i = 0; i < trueClause.size(); i++)
        delete trueClause[i];
    for(int i = 0; i < falseClause.size(); i++)
        delete falseClause[i];
}

void ifBlockNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitIfBlockNode(this);
}

//
// controlBlock Class: Function Definitions
//

// private: */

// protected: */

// public: */

controlBlock::controlBlock(programTree* initCVal, vector<programTree*> initExprSeq)
    : programTree(new controlBlockNode(initCVal, initExprSeq)) {
    // Do Nothing
}

controlBlock::~controlBlock() {
    delete rootNode;
}

//
// controlBlockNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

controlBlockNode::controlBlockNode(programTree* initCVal, vector<programTree*> initExprSeq)
    : cVal(initCVal), exprSeq(initExprSeq) {
    // Do Nothing
}

controlBlockNode::~controlBlockNode() {
    delete cVal;
    for(int i = 0; i < exprSeq.size(); i++)
        delete exprSeq[i];
}

void controlBlockNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitControlBlockNode(this);
}

//
// variableBlock Class: Function Definitions
//

// private: */

// protected: */

// public: */

variableBlock::variableBlock(vector<programTree*> initVarList, vector<programTree*> initExprSeq)
    : programTree(new variableBlockNode(initVarList, initExprSeq)) {
    // Do Nothing
}

variableBlock::~variableBlock() {
    delete rootNode;
}

//
// variableBlockNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

variableBlockNode::variableBlockNode(vector<programTree*> initVarList, vector<programTree*> initExprSeq)
    : varList(initVarList), exprSeq(initExprSeq) {
    // Do Nothing
}

variableBlockNode::~variableBlockNode() {
    for(int i = 0; i < varList.size(); i++)
        delete varList[i];
    for(int i = 0; i < exprSeq.size(); i++)
        delete exprSeq[i];
}

int variableBlockNode::totalSizeOfVars() const {
    int total = 0;
    for(int i = 0; i < varList.size(); i++)
        total += sizeOf(typeOf(varList[i]));
    return total;
}

int variableBlockNode::numVars() const {
    return varList.size();
}

void variableBlockNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitVariableBlockNode(this);
}

//
// functionApplication Class: Function Definitions
//

// private: */

// protected: */

// public: */

functionApplication::functionApplication(programTree* initFuncPart, vector<vector<programTree*> > initParamList)
    : programTree(new functionApplicationNode(initFuncPart, initParamList)) {
    // Do Nothing
}

functionApplication::~functionApplication() {
    delete rootNode;
}

//
// functionApplicationNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

functionApplicationNode::functionApplicationNode(programTree* initFuncPart, vector<vector<programTree*> > initParamList)
    : funcPart(initFuncPart), paramList(initParamList) {
    // Do Nothing
}

functionApplicationNode::~functionApplicationNode() {
    delete funcPart;
    for(int i = 0; i < paramList.size(); i++)
        for(int j = 0; j < paramList[i].size(); j++)
            delete paramList[i][j];
}

void functionApplicationNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitFunctionApplicationNode(this);
}

//
// constantExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

constantExpression::constantExpression(int initIntValue)
    : programTree(new constantExpressionNode(initIntValue)) {
    // Do Nothing
}

constantExpression::~constantExpression() {
    delete rootNode;
}

//
// constantExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

constantExpressionNode::constantExpressionNode(int initIntValue)
    : intValue(initIntValue) {
    // Do Nothing
}

constantExpressionNode::~constantExpressionNode() {
    // Do Nothing
}

void constantExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitConstantExpressionNode(this);
}

//
// trivExpression Class: Function Definitions
//

// private: */

// nothing

// protected: */

// nothing

// public: */

trivExpression::trivExpression()
    : programTree(new trivExpressionNode()) {
    // Do Nothing
}

trivExpression::~trivExpression() {
    delete rootNode;
}

//
// trivExpressionNode Class: Function Definitions
//

// private: */

// nothing

// protected: */

// nothing

// public: */

trivExpressionNode::trivExpressionNode() {
    // Do Nothing
}

trivExpressionNode::~trivExpressionNode() {
    // Do Nothing
}

void trivExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitTrivExpressionNode(this);
}

//
// vectorRefExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

vectorRefExpression::vectorRefExpression(programTree* initVecPart, vector<programTree*> initIndexPart)
    : programTree(new vectorRefExpressionNode(initVecPart, initIndexPart)) {
    // Do Nothing
}

vectorRefExpression::~vectorRefExpression() {
    delete rootNode;
}

//
// vectorRefExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

vectorRefExpressionNode::vectorRefExpressionNode(programTree* initVecPart, vector<programTree*> initIndexPart)
    : vecPart(initVecPart), indexPart(initIndexPart) {
    // Do Nothing
}

vectorRefExpressionNode::~vectorRefExpressionNode() {
    delete vecPart;
    for(int i = 0; i < indexPart.size(); i++)
        delete indexPart[i];
}

void vectorRefExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitVectorRefExpressionNode(this);
}

//
// dereferenceExpression Class: Function Definitions
//

// private: */

// protected: */

// public: */

dereferenceExpression::dereferenceExpression(programTree* initSubTree)
    : programTree(new dereferenceExpressionNode(initSubTree)) {
    // Do Nothing
}

dereferenceExpression::~dereferenceExpression() {
    delete rootNode;
}

//
// dereferenceExpressionNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

dereferenceExpressionNode::dereferenceExpressionNode(programTree* initSubTree)
    : subTree(initSubTree) {
    // Do Nothing
}

dereferenceExpressionNode::~dereferenceExpressionNode() {
    delete subTree;
}

void dereferenceExpressionNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitDereferenceExpressionNode(this);
}

//
// variableLiteral Class: Function Definitions
//

// private: */

// protected: */

// public: */

variableLiteral::variableLiteral(string initId, typeTree* initType)
    : programTree(new variableLiteralNode(initId, initType)) {
    // Do Nothing
}

variableLiteral::~variableLiteral() {
    delete rootNode;
}

//
// variableLiteralNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

variableLiteralNode::variableLiteralNode(string initId, typeTree* initType)
    : id(initId), type(initType) {
    // Do Nothing
}

variableLiteralNode::~variableLiteralNode() {
    // Do Nothing
}

void variableLiteralNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitStringLiteralNode(this);
}

//
// programError Class: Function Definitions
//

// private: */

// protected: */

// public: */

programError::programError()
    : programTree(new programErrorNode()) {
    // Do Nothing
}

programError::~programError() {
    delete rootNode;
}

//
// programErrorNode Class: Function Definitions
//

// private: */

// protected: */

// public: */

programErrorNode::programErrorNode() {
    // Do Nothing
}

programErrorNode::~programErrorNode() {
    // Do Nothing
}

void programErrorNode::accept(abstractProgramTreeVisitor* treeVisitor) {
    treeVisitor->visitProgramErrorNode(this);
}

#include "codeGenerator.h"
#include "../options/options.h"
#include "../programTree/programTree.h"
#include "../programTree/syntaxTree.h"
#include "../typeTree/typeTree.h"
#include "../typeTree/typeTreeVisitors.h"
#include "../programTree/programTreeVisitors.h"
#include "../symbolTable/symbolTable.h"
#include "../error/error.h"
#include "../stringFormat/stringFormat.h"
#include ".message.h"
#include "vecFunc.h"

// this library includes all the associated stream libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

//////
////// Function Declarations:
//////

// Symbol Table for our code generator
static symbolTable codeGenSymbTable;

// Generates code to emulate the enter $v, $l command
void enter(int v, int l, outputStream* out);

class numberGenerator {
private:
    int lastVal;
    int (*inc)(int);
    static int increment(int i) {
        return i+1;
    }
public:
    numberGenerator()
        : lastVal(0), inc(&increment) {}

    numberGenerator(int initVal)
        : lastVal(initVal), inc(&increment) {}

    numberGenerator(int initVal, int (*initInc)(int))
        : lastVal(initVal), inc(initInc) {}

    virtual ~numberGenerator() {}

    int getNewNumber() {
        lastVal = (*inc)(lastVal);
        return lastVal;
    }

    int getNumber() const {
        return lastVal;
    }

    string getStr() const {
        return intToStr(lastVal);
    }
};

// Tells us how deep we are
static int lexicalLevel = 0;

// Master function for all code generation.
// Prints the assembly code output to the given ostream.
void generateCode(ostream* initOutFileStream, const string& filename) {
    numberGenerator numberer;
    numberGenerator funNumberer;
    outputStream masterStream = outputStream(initOutFileStream);
    codeGeneratorRValue generator(&masterStream, &numberer, &funNumberer);

    masterStream.printComment("Start of Program Prefix");
    masterStream.printCode(".title \"CCL Program\"");
    masterStream.printNewLine();

    masterStream.printBlockComment("Initialized R/W Data");
    masterStream.printCode(".section .data");
    masterStream.printNewLine();

    masterStream.beginSection("callerebp:");
    masterStream.printCode(".long 0");
    masterStream.endSection();

    masterStream.beginSection("inputBuffer:");
    masterStream.printCode(".int 0");
    masterStream.endSection();

    masterStream.beginSection("i:");
    masterStream.printCode(".int 0");
    masterStream.endSection();

    // Do R/W Data Section Stuff Here

    masterStream.printBlockComment("Section for Initialized R Data");
    masterStream.printCode(".section .rodata");
    masterStream.printNewLine();

    masterStream.beginSection("errorVectorAccess:");
    masterStream.printCode(".string \"Vector Access Out of Bounds\\n\\tsize: %d\\n\\tindex: %d\\n\"");
    masterStream.endSection();

    masterStream.beginSection("outputOperatorString:");
    masterStream.printCode(".string \"[output:] %d\\n\"");
    masterStream.endSection();

    masterStream.printCode("inputPromptString:");
    masterStream.beginSection();
    masterStream.printCode(".string \"[input:] \"");
    masterStream.endSection();

    masterStream.beginSection("inputFormatString:");
    masterStream.printCode(".string \"%d\"");
    masterStream.endSection();

    masterStream.beginSection("newline:");
    masterStream.printCode(".string \"\\n\"");
    masterStream.endSection();

    masterStream.beginSection("debug1:");
    masterStream.printCode(".string \"[debug:] %d\\n\"");
    masterStream.endSection();

    masterStream.beginSection("debug2:");
    masterStream.printCode(".string \"[debug]\\n\"");
    masterStream.endSection();

    // Do R Data Section Stuff Here

    masterStream.printBlockComment("Section for Code");
    masterStream.printCode(".section .text");
    masterStream.printNewLine();

    masterStream.printComment("vector stuff:");
    masterStream.printNewLine();
    masterStream.printCode(vecFuncs);

    masterStream.printComment("End of Program Prefix");
    masterStream.printNewLine();

    masterStream.printComment("start of program suffix");
    masterStream.printComment("declare the label main as the program entry point");
    masterStream.printCode(".global main");
    masterStream.printCode(".align 4");

    masterStream.printCode("main:");
    masterStream.printCode("beginProgram:");
    masterStream.beginSection();

    masterStream.printComment("Preserve ebp; establish ebp as frame pointer;");
    masterStream.printComment("and preserve ebx, esi, and edi (per *nix C conventions)");
    masterStream.printCode("enter $0, $0");
    masterStream.printCode("pushl %ebx");
    masterStream.printCode("pushl %esi");
    masterStream.printCode("pushl %edi");
    masterStream.printNewLine();

    masterStream.printComment("push space for main function return value");
    int SizeOfMainReturnType = sizeOf(returnType(syntaxTree.secondReference()));
    masterStream.printCode("subl $" + intToStr(SizeOfMainReturnType) + ", %esp");
    masterStream.printNewLine();

    masterStream.printComment("simulate push of main function ip & ep");
    masterStream.printCode("subl $8, %esp");
    masterStream.printNewLine();

    masterStream.printComment("call main function");
    masterStream.printCode("calll function1");
    masterStream.printNewLine();

    masterStream.printComment("discard return value");
    masterStream.printCode("addl $" + intToStr(SizeOfMainReturnType) + ", %esp");
    masterStream.printNewLine();

    masterStream.printCode("endMasterFunction:");

    masterStream.printBlockComment("Put return value 0 in eax (per *nix C conventions)");
    masterStream.printCode("xorl %eax, %eax");
    masterStream.printNewLine();

    masterStream.printComment("Restore edi, esi, and ebx; discard stack frame;");
    masterStream.printComment("and restore ebp (per *nix C conventions)");
    masterStream.printCode("popl %edi");
    masterStream.printCode("popl %esi");
    masterStream.printCode("popl %ebx");
    masterStream.printCode("leave");
    masterStream.printNewLine();

    masterStream.printBlockComment("Return to *nix");
    masterStream.printCode("ret");
    masterStream.printNewLine();

    masterStream.endSection();
    masterStream.printComment("End of Program Suffix");
    masterStream.printNewLine();

    generator.visit(*syntaxTree.firstReference());

    masterStream.dumpLazyBuffer();
    masterStream.dumpBuffer();
    if(useMessage1)
        masterStream.printCode(message1);
    else if(useMessage2)
        masterStream.printCode(message2);
    return;
}

// Generates code to emulate the enter $v, $l command
void enter(int l, outputStream* out, numberGenerator* numberer) {
    out->beginSection("emulation of enter instruction");
    if(l > 1)
        out->printCode("movl %ebp, %eax");
    out->printCode("pushl %ebp");
    out->printCode("movl %esp, %ebp");
    if(l > 1) {
        numberer->getNewNumber();
        out->printCode("movl $1, %ecx");
        out->printCode("enterStart" + numberer->getStr() + ":");
        out->printCode("movl %ecx, %ebx");
        out->printCode("cmpl $" + intToStr(l) + ", %ebx");
        out->printCode("je enterEnd" + numberer->getStr());
        out->printComment("pushl -(4*ecx)+eax");
        out->printCode("movl %ecx, %ebx");
        out->printComment("ebx = %ecx");
        out->printCode("sal %ebx");
        out->printCode("sal %ebx");
        out->printComment("ebx = 4*ecx");
        out->printCode("negl %ebx");
        out->printComment("ebx = -(4*ecx)");
        out->printCode("addl %eax, %ebx");
        out->printComment("ebx = -(4*ecx)+eax");
        out->printCode("pushl (%ebx)");
        out->printComment("ecx++;");
        out->printCode("incl %ecx");
        out->printCode("jmp enterStart" + numberer->getStr());
        out->printCode("enterEnd" + numberer->getStr() + ":");
    }
    if(l > 0)
        out->printCode("pushl %ebp");
    out->endSection("emulation of enter instruction");
}

//
// codeGenerator Class: Function Definitions
//
codeGeneratorRValue::codeGeneratorRValue(outputStream* initOut,
                                        numberGenerator* initNumberer,
                                        numberGenerator* initFunNumberer)
    : out(initOut), numberer(initNumberer), funNumberer(initFunNumberer), vecSizesBackwards(false) {
    // Do Nothing
}

void codeGeneratorRValue::visit(programTree& p, bool genBackwards) {
    if(genBackwards)
        vecSizesBackwards = true;
    else
        vecSizesBackwards = false;
    p.accept(this);
}

// Mathematical Operations

void codeGeneratorRValue::visitConstantExpressionNode(constantExpressionNode* visitedNodePtr) {
    out->printCode("pushl $" + intToStr(visitedNodePtr->intValue) + " # integer constant");
}

void codeGeneratorRValue::visitTrivExpressionNode(trivExpressionNode*) {
    out->printCode("pushl $0 # triv constant");
}

void codeGeneratorRValue::visitEqExpressionNode(eqExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("= expression");
    out->printComment("evaluate left hand side");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side");
    v.visit(*visitedNodePtr->rhs);
    out->printComment("compare the values");
    out->printCode("popl %ebx # pop the rhs into ebx");
    out->printCode("popl %eax # pop the lhs into eax");
    int localNum = numberer->getNewNumber();
    out->printCode("cmpl %ebx, %eax");
    out->printCode("jne falseExpr" + intToStr(localNum));
    out->printCode("pushl $1");
    out->printCode("jmp endExpr" + intToStr(localNum));
    out->printCode("falseExpr" + intToStr(localNum) + ":");
    out->printCode("pushl $0");
    out->printCode("endExpr" + intToStr(localNum) + ":");
    out->endSection("= expression");
}

void codeGeneratorRValue::visitNeqExpressionNode(neqExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("<> expression");
    out->printComment("evaluate left hand side");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side");
    v.visit(*visitedNodePtr->rhs);
    out->printComment("compare the values");
    out->printCode("popl %ebx # pop the rhs into ebx");
    out->printCode("popl %eax # pop the lhs into eax");
    int localNum = numberer->getNewNumber();
    out->printCode("cmpl %ebx, %eax");
    out->printCode("je falseExpr" + intToStr(localNum));
    out->printCode("pushl $1");
    out->printCode("jmp endExpr" + intToStr(localNum));
    out->printCode("falseExpr" + intToStr(localNum) + ":");
    out->printCode("pushl $0");
    out->printCode("endExpr" + intToStr(localNum) + ":");
    out->endSection("<> expression");
}

void codeGeneratorRValue::visitLessExpressionNode(lessExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("< expression");
    out->printComment("evaluate left hand side");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side");
    v.visit(*visitedNodePtr->rhs);
    out->printComment("compare the values");
    out->printCode("popl %ebx # pop the rhs into ebx");
    out->printCode("popl %eax # pop the lhs into eax");
    int localNum = numberer->getNewNumber();
    out->printCode("cmpl %ebx, %eax");
    out->printCode("jnl falseExpr" + intToStr(localNum));
    out->printCode("pushl $1");
    out->printCode("jmp endExpr" + intToStr(localNum));
    out->printCode("falseExpr" + intToStr(localNum) + ":");
    out->printCode("pushl $0");
    out->printCode("endExpr" + intToStr(localNum) + ":");
    out->endSection("< expression");
}

void codeGeneratorRValue::visitLeqExpressionNode(leqExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("<= expression");
    out->printComment("evaluate left hand side");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side");
    v.visit(*visitedNodePtr->rhs);
    out->printComment("compare the values");
    out->printCode("popl %ebx # pop the rhs into ebx");
    out->printCode("popl %eax # pop the lhs into eax");
    int localNum = numberer->getNewNumber();
    out->printCode("cmpl %ebx, %eax");
    out->printCode("jnle falseExpr" + intToStr(localNum));
    out->printCode("pushl $1");
    out->printCode("jmp endExpr" + intToStr(localNum));
    out->printCode("falseExpr" + intToStr(localNum) + ":");
    out->printCode("pushl $0");
    out->printCode("endExpr" + intToStr(localNum) + ":");
    out->endSection("<= expression");
}

void codeGeneratorRValue::visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("> expression");
    out->printComment("evaluate left hand side");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side");
    v.visit(*visitedNodePtr->rhs);
    out->printComment("compare the values");
    out->printCode("popl %ebx # pop the rhs into ebx");
    out->printCode("popl %eax # pop the lhs into eax");
    int localNum = numberer->getNewNumber();
    out->printCode("cmpl %ebx, %eax");
    out->printCode("jng falseExpr" + intToStr(localNum));
    out->printCode("pushl $1");
    out->printCode("jmp endExpr" + intToStr(localNum));
    out->printCode("falseExpr" + intToStr(localNum) + ":");
    out->printCode("pushl $0");
    out->printCode("endExpr" + intToStr(localNum) + ":");
    out->endSection("> expression");
}

void codeGeneratorRValue::visitGeqExpressionNode(geqExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection(">= expression");
    out->printComment("evaluate left hand side");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side");
    v.visit(*visitedNodePtr->rhs);
    out->printComment("compare the values");
    out->printCode("popl %ebx # pop the rhs into ebx");
    out->printCode("popl %eax # pop the lhs into eax");
    int localNum = numberer->getNewNumber();
    out->printCode("cmpl %ebx, %eax");
    out->printCode("jnge falseExpr" + intToStr(localNum));
    out->printCode("pushl $1");
    out->printCode("jmp endExpr" + intToStr(localNum));
    out->printCode("falseExpr" + intToStr(localNum) + ":");
    out->printCode("pushl $0");
    out->printCode("endExpr" + intToStr(localNum) + ":");
    out->endSection(">= expression");
}

void codeGeneratorRValue::visitSumExpressionNode(sumExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("+ expression");
    out->printComment("evaluate left hand side:");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side:");
    v.visit(*visitedNodePtr->rhs);
    out->printCode("popl %eax # pop the right hand side");
    out->printCode("popl %ebx # pop the left hand side");
    out->printCode("addl %ebx, %eax # add them");
    out->printCode("pushl %eax # push the result");
    out->endSection("+ expression");
}

void codeGeneratorRValue::visitDiffExpressionNode(diffExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("- expression ");
    out->printComment("evaluate left hand side:");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side:");
    v.visit(*visitedNodePtr->rhs);
    out->printCode("popl %ebx # pop the right hand side");
    out->printCode("popl %eax # pop the left hand side");
    out->printCode("subl %ebx, %eax # subtract them");
    out->printCode("pushl %eax # push the result");
    out->endSection("- expression");
}

void codeGeneratorRValue::visitProductExpressionNode(productExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("* expression");
    out->printComment("evaluate left hand side:");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side:");
    v.visit(*visitedNodePtr->rhs);
    out->printCode("popl %ebx # pop the right hand side");
    out->printCode("popl %eax # pop the left hand side");
    out->printCode("imul %ebx # EDX:EAX = EAX * EBX");
    out->printComment("we only care about the EAX part");
    out->printCode("pushl %eax # push the result");
    out->endSection("* expression");
}

void codeGeneratorRValue::visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("/ expression");
    out->printComment("evaluate left hand side:");
    v.visit(*visitedNodePtr->lhs);
    out->printComment("evaluate right hand side:");
    v.visit(*visitedNodePtr->rhs);
    out->printCode("popl %ebx # pop the right hand side");
    out->printCode("popl %eax # pop the left hand side");
    out->printCode("cdq # so that the division works properly");
    out->printCode("idiv %ebx # divide them");
    out->printCode("pushl %eax # push the result");
    out->endSection("/ expression");
}

void codeGeneratorRValue::visitParenExpressionNode(parenExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("( ) expression ");
    for(int i = 0; i < visitedNodePtr->subTree.size(); i++) {
        programTree* currExpression = visitedNodePtr->subTree[i];
        typeTree* currType = typeOf(currExpression);
        v.visit(*currExpression);
        if(i < visitedNodePtr->subTree.size()-1){
            out->printCode("addl $" + intToStr(sizeOf(currType)) + ", %esp # discarding result");
        }
    }
    out->endSection("( ) expression");
}

void codeGeneratorRValue::visitPlusExpressionNode(plusExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("unary + expression");
    v.visit(*visitedNodePtr->subTree);
    out->endSection("unary + expression");
}

void codeGeneratorRValue::visitNegationExpressionNode(negationExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("unary - expression");
    v.visit(*visitedNodePtr->subTree);
    out->printCode("popl %eax # pop the result into eax");
    out->printCode("movl $-1, %ebx # move -1 into ebx");
    out->printCode("mul %ebx # EDX:EAX = EAX * EBX");
    out->printCode("pushl %eax # push the result");
    out->endSection("unary - expression");
}

// Input/Ouput Operations

void codeGeneratorRValue::visitInputExpressionNode(inputExpressionNode* visitedNodePtr) {
    out->beginSection("input expression");
    codeGeneratorLValue v(out, numberer, funNumberer);
    v.visit(*visitedNodePtr->subTree);
    out->printCode("pushl $inputPromptString");
    out->printCode("calll printf");
    out->printCode("addl $4, %esp # discard prompt string");
    out->printCode("pushl $inputBuffer");
    out->printCode("pushl $inputFormatString");
    out->printCode("calll scanf");
    out->printCode("addl $8, %esp # discard prompt string and buffer addresses");
    out->printCode("popl %eax # pop the address of the variable into eax");
    out->printCode("movl inputBuffer, %ebx # move the contents of the buffer to the variable");
    out->printCode("movl %ebx, (%eax) # .");
    out->printCode("pushl %ebx # push the inputted value");
    out->endSection("output expression");
}

void codeGeneratorRValue::visitOutputExpressionNode(outputExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("output expression");
    v.visit(*visitedNodePtr->subTree);
    out->printComment("the value to be printed is a 4-byte integer and is sitting on top of the stack");
    out->printCode("pushl $outputOperatorString");
    out->printCode("calll printf # print the output Format String");
    out->printCode("addl $4, %esp # discard address of output format string");
    out->endSection("output expression");
}

// Control Mechanisms

void codeGeneratorRValue::visitFunctionConstantNode(functionConstantNode* visitedNodePtr) {
    outputStream* newOut = new outputStream;
    codeGeneratorRValue v(newOut, numberer, funNumberer);
    codeGenSymbTable.enterScope();
    lexicalLevel++;
    int totalParamSize = visitedNodePtr->totalSizeOfParameters();
    int numParams = visitedNodePtr->numParams();
    string id;
    int lastSize = 0;
    int totalSize = 0;
    for(int i = 0; i < numParams; i++){
        id = retrieveIdentifier(visitedNodePtr->paramRef(i));
        symbolDeclaration symb(0, // line number, unused
                            id, // identifier
                            deepCopy(typeOf(visitedNodePtr->paramRef(i)))); // type
        symb.lexicalLevel = lexicalLevel;
        symb.paramIndex = totalSize;
        lastSize = sizeOf(typeOf(visitedNodePtr->paramRef(i)));
        codeGenSymbTable.insert(id, symb);
        totalSize += lastSize;
    }
    int localNum = funNumberer->getNewNumber();
    int returnTypeSize = sizeOf(typeOf(visitedNodePtr->exprList[visitedNodePtr->exprList.size()-1]));
    newOut->beginSection("function " + intToStr(localNum));
    newOut->printComment("lexical level: " + intToStr(lexicalLevel));
    newOut->printCode("function" + intToStr(localNum) + ":");
    newOut->beginSection("function preamble");
    newOut->printCode("movl %ebp, callerebp # save caller's bp in cx");
    newOut->printCode("movl %esp, %ebp # save caller's sp into bx for indirect addressing");
    newOut->printCode("movl " + intToStr(4+totalParamSize) + "(%ebp), %ebp # move the creator's function ep into bp");
    enter(lexicalLevel, newOut, numberer);
    newOut->printCode("movl callerebp,  %eax");
    newOut->printCode("movl %eax, (%ebp) # move saved caller's bp into saved bp spot for restoration by leave");
    newOut->endSection("function preamble");
    newOut->beginSection("function body");
    for(int i = 0; i < visitedNodePtr->exprList.size(); i++) {
        programTree* currExpression = visitedNodePtr->exprList[i];
        typeTree* currType = typeOf(currExpression);
        v.visit(*currExpression);
        if(i < visitedNodePtr->exprList.size()-1) {
            newOut->printCode("addl $" + intToStr(sizeOf(currType)) + ", %esp # discarding result");
        }
    }
    newOut->endSection("function body");
    newOut->beginSection("function closing");
    newOut->printComment("copy function return value into space reserved by caller");
    for(int i = 0; i < returnTypeSize; i+=4) {
        newOut->printCode("popl " + intToStr(16 + totalParamSize + i) + "(%ebp)");
    }
    newOut->printCode("leave # pop stack (including display) and restore caller's bp");
    newOut->printCode("ret $" + intToStr(totalParamSize+8) +
        " # return to caller and discard actuals and function constant value");
    newOut->endSection("function closing");
    newOut->endSection("function " + intToStr(localNum));
    out->lazyMerge(newOut);
    if(lexicalLevel > 1) {
        out->beginSection("function constant");
        out->printCode("pushl $function" + intToStr(localNum) + " # push the ip");
        out->printCode("pushl %ebp # push the ep");
        out->endSection("function constant");
    }
    lexicalLevel--;
    codeGenSymbTable.leaveScope();
    delete newOut;
}

void codeGeneratorRValue::visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("function application expression");
    int sizeOfReturnVal = sizeOf(returnType(typeOf(visitedNodePtr->funcPart)));
    out->printCode("subl $" + intToStr(sizeOfReturnVal) + ", %esp # allocate space for return value");
    v.visit(*visitedNodePtr->funcPart);
    out->printComment("function constant's <ep, ip> pair is sitting on the stack, with ep on top");
    out->printNewLine();

    int totalSize = 0;
    out->printComment("evaluating parameter values");
    for(int paramNum = visitedNodePtr->paramList.size()-1; paramNum >= 0; paramNum--) {
        for(int exprNum = 0; exprNum < visitedNodePtr->paramList[paramNum].size(); exprNum++) {
            programTree* currExpression = visitedNodePtr->paramList[paramNum][exprNum];
            v.visit(*currExpression);
        }
        totalSize += sizeOf(typeOf(visitedNodePtr->paramList[paramNum]));
    }
    out->printNewLine();

    out->printCode("movl " + intToStr(4 + totalSize) + "(%esp), %eax # move the ip into eax");
    out->printCode("calll *%eax");

    out->endSection("function application expression");
}

void codeGeneratorRValue::visitIfBlockNode(ifBlockNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    int localNum = numberer->getNewNumber();
    out->beginSection("if block");
    out->printComment("evaluate condition");
    for(int i = 0; i < visitedNodePtr->test.size(); i++){
        programTree* currExpression = visitedNodePtr->test[i];
        v.visit(*currExpression);
        if(i != visitedNodePtr->test.size()-1)
            out->printCode("addl $" + intToStr(sizeOf(typeOf(currExpression))) + ", %esp # discard the result");
    }
    out->printComment("begin section for first half");
    out->printCode("popl %eax # pop the conditional result");
    out->printCode("cmpl $0, %eax # compare to zero");
    out->printCode("je falseClause" + intToStr(localNum) + " # jump to false clause");
    out->printComment("true clause:");
    for(int i = 0; i < visitedNodePtr->trueClause.size(); i++){
        int size = sizeOf(typeOf(visitedNodePtr->trueClause[i]));
        v.visit(*visitedNodePtr->trueClause[i]);
        if(i != visitedNodePtr->trueClause.size()-1)
            out->printCode("addl $" + intToStr(size) + ", %esp # discard the result");
    }
    out->printCode("jmp endOfIf" + intToStr(localNum) + " # jump over false clause");
    out->printCode("falseClause" + intToStr(localNum) + ":");
    for(int i = 0; i < visitedNodePtr->falseClause.size(); i++){
        int size = sizeOf(typeOf(visitedNodePtr->falseClause[i]));
        v.visit(*visitedNodePtr->falseClause[i]);
        if(i != visitedNodePtr->falseClause.size()-1)
            out->printCode("addl $" + intToStr(size) + ", %esp # discard the result");
    }
    out->printCode("endOfIf" + intToStr(localNum) + ":");
    out->endSection("if block");
}

void codeGeneratorRValue::visitWhileBlockNode(whileBlockNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    int localNum = numberer->getNewNumber();
    out->beginSection("if block");
    out->printCode("whileStart" + intToStr(localNum) + ":");
    out->printComment("evaluate condition");
    for(int i = 0; i < visitedNodePtr->test.size(); i++){
        programTree* currExpression = visitedNodePtr->test[i];
        v.visit(*currExpression);
        if(i != visitedNodePtr->test.size()-1)
            out->printCode("addl $" + intToStr(sizeOf(typeOf(currExpression))) + ", %esp # discard the result");
    }
    out->printComment("the value on top of the stack is a 4-byte integer cooresponding to the while test");
    out->printCode("movl (%esp), %eax # move the value into eax without popping it");
    out->printCode("movl $0, %ebx # move 0 into ebx");
    out->printCode("cmpl %eax, %ebx # compare to 0");
    out->printCode("je whileEnd" + intToStr(localNum));
    out->printCode("addl $4, %esp # discard the value on top of the stack if it's not 0");
    out->beginSection("while body");
    for(int i = 0; i < visitedNodePtr->exprSeq.size(); i++){
        programTree* currExpression = visitedNodePtr->exprSeq[i];
        v.visit(*currExpression);
        out->printCode("addl $" + intToStr(sizeOf(typeOf(currExpression))) + ", %esp # discard the result");
    }
    out->printCode("jmp whileStart" + intToStr(localNum));
    out->endSection("while body");
    out->printCode("whileEnd" + intToStr(localNum) + ":");
    out->endSection("while block");
}

void codeGeneratorRValue::visitControlBlockNode(controlBlockNode* visitedNodePtr) {
    codeGeneratorRValue v1(out, numberer, funNumberer);
    codeGeneratorLValue v2(out, numberer, funNumberer);
    numberer->getNewNumber();
    int localNum = numberer->getNumber();
    int exprSize = sizeOf(typeOf(visitedNodePtr->exprSeq));
    out->beginSection("control block");
    out->printComment("allocate space for the return value");
    out->printCode("subl $" + intToStr(exprSize) + ", %esp");
    out->printNewLine();

    out->printComment("setup the continuation value");
    out->printComment("generate the l-value");
    v2.visit(*visitedNodePtr->cVal);
    out->printCode("popl %eax # pop address of continuation value");
    out->printCode("movl %esp, (%eax) # setup the sp of the cVal");
    out->printCode("movl %ebp, 4(%eax) # setup the ep of the cVal");
    out->printCode("movl $endControl" + intToStr(localNum) + ", 8(%eax) # setup the ip of the cVal");
    out->printNewLine();

    out->printComment("generate code for the body");
    for(int i = 0; i < visitedNodePtr->exprSeq.size(); i++){
        programTree* currExpression = visitedNodePtr->exprSeq[i];
        v1.visit(*currExpression);
        if(i < visitedNodePtr->exprSeq.size()-1)
            out->printCode("addl $" + intToStr(sizeOf(typeOf(currExpression))) + ", %esp # discard the result");
    }
    out->printNewLine();

    out->printComment("if we never hit a continues expression");
    out->printComment("then copy the value into the space provided");
    switch(exprSize) {
        case 12:
            out->printCode("popl %eax # pop the value");
            out->printCode("popl %ebx # ...");
            out->printCode("popl %ecx # ...");
            out->printCode("movl %eax, (%esp)  # place into reserved space");
            out->printCode("movl %ebx, 4(%esp) # ...");
            out->printCode("movl %ecx, 8(%esp) # ...");
            break;
        case 8:
            out->printCode("popl %eax # pop the value");
            out->printCode("popl %ebx # ...");
            out->printCode("movl %eax, (%esp)  # place into reserved space");
            out->printCode("movl %ebx, 4(%esp) # ...");
            break;
        case 4:
            out->printCode("popl %eax # pop the value");
            out->printCode("movl %eax, (%esp) # place into reserved space");
    }
    out->printComment("otherwise we're good to go");
    out->printCode("endControl" + intToStr(localNum) + ":");
    out->endSection("control block");
}

void codeGeneratorRValue::visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("continues expression");
    numberer->getNewNumber();
    int localNum = numberer->getNumber();
    int exprSize = sizeOf(typeOf(visitedNodePtr->rhs));

    out->printComment("evaluating continuation value");
    v.visit(*visitedNodePtr->lhs);

    out->printComment("evaluating right-hand-side");
    v.visit(*visitedNodePtr->rhs);

    out->printComment("extract sp from continuation value");
    out->printCode("movl " + intToStr(exprSize) + "(%esp), %eax");
    switch(exprSize) {
        case 12:
            out->printCode("popl (%eax)  # pop into reserved space");
            out->printCode("popl 4(%eax) # ...");
            out->printCode("popl 8(%eax) # ...");
            break;
        case 8:
            out->printCode("popl (%eax)  # pop into reserved space");
            out->printCode("popl 4(%eax) # ...");
            break;
        case 4:
            out->printCode("popl (%eax)  # pop into reserved space");
            break;
    }
    out->printCode("popl %eax # pop the sp from the continuation value");
    out->printCode("popl %ebx # ...     ep ...");
    out->printCode("popl %ecx # ...     ip ...");
    out->printCode("movl %eax, %esp # restore the sp");
    out->printCode("movl %ebx, %ebp # restore the ep");
    out->printCode("jmpl *%ecx      # restore the ip");
    out->endSection("continues expression");
}


// Other Stuff

void codeGeneratorRValue::visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v1(out, numberer, funNumberer);
    out->beginSection("assignment expression");
    codeGeneratorLValue v2(out, numberer, funNumberer);
    v2.visit(*visitedNodePtr->lhs);
    out->printBlockComment(string("keep in mind that the l-value of something more than 4 bytes long\n") +
                    "is the TOP of the object");
    v1.visit(*visitedNodePtr->rhs);
    switch(sizeOf(typeOf(visitedNodePtr->rhs))) {
    case 12:
        out->printCode("popl %eax # eax holds top of the value to be copied");
        out->printCode("popl %ebx # ebx holds the middle of the value to be copied");
        out->printCode("popl %ecx # ecx holds the bottom of the value to be copied");
        out->printCode("popl %edx # edx holds the destination value");
        out->printCode("movl %eax, (%edx) # copy the top");
        out->printCode("movl %ebx, 4(%edx) # copy the middle");
        out->printCode("movl %ecx, 8(%edx) # copy the bottom");
        out->printCode("pushl %ecx # push the bottom");
        out->printCode("pushl %ebx # push the middle");
        out->printCode("pushl %eax # push the top");
        break;
    case 8:
        out->printCode("popl %eax # eax holds top half of the value to be copied");
        out->printCode("popl %ebx # ebx now holds the bottom half the value");
        out->printCode("popl %edx # edx holds the destination value");
        out->printCode("movl %eax, (%edx) # copy the top half");
        out->printCode("movl %ebx, 4(%edx) # copy the second half");
        out->printCode("pushl %ebx # push the bottom half");
        out->printCode("pushl %eax # push the top half");
        break;
    case 4:
        out->printCode("popl %eax # eax holds the value to be copied");
        out->printCode("popl %edx # edx holds the destination value");
        out->printCode("movl %eax, (%edx) # perform the copy");
        out->printCode("pushl %eax # pushl the rhs value");
        break;
    }
    out->endSection("assignment expression");
}

void codeGeneratorRValue::visitStringLiteralNode(variableLiteralNode* visitedNodePtr) {
    out->beginSection("variable R-value");
    codeGenSymbTable.retrieve(visitedNodePtr->id);
    if(codeGenSymbTable.success()){
        symbolDeclaration symb = codeGenSymbTable.successAddress();
        int varLexLevel = symb.lexicalLevel;
        int varParamIndex = symb.paramIndex;
        typeTree* varType = symb.type();
        if(varLexLevel == lexicalLevel) {
            out->printComment("extracting from the same lexical level");
            out->printComment(intToStr(varLexLevel) + " lexical level");
            out->printComment(intToStr(varParamIndex) + " parameter ref");
            out->printComment("push the variable value:");
            switch(sizeOf(varType)) {
                case 12:
                    out->printCode("pushl " + intToStr(16+varParamIndex) + "(%ebp)");
                case 8:
                    out->printCode("pushl " + intToStr(12+varParamIndex) + "(%ebp)");
                case 4:
                    out->printCode("pushl " + intToStr(8 + varParamIndex) + "(%ebp)");
                    break;
            }
        }
        else {
            out->printComment("extracting from a lexical level deeper than our own");
            out->printCode("movl " + intToStr(-4*varLexLevel) + "(%ebp), %eax");
            out->printComment("eax is now the address of the desired display");
            out->printComment(intToStr(varLexLevel) + " lexical level");
            out->printComment(intToStr(varParamIndex) + " parameter ref");
            switch(sizeOf(varType)) {
                case 12:
                    out->printCode("pushl " + intToStr(16+varParamIndex) + "(%eax)");
                case 8:
                    out->printCode("pushl " + intToStr(12+varParamIndex) + "(%eax)");
                case 4:
                    out->printCode("pushl " + intToStr(8 + varParamIndex) + "(%eax)");
                    break;
            }
        }
    }
    else {
        out->printComment("invalid identifier");
        out->printCode("pushl $0");
    }
    out->endSection("variable R-value");
}

void codeGeneratorRValue::visitVariableBlockNode(variableBlockNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    codeGenSymbTable.enterScope();
    lexicalLevel++;
    int totalParamSize = visitedNodePtr->totalSizeOfVars();
    int numParams = visitedNodePtr->numVars();
    vector<orderedPair<int, int> > vecs;
    string id;
    int lastSize = 0;
    int totalSize = 0;
    for(int i = numParams-1; i >= 0; i--){
        symbolDeclaration symb;
        id = retrieveIdentifier(visitedNodePtr->varList[i]);
        symb = symbolDeclaration(0, // line number, unused
                                id, // identifier
                                deepCopy(typeOf(visitedNodePtr->varList[i]))); // type
        if(isRefvec(typeOf(visitedNodePtr->varList[i]))) {
            vecs.push_back(orderedPair<int, int>(i, totalSize));
        }
        symb.lexicalLevel = lexicalLevel;
        symb.paramIndex = totalSize;
        lastSize = sizeOf(typeOf(visitedNodePtr->varList[i]));
        totalSize += lastSize;
        codeGenSymbTable.insert(id, symb);
    }
    int localNum = numberer->getNewNumber();
    int returnTypeSize = sizeOf(typeOf(visitedNodePtr->exprSeq[visitedNodePtr->exprSeq.size()-1]));
    out->beginSection("vars block " + intToStr(localNum));
    out->printComment("lexical level: " + intToStr(lexicalLevel));
    out->printComment("number of params: " + intToStr(numParams));
    out->printComment("size of params: " + intToStr(totalParamSize));
    out->printComment("number of vecs:" + intToStr(vecs.size()));

    out->printComment("setup the display");
    switch(sizeOf(typeOf(visitedNodePtr->exprSeq[visitedNodePtr->exprSeq.size()-1]))) {
        case 12:
            out->printCode("subl $12, %esp # push space for return value");
            break;
        case 8:
            out->printCode("subl $8, %esp # push space for return value");
            break;
        case 4:
            out->printCode("subl $4, %esp # push space for return value");
            break;
    }
    out->printCode("pushl $0 # push the fake ip");
    out->printCode("pushl %ebp # push creator's ep");
    out->printComment("push the default variable values onto the stack:");
    for(int i = 0; i < numParams; i++){
        switch(sizeOf(typeOf(visitedNodePtr->varList[i]))) {
            case 12:
                out->printCode("pushl $0");
            case 8:
                out->printCode("pushl $0");
            case 4:
                out->printCode("pushl $0");
                break;
        }
    }
    out->printCode("pushl $0 # push the fake return address");
    out->beginSection("vars preamble");
    enter(lexicalLevel, out, numberer);
    if(vecs.size() > 0) {
        // this should be at offset 4+lexicalLevel
        out->printCode("pushl $0 # space for vec local variable");
        out->printComment("setup vectors");

        for(int i = 0; i < vecs.size(); i++) {
            int paramRef = vecs[i].firstReference();
            programTree* currVec = visitedNodePtr->varList[paramRef];
            out->beginSection("vector " + intToStr(i));
            int stackRef = vecs[i].secondReference();
            typeTree* vecSubType = unRefvec(typeOf(currVec));
            out->printComment("vector of " + toStr(vecSubType));

            out->printComment("evaluate size expression");
            v.visit(*currVec);

            out->printCode("movl %esp, %eax");

            out->printCode("subl $4, %esp # reserve space for return value");
            out->printCode("pushl %eax # push the size array's pointer");
            out->printCode("pushl $" + intToStr(dimension(typeOf(currVec))) + " # push the dimension onto the stack");
            out->printCode("pushl $" + intToStr(baseElementSize(currVec)) + " # push the size of a base element");
            out->printCode("calll sizeOfVecs");
            out->printCode("popl %ebx # ebx now holds the size");
            out->printCode("subl $8, %ebx # the top refvec is already allocated");
            out->printComment("now ebx holds the size of the allocated vector");
            out->printCode("subl %ebx, %esp # allocate the space");
            out->printCode("movl %esp, %ecx");
            out->printComment("ecx = array pointer");
            out->printComment("ebx = total vector size");
            out->printComment("eax = size array pointer");
            out->printCode("pushl %eax # push the size array pointer");
            out->printCode("pushl $" + intToStr(dimension(typeOf(currVec))) + " # push the dimension");
            out->printCode("pushl $" + intToStr(baseElementSize(currVec)) + " # push the base element size");
            out->printCode("pushl %ecx # push the arena pointer");
            out->printCode("leal " + intToStr(8+stackRef) + "(%ebp), %eax # calculate the vp");
            out->printCode("pushl %eax # push the vp");
            out->printCode("call setupVector # setup the vector");
            out->endSection("vector " + intToStr(i));
        }
    }
    out->endSection("vars preamble");

    out->beginSection("vars body");
    for(int i = 0; i < visitedNodePtr->exprSeq.size(); i++) {
        programTree* currExpression = visitedNodePtr->exprSeq[i];
        typeTree* currType = typeOf(currExpression);
        v.visit(*currExpression);
        if(i < visitedNodePtr->exprSeq.size()-1) {
            out->printCode("addl $" + intToStr(sizeOf(currType)) + ", %esp # discarding result");
        }
    }
    out->endSection("vars body");

    out->beginSection("vars closing");
    out->printComment("copy vars return value into space reserved by caller");
    for(int i = 0; i < returnTypeSize; i+=4) {
        out->printCode("popl " + intToStr(16 + totalParamSize + i) + "(%ebp)");
    }
    out->printCode("leave # pop stack (including display) and restore caller's bp");
    out->printCode("addl $" + intToStr(totalParamSize+12) + ", %esp # discard junk on top of stack.");

    out->endSection("vars closing");

    out->endSection("vars " + intToStr(localNum));
    lexicalLevel--;
    codeGenSymbTable.leaveScope();
}

// @
// Converts from an l-value to an r-value
void codeGeneratorRValue::visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr) {
    out->beginSection("@ r-value");
    codeGeneratorRValue v(out, numberer, funNumberer);
    v.visit(*visitedNodePtr->subTree);
    out->printCode("popl %eax # get the l-value");
    switch(sizeOf(unRef(typeOf(visitedNodePtr->subTree)))) {
        case 12:
            out->printCode("pushl 8(%eax) # push the r-value");
            out->printCode("pushl 4(%eax)");
            out->printCode("pushl (%eax)");
            break;
        case 8:
            out->printCode("pushl 4(%eax) # push the r-value");
            out->printCode("pushl (%eax)");
            break;
        case 4:
            out->printCode("pushl (%eax) # push the r-value");
            break;
    }
    out->endSection("@ r-value");
}

// &
// Converts from an r-value to an l-value
void codeGeneratorRValue::visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr) {
    codeGeneratorLValue v(out, numberer, funNumberer);
    out->beginSection("& r-value");
    v.visit(*visitedNodePtr->subTree);
    out->endSection("& r-value");
}

// This shouldn't ever happen.
void codeGeneratorRValue::visitProgramErrorNode(programErrorNode* visitedNodePtr) {
    out->printComment("Program Error Node Reached");
    out->printComment("Something went VERY wrong.");
}

void codeGeneratorRValue::visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr) {
    out->printComment("Parameter Declaration Node Reached");
    out->printComment("Something went VERY wrong.");
}
void codeGeneratorRValue::visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr) {
    out->printComment("visited a variable declaration of type: " + toStr(visitedNodePtr->type()));
}

//
// Vector Stuff:
//

void codeGeneratorRValue::visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("vector size expression");
    out->printComment("extract the r-value of the vector");
    v.visit(*visitedNodePtr->subTree);
    out->printComment("the reference to the vector is on top of the stack");
    out->printCode("addl $4, %esp");
    out->printComment("the size is under it, so just leave it on the stack");
    out->endSection("vector size expression");
}

void codeGeneratorRValue::visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    typeTree* vecSubType = unRefvec(typeOf(visitedNodePtr->vecPart));
    numberer->getNewNumber();
    int localNum = numberer->getNumber();
    out->beginSection("vector ref r-val operation");
    out->printComment("extract the r-value of the vector");
    v.visit(*visitedNodePtr->vecPart);
    out->printComment("evaluate the index expression");
    for(int i = 0; i < visitedNodePtr->indexPart.size(); i++) {
        v.visit(*visitedNodePtr->indexPart[i]);
        if(i < visitedNodePtr->indexPart.size()-1)
            out->printCode("addl $" + intToStr(sizeOf(typeOf(visitedNodePtr->indexPart[i]))) + ", %esp # discard the result");
    }
    out->printCode("popl %eax # eax = index");
    out->printCode("popl %ebx # ebx = vector reference");
    out->printCode("popl %ecx # ecx = vector size");
    out->printCode("cmpl %ecx, %eax # compare the index to the size");
    out->printCode("jge vecRefBAD" + intToStr(localNum));
    out->printCode("movl $0, %edx   # setup the next compare");
    out->printCode("cmpl %edx, %eax # compare the index to 0");
    out->printCode("jl vecRefBAD" + intToStr(localNum));
    out->printCode("jmp vecRefGOOD" + intToStr(localNum));
    out->printCode("vecRefBAD" + intToStr(localNum) + ":");
    out->printCode("pushl %eax");
    out->printCode("pushl %ecx");
    out->printCode("pushl $errorVectorAccess");
    out->printCode("calll printf");
    out->printCode("addl $4, %esp");
    out->printCode("movl $-1, %eax  # purposefully throw a segfault");
    out->printCode("movl $0, (%eax) # TODO find out if there's a better way to do this...");
    out->printCode("vecRefGOOD" + intToStr(localNum) + ":");
    out->printCode("movl $" + intToStr(sizeOf(vecSubType)) + ", %edx # move element size into edx");
    out->printCode("mull %edx");
    out->printCode("addl %ebx, %eax # eax = (element size)*index + vec ref");
    switch(sizeOf(vecSubType)) {
        case 12:
            break;
            out->printCode("pushl 8(%eax)");
            out->printCode("pushl 4(%eax)");
            out->printCode("pushl (%eax)");
        case 8:
            out->printCode("pushl 4(%eax)");
            out->printCode("pushl (%eax)");
            break;
        case 4:
            out->printCode("pushl (%eax)");
            break;
    }
    out->endSection("vector ref r-val operation");
}

void codeGeneratorRValue::visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr) {
    out->beginSection("vector creation expression");
    codeGeneratorRValue v(out, numberer, funNumberer);
    if(vecSizesBackwards != backwards) {
        out->printComment("print vector sizes");
        if(visitedNodePtr->vectorSubtype() != NULL)
            v.visit(*visitedNodePtr->vectorSubtype(), vecSizesBackwards);
        for(int i = 0; i < visitedNodePtr->sizeExpression().size(); i++) {
            v.visit(*visitedNodePtr->sizeExpression()[i]);
            if(i < visitedNodePtr->sizeExpression().size()-1)
                out->printCode("addl $4, %esp # discard value on stack");
        }
    }
    else {
        out->printComment("print vector sizes BACKWARDS");
        for(int i = 0; i < visitedNodePtr->sizeExpression().size(); i++) {
            v.visit(*visitedNodePtr->sizeExpression()[i]);
            if(i < visitedNodePtr->sizeExpression().size()-1)
                out->printCode("addl $4, %esp # discard value on stack");
        }
        if(visitedNodePtr->vectorSubtype() != NULL)
            v.visit(*visitedNodePtr->vectorSubtype(), vecSizesBackwards);
    }
    out->endSection("vector creation expression");
}

//
// codeGeneratorLValue Class: Function Definitions
//

codeGeneratorLValue::codeGeneratorLValue(outputStream* initOut, numberGenerator* initNumberer, numberGenerator* initFunNumberer)
    : out(initOut), numberer(initNumberer), funNumberer(initFunNumberer) {
}

void codeGeneratorLValue::visit(programTree& p) {
    p.accept(this);
}

void codeGeneratorLValue::defaultCase() {
    out->printBlockComment("ERROR:\nDefault Case Hit for l-val Visitor");
}

void codeGeneratorLValue::visitStringLiteralNode(variableLiteralNode* visitedNodePtr) {
    out->beginSection("variable l-value");
    codeGenSymbTable.retrieve(visitedNodePtr->id);
    if(codeGenSymbTable.success()){
        symbolDeclaration symb = codeGenSymbTable.successAddress();
        int varLexLevel = symb.lexicalLevel;
        int varParamIndex = symb.paramIndex;
        typeTree* varType = symb.type();
        if(varLexLevel == lexicalLevel) {
            out->printComment("extracting from the same lexical level");
            out->printComment(intToStr(varLexLevel) + " lexical level");
            out->printComment(intToStr(varParamIndex) + " parameter ref");
            out->printComment("push the variable value:");
            out->printCode("leal " + intToStr(8 + varParamIndex) + "(%ebp), %eax");
        }
        else {
            out->printComment("extracting from a lexical level deeper than our own");
            out->printCode("movl " + intToStr(-4*varLexLevel) + "(%ebp), %eax");
            out->printComment("eax is now the address of the desired display");
            out->printComment(intToStr(varLexLevel) + " lexical level");
            out->printComment(intToStr(varParamIndex) + " parameter ref");
            out->printCode("leal " + intToStr(8 + varParamIndex) + "(%eax), %eax");
        }
        out->printCode("pushl %eax");
    }
    else {
        fatalError("failed to find identifier: " + visitedNodePtr->id);
        out->printCode("pushl $0");
    }
    out->endSection("variable l-value");
}

void codeGeneratorLValue::visitDereferenceExpressionNode(dereferenceExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    out->beginSection("@ l-value");
    v.visit(*visitedNodePtr->subTree);
    out->endSection("@ l-value");
}

void codeGeneratorLValue::visitReferenceExpressionNode(referenceExpressionNode* visitedNodePtr) {
    out->beginSection("& l-value");
    out->printComment("BAD BAD BAD");
    out->endSection("& l-value");
}

void codeGeneratorLValue::visitParenExpressionNode(parenExpressionNode* visitedNodePtr) {
    codeGeneratorLValue v(out, numberer, funNumberer);
    out->beginSection("( ) l-value");
    for(int i = 0; i < visitedNodePtr->subTree.size()-1; i++) {
        codeGeneratorRValue v(out, numberer, funNumberer);
        v.visit(*visitedNodePtr->subTree[i]);
        int size = sizeOf(typeOf(visitedNodePtr->subTree[i]));
        out->printCode("addl $" + intToStr(size) + ", %esp # discard the result");
    }
    v.visit(*visitedNodePtr->subTree[visitedNodePtr->subTree.size()-1]);
    out->endSection("( ) l-value");
}

void codeGeneratorLValue::visitVectorRefExpressionNode(vectorRefExpressionNode* visitedNodePtr) {
    codeGeneratorRValue v(out, numberer, funNumberer);
    typeTree* vecSubType = unRefvec(typeOf(visitedNodePtr->vecPart));
    numberer->getNewNumber();
    int localNum = numberer->getNumber();
    out->beginSection("vector ref l-val operation");
    out->printComment("extract the r-value of the vector");
    v.visit(*visitedNodePtr->vecPart);
    out->printComment("evaluate the index expression");
    for(int i = 0; i < visitedNodePtr->indexPart.size(); i++) {
        v.visit(*visitedNodePtr->indexPart[i]);
        if(i < visitedNodePtr->indexPart.size()-1)
            out->printCode("addl $" + intToStr(sizeOf(typeOf(visitedNodePtr->indexPart[i]))) + ", %esp # discard the result");
    }
    out->printCode("popl %eax # eax = index");
    out->printCode("popl %ebx # ebx = vector reference");
    out->printCode("popl %ecx # ecx = vector size");
    out->printCode("cmpl %ecx, %eax # compare the index to the size");
    out->printCode("jge vecRefBAD" + intToStr(localNum));
    out->printCode("movl $0, %edx   # setup the next compare");
    out->printCode("cmpl %edx, %eax # compare the index to 0");
    out->printCode("jl vecRefBAD" + intToStr(localNum));
    out->printCode("jmp vecRefGOOD" + intToStr(localNum));
    out->printCode("vecRefBAD" + intToStr(localNum) + ":");
    out->printCode("pushl $errorVectorAccess");
    out->printCode("calll printf");
    out->printCode("addl $4, %esp");
    out->printCode("movl $-1, %eax  # purposefully throw a segfault");
    out->printCode("movl $0, (%eax) # find out if there's a better way to do this...");
    out->printCode("vecRefGOOD" + intToStr(localNum) + ":");
    out->printCode("movl $" + intToStr(sizeOf(vecSubType)) + ", %edx # move element size into edx");
    out->printCode("mull %edx");
    out->printCode("addl %ebx, %eax # eax = (element size)*index + vec ref");
    out->printCode("pushl %eax");
    out->endSection("vector ref l-val operation");
}

void codeGeneratorLValue::visitFunctionConstantNode(functionConstantNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitParameterDeclarationNode(parameterDeclarationNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitVariableDeclarationNode(variableDeclarationNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitContinuesExpressionNode(continuesExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitAssignmentExpressionNode(assignmentExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitEqExpressionNode(eqExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitNeqExpressionNode(neqExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitLessExpressionNode(lessExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitLeqExpressionNode(leqExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitGreaterExpressionNode(greaterExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitGeqExpressionNode(geqExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitSumExpressionNode(sumExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitDiffExpressionNode(diffExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitProductExpressionNode(productExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitQuotientExpressionNode(quotientExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitInputExpressionNode(inputExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitOutputExpressionNode(outputExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitPlusExpressionNode(plusExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitNegationExpressionNode(negationExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitVecSizeExpressionNode(vecSizeExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitWhileBlockNode(whileBlockNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitIfBlockNode(ifBlockNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitControlBlockNode(controlBlockNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitVariableBlockNode(variableBlockNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitFunctionApplicationNode(functionApplicationNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitConstantExpressionNode(constantExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitTrivExpressionNode(trivExpressionNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitVectorDeclarationNode(vectorDeclarationNode* visitedNodePtr){ defaultCase(); }
void codeGeneratorLValue::visitProgramErrorNode(programErrorNode* visitedNodePtr){ defaultCase(); }

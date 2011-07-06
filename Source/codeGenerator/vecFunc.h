const string vecFuncs = "\n\
.global sizeOfVecs\n\
.align 4\n\
# This function takes as parameters:\n\
#   <top of stack>\n\
#   t   - the size of a single element of the vector\n\
#   n   - the size of the array...\n\
#   sp  - a pointer to an array of sizes\n\
#   rv  - space for return value\n\
#   <bottom of stack>\n\
#\n\
# This function assumes that:\n\
#   the sizes are pushed onto the stack in order of level\n\
#   (the outermost size is pushed first and the innermost size is pushed last),\n\
#   a 4-bytes space is left on the stack before any of the parameters are pushed.\n\
#\n\
# This function DOES NOT pop any values off the stack when it returns.\n\
# It leaves the stack exactly how it was when it was called.\n\
# Care should be taken to pop the values off the stack for sanitation.\n\
#\n\
sizeOfVecs:\n\
    enter $0, $0 # save stack frame\n\
    pushal # push registers\n\
\n\
    #\n\
    # the parameters are:\n\
    #   t   is at 8(%ebp)\n\
    #   n   is at 12(%ebp)\n\
    #   sp  is at 16(%ebp)\n\
    #   rv  is at 20(%ebp)\n\
    #\n\
\n\
    # int total = t;\n\
    # total will be %ebx\n\
    movl 8(%ebp), %ebx\n\
\n\
    # int i = n-1;\n\
    # i will be stored in %ecx\n\
    movl 12(%ebp), %ecx\n\
    decl %ecx\n\
\n\
  vecSizesStartLoop:\n\
    # while(0 <= i){\n\
    cmpl $0, %ecx\n\
    jl vecSizesEndLoop\n\
\n\
    # total = 8 + sp[i]*total; \n\
    # sp[i] is really: sp + 4i\n\
    # so...\n\
    movl %ecx, %eax     # eax = i\n\
    sall %eax\n\
    sall %eax           # eax = 4i\n\
    addl 16(%ebp), %eax # eax = sp + 4i\n\
    # now %eax is the position of sp[i]\n\
    movl (%eax), %eax   # eax = sp[i]\n\
\n\
    # now %eax holds sp[i], we need to multiply by the total\n\
    mull %ebx\n\
\n\
    # now %eax = sp[i]*total\n\
    addl $8, %eax\n\
\n\
    # now %eax = 8 + sp[i]*total\n\
    movl %eax, %ebx\n\
\n\
    # i--;\n\
    decl %ecx\n\
    jmp vecSizesStartLoop\n\
    # }\n\
  vecSizesEndLoop:\n\
\n\
#    pushl %ebx\n\
#    pushl $debug1\n\
#    calll printf\n\
#    addl $4, %esp\n\
#    popl %ebx\n\
\n\
    movl %ebx, 20(%ebp)\n\
\n\
    # return total;\n\
    popal # pop saved registers\n\
    leave # restore stack frame\n\
    ret $12 # return and pop parameters\n\
\n\
setupVectorMessage:\n\
    .string \"\"\n\
    .string \"setup vector:\\n\\tvp:\\t0x%x\\n\\tap:\\t0x%x\\n\\tt:\\t%d\\n\\tn:\\t%d\\n\\tsp:\\t0x%x\\n\\tsp[0]:\\t%d\\n\"\n\
\n\
.align 4\n\
.global setupVector\n\
#\n\
# Sets up a vector from previously allocated space.\n\
#\n\
# Has these parameters:\n\
#   <top of stack>\n\
#   vp  - pointer to refvec we're initializing\n\
#   ap  - pointer to an arena of space for use\n\
#   t   - the size of an element of the vector\n\
#   n   - dimension of the vector\n\
#   sp  - pointer to array of sizes\n\
#   <bottom of stack>\n\
#\n\
setupVector:\n\
    enter $4, $0\n\
    pushal\n\
\n\
#   pushl $debug2\n\
#   calll printf\n\
#   addl $4, %esp\n\
\n\
    # space for recursive total size\n\
    #       is at -4(%ebp)\n\
    # vp    is at 8(%ebp)\n\
    # ap    is at 12(%ebp)\n\
    # t     is at 16(%ebp)\n\
    # n     is at 20(%ebp)\n\
    # sp    is at 24(%ebp)\n\
\n\
    movl 24(%ebp), %ecx\n\
    movl (%ecx), %eax\n\
    pushl %eax\n\
    pushl %ecx\n\
    pushl 20(%ebp)\n\
    pushl 16(%ebp)\n\
    pushl 12(%ebp)\n\
    pushl 8(%ebp)\n\
    pushl $setupVectorMessage\n\
    calll printf\n\
    addl $28, %esp\n\
\n\
    # setup the refvec to point to the appropriate place\n\
    movl 8(%ebp), %eax\n\
    movl 12(%ebp), %ebx\n\
    movl %ebx, (%eax)\n\
    # setup the size:\n\
    movl 24(%ebp), %ebx\n\
    movl (%ebx), %ebx\n\
    movl %ebx, 4(%eax)\n\
\n\
    movl 20(%ebp), %eax\n\
    cmpl $1, %eax\n\
    je setupVecEndLoop\n\
\n\
    # vp = ap\n\
    movl 12(%ebp), %eax\n\
    movl %eax, 8(%ebp)\n\
\n\
    # ap += 8*sp[0]\n\
    movl 24(%ebp), %eax\n\
    movl (%eax), %eax\n\
    sall %eax\n\
    sall %eax\n\
    sall %eax\n\
    addl 12(%ebp), %eax\n\
    movl %eax, 12(%ebp)\n\
\n\
    # recrSize = sizeOfVecs(t, n-1, sp+4);\n\
    subl $4, %esp\n\
\n\
    movl 24(%ebp), %eax\n\
    addl $4, %eax\n\
    pushl %eax\n\
\n\
    movl 20(%ebp), %eax\n\
    decl %eax\n\
    pushl %eax\n\
\n\
    movl 16(%ebp), %eax\n\
    pushl %eax\n\
\n\
    calll sizeOfVecs\n\
\n\
    popl %eax\n\
    subl $8, %eax\n\
    movl %eax, -4(%ebp)\n\
\n\
    # now we need to do the for loop\n\
\n\
    # i = 0\n\
    movl $0, %ecx\n\
  setupVecStartLoop:\n\
    movl 24(%ebp), %eax\n\
    movl (%eax), %eax\n\
    # loop if i < sp[0]\n\
    cmpl %ecx, %eax\n\
    jle setupVecEndLoop\n\
\n\
    # -- body of for loop --\n\
\n\
    # push the parameters for setup vector\n\
\n\
    # push sp+4\n\
    movl 24(%ebp), %eax\n\
    addl $4, %eax\n\
    pushl %eax\n\
\n\
    # push n-1\n\
    movl 20(%ebp), %eax\n\
    decl %eax\n\
    pushl %eax\n\
\n\
    # push t\n\
    movl 16(%ebp), %eax\n\
    pushl %eax\n\
\n\
    # push ap\n\
    movl 12(%ebp), %eax\n\
    pushl %eax\n\
\n\
    # push the vp\n\
    movl 8(%ebp), %eax\n\
    pushl %eax\n\
\n\
    # call the function\n\
    calll setupVector\n\
\n\
    # vp += 8\n\
    movl 8(%ebp), %eax\n\
    addl $8, %eax\n\
    movl %eax, 8(%ebp)\n\
\n\
    # ap += recrSize\n\
    movl -4(%ebp), %eax\n\
    addl 12(%ebp), %eax\n\
    movl %eax, 12(%ebp)\n\
\n\
    # -- end body of for loop --\n\
\n\
    incl %ecx\n\
    jmp setupVecStartLoop\n\
    # end for loop\n\
  setupVecEndLoop:\n\
\n\
    # no return value to copy\n\
\n\
    popal\n\
    leave\n\
    ret $20\n\
";

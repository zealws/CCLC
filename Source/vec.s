.section .text
.align 4
.global sizeOfVecs
# This function takes as parameters:
#   the sizes of each vector in a multi-dimensional vector,
#   the size of one element of the vector,
#   the dimension of the vector.
#
# This function assumes that:
#   the sizes are pushed onto the stack in order of level
#   (the outermost size is pushed first and the innermost size is pushed last),
#   a 4-bytes space is left on the stack before any of the parameters are pushed.
#
# This function DOES NOT pop any values off the stack when it returns.
# It leaves the stack exactly how it was when it was called.
# Care should be taken to pop the values off the stack for sanitation.
#
sizeOfVecs:
    enter $0, $0
    pushal
    # depth of the vector is the first parameter at 4(%ebp)
    movl $0, %ecx
    movl $0, %ebx
    movl 12(%ebp), %eax
  vecSizeBeginLoop:
    cmpl 8(%ebp), %ecx
    je vecSizeEndLoop
    # at this point in the execution:
    #   ecx holds the index of the current vector
    #   eax holds the size of the subvec for the vec we're looking at
    #   8(%ebp) holds the dimension of the vector
    #   12(%ebp) holds the size of one element of the vector
    movl %ecx, %edx
    sall %edx
    sall %edx
    addl $16, %edx
    addl %ebp, %edx
    # edx points to the size of our current vec
    mull (%edx)
    # Now eax holds the scaled value
    
    addl $8, %eax
#    pushl %ecx
#    pushl (%edx)
#    pushl $outputInt
#    calll printf
#    addl $8, %esp
#    popl %ecx
    inc %ecx
    jmp vecSizeBeginLoop
  vecSizeEndLoop: 
    # eax now holds the total size of the vector
    # ecx now is the dimension + 1
    # we can use it now for referencing the return value space
    sall %ecx
    sall %ecx
    addl $16, %ecx
    addl %ebp, %ecx
    movl %eax, (%ecx)
    popal
    leave
    ret
.align 4
.global setupVector
#
# Sets up a vector from previously allocated space.
#
# Has these parameters:
#   <top of stack>
#   vp - pointer to refvec we're initializing
#   ap - pointer to an arena of space for use
#   t  - the size of an element of the vector
#   n  - dimension of the vector
#   a0 - size of the vector we're setting up
#   a1 
#   a2 
#   ...
#   an-1 - sizes of the subvectors
#
setupVector:
    enter $4, $0
    pushal
    # space for recursive total size is at
    #   -4(%ebp)
    # vp is at 8(%ebp)
    # ap is at 12(%ebp)
    # t is at 16(%ebp)
    # n  is at 20(%ebp)
    # a0 is at 24(%ebp)
    # a1 is at 28(%ebp)
    # ...
    # an-1 is at (20+4(n-1))(%ebp)
    # setup the refvec to point to the appropriate place
    movl 8(%ebp), %eax
    movl 12(%ebp), %ebx
    movl %ebx, (%eax)
    # setup the size part of the refvec
    movl 24(%ebp), %ebx
    movl %ebx, 4(%eax)
    # compare n to 0, if they are equal, jump to the end
    movl 20(%ebp), %eax
    cmpl $0, %eax
    je endOfSetupVector
    # setup n as n-1 for convenience
    movl 20(%ebp), %eax
    decl %eax
    movl %eax, 20(%ebp)
    # this is where we start setting up the first call to sizeOfVecs
    subl $4, %esp
    # next call the recursive total size
    # we need a loop to push the parameters of variable size
    movl 20(%ebp), %ecx
  beginPushParameter1Loop:
    cmpl $0, %ecx
    je endPushParameter1Loop
    movl %ecx, %eax
    sall %eax
    sall %eax
    # eax = 4i
    addl $24, %eax
    # eax = 24+4i
    addl %ebp, %eax
    # eax = 24+4i(%ebp)
    # push the parameter value
    pushl (%eax)
    decl %ecx
    jmp beginPushParameter1Loop
  endPushParameter1Loop:
    # n-1 values were pushed onto the stack
    # we need to push the rest of the values
    # push t
    pushl 16(%ebp)
    # push n-1
    pushl 20(%ebp)
    # call the size function
    call sizeOfVecs
    # we need to clean up the stack
    # we pushed 8+4(n-1) bytes of junk
    # so we need to pop that much off
    movl 20(%ebp), %eax
    sall %eax
    sall %eax
    addl $8, %eax
    addl %eax, %esp
    # now the return value for the size is sitting on top of the stack
    # move the calculated size into the local variable space
    popl %eax
    movl %eax, -4(%ebp)
    # as of now, the stack is clean
    # the first thing to do is set
    # vp = ap + totalSize
    # we just calculated totalSize
    movl -4(%ebp), %eax
    # so we can add ap to it
    addl 12(%ebp), %eax
    # and assign that to vp
    movl %eax, 8(%ebp)
    # now we need to emulate the for loop
    # the counter will be stored in ecx
    movl $0, %ecx
  beginForLoop1:
    movl 20(%ebp), %eax
    incl %eax
    cmpl %ecx, %eax
    je endForLoop1
    # -- body of for loop --
    # now we need to make the recursive call to setupVector
    # it has no return value, so don't allocate space for it
    # start by pushing all the vector sizes
    # starting with the innermost one
    movl 20(%ebp), %ebx
  beginPushParameter2Loop:
    cmpl $0, %ebx
    je endPushParameter2Loop
    movl %ebx, %eax
    sall %eax
    sall %eax
    # eax = 4i
    addl $24, %eax
    # eax = 24+4i
    addl %ebp, %eax
    # eax = 24+4i(%ebp)
    # push the parameter value
    pushl (%eax)
    decl %ebx
    jmp beginPushParameter2Loop
  endPushParameter2Loop:
    # now we have pushed all the a1 .. an-1 onto the stack
    # we just need to push the dimension
    pushl 20(%ebp)
    # and t
    pushl 16(%ebp)
    # and the ap
    pushl 12(%ebp)
    # and the vp
    pushl 8(%ebp)
    # now make the call
    calll setupVector
    # now clean up the stack
    # we've pushed 16+4(n-1) bytes onto the stack
    movl 20(%ebp), %eax
    # eax = n-1
    sall %eax
    sall %eax
    # eax = 4(n-1)
    addl $16, %eax
    # eax = 16+4(n-1)
    # clean the space up
    addl %eax, %esp
    # ap += 8
    movl 12(%ebp), %eax
    addl $8, %eax
    movl %eax, 12(%ebp)
    # vp += totalSize
    movl 8(%ebp), %eax
    addl -4(%ebp), %eax
    movl %eax, 8(%ebp)
    # -- end body of for loop --
    incl %ecx
    jmp beginForLoop1
  endForLoop1:
  endOfSetupVector:
    popal
    leave
    ret

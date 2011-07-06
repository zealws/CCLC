/*
 * Run-time flag to give verbose warnings and error messages
 *
 * If this is set to true, the parser will:
 *
 *  1) Print a warning for shadowed variables.
 *
 *  2) Print a note for type checking errors when appropriate with both the
 *     expected type, and the given type. This can be helpful for debugging
 *     CCL code, as well as the compiler itself.
 */
extern bool verboseMessages;

extern bool useMessage1;

extern bool useMessage2;

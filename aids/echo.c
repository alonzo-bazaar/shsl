#include <stdio.h>
#include "util.h"

int main(int argc, char** argv) {
    progname = argv[0];
    SHIFT(argc, argv);

    bool no_trail = false; // should we skip the trailing newline?
    FILE* out = NULL;      // where to echo shit to

    while(argc && argv[0][0] == '-') {
        switch(argv[0][1]) {
            case 'e': // standard Error
                if(out) warn("reassigning output stream, ignoring reassignment");
                else out = stderr;
                SHIFT(argc, argv);
                break;
            case 's': // Standard out
            case 'o': // standard Out
                if(out) warn("reassigning output stream, ignoring reassignment"); 
                else out = stdout;
                    
                SHIFT(argc, argv);
                break;
            case 'n':
                no_trail=true;
                SHIFT(argc, argv);
                break;
            case '-':
                SHIFT(argc, argv);
                goto done_with_flags;
            default:
                warn("ignored flag %s", argv[0]);
                SHIFT(argc, argv);
                continue;
        }
    }
 done_with_flags:
    if(!out) out = stdout;

    for(int i = 0; i<argc; ++i) {
        fputs(argv[i], out);
        if(i != (argc-1))
            fputs(SEPARATOR, out);
    }

    if(!no_trail)
        fputs(NEWLINE, out);

    return 0;
}

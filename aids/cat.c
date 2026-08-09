#include<stdio.h>
#include "util.h"
#define BUFSIZE 4096

int main(int argc, char** argv) {
    progname = argv[0];

    SHIFT(argc, argv);

    FILE* in = NULL;
    FILE* out = NULL;

    // determine which input and output to use
    while(argc) {
        if(argv[0][0] == '-') {
            switch(argv[0][1]) {
                case '\0': // flag was just -
                case 's':  // flag was -s
                    if(in) warn("reassigning input stream, ignoring reassignment"); 
                    else in = stdin;
                    SHIFT(argc, argv);
                    break;

                case 'e':
                    if(out) warn("reassigning input stream, ignoring reassignment"); 
                    else out = stdout;
                    SHIFT(argc, argv);
                    break;

                default:
                    warn("ignoring flag flag %s", argv[0]);
                    SHIFT(argc, argv);
                    continue;
            }
        }
        else {
            if(in) warn("reassigning input stream, ignoring reassignment"); 
            else {
                in = fopen(argv[0], "r");
                if(!in) die("could not open input file %s", argv[0]);
            }
        }
    }

    // set default values to in and out if none were set
    if(!in) in = stdin;
    if(!out) out = stdout;

    // now do the cat thing
    char buf[BUFSIZE];
    size_t n_read;
    while((n_read = fread(buf, sizeof(char), BUFSIZE, in)))
        if(!fwrite(buf, sizeof(char), n_read, out)) die("failed to write data");

    if(ferror(in))
        die("error while reading");

    return 0;
}

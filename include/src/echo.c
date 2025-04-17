#include "../header/utils.h"



void echo_main(int argc, char **argv) {
    int n_flag = 0;
    int e_flag = 0;
    int E_flag = 0;
    int suppress_newline = 0;
    int start = 1;

    // Parse command line flags
    while (start < argc && argv[start][0] == '-') {
        char *flag = argv[start] + 1;  // Skip '-'
        if (*flag == '\0') break;      // Handle lone '-' argument
        
        while (*flag) {
            switch (*flag) {
                case 'n': n_flag = 1; break;
                case 'e': 
                    e_flag = 1;
                    E_flag = 0;  // -e takes precedence over -E
                    break;
                case 'E':
                    E_flag = 1;
                    e_flag = 0;  // -E takes precedence over -e
                    break;
            }
            flag++;
        }
        start++;
    }

    int process_escapes = e_flag && !E_flag;

    // Process arguments
    for (int i = start; i < argc && !suppress_newline; i++) {
        char *arg = argv[i];
        while (*arg && !suppress_newline) {
            if (process_escapes && *arg == '\\') {
                arg++;  // Skip backslash
                
                if (*arg == '\0') {
                    putchar('\\');
                    break;
                }

                switch (*arg) {
                    case 'a':  putchar('\a'); break;
                    case 'b':  putchar('\b'); break;
                    case 'c':  suppress_newline = 1; break;
                    case 'e':  putchar('\033'); break;
                    case 'f':  putchar('\f'); break;
                    case 'n':  putchar('\n'); break;
                    case 'r':  putchar('\r'); break;
                    case 't':  putchar('\t'); break;
                    case 'v':  putchar('\v'); break;
                    case '\\': putchar('\\'); break;
                    case '0':  // Octal escape
                    {
                        int val = 0;
                        int digits = 0;
                        arg++;  // Skip '0'
                        
                        while (digits < 3 && *arg >= '0' && *arg <= '7') {
                            val = val * 8 + (*arg - '0');
                            arg++;
                            digits++;
                        }
                        putchar(val);
                        arg--;  // Compensate for final increment
                        break;
                    }
                    default:
                        putchar('\\');
                        putchar(*arg);
                        break;
                }
                arg++;
            } else {
                putchar(*arg++);
            }
        }

        // Add space between arguments unless suppressed
        if (i < argc - 1 && !suppress_newline) {
            putchar(' ');
        }
    }

    // Add final newline unless suppressed
    if (!n_flag && !suppress_newline) {
        putchar('\n');
    }
}

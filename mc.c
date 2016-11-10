/*
    MOUSE - A Language for Microcomputers (compiler)
    as described by Peter Grogono in July 1979 BYTE Magazine

    12/07/2001 - Ready for SourceForge
    12/12/2001 - another test
    12/12/2001 - This is a test comment.
*/
#include <stdio.h>

enum tagtype { MACRO, PARAM, LOOP };
struct frame {
    enum tagtype tag;
    int pos, off;
};

FILE *infile;
char prog[5000];
int definitions[26];
int nprocparms[26];
int calstack[20], data[260], cal, chpos, level, offset, parnum, parbal, temp;
struct frame stack[20];
int nparms, lineno = 1;
char procname;
char ch;

#define num(ch) (ch - 'A')
#define val(ch) (ch - '0')
#define nextchar() (ch = prog[chpos++])

void load() {
    char this, last;
    int charnum;
    for (charnum = 0; charnum < 26; charnum++)
    {
       definitions[charnum] = 0;
       nprocparms[charnum] = 0;
    }
    charnum = 0;
    this = ' ';
    do {
       last = this;
       this = fgetc(infile);
       if (this == '\'') {
          do {
             this = fgetc(infile);
          } while (this != '\n');
       }
       else {
          prog[charnum] = this;
          if (this >= 'A' && this <= 'Z' && last == '$')
             definitions[num(this)] = charnum;
          charnum++;
       }
    } while (this != '$' || last != '$');
}

int main(int argc, char *argv[]) {
    int i, j;
    if (argc >= 0)
    {
       if (argc != 2) infile = stdin;
       else {
          infile = fopen(argv[1], "r");
          if (infile == NULL) {
             puts("Error: cannot load program file\n");
             return 0;
          }
       }
       printf("#line 1\n");
       printf("#include <stdio.h>\n");
       printf("int sp = 0;\n");
       printf("int stack[1024];\n");
       printf("void push(i) {stack[sp++] = i;}\n");
       printf("int pop() {return stack[--sp];}\n");
       printf("void main()\n");
       printf("{\n");
       printf("int data[26];\n");
       printf("int temp;\n");
       load();
       if (infile != stdin) fclose(infile);
       chpos = level = offset = cal = 0;
    }
    do {
       nextchar();
       switch (ch) {
       case '\n':
          lineno++;
          printf("#line %d\n", lineno);
          break;
       case ']': printf("}\n"); break;
       case ' ': case '$': break;
       case '0': case '1': case '2': case '3': case '4': case '5':
       case '6': case '7': case '8': case '9':
          temp = 0;
          while (ch >= '0' && ch <= '9') {
             temp = 10 * temp + val(ch);
             nextchar();
          }
          printf("push(%d);\n", temp);
          chpos--;
          break;
       case 'A': case 'B': case 'C': case 'D': case 'E':
       case 'F': case 'G': case 'H': case 'I': case 'J':
       case 'L': case 'M': case 'N': case 'O': case 'P':
       case 'Q': case 'R': case 'S': case 'T': case 'U':
       case 'V': case 'W': case 'X': case 'Y': case 'Z':
          printf("push(%d);\n", num(ch));
          break;
       case '?':
          printf("scanf(\"%%d\", &temp);\n");
          printf("push(temp);\n");
          break;
       case '!':
          printf("printf(\"%%d\", pop());\n");
          printf("fflush(stdout);\n");
          break;
       case '+':
          printf("push(pop() + pop());\n");
          break;
       case '-':
          printf("push(pop() - pop());\n");
          break;
       case '*':
          printf("push(pop() * pop());\n");
          break;
       case '/':
          printf("push(pop() / pop());\n");
          break;
       case '.':
          printf("push(data[pop()]);\n");
          break;
       case '=':
          printf("temp = pop();\n");
          printf("data[pop()] = temp;\n");
          break;
       case '"':
          printf("printf(\"");
          do {
             nextchar();
             if (ch == '!') printf("\\n");
             else if (ch != '\"') printf("%c", ch);
          } while (ch != '\"');
          printf("\");\n");
          break;
       case '[':
          printf("if (pop() > 0) {\n");
          break;
       case '(':
          printf("while (1) {\n");
          break;
       case '^':
          printf("if (pop() <= 0) break;\n");
          break;
       case ')':
          printf("}\n");
          break;
       case '#':
          nparms = 0;
          nextchar();
          procname = ch;
          main(-1, 0);
          printf("proc%c(", procname);
          nprocparms[procname - 'A'] = nparms;
          for (i=0; i<nparms; i++)
          {
             printf("pop()");
             if (i < nparms - 1) printf(",");
          }
          printf(");\n");
          break;
       case '@':
          printf("return;\n");
          break;
       case '%':
          nextchar();
          printf("push(parm%c);\n", ch);
          break;
       case ';':
          return 0;
       case ',': /* pop(); */ nparms++; break;
       }
    } while (ch != '$');
    printf("}\n");
    if (argc != -1)
    {
       for (i=0; i<26; i++)
       {
          if (definitions[i])
          {
             printf("int proc%c(", i + 'A');
             for (j=0; j<nprocparms[i]; j++)
             {
                printf("int parm%c", 
                   nprocparms[i] - j + 'A' - 1);
                if (j < nprocparms[i] - 1)
                   printf(",");
             }
             printf(") {\n");
             printf("int data[26];\n");
             printf("int temp;\n");
             chpos = definitions[i] + 1;
             main(-1, 0);
          }
       }
    }
    return 0;
}



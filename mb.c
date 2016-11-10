/*
    MOUSE - A Language for Microcomputers (interpreter)
    as described by Peter Grogono in July 1979 BYTE Magazine
*/
#include <stdio.h>
#include <string.h>

enum tagtype { MACRO, PARAM, LOOP };
struct frame {
    enum tagtype tag;
    int pos, off;
};

FILE *infile;
char prog[5000];
int definitions[26];
int calstack[256], data[256], cal, chpos, level, offset, parnum, parbal, temp;
struct frame stack[256];
char ch;
int end;

#define num(ch) (ch - 'A')
#define val(ch) (ch - '0')
#define nextchar() (ch = prog[chpos++])

void dumpline()
{
   int p = chpos, l = 0, a = 0, i;
   char buf[256];
   while (p >= 0 && prog[p] != '\n' && prog[p] != '\r') p--;
   p++;
   printf("\n###data ");
   for (i=0; i<13; i++) printf("%c=%d ",i+'A',data[i + offset]);
   printf("\n        ");
   for (; i<26; i++) printf("%c=%d ",i+'A',data[i + offset]);
   printf("\n###stack ");
   if (cal > 0)
   {
      for (i=0; i<cal; i++) printf("%d ", calstack[i]);
   }
   else printf("<empty>");
   printf("\n###");
   do {
      printf("%c", prog[p]);
      if (p == chpos) a = l;
      p++; l++;
   } while (prog[p] != '\n' && prog[p] != '\r' && p < end);
   printf("\n###");
   for (i=0; i<l; i++) if (i == a) printf("^"); else printf(" ");
   printf("?");
   fgets(buf, 256, stdin);
}

void pushcal(int datum) {
   calstack[cal++] = datum;
}
int popcal() {
   return calstack[--cal];
}

void push(enum tagtype tagval) {
    stack[level].tag = tagval;
    stack[level].pos = chpos;
    stack[level++].off = offset;
}

void pop() {
    chpos = stack[--level].pos;
    offset = stack[level].off;
}

void skip(char lch, char rch) {
    int cnt = 1;
    do {
       nextchar();
       if (ch == lch) cnt++;
       else if (ch == rch) cnt--;
    } while (cnt != 0);
}

void load() {
    char this, last;
    int charnum;
    for (charnum = 0; charnum < 26; charnum++)
       definitions[charnum] = 0;
    charnum = 0;
    this = ' ';
    do {
       last = this;
       this = fgetc(infile);
       if (this == '\'') {
          do {
             this = fgetc(infile);
          } while (this != '\n');
          prog[charnum++] = this;
       }
       else {
          prog[charnum] = this;
          if (this >= 'A' && this <= 'Z' && last == '$')
          {
             definitions[num(this)] = charnum + 1;
             printf("defined $%c\n", this);
          }
          charnum++;
       }
    } while (this != '$' || last != '$');
    end = charnum;
}

int main(int argc, char *argv[]) {
    if (argc < 2) infile = stdin;
    else {
       infile = fopen(argv[1], "r");
       if (infile == NULL) {
          puts("Error: cannot load program file\n");
          return 0;
       }
    }
    load();
    if (infile != stdin) fclose(infile);
    chpos = level = offset = cal = 0;
    do {
       if (!strchr("\n\t\r ", ch)) dumpline();
       nextchar();
       switch (ch) {
       case ' ': case ']': case '$': break;
       case '0': case '1': case '2': case '3': case '4': case '5':
       case '6': case '7': case '8': case '9':
          temp = 0;
          while (ch >= '0' && ch <= '9') {
             temp = 10 * temp + val(ch);
             nextchar();
          }
          pushcal(temp);
          chpos--;
          break;
       case 'A': case 'B': case 'C': case 'D': case 'E':
       case 'F': case 'G': case 'H': case 'I': case 'J':
       case 'L': case 'M': case 'N': case 'O': case 'P':
       case 'Q': case 'R': case 'S': case 'T': case 'U':
       case 'V': case 'W': case 'X': case 'Y': case 'Z':
          pushcal(num(ch) + offset);
          break;
       case '?':
          scanf("%d", &temp);
          pushcal(temp);
          break;
       case '!': printf("%d", popcal()); fflush(stdout); break;
       case '+': pushcal(popcal() + popcal()); break;
       case '-': pushcal(popcal() - popcal()); break;
       case '*': pushcal(popcal() * popcal()); break;
       case '/': pushcal(popcal() / popcal()); break;
       case '.':
          pushcal(data[popcal()]);
          break;
       case '=':
          temp = popcal();
          data[popcal()] = temp;
          break;
       case '"':
          do {
             nextchar();
             if (ch == '!') putchar('\n');
             else if (ch != '"') putchar(ch);
          } while (ch != '"');
          break;
       case '[':
          if (popcal() <= 0) skip('[', ']');
          break;
       case '(': push(LOOP); break;
       case '^':
          if (popcal() <= 0) {
             pop();
             skip('(', ')');
          }
          break;
       case ')': chpos = stack[level - 1].pos; break;
       case '#':
          nextchar();
          if (definitions[num(ch)] > 0) {
             push(MACRO);
             chpos = definitions[num(ch)];
             offset += 26;
          }
          else skip('#', ';');
          break;
       case '@': case '}': pop(); skip('#', ';'); break;
       case '%':
          nextchar();
          parnum = num(ch);
          push(PARAM);
          parbal = 1;
          temp = level - 1;
          do {
             temp--;
             switch (stack[temp].tag) {
             case MACRO: parbal--; break;
             case PARAM: parbal--; break;
             case LOOP: break;
             }
          } while (parbal != 0);
          chpos = stack[temp].pos;
          offset = stack[temp].off;
          do {
       if (!strchr("\n\t\r ", ch)) dumpline();
             nextchar();
             if (ch == '#') {
                skip('#', ';');
       if (!strchr("\n\t\r ", ch)) dumpline();
                nextchar();
             }
             if (ch == ',') parnum--;
          } while (parnum >= 0 && ch != ';');
          if (ch == ';') pop();
          break;
       case ',': case ';': pop(); break;
       }
    } while (ch != '$');
    return 0;
}


#line 1
#include <stdio.h>
int sp = 0;
int stack[1024];
void push(i) {stack[sp++] = i;}
int pop() {return stack[--sp];}
void main()
{
int data[26];
int temp;
printf("\n");
#line 2
printf("     ___    \n");
#line 3
printf("    /...\   \n");
#line 4
printf("   /.=.=.\  \n");
#line 5
printf("   |_____|  \n");
#line 6
printf("   _/ | \_  \n");
#line 7
printf("            \n");
#line 8
printf("Lunar Lander\n");
#line 9
printf("\n");
#line 10
#line 11
push(5);
push(1000);
temp = pop();
data[pop()] = temp;
push(0);
push(100);
temp = pop();
data[pop()] = temp;
push(17);
push(100);
temp = pop();
data[pop()] = temp;
push(8);
push(0);
temp = pop();
data[pop()] = temp;
push(9);
push(0);
temp = pop();
data[pop()] = temp;
push(6);
push(3);
push(0);
push(pop() - pop());
temp = pop();
data[pop()] = temp;
#line 12
while (1) {
#line 13
printf("\n");
#line 14
printf("### Alt=");
push(0);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf(" Range=");
push(17);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf(" Fuel=");
push(5);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
#line 15
printf(" HV=");
push(8);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf(" VV=");
push(9);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf(" Grav=");
push(6);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf(" ###\n");
#line 16
#line 17
push(5);
push(data[pop()]);
if (pop() > 0) {
#line 18
printf("Horizontal Thrust? ");
#line 19
push(7);
scanf("11905", &temp);
push(temp);
temp = pop();
data[pop()] = temp;
#line 20
printf("Vertical Thrust? ");
#line 21
push(21);
scanf("11905", &temp);
push(temp);
temp = pop();
data[pop()] = temp;
#line 22
}
#line 23
push(5);
push(data[pop()]);
push(0);
push(pop() - pop());
if (pop() > 0) {
#line 24
printf("Out of fuel.\n");
push(7);
push(0);
temp = pop();
data[pop()] = temp;
#line 25
push(21);
push(0);
temp = pop();
data[pop()] = temp;
#line 26
}
#line 27
push(8);
push(8);
push(data[pop()]);
push(7);
push(data[pop()]);
push(pop() + pop());
temp = pop();
data[pop()] = temp;
push(9);
push(9);
push(data[pop()]);
push(6);
push(data[pop()]);
push(pop() + pop());
push(21);
push(data[pop()]);
push(pop() + pop());
temp = pop();
data[pop()] = temp;
push(0);
push(0);
push(data[pop()]);
push(9);
push(data[pop()]);
push(pop() + pop());
temp = pop();
data[pop()] = temp;
push(17);
push(17);
push(data[pop()]);
push(8);
push(data[pop()]);
push(pop() + pop());
temp = pop();
data[pop()] = temp;
push(7);
push(data[pop()]);
push(0);
push(pop() - pop());
if (pop() > 0) {
#line 28
push(7);
push(7);
push(data[pop()]);
push(0);
push(pop() - pop());
temp = pop();
data[pop()] = temp;
}
#line 29
push(21);
push(data[pop()]);
push(0);
push(pop() - pop());
if (pop() > 0) {
#line 30
push(21);
push(21);
push(data[pop()]);
push(0);
push(pop() - pop());
temp = pop();
data[pop()] = temp;
}
#line 31
push(5);
push(7);
push(data[pop()]);
push(21);
push(data[pop()]);
push(5);
push(data[pop()]);
push(pop() - pop());
push(pop() - pop());
temp = pop();
data[pop()] = temp;
push(0);
push(data[pop()]);
push(0);
push(pop() - pop());
if (pop() > 0) {
#line 32
printf("\n\n### You landed with\n");
#line 33
printf("a horizontal velocity of ");
push(8);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf("\n");
#line 34
printf("a vertical velocity of ");
push(9);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf("\n");
#line 35
push(17);
push(data[pop()]);
printf("%d", pop());
fflush(stdout);
printf(" meters from the landing pad.\n");
#line 36
push(0);
if (pop() <= 0) break;
#line 37
}
#line 38
}
#line 39
}

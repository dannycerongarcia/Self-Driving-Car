#ifndef FOO_H_
#define FOO_H_

int init(char[6],char[7]);
int initHelper(struct motor *, char[7]);
int foward(struct motor *,int,char[7]);
int reverse(struct motor *,int,char[7]);
int stop(struct motor *, char[7]);
int run(int);

#endif // FOO_H_
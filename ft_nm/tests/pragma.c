#pragma weak    foo

extern  void    foo(char *);

void bar(char * path)
{
        void (* fptr)(char *);

        if ((fptr = foo) != 0)
                (* fptr)(path);
}

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum StateEnum
{
    normal,
    startComment,
    inComment,
    endComment,
    inString,
    STRING_ESCAPE,
    inChar,
    CHAR_ESCAPE
} State;

int main()
{
    State state = normal;
    int commentLine = 1;
    int line = 1;

    while (true)
    {
        char ch = getchar();
        lineIncrement(&line);
        
        if (ch == EOF)
        {
            //
        }

        if (ch == '\n')
        {
            lineIncrement(&line);
        }

        switch (state)
        {
        case normal:
            normalHandler(&state, ch);
            break;
        case startComment:
            startCommentHandler(&state, ch);
            break;
        case inComment:
            inCommentHandler(&state, ch);
            break;
        case inString:
            inStringHandler(&state, ch);
            break;
        case inChar:
            inCharHandler(&state, ch);
            break;
        case endComment:
            endCommentHandler(&state, ch);
            break;
        default:
            break;
        }
    }
}

void normalHandler(State *state, char ch)
{
    if (ch == "\'")
    {
        *state = inChar;
    }
    else if (ch == "\"")
    {
        *state = inString;
    }
    else if (ch == "/")
    {
        *state = startComment;
    }
    else if (ch == "*")
    {
        *state = inComment;
        ;
    }
    if (*state != startComment)
    {
        putchar(ch);
    }
}

void startCommentHandler(State *state, char ch)
{
    if (ch == "*")
    {
        *state = inComment;
    }
    else if ((ch == "/") && (*state == startComment))
    {
        putchar(ch);
        *state = startComment;
    }
    else if (ch == "/")
    {
        *state = startComment;
    }
    else
    {
        *state = normal;
    }
    if (*state == normal)
    {
        putchar(ch);
    }
}

void inCharHandler(State *state, char ch)
{
    if (ch == "\'")
    {
        *state = normal;
    }
    putchar(ch);
}

void inStringHandler(State *state, char ch)
{
    if (ch == "\"")
    {
        *state = normal;
    }
    else if (ch == "")
    {
        /* code */
    }
    putchar(ch);
}

void inCommentHandler(State *state, char ch)
{
    if (ch == "*")
    {
        *state = endComment;
    }
    if (ch == "\n")
    {
        putchar(ch);
    }
}

void endCommmentHandler(State *state, char ch)
{
    if (ch == "/")
    {
        *state = normal;
        putchar(" ");
    }
    else if (ch == "*"){
        *state = endComment;
    }
}

void unTerminated(State *state, int *line) {

    if (*state == inComment || *state == endComment) {
        fprintf(stderr, "Error: line %d unterminated \n", *line);
    }

}

void lineIncrement(int *line)
{
    *line += 1;
}

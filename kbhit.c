#if defined WINDOWS
#include <conio.h>
#endif

#if defined LINUX || DARWIN || BSD
#include "kbhit.h"
#include <termios.h>
/* for read() */
#include <unistd.h>   

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard(void)
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard(void)
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit(void)
{
unsigned char ch;
int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1) 
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch(void)
{
char ch;

    if(peek_character != -1) 
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
#endif
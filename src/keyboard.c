#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/keyboard.h"
#include <stdio.h>

static struct termios oldt, newt;

void init_keyboard() {
    tcgetattr(STDIN_FILENO, &oldt); // salva as configurações do terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // desabilita o buffer de entrada e o eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void close_keyboard() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restaura as configurações originais
}

int kbhit() {
    struct termios oldt, newt;
    int oldf;
    char ch;
    ssize_t nread;
  
    // Salva as configurações atuais do terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // Desabilita o modo canônico e o eco
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  
    // Salva as flags atuais do descritor de arquivo
    oldf = fcntl(STDIN_FILENO, F_GETFL);
    // Configura o descritor para não bloqueante
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  
    // Tenta ler um byte
    nread = read(STDIN_FILENO, &ch, 1);
  
    // Restaura as configurações originais
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
  
    if(nread == 1) {
        // Caracter foi lido, coloca-o de volta no buffer
        ungetc(ch, stdin);
        return 1;
    }
  
    return 0;
}

int readch() {
    return getchar();
}
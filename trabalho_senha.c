#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
  #include <conio.h>
#else
  #include <termios.h>
  #include <unistd.h>
#endif

#define MAX_SENHA 128

int ler_senha_arquivo(char *senhaCorreta, size_t tam) {
    FILE *f = fopen("senha.txt", "r");
    if (!f) return -1;
    if (!fgets(senhaCorreta, (int)tam, f)) { fclose(f); return -2; }
    size_t len = strlen(senhaCorreta);
    while (len > 0 && (senhaCorreta[len-1]=='\n'||senhaCorreta[len-1]=='\r')) {
        senhaCorreta[--len]='\0';
    }
    fclose(f);
    return 0;
}

int ler_senha_mascarada(char *dest, size_t maxLen) {
    size_t pos = 0; int c=0;
#ifdef _WIN32
    while (1) {
        c = _getch();
        if (c=='\r'||c=='\n'){ putchar('\n'); break; }
        else if (c==8){ if(pos>0){ pos--; putchar('\b'); putchar(' '); putchar('\b'); } }
        else if (c==3) return -1;
        else { if (pos+1<maxLen){ dest[pos++]=(char)c; putchar('*'); } }
    }
#else
    struct termios oldt,newt;
    if (tcgetattr(STDIN_FILENO,&oldt)!=0) return -1;
    newt=oldt; newt.c_lflag&=~(ICANON|ECHO);
    newt.c_cc[VMIN]=1; newt.c_cc[VTIME]=0;
    if(tcsetattr(STDIN_FILENO,TCSANOW,&newt)!=0) return -1;
    while (1){
        char ch; ssize_t r=read(STDIN_FILENO,&ch,1);
        if(r<=0){ tcsetattr(STDIN_FILENO,TCSANOW,&oldt); return -1; }
        c=(unsigned char)ch;
        if(c=='\r'||c=='\n'){ putchar('\n'); break; }
        else if(c==127||c==8){ if(pos>0){ pos--; putchar('\b'); putchar(' '); putchar('\b'); } }
        else if(c==3){ tcsetattr(STDIN_FILENO,TCSANOW,&oldt); return -1; }
        else{ if(pos+1<maxLen){ dest[pos++]=(char)c; putchar('*'); } }
    }
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
#endif
    dest[pos]='\0'; return 0;
}

int main(void) {
    char senhaCorreta[MAX_SENHA];
    int ret=ler_senha_arquivo(senhaCorreta,sizeof(senhaCorreta));
    if(ret==-1){ fprintf(stderr,"Erro: arquivo 'senha.txt' nao encontrado.\n"); return 1; }
    else if(ret==-2){ fprintf(stderr,"Erro: nao foi possivel ler a senha.\n"); return 1; }

    printf("Digite a senha: "); fflush(stdout);
    char entrada[MAX_SENHA];
    if(ler_senha_mascarada(entrada,sizeof(entrada))!=0){
        fprintf(stderr,"\nEntrada interrompida.\n"); return 1;
    }
    if(strcmp(entrada,senhaCorreta)==0) printf("Senha correta! Acesso permitido.\n");
    else printf("Senha incorreta! Acesso negado.\n");
    return 0;
}

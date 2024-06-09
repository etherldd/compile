#include "sem.h"

Node* syntax_tree=NULL;
extern int yyparse();
extern void yyrestart(FILE*);

char* copy(const char* src) {
    if (src == NULL) return NULL;
    size_t length = strlen(src) + 1;
    char* p = malloc(length); 
    if (p == NULL)  return NULL;
    strcpy(p, src);
    return p;
}

Node* CreateTerminalNode(int terminal,char* type,int line,char* val){
    Node* node=(Node*)malloc(sizeof(Node));
    memset(node,0,sizeof(Node));
    node->T=terminal;
    node->type=type;
    node->line=line;
    node->val=copy(val);
    return node;
}

Node* CreateUnterminalNode(char* type,int line,Node* child){
    Node* node=(Node*)malloc(sizeof(Node));
    memset(node,0,sizeof(Node));
    node->T=0;
    node->type=type;
    node->line=line;
    node->child=child;
    return node;
}


void AddChild(Node* node,Node* child){
    if(child == NULL)
        return;
    if(node->child == NULL)
        node->child=child;
    else{
        for(Node* i=node->child; i; i=i->next)
            if(i->next == NULL){
                i->next=child;
                break;
            }
    }
}


int main(int argc, char **argv)
{
    if (argc <= 1) return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    initSymTab();
    analyze(syntax_tree);
    return 0;
}

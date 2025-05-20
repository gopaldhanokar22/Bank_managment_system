#include "bank.h"

void save_accounts_to_file(Node* head)
{
    FILE* file=fopen(FILENAME,"wb");
    if(!file)
	    return;

    Node* current=head;
    while(current) 
    {
        fwrite(&current->account,sizeof(Account),1,file);
        current=current->next;
    }
    fclose(file);
}

void load_accounts_from_file(Node** head)
{
    FILE* file=fopen(FILENAME,"rb");
    if (!file) 
	    return;

    Account account;
    while(fread(&account,sizeof(Account),1,file))
    {
        insert_node(head,&account);
    }
    fclose(file);
}

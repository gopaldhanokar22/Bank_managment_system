#include "bank.h"

void search_account(Node* head)
{
    int choice;
    printf("\nSearch by:\n1. Account Number\n2. Account Name\n3. Contact Number\nEnter choice: ");
    __fpurge(stdin);
    scanf("%d",&choice);
    
    switch(choice){
        case 1:
	{
            int account_number;
            printf("Enter account number: ");
	    __fpurge(stdin);
            scanf("%d",&account_number);
            Node* current = head;
            while(current)
	    {
                if(current->account.account_number == account_number)
	       	{
                    printf("\nAccount Found:\nAccount Number: %d\nAccount Name: %s\nBalance: %.2lf\nContact: %s\n",
                           current->account.account_number, current->account.account_name,
                           current->account.balance, current->account.contact_number);
                    return;
                }
                current=current->next;
            }
            printf("Account not found.\n");
            break;
        }
        case 2:
	{
            char name[100];
            printf("Enter account name: ");
	    __fpurge(stdin);
            scanf("%[^\n]",name);
            int found=0;
            Node* current=head;
            while(current)
	    {
                if(strstr(current->account.account_name, name))
		{
                    printf("\nAccount Number: %d\nAccount Name: %s\nBalance: %.2lf\nContact: %s\n",
                           current->account.account_number, current->account.account_name,
                           current->account.balance, current->account.contact_number);
                    found=1;
                }
                current=current->next;
            }
            if(!found)printf("No accounts found.\n");
            break;
        }
        case 3: 
	{
            char contact[15];
            printf("Enter contact number: ");
	    __fpurge(stdin);
            scanf("%[^\n]",contact);
            int found=0;
            Node* current=head;
            while(current)
	    {
                if(strcmp(current->account.contact_number,contact)==0)
	       	{
                    printf("\nAccount Number: %d\nAccount Name: %s\nBalance: %.2lf\nContact: %s\n",
                           current->account.account_number, current->account.account_name,
                           current->account.balance, current->account.contact_number);
                    found=1;
                }
                current=current->next;
            }
            if(!found)
		    printf("No accounts found.\n");
            break;
        }
        default:printf("Invalid choice.\n");
    }
}

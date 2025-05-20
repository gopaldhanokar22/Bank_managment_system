#include "bank.h"

void create_account(Node** head)
{
    Account new_account;
    new_account.transaction_count = 0;
    
    printf("Enter account number: ");
    __fpurge(stdin);
    scanf("%d",&new_account.account_number);
    
    if(is_account_exists(*head,new_account.account_number))
    {
        printf("Account already exists.\n");
        return;
    }
    
    printf("Enter account name: ");
    __fpurge(stdin);
    scanf("%[^\n]",new_account.account_name);
    
    printf("Enter initial deposit: ");
    __fpurge(stdin);
    scanf("%lf",&new_account.balance);
    
    printf("Enter contact number: ");
    __fpurge(stdin);
    scanf("%[^\n]",new_account.contact_number);
    
    add_transaction(&new_account,DEPOSIT,new_account.balance,"Initial deposit");
    insert_node(head,&new_account);
    printf("Account created successfully!\n");
}

void display_all_accounts(Node* head)
{
    if(!head)
    {
        printf("No accounts found.\n");
        return;
    }
    
    printf("\nAll Accounts:\n");
    printf("----------------------------------------------------------------------------\n");
    printf("| %-15s | %-20s | %-10s | %-15s |\n", "Account Number", "Account Name", "Balance", "Contact Number");
    printf("----------------------------------------------------------------------------\n");
    
    Node* current=head;
    while(current)
    {
        printf("| %-15d | %-20s | %-10.2lf | %-15s |\n", 
               current->account.account_number, 
               current->account.account_name, 
               current->account.balance,
               current->account.contact_number);
        current = current->next;
    }
    printf("-----------------------------------------------------------------\n");
}

void balance_enquiry(Node* head)
{
    int account_number;
    printf("Enter account number: ");
    __fpurge(stdin);
    scanf("%d", &account_number);
    
    Node* current=head;
    while(current)
    {
        if(current->account.account_number==account_number)
	{
            printf("\nAccount Number: %d\n",current->account.account_number);
            printf("Account Name: %s\n",current->account.account_name);
            printf("Current Balance: %.2lf\n",current->account.balance);
            printf("Contact Number: %s\n",current->account.contact_number);
            return;
        }
        current=current->next;
    }
    printf("Account not found.\n");
}

int is_account_exists(Node* head,int account_number)
{
    Node* current=head;
    while(current)
    {
        if(current->account.account_number==account_number) 
		return 1;
        current=current->next;
    }
    return 0;
}

Node* create_new_node(const Account* account) {
    Node* new_node=malloc(sizeof(Node));
    if(!new_node) 
	    exit(EXIT_FAILURE);
    new_node->account=*account;
    new_node->next=NULL;
    return new_node;
}

void insert_node(Node** head,const Account* account) {
    Node* new_node=create_new_node(account);
    if(!*head) 
    {
        *head=new_node;
    }
    else
    {
        Node* current=*head;
	while(current->next)
		current=current->next;
        current->next=new_node;
    }
}

void free_list(Node* head)
{
    while(head)
    {
        Node* temp=head;
        head=head->next;
        free(temp);
    }
}

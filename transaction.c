#include "bank.h"

void deposit(Node* head)
{
    int account_number;
    double amount;
    printf("Enter account number: ");
    __fpurge(stdin);
    scanf("%d",&account_number);
    
    Node* current = head;
    while(current)
    {
        if(current->account.account_number==account_number)
	{
            printf("Enter amount: ");
	    __fpurge(stdin);
            scanf("%lf",&amount);
            if(amount<=0)
	    {
                printf("Invalid amount.\n");
                return;
            }
            current->account.balance+=amount;
            add_transaction(&current->account, DEPOSIT, amount, "Cash deposit");
            printf("Deposit successful. New balance: %.2lf\n", current->account.balance);
            return;
        }
        current=current->next;
    }
    printf("Account not found.\n");
}

void withdraw(Node* head) 
{
    int account_number;
    double amount;
    printf("Enter account number: ");
    __fpurge(stdin);
    scanf("%d", &account_number);
    
    Node* current = head;
    while(current)
    {
        if(current->account.account_number==account_number)
	{
            printf("Enter amount: ");
	    __fpurge(stdin);
            scanf("%lf",&amount);
            if(amount<=0)
	    {
                printf("Invalid amount.\n");
                return;
            }
            if(amount>current->account.balance)
	    {
                printf("Insufficient balance.\n");
                return;
            }
            current->account.balance-=amount;
            add_transaction(&current->account, WITHDRAWAL, amount, "Cash withdrawal");
            printf("Withdrawal successful. New balance: %.2lf\n", current->account.balance);
            return;
        }
        current=current->next;
    }
    printf("Account not found.\n");
}

void transfer(Node* head) {
    int from_account, to_account;
    double amount;
    printf("Enter your account number: ");
    __fpurge(stdin);
    scanf("%d",&from_account);
    printf("Enter recipient account number: ");
    __fpurge(stdin);
    scanf("%d",&to_account);
    
    if (from_account==to_account) {
        printf("Cannot transfer to same account.\n");
        return;
    }
    
    Node* from_node=NULL;
    Node* to_node=NULL;
    Node* current=head;
    
    while(current)
    {
        if(current->account.account_number==from_account) 
		from_node=current;
        if(current->account.account_number == to_account) 
		to_node=current;
        current = current->next;
    }
    
    if(!from_node)
    {
        printf("Your account not found.\n");
        return;
    }
    if(!to_node)
    {
        printf("Recipient account not found.\n");
        return;
    }
    
    printf("Enter amount: ");
    __fpurge(stdin);
    scanf("%lf", &amount);
    
    if(amount <= 0)
    {
        printf("Invalid amount.\n");
        return;
    }
    if(amount > from_node->account.balance)
    {
        printf("Insufficient balance.\n");
        return;
    }
    
    from_node->account.balance -= amount;
    to_node->account.balance += amount;
    
    char description[100];
    snprintf(description, sizeof(description), "Transfer to %d", to_account);
    add_transaction(&from_node->account, TRANSFER_OUT, amount, description);
    
    snprintf(description, sizeof(description), "Transfer from %d", from_account);
    add_transaction(&to_node->account, TRANSFER_IN, amount, description);
    
    printf("Transfer successful. Your new balance: %.2lf\n", from_node->account.balance);
}

void display_transaction_history(Node* head)
{
    int account_number;
    printf("Enter account number: ");
    __fpurge(stdin);
    scanf("%d",&account_number);
    
    Node* current=head;
    while(current) 
    {
        if(current->account.account_number==account_number)
	{
            printf("\nTransaction History for Account: %d (%s)\n", 
                   current->account.account_number, current->account.account_name);
            printf("--------------------------------------------------\n");
            
            int start=(current->account.transaction_count>5)? 
                        current->account.transaction_count-5:0;
            
            for(int i=start; i<current->account.transaction_count;i++) 
	    {
                display_transaction(&current->account.transactions[i]);
            }
            
            printf("Current Balance: %.2lf\n", current->account.balance);
            printf("--------------------------------------------------\n");
            return;
        }
        current=current->next;
    }
    printf("Account not found.\n");
}

void add_transaction(Account* account, TransactionType type, double amount, const char* description) {
    if(account->transaction_count >= MAX_TRANSACTIONS) {
        for(int i=0; i<MAX_TRANSACTIONS-1;i++)
       	{
            account->transactions[i]=account->transactions[i+1];
        }
        account->transaction_count=MAX_TRANSACTIONS-1;
    }
    
    Transaction new_transaction;
    new_transaction.transaction_id=(uint32_t)time(NULL)+account->transaction_count;
    new_transaction.timestamp=time(NULL);
    new_transaction.type=type;
    new_transaction.amount=amount;
    strncpy(new_transaction.description, description, sizeof(new_transaction.description)-1);
    new_transaction.description[sizeof(new_transaction.description)-1]='\0';
    
    account->transactions[account->transaction_count++]=new_transaction;
}

void display_transaction(const Transaction* transaction)
{
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&transaction->timestamp));
    
    const char* type_str;
    switch(transaction->type) {
        case DEPOSIT: type_str = "DEPOSIT"; 
		      break;
        case WITHDRAWAL: type_str = "WITHDRAWAL"; 
			 break;
        case TRANSFER_IN: type_str = "TRANSFER+"; 
			  break;
        case TRANSFER_OUT: type_str = "TRANSFER-"; 
			   break;
        default: type_str = "UNKNOWN"; 
		 break;
    }
    
    printf("%s | %10u | %-10s | %10.2lf | %s\n", 
           time_str, transaction->transaction_id, type_str,
           transaction->amount, transaction->description);
}

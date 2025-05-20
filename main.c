#include "bank.h"

void display_menu()
{
    printf("\n------------------MENU--------------------------\n");
    printf("c/C: Create account.\n");
    printf("h/H: Transaction history (last 5 transactions).\n");
    printf("w/W: Withdraw amount.\n");
    printf("d/D: Deposit amount.\n");
    printf("b/B: Balance enquiry.\n");
    printf("t/T: Transfer money.\n");
    printf("e/E: Display all accounts details.\n");
    printf("s/S: Save the accounts info in file.\n");
    printf("f/F: Finding/searching for specific account.\n");
    printf("q/Q: Quit from app.\n");
    printf("-------------------------------------------------\n");
}

int main()
{
    Node* head=NULL;
    char choice;

    load_accounts_from_file(&head);

    do
    {
        display_menu();
        printf("Enter your choice: ");
	__fpurge(stdin);
        scanf("%c", &choice);

        switch(choice)
	{
            case 'c': 
	    case 'C': create_account(&head);
				break;
            case 'h':
	    case 'H': display_transaction_history(head);
				break;
            case 'w':
	    case 'W': withdraw(head);
				break;
            case 'd':
	    case 'D': deposit(head);
				break;
            case 'b':
	    case 'B': balance_enquiry(head);
				break;
            case 't':
	    case 'T': transfer(head);
				break;
            case 'e':
	    case 'E': display_all_accounts(head);
				break;
            case 's':
	    case 'S': save_accounts_to_file(head);
				break;
            case 'f':
	    case 'F': search_account(head);
				break;
            case 'q':
	    case 'Q': save_accounts_to_file(head);
				break;
            default: printf("Invalid choice.\n");
        }
    }while(choice!='q' && choice!='Q');

    free_list(head);
    return 0;
}

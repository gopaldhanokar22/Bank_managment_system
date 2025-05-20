#ifndef BANK_H
#define BANK_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<time.h>
#include<stdio_ext.h>

#define MAX_ACCOUNTS 1000
#define MAX_TRANSACTIONS 100
#define FILENAME "accounts.dat"

typedef enum
{
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER_IN,
    TRANSFER_OUT
}TransactionType;

typedef struct 
{
    uint32_t transaction_id;
    time_t timestamp;
    TransactionType type;
    double amount;
    char description[100];
}Transaction;

typedef struct
{
    int account_number;
    char account_name[100];
    double balance;
    char contact_number[15];
    Transaction transactions[MAX_TRANSACTIONS];
    int transaction_count;
}Account;

typedef struct Node
{
    Account account;
    struct Node* next;
}Node;

void create_account(Node** head);
void display_all_accounts(Node* head);
void balance_enquiry(Node* head);
void save_accounts_to_file(Node* head);
void load_accounts_from_file(Node** head);
void deposit(Node* head);
void withdraw(Node* head);
void transfer(Node* head);
void display_transaction_history(Node* head);
void search_account(Node* head);
int is_account_exists(Node* head, int account_number);
void add_transaction(Account* account, TransactionType type, double amount, const char* description);
void display_transaction(const Transaction* transaction);
Node* create_new_node(const Account* account);
void insert_node(Node** head, const Account* account);
void free_list(Node* head);

#endif

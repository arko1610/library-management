#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define MAX_BOOK_NAME      50
#define MAX_AUTHOR_NAME    50
#define FILE_NAME          "LibraryManagement.bin"
#define FILE_HEADER_SIZE   sizeof(sFileHeader)

// Structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;

// File header structure
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;

// Book information structure
typedef struct
{
    unsigned int books_id;
    char bookName[MAX_BOOK_NAME];
    char authorName[MAX_AUTHOR_NAME];
    Date bookIssueDate;
} s_BooksInfo;

// Function to print a message in the center of the screen
void printMessageCenter(const char* message)
{
    int len = 0;
    int pos = 0;
    len = (78 - strlen(message)) / 2;
    printf("\t\t\t");
    for (pos = 0; pos < len; pos++)
        printf(" ");
    printf("%s", message);
}

// Function to display the program header message
void headMessage(const char* message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Library Management System Project in C        ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}

// Function to display a welcome message
void welcomeMessage()
{
    headMessage("www.shahriar book.com");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 LIBRARY                   =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}

// Function to check if a given string is a valid name
int isNameValid(const char* name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for (index = 0; index < len; ++index)
    {
        if (!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}

// Function to check leap year
int IsLeapYear(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

// Function to check if a given date is valid
int isValidDate(Date* validDate)
{
    if (validDate->yyyy > 9999 || validDate->yyyy < 1900)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    if (validDate->mm == 4 || validDate->mm == 6 || validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}

// Function to add a book to the database
void addBookInDataBase()
{
    s_BooksInfo addBookInfoInDataBase = { 0 };
    FILE* fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME, "ab+");
    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW BOOKS");
    printf("\n\n\t\t\tENTER BOOK DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tBook ID NO  = ");
    fflush(stdin);
    scanf("%u", &addBookInfoInDataBase.books_id);
    do
    {
        printf("\n\t\t\tBook Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.bookName, MAX_BOOK_NAME, stdin);
        status = isNameValid(addBookInfoInDataBase.bookName);
        if (!status)
        {
            printf("\n\t\t\tName contains invalid characters. Please enter again.");
        }
    } while (!status);

    // Rest of the code for adding book details...

    fwrite(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp);
    fclose(fp);
}

// Function to search for a book in the database
// ...

// Function to search for a book in the database
void searchBooks()
{
    char bookName[MAX_BOOK_NAME] = { 0 };
    s_BooksInfo addBookInfoInDataBase = { 0 };
    FILE* fp = NULL;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }

    headMessage("SEARCH BOOKS");
    printf("\n\n\t\t\tEnter Book Name to search: ");
    fflush(stdin);
    fgets(bookName, MAX_BOOK_NAME, stdin);

    while (fread(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if (!strcmp(addBookInfoInDataBase.bookName, bookName))
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        // Print book details
        printf("\n\t\t\tBook id = %u\n", addBookInfoInDataBase.books_id);
        printf("\t\t\tBook name = %s", addBookInfoInDataBase.bookName);
        printf("\t\t\tBook authorName = %s", addBookInfoInDataBase.authorName);
        printf("\t\t\tBook issue date(day/month/year) = (%d/%d/%d)\n",
               addBookInfoInDataBase.bookIssueDate.dd, addBookInfoInDataBase.bookIssueDate.mm,
               addBookInfoInDataBase.bookIssueDate.yyyy);
    }
    else
    {
       printf("\n\t\t\tBook id = %u\n", addBookInfoInDataBase.books_id);
        printf("\t\t\tBook name = %s", addBookInfoInDataBase.bookName);
        printf("\t\t\tBook authorName = %s", addBookInfoInDataBase.authorName);
        printf("\t\t\tBook issue date(day/month/year) = (%d/%d/%d)\n",
               addBookInfoInDataBase.bookIssueDate.dd, addBookInfoInDataBase.bookIssueDate.mm,
               addBookInfoInDataBase.bookIssueDate.yyyy);
    }

    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to the main menu.....");
    getchar();
}

// Function to view the list of books in the database
void viewBooks()
{
    s_BooksInfo addBookInfoInDataBase = { 0 };
    FILE* fp = NULL;
    unsigned int countBook = 1;
    int found = 0;

    headMessage("VIEW BOOKS DETAILS");
    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    if (fseek(fp, FILE_HEADER_SIZE, SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }

    while (fread(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\tBook Count = %u\n\n", countBook);
        printf("\t\t\tBook id = %u", addBookInfoInDataBase.books_id);
        printf("\n\t\t\tBook name = %s", addBookInfoInDataBase.bookName);
        printf("\t\t\tBook authorName = %s", addBookInfoInDataBase.authorName);
        printf("\t\t\tBook issue date(day/month/year) = (%d/%d/%d)\n\n",
               addBookInfoInDataBase.bookIssueDate.dd, addBookInfoInDataBase.bookIssueDate.mm,
               addBookInfoInDataBase.bookIssueDate.yyyy);
        found = 1;
        ++countBook;
    }

    fclose(fp);

    if (!found)
    {
        printf("\n\t\t\tNo Record\n");
    }

    printf("\n\n\t\t\tPress any key to go to the main menu.....");
    fflush(stdin);
    getchar();
}

// Function to delete a book from the database
void deleteBooks()
{
    int bookDelete = 0;
    sFileHeader fileHeaderInfo = { 0 };
    s_BooksInfo addBookInfoInDataBase = { 0 };
    FILE* fp = NULL;
    FILE* tmpFp = NULL;
    int status = 0;
    int found = 0;

    headMessage("Delete Books Details");
    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    tmpFp = fopen("tmp.bin", "wb");

    if (tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }

    fread(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo, FILE_HEADER_SIZE, 1, tmpFp);

    printf("\n\t\t\tEnter Book ID NO. for delete: ");
    scanf("%d", &bookDelete);

    while (fread(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if (addBookInfoInDataBase.books_id != bookDelete)
        {
            fwrite(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }

    if (found)
    {
        printf("\n\t\t\tRecord deleted successfully.....\n");
    }
    else
    {
        printf("\n\t\t\tRecord not found\n");
    }

    fclose(fp);
    fclose(tmpFp);

    remove(FILE_NAME);
    rename("tmp.bin", FILE_NAME);
}

// Function to update the login credentials
void updateCredential(void)
{
    sFileHeader fileHeaderInfo = { 0 };
    FILE* fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = { 0 };
    unsigned char password[MAX_SIZE_PASSWORD] = { 0 };

    headMessage("Update Credential");
    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }

    fread(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);

    if (fseek(fp, 0, SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }

    printf("\n\n\t\t\tNew Username: ");
    fflush(stdin);
    fgets(userName, MAX_SIZE_USER_NAME, stdin);

    printf("\n\n\t\t\tNew Password: ");
    fflush(stdin);
    fgets(password, MAX_SIZE_PASSWORD, stdin);

    strncpy(fileHeaderInfo.username, userName, sizeof(userName));
    strncpy(fileHeaderInfo.password, password, sizeof(password));

    fwrite(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
    fclose(fp);

    printf("\n\t\t\tYour Password has been changed successfully\n");
    printf("\n\t\t\tLogin Again:");
    fflush(stdin);
    getchar();
    exit(1);
}

// ...


// Main menu function
void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1. Add Books");
        printf("\n\t\t\t2. Search Books");
        printf("\n\t\t\t3. View Books");
        printf("\n\t\t\t4. Delete Book");
        printf("\n\t\t\t5. Update Password");
        printf("\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBookInDataBase();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            viewBooks();
            break;
        case 4:
            deleteBooks();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }
    } while (choice != 0);
}

// Login function
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = { 0 };
    unsigned char password[MAX_SIZE_PASSWORD] = { 0 };
    int attempts = 0;
    sFileHeader fileHeaderInfo = { 0 };
    FILE* fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
    fclose(fp);

    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fflush(stdin);
        fgets(userName, MAX_SIZE_USER_NAME, stdin);
        printf("\n\t\t\t\tPassword:");
        fflush(stdin);
        fgets(password, MAX_SIZE_PASSWORD, stdin);

        if ((strcmp(userName, fileHeaderInfo.username) == 0) && (strcmp(password, fileHeaderInfo.password) == 0))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed. Enter Again Username & Password\n\n");
            attempts++;
        }
    } while (attempts <= 3);

    if (attempts > 3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry, Unknown User.\n");
        getch();
        system("cls");
    }
}

// Function to check if the file exists
int isFileExists(const char* path)
{
    FILE* fp = fopen(path, "rb");
    int status = 0;
    if (fp != NULL)
    {
        status = 1;
        fclose(fp);
    }
    return status;
}

// Initialization function
void init()
{
    FILE* fp = NULL;
    int status = 0;
    const char defaultUsername[] = "arko1610\n";
    const char defaultPassword[] = "arko1610\n";
    sFileHeader fileHeaderInfo = { 0 };
    status = isFileExists(FILE_NAME);
    if (!status)
    {
        fp = fopen(FILE_NAME, "wb");
        if (fp != NULL)
        {
            strncpy(fileHeaderInfo.password, defaultPassword, sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username, defaultUsername, sizeof(defaultUsername));
            fwrite(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

// Main function
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}



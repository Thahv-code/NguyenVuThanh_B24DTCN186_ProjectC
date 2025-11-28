#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *strcasestr(const char *haystack, const char *needle)
{
    if (!*needle)
        return (char *)haystack;

    for (const char *p = haystack; *p; p++)
    {
        const char *h = p;
        const char *n = needle;
        while (*n && *h && tolower((unsigned char)*h) == tolower((unsigned char)*n))
        {
            h++;
            n++;
        }
        if (!*n)
            return (char *)p;
    }
    return NULL;
}

int isSpace(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return 1;
    }

    while (*str)
    {
        if (!isspace((unsigned char)*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

int isValidName(const char *name)
{
    if (isSpace(name))
        return 0;
    int hasAlpha = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        if (isalpha((unsigned char)name[i]))
        {
            hasAlpha = 1;
            break;
        }
    }
    return hasAlpha;
}

int isValidPhone(const char *phone)
{
    int len = strlen(phone);
    if (len < 1 || len > 11)
        return 0;
    for (int i = 0; i < len; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
            return 0;
    }
    return 1;
}

#define MAX_ACCOUNT 50

typedef struct account
{
    int id;
    char fullName[50];
    char phoneNumber[12];
    int status;
    double balance;
} account;

account fakeAccounts[5] = {
    {1, "Nguyen Van A", "0000000001", 1, 1000},
    {2, "Tran Thi B", "0000000002", 1, 2000},
    {3, "Le Van C", "0000000003", 1, 3000},
    {4, "Pham Thi D", "0000000004", 1,4000},
    {5, "Hoang Van E", "0000000005", 1, 5000}
};

void sortBalance(account accounts[], int accountCount)
{
    for (int i = 0; i < accountCount - 1; i++)
    {
        for (int j = 0; j < accountCount - i - 1; j++)
        {
            if (accounts[j].balance < accounts[j + 1].balance)
            {
                account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
    printf("Danh sach da duoc sap xep theo so du giam dan.\n");
}

void sortName(account accounts[], int accountCount)
{
    for (int i = 0; i < accountCount - 1; i++)
    {
        for (int j = 0; j < accountCount - i - 1; j++)
        {
            if (strcmp(accounts[j].fullName, accounts[j + 1].fullName) > 0)
            {
                account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
    printf("Danh sach da duoc sap xep theo ten A-Z.\n");
}

int getNumber(char suggest[], int min, int max)
{
    char string[20];
    int number;

    while (1)
    {
        printf("%s (tu %d den %d): ", suggest, min, max);
        fgets(string, sizeof(string), stdin);
        string[strcspn(string, "\n")] = 0;

        if (string[0] == '\0')
        {
            printf("Vui long khong de trong.\n");
            continue;
        }

        int isDigit = 1;
        for (int i = 0; i < strlen(string); i++)
        {
            if (!isdigit((unsigned char)string[i]))
            {
                isDigit = 0;
                break;
            }
        }

        if (!isDigit)
        {
            printf("Vui long nhap so nguyen.\n");
            continue;
        }

        number = atoi(string);
        if (number >= min && number <= max)
        {
            return number;
        }
        else
        {
            printf("Vui long nhap so trong khoang tu %d den %d.\n", min, max);
        }
    }
}

void addNewAccount(account accounts[], int *accountCount)
{
    if (*accountCount >= MAX_ACCOUNT)
    {
        printf("So luong tai khoan da dat toi da.\n");
        return;
    }

    account *acc = &accounts[*accountCount];
    int id;
    char fullName[50];
    char phoneNumber[12];
    char idStr[20];

    // Nhập ID
    do
    {
        printf("Nhap id nguoi dung: ");
        fgets(idStr, sizeof(idStr), stdin);
        idStr[strcspn(idStr, "\n")] = '\0'; // bỏ ký tự xuống dòng

        if (isSpace(idStr))
        {
            printf("ID khong duoc de trong.\n");
            continue;
        }

        // Kiểm tra ID là số
        int valid = 1;
        for (int i = 0; idStr[i]; i++)
        {
            if (!isdigit((unsigned char)idStr[i]))
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            printf("ID phai la so nguyen.\n");
            continue;
        }

        id = atoi(idStr);
        if (id <= 0)
        {
            printf("ID phai la so nguyen duong.\n");
            continue;
        }

        int duplicate = 0;
        for (int i = 0; i < *accountCount; i++)
        {
            if (accounts[i].id == id)
            {
                printf("ID nay da ton tai.\n");
                duplicate = 1;
                break;
            }
        }
        if (duplicate)
            continue;

        break;

    } while (1);

    // Nhập họ tên
    do
    {
        printf("Nhap ho ten: ");
        fgets(fullName, sizeof(fullName), stdin);
        fullName[strcspn(fullName, "\n")] = '\0';

        if (!isValidName(fullName))
        {
            printf("Ho ten khong hop le. Vui long nhap lai.\n");
            continue;
        }
        break;
    } while (1);

    // Nhập số điện thoại
    do
    {
        printf("Nhap so dien thoai: ");
        fgets(phoneNumber, sizeof(phoneNumber), stdin);
        phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

        if (!isValidPhone(phoneNumber))
        {
            printf("So dien thoai khong hop le. Vui long nhap lai.\n");
            continue;
        }
        break;
    } while (1);

    acc->id = id;
    strcpy(acc->fullName, fullName);
    strcpy(acc->phoneNumber, phoneNumber);
    acc->status = 1;
    (*accountCount)++;

    printf("Them tai khoan thanh cong!\n");
}

void updateAccount(account accounts[], int accountCount)
{
    char idStr[20];
    int id;

    // Nhập ID
    while (1)
    {
        printf("Nhap ID tai khoan can cap nhat: ");
        fgets(idStr, sizeof(idStr), stdin);
        idStr[strcspn(idStr, "\n")] = '\0'; // bỏ ký tự xuống dòng

        if (isSpace(idStr))
        {
            printf("ID khong duoc de trong.\n");
            continue;
        }

        // Kiểm tra ID là số
        int valid = 1;
        for (int i = 0; idStr[i]; i++)
        {
            if (!isdigit((unsigned char)idStr[i]))
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            printf("ID phai la so nguyen.\n");
            continue;
        }

        id = atoi(idStr);
        if (id <= 0)
        {
            printf("ID phai lon hon 0.\n");
            continue;
        }
        break;
    }

    // Tìm tài khoản
    int found = -1;
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Khong tim thay tai khoan nay.\n");
        return;
    }

    printf("Nhap ho ten moi (Enter de bo qua): ");
    char newName[50];
    fgets(newName, sizeof(newName), stdin);
    if (!isSpace(newName) && newName[0] != '\n')
    {
        newName[strcspn(newName, "\n")] = '\0';
        strcpy(accounts[found].fullName, newName);
    }

    printf("Nhap sdt moi (Enter de bo qua): ");
    char newPhone[12];
    fgets(newPhone, sizeof(newPhone), stdin);
    if (!isSpace(newPhone) && newPhone[0] != '\n')
    {
        newPhone[strcspn(newPhone, "\n")] = '\0';
        strcpy(accounts[found].phoneNumber, newPhone);
    }

    printf("Cap nhat thanh cong!\n");
}

void displayAccount(account accounts[], int accountCount)
{
    if (accountCount == 0)
    {
        printf("Khong co tai khoan nao.\n");
        return;
    }

    printf("|| ID ||          Ho & Ten           ||     SDT      || Status ||  Balance  ||\n");
    printf("||==========================================================================||\n");
    for (int i = 0; i < accountCount; i++)
    {
        printf("|| %-2d || %-24s || %-12s || %-7s || %-9.2f ||\n",
               accounts[i].id,
               accounts[i].fullName,
               accounts[i].phoneNumber,
               accounts[i].status == 1 ? "Active" : "Locked",
               accounts[i].balance);
    }
    printf("||==========================================================================||\n");
}

void lockOrDeleteAccount(account accounts[], int *accountCount)
{
    if (*accountCount == 0)
    {
        printf("Loi: Chua co tai khoan nao.\n");
        return;
    }

    char idStr[20];
    int id;

    // Nhập ID
    while (1)
    {
        printf("Nhap ID tai khoan can khoa/xoa: ");
        fgets(idStr, sizeof(idStr), stdin);
        idStr[strcspn(idStr, "\n")] = 0;

        if (isSpace(idStr) || strlen(idStr) == 0)
        {
            printf("Loi: ID khong duoc de trong.\n");
            continue;
        }

        // Kiểm tra ID là số
        int valid = 1;
        for (int i = 0; idStr[i]; i++)
        {
            if (!isdigit((unsigned char)idStr[i]))
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            printf("Loi: ID phai la so nguyen.\n");
            continue;
        }

        id = atoi(idStr);
        if (id <= 0)
        {
            printf("Loi: ID phai lon hon 0.\n");
            continue;
        }
        break;
    }

    // Tìm tài khoản
    int found = -1;
    for (int i = 0; i < *accountCount; i++)
    {
        if (accounts[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Khong tim thay tai khoan voi ID %d.\n", id);
        return;
    }

    printf("Tai khoan hien tai: ID=%d | Ten=%s | SDT=%s | Trang thai=%s\n",
           accounts[found].id,
           accounts[found].fullName,
           accounts[found].phoneNumber,
           accounts[found].status == 1 ? "Active" : "Locked");

    // Nhập lựa chọn
    int choice;
    char choiceStr[20];
    while (1)
    {
        printf("Ban muon lam gi?\n1. Khoa tai khoan\n2. Xoa tai khoan\nLua chon: ");
        fgets(choiceStr, sizeof(choiceStr), stdin);
        choiceStr[strcspn(choiceStr, "\n")] = 0;

        if (isSpace(choiceStr) || strlen(choiceStr) == 0)
        {
            printf("Lua chon khong duoc de trong.\n");
            continue;
        }

        choice = atoi(choiceStr);

        if (choice == 1)
        {
            char confirm[10];
            printf("Ban co chac chan muon KHOA tai khoan nay? (Y/N): ");
            fgets(confirm, sizeof(confirm), stdin);
            confirm[strcspn(confirm, "\n")] = 0;

            if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0)
            {
                accounts[found].status = 0;
                printf("Tai khoan da bi KHOA.\n");
            }
            else
            {
                printf("Huy thao tac.\n");
            }
            break;
        }
        else if (choice == 2)
        {
            char confirm[10];
            printf("Ban co chac chan muon XOA tai khoan nay? (Y/N): ");
            fgets(confirm, sizeof(confirm), stdin);
            confirm[strcspn(confirm, "\n")] = 0;

            if (isSpace(confirm) || strlen(confirm) == 0)
            {
                printf("Loi: Khong duoc de trong.\n");
                continue;
            }

            if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0)
            {
                for (int i = found; i < *accountCount - 1; i++)
                {
                    accounts[i] = accounts[i + 1];
                }
                (*accountCount)--;
                printf("Tai khoan da bi XOA.\n");
            }
            else
            {
                printf("Huy thao tac.\n");
            }
            break;
        }
        else
        {
            printf("Lua chon khong hop le.\n");
        }
    }
}

void searchAccount(account accounts[], int accountCount)
{
    char keyword[50];

    printf("Nhap tu khoa tim kiem (ID hoac Ten): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    if (strlen(keyword) == 0)
    {
        printf("Tu khoa khong duoc de trong.\n");
        return;
    }

    int found = 0;
    printf("|| ID ||          Ho & Ten           ||     SDT     || Status ||\n");
    printf("||============================================================||\n");

    char keywordLower[50];
    size_t kwlen = strlen(keyword);
    for (size_t k = 0; k < kwlen; k++)
        keywordLower[k] = (char)tolower((unsigned char)keyword[k]);
    keywordLower[kwlen] = '\0';

    for (int i = 0; i < accountCount; i++)
    {
        char idString[20];
        sprintf(idString, "%d", accounts[i].id);

        char nameLower[50];
        size_t namelen = strlen(accounts[i].fullName);
        for (size_t k = 0; k < namelen; k++)
            nameLower[k] = (char)tolower((unsigned char)accounts[i].fullName[k]);
        nameLower[namelen] = '\0';

        if (strstr(idString, keyword) != NULL ||
            strstr(nameLower, keywordLower) != NULL)
        {
            printf("|| %-2d || %-24s || %-12s || %-6s ||\n",
                   accounts[i].id,
                   accounts[i].fullName,
                   accounts[i].phoneNumber,
                   accounts[i].status == 1 ? "Active" : "Locked");

            found = 1;
        }
    }
    printf("||============================================================||\n");

    if (!found)
        printf("Khong tim thay tai khoan nao\n");
}

void sortAccounts(account accounts[], int accountCount) {
    char choiceStr[10];
    int choice;

    while (1) {
        printf("Ban muon sap xep theo gi?\n");
        printf("1. Theo so du giam dan\n");
        printf("2. Theo ten A-Z\n");
        printf("Lua chon: ");
        fgets(choiceStr, sizeof(choiceStr), stdin);
        choiceStr[strcspn(choiceStr, "\n")] = '\0';

        if (strlen(choiceStr) == 0) {
            printf("Lua chon khong duoc de trong.\n");
            continue;
        }

        choice = atoi(choiceStr);

        if (choice == 1) {
            sortBalance(accounts, accountCount);
            break;
        } else if (choice == 2) {
            sortName(accounts, accountCount);
            break;
        } else {
            printf("Lua chon khong hop le.\n");
        }
    }
}

    int main()
{
    int choice;
    int accountCount = 0;
    account accounts[MAX_ACCOUNT];
    for (int i = 0; i < 5; i++)
    {
        accounts[i] = fakeAccounts[i];
    }
    accountCount = 5;

    do
    {
        printf("||=======================QUAN LY NGAN HANG===================||\n");
        printf("||                     1. Them tai khoan                     ||\n");
        printf("||                     2. Cap nhat thong tin                 ||\n");
        printf("||                     3. Quan ly trang thai(Khoa/xoa)       ||\n");
        printf("||                     4. Tra cuu                            ||\n");
        printf("||                     5. Hien thi danh sach                 ||\n");
        printf("||                     6. Sap xep danh sach                  ||\n");
        printf("||                     7. Giao dich chuyen khoan             ||\n");
        printf("||                     8. Lich su giao dich                  ||\n");
        printf("||                     9. Thoat                              ||\n");
        printf("||===========================================================||\n");

        choice = getNumber("Moi nhap lua chon", 1, 9);

        switch (choice)
        {
        case 1:
            addNewAccount(accounts, &accountCount);
            break;
        case 2:
            updateAccount(accounts, accountCount);
            break;
        case 3:
            lockOrDeleteAccount(accounts, &accountCount);
            break;
        case 4:
            searchAccount(accounts, accountCount);
            break;
        case 5:
            displayAccount(accounts, accountCount);
            break;
        case 6:
            sortAccounts(accounts, accountCount);
            break;
        case 9:
            printf("Bye!\n");
            return 0;
        default:
            printf("Lua chon khong hop le\n");
            break;
        }
    } while (choice != 9);

    return 0;
}

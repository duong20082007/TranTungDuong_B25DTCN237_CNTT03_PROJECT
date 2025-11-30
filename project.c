#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct {
	int day, month, year;
}Date;
typedef struct {
	int bookId;
	char title[50];
	char author[50];
	int publishYear, quantity;
}Book;
typedef struct {
	int borrowId, bookId, status;
	Date borrowDate;
	Date borrowReturn;
	char borrowerName[50];
}Borrow;
Book books[100];
int bookCount = 0;
int isBookIdExist(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookId == id) {
            return 1;
        }
    }
    return 0;
}
int isTitleDuplicate(const char *title, int currentId) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookId != currentId) {
            if (strcmp(books[i].title, title) == 0) {
                return 1; 
            }
        }
    }
    return 0; 
}
int generateNewBookId() {
    if (bookCount == 0) {
        return 1;
    }
    int maxId = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookId > maxId) {
            maxId = books[i].bookId;
        }
    }
    return maxId + 1;
}
void addNewBook() {
    if (bookCount >= 100) {
        printf("\nLoi. Danh sach da day ");
        return;
    }

    Book newBook;
    newBook.bookId = generateNewBookId();
    int isValid = 0;
    printf("\n--- CHUC NANG THEM MOI (ID: %d) ---\n", newBook.bookId);
    do {
        isValid = 1;
        printf("Nhap tieu de sach: ");
        fflush(stdin);
        if (fgets(newBook.title, sizeof(newBook.title), stdin) == NULL) {
            isValid = 0;
        } else {
            newBook.title[strcspn(newBook.title, "\n")] = 0;
        }

        printf("Nhap ten tac gia: ");
        fgets(newBook.author, sizeof(newBook.author), stdin);
        newBook.author[strcspn(newBook.author, "\n")] = 0;

        printf("Nhap nam xuat ban: ");
        if (scanf("%d", &newBook.publishYear) != 1) {
            printf("Loi. Nam xuat ban phai la so nguyen \n");
            fflush(stdin);
            isValid = 0;
            continue;
        }

        printf("Nhap so luong sach: ");
        if (scanf("%d", &newBook.quantity) != 1) {
            printf("Loi. So luong phai la so nguyen \n");
            fflush(stdin);
            isValid = 0;
            continue;
        }
        if (strlen(newBook.title) == 0) {
            printf("Loi. Tieu de khong duoc de trong \n");
            isValid = 0;
        } else if (isTitleDuplicate(newBook.title, -1)) { 
            printf("Loi. Tieu de sach da ton tai \n");
            isValid = 0;
        }
        
        if (strlen(newBook.author) == 0) {
            printf("Loi. Ten tac gia khong duoc de trong \n");
            isValid = 0;
        }

        if (newBook.publishYear < 1900) {
            printf("Loi. Nam xuat ban phai lon hon %d \n", 1900);
            isValid = 0;
        }

        if (newBook.quantity <= 0) {
            printf("Loi. So luong sach phai lon hon 0 \n");
            isValid = 0;
        }
        
        if (isValid == 0) {
            printf("Vui long nhap du lieu \n");
        }
        
    } while (isValid == 0);
    books[bookCount] = newBook;
    bookCount++;

    printf("\n--- Them danh sach thanh cong (ID: %d) ---\n", newBook.bookId);
}
void updateBookInfo() {
    int targetId;
    int targetIndex = -1; 

    printf("\n--- CHUC NANG CAP NHAT THONG TIN SACH ---\n");
    printf("Nhap ID sach can cap nhat: ");
    if (scanf("%d", &targetId) != 1) {
        printf("Loi. ID phai la so nguyen \n");
        fflush(stdin);
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookId == targetId) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        printf("\nThong bao khong tim thay sach ID %d.\n", targetId);
        return;
    }
    Book tempBook = books[targetIndex]; 
    int isValid = 0;
    
    printf("\nDang cap nhat sach ID: %d | Tieu de cu: %s\n", books[targetIndex].bookId, books[targetIndex].title);

    do {
        isValid = 1;
        printf("Nhap tieu de moi: ", books[targetIndex].title);
        fflush(stdin);
        if (fgets(tempBook.title, sizeof(tempBook.title), stdin) == NULL) {
            isValid = 0;
        } else {
            tempBook.title[strcspn(tempBook.title, "\n")] = 0;
        }
        
        printf("Nhap ten tac gia moi: ", books[targetIndex].author);
        fgets(tempBook.author, sizeof(tempBook.author), stdin);
        tempBook.author[strcspn(tempBook.author, "\n")] = 0;

        printf("Nhap nam xuat ban moi: ", books[targetIndex].publishYear);
        if (scanf("%d", &tempBook.publishYear) != 1) {
            printf("Loi. Nam xuat ban phai la so nguyen \n");
            fflush(stdin);
            isValid = 0;
            continue;
        }
        printf("Nhap so luong sach moi: ", books[targetIndex].quantity);
        if (scanf("%d", &tempBook.quantity) != 1) {
            printf("Loi. So luong phai la so nguyen \n");
            fflush(stdin);
            isValid = 0;
            continue;
        }
        if (strlen(tempBook.title) == 0) {
            printf("Loi. Tieu de khong duoc de trong \n");
            isValid = 0;
        } else if (isTitleDuplicate(tempBook.title, targetId)) { 
            printf("Loi. Tieu de da co trong sach khac \n");
            isValid = 0;
        }
        if (strlen(tempBook.author) == 0) {
            printf("Loi. Ten tac gia khong duoc de trong \n");
            isValid = 0;
        }
        if (tempBook.publishYear < 1900) {
            printf("Loi. Nam xuat ban phai hon hon %d.\n", 1900);
            isValid = 0;
        }
        if (tempBook.quantity <= 0) {
            printf("Loi so luong sach phai lon hon 0 \n");
            isValid = 0;
        }
        if (isValid == 0) {
            printf("Vui long nhap lai \n");
        }
    } while (isValid == 0);

    books[targetIndex] = tempBook;

    printf("\n--- Cap nhat danh sach %d thanh cong! ---\n", targetId);
}
int calculateTotalPages() {
    if (bookCount == 0) return 1;
    return (bookCount + 10 - 1) /10;
}
void displayBooksByPage(int pageNumber, int totalPages) {
    if (bookCount == 0) {
        printf("Danh sach trong\n");
        return;
    }
    int start_index = (pageNumber - 1) * 10;
    int end_index = start_index + 10;
    if (end_index > bookCount) {
        end_index = bookCount;
    }
    printf("\n              --- Danh sach SACH (Trang %d/%d) ---\n", pageNumber, totalPages);
    printf("| %-4s | %-25s | %-15s | %-8s | %-8s |\n", "ID", "Tieu de", "Tac gia", "Nam XB", "SL");
    printf("----------------------------------------------------------------------------\n");

    for (int i = start_index; i < end_index; i++) {
        printf("| %-4d | %-25s | %-15s | %-8d | %-8d |\n", books[i].bookId, books[i].title, books[i].author, books[i].publishYear, books[i].quantity);
    printf("----------------------------------------------------------------------------\n");
	}
}
void displayBookListWithPagination() {
    int currentPage = 1;
    int choicePage;
    
    printf("\n--- CHUC NANG HIEN THI DANH SACH ---\n");

    if (bookCount == 0) {
        printf("Danh sach trong \n");
        return;
    }
    
    do {
        int totalPages = calculateTotalPages();
        displayBooksByPage(currentPage, totalPages);
        
        printf("\nLua chon:\n");
        printf("1. Quay lai trang truoc\n", (currentPage > 1 ? currentPage - 1 : currentPage));
        printf("2. Quay lai MENU\n");
        printf("3. Chuyen trang tiep theo\n", (currentPage < totalPages ? currentPage + 1 : currentPage));
        printf("Nhap lua chon: ");
        
        if (scanf("%d", &choicePage) != 1) {
            printf("\nLoi. Vui long nhap lai \n");
            fflush(stdin);
            choicePage = -1; 
        } else {
        	fflush(stdin);
        }
        switch (choicePage) {
            case 1: 
                if (currentPage > 1) {
                    currentPage--;
                } else {
                    printf("Khong the lui them \n");
                }
                break;
                
            case 3: 
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("Khong the tien them \n");
                }
                break;
                
            case 2:
                printf("\nDa thoat chuc nang\n");
                break;
                
            default: 
                printf("\nLoi. Lua chon khong hop le \n", choicePage);
                choicePage = 2; 
                break;
        }
    } while (choicePage != 2);
}
int getBookIndexById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookId == id) {
            return i;
        }
    }
    return -1;
}
int borrowCount = 0;
Borrow borrows[100];
int isBookCurrentlyBorrowed(int bookId) {
    for (int i = 0; i < borrowCount; i++) {
        if (borrows[i].bookId == bookId && borrows[i].status == 0) { 
            return 1; 
        }
    }
    return 0; 
}
void deleteBookInfo() {
    int targetId;
    int targetIndex = -1;
    
    printf("\n--- CHUC NANG XOA THONG TIN SACH ---\n");
    
    printf("Nhap ID sach muon xoa: ");
    if (scanf("%d", &targetId) != 1) {
        printf("Loi. Vui long nhap lai \n");
        fflush(stdin);
        return;
    }
    fflush(stdin);
    
    targetIndex = getBookIndexById(targetId);
    if (targetIndex == -1) {
        printf("\nKhong tim thay sach ID %d. Quay lai MENU \n", targetId);
        return;
    }
    if (isBookCurrentlyBorrowed(targetId)) {
        printf("\nKhong the xoa vi co nguoi muon chua tra \n", targetId);
        return;
    }
    char confirm[5];
    printf("\nBan co chac muon xoa sach ID %d khong ? (c/k): ", 
           targetId, books[targetIndex].title);
    if (fgets(confirm, sizeof(confirm), stdin) == NULL) {
    } else {
        confirm[strcspn(confirm, "\n")] = 0;
    }

    if (strcmp(confirm, "c") != 0 && strcmp(confirm, "C") != 0) {
        printf("Huy bo thao tac xoa\n");
        return;
    }
    for (int i = targetIndex; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;
    printf("\n--- Xoa sach thanh cong ! ---\n", targetId);
}
void toLowerStr(char str[]) { 
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
int string_contains(const char haystack[], const char needle[]) {
    char tempHaystack[50];
    char tempNeedle[50];

    strncpy(tempHaystack, haystack, 49);
    tempHaystack[49] = '\0';
    
    strncpy(tempNeedle, needle, 49);
    tempNeedle[49] = '\0';

    toLowerStr(tempHaystack);
    toLowerStr(tempNeedle);

    if (strstr(tempHaystack, tempNeedle) != NULL) { 
        return 1;
    }
    return 0;
}
void searchBooksByTitle() {
    char searchTitle[50];
    int foundCount = 0;
    
    printf("\n--- CHUC NANG TIM KIEM SACH (TUONG DOI) ---\n");
    do {
        printf("Nhap ten sach muon tim: ");
        fflush(stdin);
        if (fgets(searchTitle, 50, stdin) == NULL) {
        } else {
            searchTitle[strcspn(searchTitle, "\n")] = 0;
        }
        if (strlen(searchTitle) == 0) {
            printf("\nLoi. Ten sach khong duoc de trong. Yeu cau nhap lai.\n");
        }
    } while (strlen(searchTitle) == 0);
    printf("\n--- KET QUA TIM KIEM CHO: \"%s\" ---\n", searchTitle);
    printf("| %-4s | %-25s | %-15s | %-8s | %-8s |\n", "ID", "Tieu de", "Tac gia", "Nam XB", "SL");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        if (string_contains(books[i].title, searchTitle)) {
            printf("| %-4d | %-25s | %-15s | %-8d | %-8d |\n", books[i].bookId, books[i].title, books[i].author, books[i].publishYear, books[i].quantity);
            printf("----------------------------------------------------------------------------\n");
            foundCount++;
        }
    }
    if (foundCount == 0) {
        printf("Khong co sach nao co ten chua \"%s\" trong danh sach.\n", searchTitle);
    } else {
        printf("\nDa tim thay %d ket qua.\n", foundCount);
    }
}
int generateNewBorrowId() {
    if (borrowCount == 0) {
        return 1;
    }
    int maxId = 0;
    for (int i = 0; i < borrowCount; i++) {
        if (borrows[i].borrowId > maxId) {
            maxId = borrows[i].borrowId;
        }
    }
    return maxId + 1;
}
int isValidDate(Date d) {
    if (d.year < 2000) return 0;
    if (d.month < 1 || d.month > 12) return 0;
    if (d.day < 1 || d.day > 31) return 0;
    if ((d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) && d.day > 30) return 0;
    if (d.month == 2) {
        int isLeap = ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0);
        if (isLeap && d.day > 29) return 0;
        if (!isLeap && d.day > 28) return 0;
    }
    return 1;
}
int isBorrowDateValid(Date borrowDate, Date returnDate) {
    if (borrowDate.year > returnDate.year) return 0;
    if (borrowDate.year == returnDate.year && borrowDate.month > returnDate.month) return 0;
    if (borrowDate.year == returnDate.year && borrowDate.month == returnDate.month && borrowDate.day > returnDate.day) return 0;
    return 1;
}
void addNewBorrow() {
    if (borrowCount >= 100) {
        printf("\nLoi. Danh sach phieu muon da day.");
        return;
    }

    Borrow newBorrow;
    newBorrow.borrowId = generateNewBorrowId();
    newBorrow.status = 0;
    
    int isValid = 0;
    int bookIndex = -1; 
    
    printf("\n--- CHUC NANG THEM PHIEU MUON ---\n", newBorrow.borrowId);

    do {
        isValid = 1;
        printf("Nhap ma sach muon muon: ");
        if (scanf("%d", &newBorrow.bookId) != 1) {
            printf("Loi. Ma sach phai la so nguyen.\n");
            fflush(stdin);
            isValid = 0;
            continue;
        }
        bookIndex = getBookIndexById(newBorrow.bookId);
        if (bookIndex == -1) {
            printf("Loi. Khong tim thay ma sach %d.\n", newBorrow.bookId);
            isValid = 0;
        } else if (books[bookIndex].quantity <= 0) {
            printf("Loi. Sach \"%s\" da het so luong de muon.\n", books[bookIndex].title);
            isValid = 0;
        }
        if (isValid == 0) continue;
        printf("Nhap ngay muon: ");
        if (scanf("%d %d %d", &newBorrow.borrowDate.day, &newBorrow.borrowDate.month, &newBorrow.borrowDate.year) != 3) {
            printf("Loi. Ngay muon khong dung dinh dang DD MM YYYY.\n");
            fflush(stdin);
            isValid = 0;
            continue;
        }
        if (!isValidDate(newBorrow.borrowDate)) {
            printf("Loi. Ngay muon khong hop le.\n");
            isValid = 0;
            continue;
        }
        printf("Nhap ngay tra du kien: ");
        if (scanf("%d %d %d", &newBorrow.borrowReturn.day, &newBorrow.borrowReturn.month, &newBorrow.borrowReturn.year) != 3) {
            printf("Loi. Ngay tra du kien khong dung dinh dang DD MM YYYY.\n");
            fflush(stdin);
            isValid = 0;
            continue;
        }
        if (isValidDate(newBorrow.borrowReturn)==0) {
            printf("Loi. Ngay tra du kien khong hop le.\n");
            isValid = 0;
            continue;
        }
        if (isBorrowDateValid(newBorrow.borrowDate, newBorrow.borrowReturn)==0) {
            printf("Loi. Ngay tra du kien khong the truoc ngay muon.\n");
            isValid = 0;
            continue;
        }
        fflush(stdin); 
        printf("Nhap ten nguoi muon: ");
        if (fgets(newBorrow.borrowerName, sizeof(newBorrow.borrowerName), stdin) == NULL) {
            isValid = 0;
        } else {
            newBorrow.borrowerName[strcspn(newBorrow.borrowerName, "\n")] = 0;
        }

        if (strlen(newBorrow.borrowerName) == 0) {
            printf("Loi. Ten nguoi muon khong duoc de trong.\n");
            isValid = 0;
            continue;
        }
        
    } while (isValid == 0); 
    books[bookIndex].quantity--;
    borrows[borrowCount] = newBorrow;
    borrowCount++;
    printf("\n--- Them phieu muon thanh cong! ---\n", newBorrow.borrowId);
}
int getBorrowIndexById(int id) {
    for (int i = 0; i < borrowCount; i++) {
        if (borrows[i].borrowId == id) {
            return i;
        }
    }
    return -1;
}
void returnBook() {
    int targetBorrowId;
    int targetBorrowIndex = -1;
    int bookIndex = -1;
    int isValid = 0;
    Date returnDate; 
    printf("\n--- CHUC NANG TRA SACH ---\n");
    
    printf("Nhap ID phieu muon can tra: ");
    if (scanf("%d", &targetBorrowId) != 1) {
        printf("Loi. ID phieu muon phai la so nguyen.\n");
        fflush(stdin);
        return;
    }
    targetBorrowIndex = getBorrowIndexById(targetBorrowId);
    
    if (targetBorrowIndex == -1) {
        printf("\nThong bao: Khong tim thay phieu muon ID %d.\n", targetBorrowId);
        return;
    }
    if (borrows[targetBorrowIndex].status == 1) {
        printf("\nThong bao: Phieu muon ID %d da duoc tra truoc do.\n", targetBorrowId);
        return;
    }
    Borrow currentBorrow = borrows[targetBorrowIndex];
    
    do {
        isValid = 1;
        printf("\nNhap ngay thang nam tra sach thuc te: ");
        fflush(stdin); 
        if (scanf("%d %d %d", &returnDate.day, &returnDate.month, &returnDate.year) != 3) {
            printf("Loi. Ngay tra khong dung dinh dang DD MM YYYY.\n");
            isValid = 0;
            continue;
        }
        if (isValidDate(returnDate)==0) {
            printf("Loi. Ngay tra khong hop le.\n");
            isValid = 0;
            continue;
        }
        if (isBorrowDateValid(currentBorrow.borrowDate, returnDate)==0) {
             printf("Loi. Ngay tra (%d/%d/%d) khong the truoc ngay muon (%d/%d/%d).\n", returnDate.day, returnDate.month, returnDate.year,currentBorrow.borrowDate.day, currentBorrow.borrowDate.month, currentBorrow.borrowDate.year);
            isValid = 0;
            continue;
        }
        
    } while (isValid == 0);
    
    borrows[targetBorrowIndex].borrowReturn = returnDate;
    borrows[targetBorrowIndex].status = 1; 
    
    bookIndex = getBookIndexById(currentBorrow.bookId);
    if (bookIndex != -1) {
        books[bookIndex].quantity++;
    } else {
        printf("\nCanh bao: Khong tim thay sach ID %d trong kho de tang so luong.\n", currentBorrow.bookId);
    }
    printf("\n--- Tra sach thanh cong! ---\n");
    printf("Phieu muon ID %d da duoc cap nhat ngay tra: %d/%d/%d\n", targetBorrowId, returnDate.day, returnDate.month, returnDate.year);
    if (bookIndex != -1) {
        printf("So luong sach \"%s\" trong kho hien la: %d\n", books[bookIndex].title, books[bookIndex].quantity);
    }
}
int calculateTotalBorrowPages() {
    if (borrowCount == 0) return 1;
    return (borrowCount + 10 - 1) / 10;
}

void displayBorrowsByPage(int pageNumber, int totalPages) {
    if (borrowCount == 0) {
        printf("Danh sach trong\n");
        return;
    }
    int start_index = (pageNumber - 1) * 10;
    int end_index = start_index + 10;
    if (end_index > borrowCount) {
        end_index = borrowCount;
    }

    printf("\n\t\t\t--- DANH SACH PHIEU MUON (Trang %d/%d) ---\n", pageNumber, totalPages);
    printf("| %-4s | %-8s | %-15s | %-12s | %-12s | %-15s |\n", 
           "ID", "ID Sach", "Nguoi Muon", "Ngay Muon", "Ngay Tra", "Trang Thai");
    printf("-------------------------------------------------------------------------------------\n");

    for (int i = start_index; i < end_index; i++) {
        const char *statusStr = (borrows[i].status == 0) ? "DANG MUON" : "DA TRA";
        
        char borrowDateStr[11]; 
        char returnDateStr[11];
        
        sprintf(borrowDateStr, "%02d/%02d/%d", borrows[i].borrowDate.day, borrows[i].borrowDate.month, borrows[i].borrowDate.year);
        
        if (borrows[i].status == 1) {
            sprintf(returnDateStr, "%02d/%02d/%d", borrows[i].borrowReturn.day, borrows[i].borrowReturn.month, borrows[i].borrowReturn.year);
        } else {
            strcpy(returnDateStr, "Chua Tra");
        }
        
        printf("| %-4d | %-8d | %-15s | %-12s | %-12s | %-15s |\n", borrows[i].borrowId, borrows[i].bookId, borrows[i].borrowerName, borrowDateStr,returnDateStr,statusStr);
        printf("-------------------------------------------------------------------------------------\n");
    }
}
void displayBorrowListWithPagination() {
    int currentPage = 1;
    int choicePage;
    
    printf("\n--- CHUC NANG HIEN THI DANH SACH PHIEU MUON ---\n");

    if (borrowCount == 0) {
        printf("Danh sach phieu muon trong \n");
        return;
    }
    
    do {
        int totalPages = calculateTotalBorrowPages();
        displayBorrowsByPage(currentPage, totalPages);
        
        printf("\nLua chon:\n");
        printf("1. Xem trang truoc \n", (currentPage > 1 ? currentPage - 1 : currentPage));
        printf("2. Quay lai MENU\n");
        printf("3. Xem trang tiep theo \n", (currentPage < totalPages ? currentPage + 1 : currentPage));
        printf("Nhap lua chon: ");
        
        if (scanf("%d", &choicePage) != 1) {
            printf("\nLoi. Vui long nhap so hop le \n");
            fflush(stdin);
            choicePage = -1; 
        } else {
            fflush(stdin);
        }
        switch (choicePage) {
            case 1: 
                if (currentPage > 1) {
                    currentPage--;
                } else {
                    printf("Khong the lui ve trang truoc.\n");
                }
                break;
            case 3: 
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("Khong the chuyen sang trang tiep theo.\n");
                }
                break;
            case 2:
                printf("\nDa thoat chuc nang hien thi phieu muon.\n");
                break;
            default: 
                printf("\nLoi. Lua chon khong hop le. Vui long chon 1, 2 hoac 3.\n");
                choicePage = -1; 
                break;
        }
    } while (choicePage != 2);
}
int main(){
	int choice;
	books[0] = (Book){1, "Lap Trinh C", "Nguyen Van A", 2005, 10};
    books[1] = (Book){2, "Cau Truc Du Lieu", "Tran Thi B", 2018, 5};
    books[2] = (Book){3, "Mang May Tinh", "Le Van C", 2020, 15};
    books[3] = (Book){4, "He Dieu Hanh", "Pham Thi D", 2010, 8};
    books[4] = (Book){5, "Co So Du Lieu", "Hoang Van E", 2015, 12};
    books[5] = (Book){6, "Kinh Te Vi Mo", "Tran Van F", 2022, 10};
    books[6] = (Book){7, "Tieng Anh Chuyen Nganh", "Le Thi G", 2019, 7};
    books[7] = (Book){8, "Marketing Co Ban", "Nguyen Van H", 2021, 14};
    books[8] = (Book){9, "Phap Luat Dai Cuong", "Hoang Thi K", 2017, 9};
    books[9] = (Book){10, "Giai Tich 1", "Pham Van L", 2016, 20};
    books[10] = (Book){11, "Giai Tich 2", "Pham Van L", 2004, 19};
    bookCount = 11;
    borrows[0] = (Borrow){101, 1, 0, {25, 11, 2025}, {10, 12, 2025}, "Pham Minh T"}; 
    borrows[1] = (Borrow){102, 3, 1, {10, 10, 2025}, {10, 11, 2025}, "Le Van H"}; 
    borrows[2] = (Borrow){103, 5, 0, {15, 11, 2025}, {15, 12, 2025}, "Tran Thi M"}; 
	borrows[3] = (Borrow){104, 2, 1, {01, 9, 2025}, {15, 9, 2025}, "Nguyen Van A"}; 
    borrows[4] = (Borrow){105, 4, 0, {05, 11, 2025}, {05, 12, 2025}, "Bui Thi C"}; 
    borrows[5] = (Borrow){106, 6, 0, {8, 11, 2025}, {20, 12, 2025}, "Dinh Van D"}; 
    borrows[6] = (Borrow){107, 7, 1, {12, 10, 2025}, {25, 10, 2025}, "Hoang Minh E"}; 
    borrows[7] = (Borrow){108, 9, 0, {20, 11, 2025}, {30, 12, 2025}, "Vu Thi F"}; 
    borrows[8] = (Borrow){109, 10, 0, {01, 12, 2025}, {15, 01, 2026}, "Mai Van G"};
    borrows[9] = (Borrow){110, 11, 1, {03, 10, 2025}, {03, 11, 2025}, "Cao Thi H"}; 
    borrows[10] = (Borrow){111, 12, 1, {20, 8, 2025}, {29,11,2025}, "Le Thi Phuong M"};
    borrowCount = 11;
	do{
		system("cls");
		printf("\n================= MENU QUAN LY THU VIEN =================");
		printf("\n||1. Them sach moi                                     ||");
		printf("\n||2. Cap nhat thong tin sach                           ||");
		printf("\n||3. Hien thi danh sach (co phan trang)                ||");
		printf("\n||4. Xoa thong tin sach                                ||");
		printf("\n||5. Tim kiem sach (tim kiem tuong doi)                ||");
		printf("\n||6. Them moi phieu muon                               ||");
		printf("\n||7. Tra sach                                          ||");
		printf("\n||8. Hien thi danh sach phieu muon (co phan trang)     ||");
		printf("\n||0. Thoat chuong trinh                                ||");
		printf("\n=========================================================");
		printf("\nChon chuc nang: ");
		scanf("%d",&choice);	
	switch(choice){
		case 1:
			system("cls");
			addNewBook();
			fflush(stdin); 
			getchar();
			break;
		case 2:
			system("cls");
			updateBookInfo();
			fflush(stdin);
			getchar();
			break;
		case 3:
			system("cls");
			displayBookListWithPagination();
			fflush(stdin);
			getchar();
			break;
		case 4:
			system("cls");
			deleteBookInfo();
			fflush(stdin);
			getchar();
			break;
		case 5:
			system("cls");
			searchBooksByTitle();
			fflush(stdin);
			getchar();
			break;
		case 6:
			system("cls");
			addNewBorrow();
			fflush(stdin);
			getchar();
			break;
		case 7:
			system("cls");
			returnBook();
			fflush(stdin);
			getchar();
			break;
		case 8:
			system("cls");
			displayBorrowListWithPagination();
			fflush(stdin);
			getchar();
			break;
		case 0:
			printf("--- Cam on da quan ly thu vien ---");
			break;
		default:
			printf("Lua chon khong hop le. Vui long nhap lai ");
	}
	
	} while (choice != 0);
	
	return 0;
}


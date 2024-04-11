
/*=====================================================================================================================
                                   ABAS, JHONDEL MICO N.
                                MENDERICO, CHRISTIAN DAYNE R.
                                        BSIT-2A
=======================================================================================================================*/

/*=====================================================================================================================
                                   Header Files
=======================================================================================================================*/
#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define MIN_BAL 5000
using namespace std;
/*=====================================================================================================================
                                   ADT STRUCTURE
=======================================================================================================================*/
typedef struct node {
    string name, address, status, sex, birthday, contact;
    int accNum, currentBal, pin;
    struct node *next;
}NODE;
/*=====================================================================================================================
                                CLASS DEFINITION
=======================================================================================================================*/
class SystemRecord{
private: //Non Accessible objects to the user
    NODE *L;
    NODE* search(int n); //This function searches the location of the record
    NODE* add(const string& n, int accNum, int currentBal, int pin, const string& address, const string& status, const string& sex, const string& birthday, const string& contact); //This Function is to initialize the scores to zero if its a new user
public: //Accessible objects to the user
    //These functions are for the tests for each function
    NODE* enroll(); //This function includes the login interface and user registration
    void makeNull(); //This initalizes the heads of the linked list to NULL
    void download(); //This function transfers the records from the dbf file to the linked list
    void upload(); //This function transfers the records from the linked list to the dbf file
    void balanceInquiry(NODE* p); //This function prints the personal record of the user
    void withdraw(NODE* p); // This function allows the user to withdraw a specific amount of money from their account
    void deposit(NODE* p);  // This function accepts the amount the user had put in then adds it to its current balance
    void fundTransfer(NODE* p); // This function finds an existing account number and transfer the amount the user had encoded.
    void changePin(NODE* p); // This function changes the current pin of the user by overwriting it with a new 4 digit pincode
    int decrypt(int pin); // Function to decrypt encrypted pin code by converting the encrypted code to the original pin code
    int encrypt(int pin, int accNum); // function that converts the pincode to a secret code for account security.
    void messageBox(int x, int y, const string& head, const string& message); //
    NODE* registerAcc(); // This function is called when there is no detected existing file in the ATM card of the user, indicating that it is a new user, hence they need to register.

};
/*=====================================================================================================================
                                   Display Functions
=======================================================================================================================*/
void closing();
void welcome();
int menu(NODE* p); //Declaration for the Menu
void gotoxy(int x,int y);
void green(int num, int x, int y);
void drawBox(int x, int y, char value);
void drawBoxText(int x, int y, const string& text);
void header(const string& text, int x, int y, int l);
int inputInterface(int digits);
int inputPinInterface();
void warningBox(int x, int y, const string& head, const string& message);
void menuBox(int x, int y, const string& text);

int main(){
SystemRecord sr;    //This gives access to the StudentRecord class using sr
sr.makeNull();      //Initializes L and H to NULL
sr.download();      //Adds record from the dbf file to the linkedlist
NODE *newNode, *p;  //Declaration to acces the linkedlist NODE

p = sr.enroll();    //Returns the address or link of the user after login

while(true){
        system("cls");
        switch(menu(p)){
            case '1':           //withdraw
            system("cls");
            sr.withdraw(p);     // calls withdraw function with actual argument p, which is the pointer to the address of the user
            break;
            case '2':           //deposit
            system("cls");
            sr.deposit(p);      // calls deposit function with actual argument p, which is the pointer to the address of the user
            break;
            case '3':           //change pin
            system("cls");
            sr.changePin(p);    // calls change pin function with actual argument p, which is the pointer to the address of the user
            break;
            case '4':           //check balance
            system("cls");
            sr.balanceInquiry(p);   // calls balance inquiry function with actual argument p, which is the pointer to the address of the user
            break;
            case '5':           //fund transfer
            system("cls");
            sr.fundTransfer(p); // calls fund transfer function with actual argument p, which is the pointer to the address of the user
            break;
            case '6':           // upload
            sr.upload();        // calls upload function to upload the data of the user to the database
            closing();          // a display function for closing interface
            default:            // Error handling
            getch();            // Wrong inputs won't be echoed to the screen
            continue;
        }
    }
    return 0;
}
void closing(){
    system("cls");
    welcome();                  // Reuses the welcome interface since it includes the logo and the name of the ATM company
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // manipulates the properties of the console window
    CONSOLE_SCREEN_BUFFER_INFO originalAttributes;     // variable declaration of the structure CONSOLE_SCREEN_BUFFER_INFO to set the color of the text
    GetConsoleScreenBufferInfo(hConsole, &originalAttributes); // function call to retrieve information about the console screen buffer
    gotoxy(40,25);
    cout << "   Thank you for banking with us";
        while (true) {      // the text will continue blinking when the if station is not met
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);      // sets the color to BLUE
            gotoxy(40,26);
            cout << "          GET YOUR CARD..." << endl;
            Sleep(200);  // Adjust blinking speed by changing the sleep duration

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);     // sets the color to GREEN
            gotoxy(40,26);
            cout << "          GET YOUR CARD..." << endl;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // sets the color to DEFAULT COLOR


            Sleep(200);  // Adjust blinking speed by changing the sleep duration
            if (GetDriveType("D://") != DRIVE_REMOVABLE) { // block of code to exit the program when drive is ejected from the device
                system("cls");
                welcome();
                SetConsoleTextAttribute(hConsole, originalAttributes.wAttributes);  // sets the text of the program back to original to prevent texts after welcome function to being colored
                gotoxy(40, 100);
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ";
                exit(0);  // exits the program
                }
        }
}
int menu(NODE *p){
    gotoxy(10, 5);
    cout << "\e[1;33mWelcome\e[0m" << endl;
    gotoxy(10, 6);
    cout << "Username: "<< p->name <<endl;
    gotoxy(10, 10);
    cout << "\e[1;33mAccount Number:\e[0m" <<endl;
    gotoxy(10,11);
    cout << p->accNum;
    menuBox(40,5,  "   WITHDRAW [1]");             // this function prints a WITHDRAW text with a border to a specific coordinate in the console
    menuBox(64,5,  "   DEPOSIT [2]");              // this function prints a DEPOSIT text with a border to a specific coordinate in the console
    menuBox(40,10, "  CHANGE PIN [3]");            // this function prints a CHANGE PIN text with a border to a specific coordinate in the console
    menuBox(64,10, "CHECK BALANCE [4]");           // this function prints a CURRENT BALANCE text with a border to a specific coordinate in the console
    menuBox(40,15, "FUND TRANSFER [5]");           // this function prints a FUND TRANSFER text with a border to a specific coordinate in the console
    menuBox(64,15, "    EXIT [6]");                // this function prints a EXIT text with a border to a specific coordinate in the console
    gotoxy(10, 17);

    int op;
    op=_getch();                                   // the option input wont be echoed to the console
    return op;                                     // returns the value of the selection back to its calling function

}
void menuBox(int x, int y, const string& text){
    gotoxy(x, y);
    cout<<"\t"<<char(218);                  // upper left corner
    for(int i = 0; i < 20; i++)
        cout<<char(196);                    // upper right corner
    cout<<char(191);
    gotoxy(x+8,y+1);
    cout << char(179);                      // | : left border
    gotoxy(x+29,y+1);
    cout << char(179);                      // | : right border
    gotoxy(x+8,y+2);
    cout << char(179);                      // | : left border
    gotoxy(x+29,y+2);
    cout << char(179);                      // | : right border
    gotoxy(x+11,y+2);
    cout << text;                           // prints the string text
    gotoxy(x+8,y+3);
    cout << char(179);                      // | : right border
    gotoxy(x+29,y+3);
    cout << char(179);                      // | : left border
    gotoxy(x,y+4);
    cout<<"\t"<<char(192);                  // create a corner border "└"
    for(int i = 0; i < 20; i++)             // a loop to create a horizontal line "─"
        cout<<char(196);
    cout<<char(217);                        // ┘: lower right corner
    }
void blocks(int x, int y, int width){
    gotoxy(x,y);
    for (int i=0; i<width; i++)
        cout << char(219);
}
void gotoxy(int x, int y) {                 // function to set the position of text to coordinates x and y in the console
    COORD coord;                            // Data structure for SHORT X and SHORT Y
    coord.X = x;                            // Sets the horizontal coordinate to the value of x
    coord.Y = y;                            // Sets the vertical coordinate to the value of y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // set the position of the cursor in the console
}
void welcome(){
    // prints the top horizontal part of letter A
    blocks(35,7,15);
    blocks(35,8,15);
    // Prints the middle horizontal part of A
    blocks(35,14,15);
    blocks(35,15,15);
    for (int i=9; i<19; i++) // Prints the vertical left part of A
        blocks(30,i,5);
    for (int i=9; i<19; i++) // prints the vertical right part of A
        blocks(50,i,5);
    for (int i=7; i<19; i++) // for vertical left of M
        blocks(60,i,5);
    // for the slant of M
    blocks(65,9,5);
    blocks(65,10,5);
    blocks(70,11,5);
    blocks(70,12,5);
    blocks(75,9,5);
    blocks(75,10,5);
    for (int i=7; i<19; i++)    // M vertical right
        blocks(80,i,5);
    gotoxy(40,20);
    cout << "        Abas - Menderico";
    gotoxy(40,21);
    cout << "Network and Electronics Transaction";
    gotoxy(40,22);
    cout << "              AMNET";
}


NODE* SystemRecord::enroll(){ //Login interface of the user
    system("cls");
    int i=5; //Variable declarations
    int accNum, pin, enteredPin, currentPin;
    string name;
    NODE* p;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // variable declaration to manipulate colors

    while (true) {
        welcome();              // prints the Logo and the Name of the ATM company
        gotoxy(40,25);
        cout << "\e[33m        INSERT YOUR CARD...\e[0m" << endl;
        Sleep(300);             // Adjust blinking speed by changing the sleep duration
        gotoxy(40,25);
        cout << "\e[32m        INSERT YOUR CARD...\e[0m" << endl;
        Sleep(300);             // Adjust blinking speed by changing the sleep duration

        if (GetDriveType("D://") == DRIVE_REMOVABLE) {  // if the path E: is found, or if the ATM is detected
        ifstream fp("D:/AMNET-CARD.txt");     // opens the file in read mode
            if (fp){                          // if file is found
            fp >> accNum;                     // reads the data inside the file
            fp >> pin;
            fp.close();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            p=search(accNum); //searches if the account number is registered in data base
            warningBox(28, 6, "\t\t  USER IS REGISTERED", "\n\t\t\t\t          WELCOME TO OUR BANK");
            system("cls");
            while (i!=0){ //asks the user to enter their pin to log in
            header("             ENTER PIN             ", 33, 3, 35);
            header("                                   ", 33, 6, 35);
            currentPin=inputPinInterface();
                if (currentPin!=decrypt(pin) && currentPin!=p->pin){ //compares the entered pin to the decrypted pin in the flashdrive
                    i--; //number of attempts left for the user
                    ostringstream oss;
                    oss << i;
                    string attempts = oss.str();
                    if (i==0){
                    return enroll();
                    }
                    warningBox(28, 6, "\t      WARNING: Incorrect password\t\t", "\n\t\t\t\t       You have "+ attempts +" attempt(s) left");
                    cin.ignore();
                    system("cls");
                }
                else
                    break;
            }
            break;
            }
            else { // if a file has not been created yet
            warningBox(28, 6, "\t\t  WELCOME TO OUR BANK", "\n\t\t\t\t    PLEASE PROCEED TO REGISTRATION");
            p = registerAcc();  // either returns a null, 0, or a pointer
                if (p==0){ //returns 0 if user presses esc
                messageBox(28, 6, "\t         REGISTRATION VOIDED \t    ", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
                p = registerAcc();
                }
                else if (p==NULL){ //returns null if all attempts are used
                warningBox(28, 6, "\t       TOO MANY FAILED ATTEMPTS", "\n\t\t\t\t  PLEASE PROCEED AGAIN TO REGISTRATION");
                p = registerAcc();
                }
                warningBox(28, 6, "\t\t         NOTICE\t\t", "\n\t\t\t\t  5000 PESOS HAS BEEN CREDITED TO YOUR \n\t\t\t\t        ACCOUNT UPON REGISTRATION");
                // Successfully registers the account if p is not null or 0
                messageBox(28, 6, "\t     ACCOUNT SUCCESSFULLY REGISTERED     ", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
                system("cls");
                break;
                }
            }
        }
    return p; //returns the pointer of the current user
    }

int SystemRecord::encrypt(int pin, int accNum) {
    // Variable Declarations
    int encryptedPin = 0;
    int multiplier= 1;

    while (pin > 0) {
        int digit = pin % 10;           // Extract the rightmost digit
        int asciiCode = digit + '0';    // Calculate the ASCII code
        encryptedPin = (asciiCode * multiplier) + encryptedPin; // Store the ASCII code in the variable
        multiplier *=100;   // increments the multiplier so that the next digit will be positioned on the right place value
        pin /= 10; // Move to the next digit
    }
    pin =encryptedPin; // stores the value of the encrypted pin
    ofstream of("D:/AMNET-CARD.txt");   // saves the encrypted pin
        of << accNum << "\n";
        of << pin << "\n";
        of.close();

    return encryptedPin;
}

int SystemRecord::decrypt(int pin) {
    int multiplier = 1;
    int decryptedPin=0;

    while (pin > 0) {
        int digit = pin % 100; // Extract the rightmost digit (ASCII code)
        int originalDigit = digit - '0'; // Convert ASCII code back to digit
        decryptedPin += originalDigit * multiplier;
        multiplier *= 10;   // multiply by ten since the ascii code is 2 digits
        pin /= 100; // Move to the next ASCII code
    }

    return decryptedPin;
}

NODE* SystemRecord::search(int n) { //Searches if the user is existing in the record or not
    NODE* currentNode = L; //sets the pointer to the head of the node
    while (currentNode != NULL) { //traverses through linked list NODE until the end
        if (n == currentNode->accNum){//breaks the loop and returns if passed n matches with one of the records
            return currentNode;} //returns the address of the node where the name is found
        else{
            currentNode = currentNode->next;} //Goes to the next node if not found and continue the while loop
    }
    return NULL; //Returns NULL if name is not found
}
NODE* SystemRecord::add(const string& n, int accNum, int currentBal, int pin, const string& address, const string& status, const string& sex, const string& birthday, const string& contact) { //To initialize and add the records of a new user

    NODE *p, *q, *newNode; //Accesses linkedlist NODE
    newNode = new NODE; //allocates new memory for the record
    // adds the user input value to the structure
    newNode->name = n; //Adds the new record to NODE and initializes the scores to zero
    newNode->accNum = accNum;
    newNode->currentBal = currentBal;
    newNode->pin = pin;
    newNode->address = address;
    newNode->status = status;
    newNode->sex = sex;
    newNode->birthday = birthday;
    newNode->contact = contact;
    newNode->next = NULL;

    if (L == NULL) { //If list is empty, initialize L to newNode;
        L = newNode;
    } else { //If list has records, find the end of the list to put new record
        p = L;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode; //pointer of the last node
    }

    return newNode; //Returns the address of the node where the new record is added
}
void SystemRecord::balanceInquiry(NODE* p){
    // DISPLAYS THE SAVINGS TEXT DISPLAY
    gotoxy(40,8);
    cout<<char(218);                        // upper left corner
    for(int i = 0; i < 40; i++)
        cout<<char(196);                    // upper right corner
    cout<<char(191);
    gotoxy(40,9);
    cout << char(179);
    gotoxy(55,9);
    cout << "   SAVINGS";
    gotoxy(81,9);
    cout << char(179);
    gotoxy(40,10);
    cout<<char(192);                 // create a corner border "└"
    for(int i = 0; i < 40; i++)      // a loop to create a horizontal line "─"
        cout<<char(196);
    cout<<char(217);
    gotoxy(40,11);
    cout<<char(218);                  // upper left corner
    for(int i = 0; i < 40; i++)
        cout<<char(196);              // upper right corner
    cout<<char(191);
    gotoxy(40,12);
    cout << char(179);
    gotoxy(42,12);
    cout << "Current Balance: " <<setw(21)<<right<< p->currentBal; // displays the current balance of the user
    gotoxy(81,12);
    cout << char(179);

    gotoxy(40,13);
    cout<<char(192);                // create a corner border "└"
    for(int i = 0; i < 40; i++)      // a loop to create a horizontal line "─"
        cout<<char(196);
    cout<<char(217);
    // back button
    gotoxy(53,15);
    cout<<char(218);                  // upper left corner
    for(int i = 0; i < 15; i++)
        cout<<char(196);              // upper right corner
    cout<<char(191);
    gotoxy(53,16);
    cout << char(179);
    gotoxy(55,16);
    cout << "BACK [ANY KEY]";
    gotoxy(69,16);
    cout << char(179);
    gotoxy(53,17);
    cout<<char(192);                 // create a corner border "└"
    for(int i = 0; i < 15; i++)      // a loop to create a horizontal line "─"
        cout<<char(196);
    cout<<char(217);
    getch();

    return;
}

void SystemRecord::withdraw(NODE* p){   // function to dispense a certain amount
        int amount, choice;
            header("    WITHDRAW MODE : ENTER AMOUNT   ", 33, 3, 35);   // header for withdraw
            header("                                   ", 33, 6, 35);
            amount = inputInterface(8); // calls inputInterface with actual argument of 8 so that it will only accept 7 input digit
        // Valid transactions: amount will not consume the maintaining balance and it shoukd be divisible by 100
        if (p->currentBal - amount >= MIN_BAL && amount%100==0 && amount>99){
           p->currentBal = p->currentBal - amount; // deduct the amount withdrawn to the current balance

            int currentBal = p->currentBal;
            ostringstream oss;
            oss << currentBal;
            string bal = oss.str();
            messageBox(28, 6, "\t          WITHDRAW SUCCESSFUL \t\t", "\n\t\t\t\t        Current balance: "+ bal +"\n\t\t\t\t        DO YOU WANT TO CONTINUE?");
        }
         else if (amount == stoi("0x1B", nullptr, 16)){ // returns to the main menu if input is equal to ESC
            return;
        }
        else if (amount%100!=0 && amount>-1 || amount == 0){ // prompts an invalid message if amount is not divisible by 100
            messageBox(28, 6, " INVALID AMOUNT: Multiple of 100 pesos only", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
        }
        else{   // if amount withdrawn consumes the maintaining balance
            messageBox(28, 6, "   Amount Exceeded the Maintaining balance \t    ", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
            }
            return;
    }

void SystemRecord::deposit(NODE* p){    // function to deposit certain amount to the account
    int amount, choice;
    header("    DEPOSIT MODE : ENTER AMOUNT    ", 33, 3, 35); // Header display to echo DEPOSIT MODE
    header("                                   ", 33, 6, 35);
    amount = inputInterface(8);
        if (amount%10==0 && amount>=20 && amount!=30){
            p->currentBal = amount + p->currentBal; // add the deposited amount to the current balance

            int currentBal = p->currentBal;
            ostringstream oss;
            oss << currentBal;
            string bal = oss.str();
            messageBox(28, 6, "\t          DEPOSIT SUCCESSFUL \t\t", "\n\t\t\t\t        Current balance: "+ bal +"\n\t\t\t\t        DO YOU WANT TO CONTINUE?");

            }
        else if (amount == stoi("0x1B", nullptr, 16)){  // returns to the main menu if the input is ESC
            return;
        }
        else{   // prompts invalid input if there is a coin input
            messageBox(28, 6, "  INVALID AMOUNT: Accepts paper bills only", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
            }
    return;
}

void SystemRecord::fundTransfer(NODE* p){       // function for transferring funds from the current user to an existing acccount
    int amount, choice, accNum;
    NODE *q;
    header("        ENTER ACCOUNT NUMBER       ", 33,3, 35);
    header("                                   ", 33,6, 35);
    accNum=inputInterface(6);                 // calls input interface with actual argument or 11 so that it will accept 10 digit inputs
    q=search(accNum);                          // search function returns the pointer of an existing account number

    if (accNum == stoi("0x1B", nullptr, 16)){   // returns to the main menu if input is equal to ESC
        return;
    }
    else if (q==NULL ){ // if search returns NULL, then there is no account existing with the inputted accNum
        messageBox(28, 6, "\t    Account number is not registered     ", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
    }

    else{ // enters the else condition if the above condition is not met
    header(" FUND TRANSFER MODE : ENTER AMOUNT ", 33, 3, 35);
    header("                                   ", 33, 6, 35);
    amount = inputInterface(8);

        if (p->currentBal - amount >= MIN_BAL && amount>-1){
            p->currentBal = p->currentBal - amount; // deduct the amount to the current balance of the current user
            q->currentBal=q->currentBal+amount; // adds the amount to the transferred account number, q holds the pointer to the inputted accNum

            int currentBal = p->currentBal;
            ostringstream oss;
            oss << currentBal;
            string bal = oss.str();
            messageBox(28, 6, "\t          TRANSFER SUCCESSFUL \t\t", "\n\t\t\t\t        Current balance: "+ bal +"\n\t\t\t\t        DO YOU WANT TO CONTINUE?");
        }
        else{
            messageBox(28, 6, "   Amount Exceeded the Maintaining balance \t    ", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
            }
        }
    return;
}
void SystemRecord::changePin(NODE* p){  // changes pin
    int pin, match, accNum, enteredPin, i=5; // i = 5 to limit how many times the user could have error attempts

    while(i!=0){
    system("cls");
    header("         ENTER CURRENT PIN         ", 33, 3, 35);
    header("                                   ", 33, 6, 35);
    enteredPin = inputPinInterface();   // interface for inputting pin

        ifstream fp("D:/AMNET-CARD.txt");    // reads the content of the card
            while (fp >> accNum) {
                    fp >> pin;
                }
            fp.close();
        pin=decrypt(pin);
        if (enteredPin == stoi("0x1B", nullptr, 16)){ // returns to the calling function if ESC is pressed
            i++;
            return;
        }
            else if (enteredPin != pin && enteredPin !=p->pin){ //If the password does not match to the existing record
            i--;
            ostringstream oss;
            oss << i;
            string attempts = oss.str();
            if (i==0){
                return;
            }
            warningBox(28, 6, "\t      WARNING: Incorrect password\t\t", "\n\t\t\t\t       You have "+ attempts +" attempt(s) left");
            cin.ignore();
        }
        else{ // code goes here if the above conditions are not met, it will proceed with enterin new pin
            system("cls");
            header("           ENTER NEW PIN           ", 33, 3, 35);
            header("                                   ", 33, 6, 35);
            pin =  inputPinInterface(); // stores the newly inputted pin code to variable pin

            if (pin == stoi("0x1B", nullptr, 16)){
            i++;
            return;
            }
            pin=encrypt(pin, accNum);
            ofstream of("D:/AMNET-CARD.txt"); // saves new pin to the file
                        of << accNum << "\n";
                        of << pin << "\n";
                        of.close();
            messageBox(28, 6, "\t        PIN successfully updated     ", "\n\t\t\t\t\t    DO YOU WANT TO \n\t\t\t\t\tCONTINUE TRANSACTION?");
            return;
            }
    }
}

int inputInterface(int digits) {
    int amount;
    char input[7], c;
    char values[] = "1234567890";
    int start = 48; //start of cursor in birthday
    int i = 0;   //counter for attempts
    int x = 40;  // Starting X position
    int y = 10;  // Y position

    for (int i = 0; i < 10; i++) { //Loop for printing all of the numbers with borders
        drawBox(x, y, values[i]);

        if (i == 2 || i == 5) {
            x = 40;  // Reset X position for the next row
            y += 3;  // Move to the next row
        }
        else if (i == 8){
            x = 48;
            y += 3;
        }
        else {
            x += 8;  // Adjust X for the next box
        }
    }
    drawBoxText(35, y+3, "[Backspace] Del"); //prints the option delete
    drawBoxText(52, y+3, "[Enter] Confirm"); //prints the option confirm
    drawBoxText(43, y+6, "[ESC] Back     "); //prints the option back

    while (i < digits && (c=getch()) != '\r' ){ //This gets the input of the user per character
        if ( c != '\b'){ //Prints the input of user if it is not backspace
            input[i++] = c; //Stores the input of the user into input array
            if (c=='\x1b'){
                return '\x1b';          // esc
            }
            else if(i==digits){ //else if statement to limit the number of digits
            i--;
            start--;
            cout << '\b';
            }
            else if (c == '1'){ //else if statements to light up the buttons
                green(1, 40, 10);
            }
            else if (c == '2'){
                green(2, 48, 10);
            }
            else if (c == '3'){
                green(3, 56, 10);
            }
            else if (c == '4'){
                green(4, 40, 13);
            }
            else if (c == '5'){
                green(5, 48, 13);
            }
            else if (c == '6'){
                green(6, 56, 13);
            }
            else if (c == '7'){
                green(7, 40, 16);
            }
            else if (c == '8'){
                green(8, 48, 16);
            }
            else if (c == '9'){
                green(9, 56, 16);
            }
            else if (c == '0'){
                green(0, 48, 19);
            }
            else{
                cout << '\b';           // wont display other string inputs aside 0-9
                i--;
                continue;
            }
        gotoxy(start++, 7); //places the cursor in the right position
        cout << c;
        }
        else if(i>0){ //removes characters when user presses backspace
            i--;
            start--;
            cout <<"\b \b";
        }
    }
    if(c=='\r' && i==0){
        return  inputInterface(digits);
    }
    input[i] = '\0';
    amount = stoi(input); //converts character input to integer amount
    return amount; //Returns the final amount input
}

void header(const string& text, int x, int y, int l){ //Drawing function that receives a string, x and y for gotoxy, and l for the length of the box
    gotoxy(x,y);
    cout << "\xDA";                         // create a corner "┌"
    for(int i = 0; i < l; i++)              // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xBF" << endl;
    gotoxy(x,y+1);
    cout << "\xB3" << text;                 //prints the passed string
    gotoxy(x+1+l, y+1);
    cout << "\xB3" << endl;
    gotoxy(x,y+2);
    cout << "\xC0";                         // create a corner border "└"
    for(int i = 0; i < l; i++)              // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xD9";                         // prints corner "┘"
}

void drawBoxText(int x, int y, const string& text) { //A smaller text box that receives x and y for gotoxy, and string text
    gotoxy(x,y);
    cout << "\xDA";                         // create a corner "┌"
    for(int i = 0; i < 15; i++)             // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xBF" << endl;
    gotoxy(x,y+1);
    cout << "\xB3" << text << "\xB3" << endl; //prints the text passed
    gotoxy(x,y+2);
    cout << "\xC0";                          // create a corner border "└"
    for(int i = 0; i < 15; i++)                 // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xD9"; // prints corner "┘"
}

void drawBox(int x, int y, char value) {    //this prints the buttons of the inputInterface, receives x and y for gotoxy
    gotoxy(x, y);
    cout << "\xDA\xC4\xC4\xC4\xC4\xC4\xBF";
    gotoxy(x, y + 1);
    cout << "\xB3  " << value << "  \xB3";  //Prints the number inside a box
    gotoxy(x, y + 2);
    cout << "\xC0\xC4\xC4\xC4\xC4\xC4\xD9";
}

void green(int num, int x, int y){          //This function lights up the buttons, receives int num which is the number that needs to be lit, receives x and y for gotoxy
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN); //sets the background to green
    gotoxy(x, y);
    cout << "       " << endl;
    gotoxy(x, y+1);
    cout << "   " << num << "   " << endl; //passed number of the button
    gotoxy(x, y+2);
    cout << "       " << endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //stops the green background
    Sleep (200); //determines the speed of the blink
    //this resets the background to its normal white text and black background
    gotoxy(x, y);
    cout << "\xDA\xC4\xC4\xC4\xC4\xC4\xBF";
    gotoxy(x, y + 1);
    cout << "\xB3  " << num << "  \xB3";
    gotoxy(x, y + 2);
    cout << "\xC0\xC4\xC4\xC4\xC4\xC4\xD9";
}

void SystemRecord::messageBox(int x, int y, const string& head, const string& message) { //This receives x and y for gotoxy, head for the header text and message for the main message
    int choice;
    system("cls");
    gotoxy(x,y);
    cout << "\xDA";
    for(int i = 0; i < 45; i++) // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xBF" << endl;
    gotoxy(x, y+1);
    cout << "\xB3                                             \xB3" << endl; //prints the side of the box
    gotoxy(x+2,y+1);
    cout << head; //prints the passed head text
    gotoxy(x, y+2);
    cout << "\xC3";
    for(int i = 0; i < 45; i++) // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xB4";
    for (int i = 3; i < 10; i++){
        gotoxy(x, y+i);
        cout << "\xB3                                             \xB3" << endl;} //prints the side of the box
    gotoxy(x+1,y+3);
    cout << message; //prints the passed head text
    gotoxy(x,y+10);
    cout << "\xC0"; // create a corner border "└"
    for(int i = 0; i < 45; i++) // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xD9"; // prints corner "┘"
    drawBoxText(x+6, y+7, "    [1] YES    ");
    drawBoxText(x+24, y+7, "    [2] NO     ");
    cout << "\n\n";

    do{choice =_getch(); //determines the choice of the user
    }while (choice != '1' && choice != '2');
            if (choice=='1'){
                return; //returns to main program when continue
            }else{

            upload();
            closing(); //closes and uploads the data manipulated
        }
}
//warning box only has one button [press any key to proceed]
void warningBox(int x, int y, const string& head, const string& message) { //Receives x and y for gotoxy, head for head text, and message for
    int choice;
    system("cls");
    gotoxy(x,y);
    cout << "\xDA";
    for(int i = 0; i < 45; i++) // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xBF" << endl;
    gotoxy(x, y+1);
    cout << "\xB3                                             \xB3" << endl;
    gotoxy(x+2,y+1);
    cout << head; //prints the header message
    gotoxy(x, y+2);
    cout << "\xC3";
    for(int i = 0; i < 45; i++) // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xB4";
    for (int i = 3; i < 10; i++){
        gotoxy(x, y+i);
        cout << "\xB3                                             \xB3" << endl;}
    gotoxy(x+1,y+3);
    cout << message; //prints the main message
    gotoxy(x,y+10);
    cout << "\xC0";                          // create a corner border "└"
    for(int i = 0; i < 45; i++)                 // a loop to create a horizontal line "─"
        cout << "\xC4";
    cout << "\xD9"; // prints corner "┘"
    drawBoxText(x+15, y+7, "[PRESS ANY KEY]");
    cout << "\n\n";

    getch(); //to proceed with any input from the user
    return;
}

void SystemRecord::download() { //Downloads the file from dbf to linked list
    string name, address, status, sex, birthday, contact; //all of the data stored in the structire
    int accNum, pin, currentBal;
    ifstream fp("AMNET-DATABASE"); //accesses the database to transfer it to the running program
    if (fp.fail()) {
        system("cls");
    } else {
        while (getline(fp, name)) { //transfers all of the data to the structure of running program
            fp >> accNum;
            fp >> currentBal;
            fp >> pin;
            fp.ignore();
            getline(fp, address);
            getline(fp, status);
            getline(fp, sex);
            getline(fp, birthday);
            getline(fp, contact);
            fp.ignore();
            add(name, accNum, currentBal, pin, address, status, sex, birthday, contact); //adds records to the data base every iteration
        }
        fp.close(); //closes file
    }
}

void SystemRecord::upload() { //Upload the file from linkedlist to dbf
    NODE* p;
    ofstream fp("AMNET-DATABASE"); //accesses the data base to transfer records from structure to dbf
    if (fp.fail()) {
        system("cls");
    } else {
        for (p = L; p != NULL; p = p->next) { //traverses until the end of the node while writing it to the dbf file
            fp << p->name << endl;
            fp << p->accNum << endl;
            fp << p->currentBal << endl;
            fp << p->pin<< endl;
            fp << p->address << endl;
            fp << p->status << endl;
            fp << p->sex << endl;
            fp << p->birthday << endl;
            fp << p->contact << endl << endl;

        }
        fp.close(); //closes the dbf file
    }
}

void SystemRecord::makeNull(){ //Initialized code to NULL
L = NULL; //Initializes L to NULL
}

NODE* SystemRecord::registerAcc() {
    string name, address, status, sex, birthday, contact;
    int choice, accNum, enteredPin, pin, counter, tempCount;
    int i=4;
    NODE* p;
    srand(static_cast<unsigned>(time(0))); //to generate the account number of every user uniquely

    system("cls"); //Prints the interface of the registration form by strings to function header
    header("\t       REGISTRATION FORM ", 37, 2, 35);
    header(" Name: ", 25, 5, 60);
    header(" Address: ", 25, 8, 60);
    header(" Contact Number: ", 25, 11, 60);
    header(" Civil Status: ", 25, 14, 19);
    header(" [PRESS 1] SINGLE ", 46, 14, 18);
    header(" [PRESS 2] MARRIED ", 66, 14, 19);
    header(" SEX: ", 25, 17, 6);
    header("[PRESS 1] MALE ", 33, 17, 15);
    header("[PRESS 2] FEMALE ", 50, 17, 17);
    header("[PRESS 3] OTHERS ", 69, 17, 16);
    header(" Birthday (MM/DD/YYYY):  __/__/____ ", 25, 20, 60);

    cout << "\e[33m"; header(" Name: ", 25, 5, 60); cout << "\e[0m"; //sets the box to yellow when time for input
    gotoxy(33, 6);
    getline(cin, name);
    cout << "\e[32m"; header(" Name: ", 25, 5, 60); cout << "\e[0m"; //sets to green when input is done

    cout << "\e[33m"; header(" Address: ", 25, 8, 60); cout << "\e[0m"; //sets the box to yellow when time for input
    gotoxy(36, 9);
    getline(cin, address);
    cout << "\e[32m"; header(" Address: ", 25, 8, 60); cout << "\e[0m"; //sets to green when input is done

    cout << "\e[33m"; header(" Contact Number: ", 25, 11, 60); cout << "\e[0m"; //sets the box to yellow when time for input
    gotoxy(43, 12);
    getline(cin, contact);
    cout << "\e[32m"; header(" Contact Number: ", 25, 11, 60); cout << "\e[0m"; //sets to green when input is done

    cout << "\e[33m"; header(" Civil Status:      ", 25, 14, 19);  //sets the box to yellow when time for input
    header(" [PRESS 1] SINGLE ", 46, 14, 18);
    header(" [PRESS 2] MARRIED ", 66, 14, 19); cout << "\e[0m";

    gotoxy(1, 1);
    do{choice =_getch();
    }while (choice != '1' && choice != '2'); //While loop to limit other inputs than 1 and 2, asks the user if single or married

            if (choice=='1'){
                header(" Civil Status:      ", 25, 14, 19); //resets other options to white
                header(" [PRESS 2] MARRIED ", 66, 14, 19);
                status = "SINGLE"; //assigns single to status
                cout << "\e[32m"; header(" [PRESS 1] SINGLE ", 46, 14, 18); cout << "\e[0m"; //sets to green when input is done
            }else{
                header(" Civil Status:      ", 25, 14, 19); //resets other options to white
                header(" [PRESS 1] SINGLE ", 46, 14, 18);
                status = "MARRIED"; //assigns married to status
                cout << "\e[32m"; header(" [PRESS 2] MARRIED ", 66, 14, 19); cout << "\e[0m"; //sets to green when input is done
        }

    cout << "\e[33m"; header(" SEX: ", 25, 17, 6); //sets the box to yellow when time for input
    header("[PRESS 1] MALE ", 33, 17, 15);
    header("[PRESS 2] FEMALE ", 50, 17, 17);
    header("[PRESS 3] OTHERS ", 69, 17, 16); cout << "\e[0m"; //sets to green when input is done

    gotoxy(1, 1);
    do{choice =_getch();
    }while (choice != '1' && choice != '2' && choice != '3'); //While loop to limit other inputs than 1, 2, and 3, asks the user if male, female, or others

            if (choice=='1'){ //assigns male to sex
                header(" SEX: ", 25, 17, 6);  //resets other options to white
                header("[PRESS 2] FEMALE ", 50, 17, 17);
                header("[PRESS 3] OTHERS ", 69, 17, 16);
                sex = "MALE";
                cout << "\e[32m"; header("[PRESS 1] MALE ", 33, 17, 15); cout << "\e[0m"; //sets to green when input is done
            }else if (choice =='2'){ //assigns female to sex
                header(" SEX: ", 25, 17, 6);  //resets other options to white
                header("[PRESS 1] MALE ", 33, 17, 15);
                header("[PRESS 3] OTHERS ", 69, 17, 16);
                sex = "FEMALE";
                cout << "\e[32m"; header("[PRESS 2] FEMALE ", 50, 17, 17); cout << "\e[0m"; //sets to green when input is done
            }else{ //assigns others to sex
                header(" SEX: ", 25, 17, 6);  //resets other options to white
                header("[PRESS 2] FEMALE ", 50, 17, 17);
                header("[PRESS 1] MALE ", 33, 17, 15);
                sex = "OTHERS";
                cout << "\e[32m"; header("[PRESS 3] OTHERS ", 69, 17, 16); cout << "\e[0m"; //sets to green when input is done
            }

    cout << "\e[33m"; header(" Birthday (MM/DD/YYYY):  __/__/____ ", 25, 20, 60); cout << "\e[0m"; //sets the box to yellow when time for input
    gotoxy(51,21);
    getline(cin, birthday);
    cout << "\e[32m"; header(" Birthday (MM/DD/YYYY):", 25, 20, 60); cout << "\e[0m"; //sets to green when input is done

    gotoxy(75, 23);
    header(" PRESS ANY KEY TO TO CONTINUE ", 55, 23, 30);
    getch();

    while(i!=0){ //while loop for password input
    system("cls");

    while(true){
        header("        ENTER 4-DIGIT PIN          ", 33, 3, 35); //header for password input
        header("                                   ", 33, 6, 35); //box for user input
        enteredPin = inputPinInterface(); //Calls inputPinInterface which returns the value of the entered pin
        if (enteredPin == stoi("0x1B", nullptr, 16)){ //if statement if the user presses esc to back
            i++;
            return 0;
        }
        tempCount = enteredPin; //tempCount for counting the digits
        counter = 0;
        while (tempCount !=0){ //while loop
        tempCount /=10;
        counter++;
        }
        if (counter != 4){ //If the pin is not match to the existing record
            i--; //reduces the attempts of the user
            ostringstream oss;
            oss << i;
            string attempts = oss.str();
            if(i==0){
                return NULL; //returns to the calling function when attempts are all used
            }
            warningBox(28, 6, "\t         WARNING: Incorrect pin\t\t", "\n\t\t\t\t       You have "+ attempts +" attempt(s) left"); //warning box for prompt message on how many attempts left
            system("cls");
        }else{ //enters else statement and break if all pin requirements are met
            break;
        }
    }
    i=4;
    while(true){
        header("            CONFIRM PIN            ", 33, 3, 35); //header for confirm pin
        header("                                   ", 33, 6, 35); //box for user input
        pin = inputPinInterface(); //Calls inputPinInterface which returns the value of the entered pin
        if (pin == stoi("0x1B", nullptr, 16)){ //if statement if the user presses esc to back
            //i++;
            return 0;
        }
        if (pin != enteredPin){ //If the pin is not match to the existing record
            i--; //reduces the attempts of the user
            ostringstream oss;
            oss << i;
            string attempts = oss.str();
            if(i==0){
                return NULL; //returns to the calling function when attempts are all used
            }
            warningBox(28, 6, "\t      WARNING: Incorrect password\t\t", "\n\t\t\t\t       You have "+ attempts +" attempt(s) left"); //warning box for prompt message on how many attempts left
            system("cls");
        }else{ //enters else statement and break if all pin requirements are met
            break;
        }
    }

    do { //randomizes the account number of the user
            accNum = 10000 + rand() % 90000;
            p = search(accNum); //searches if the accnum generated is existing
        if (p == NULL) { //writes the accnum if it is unique
        ofstream fp("D:/AMNET-CARD.txt", ios::app); // opens the file in write mode
                    fp << accNum; // writes accNum to the flashdrive file
                    fp.close(); // close the file

                    break;
        } else {continue;}
            } while (true);

            pin=encrypt(pin, accNum); //encrypts the pin
            ofstream of("D:/AMNET-CARD.txt"); //writes the pin and accnum
                        of << accNum << "\n";
                        of << pin << "\n";
                        of.close();

            add(name, accNum, MIN_BAL, pin, address, status, sex, birthday, contact); //adds the input data in registration to the structure

            p = search(accNum); //searches the pointer of the current user
            return p; //returns the pointer of the current user
    }
        return 0;
}

int inputPinInterface() { //interface for all pin transactions
    int pin;
    char input[4], c;
    int start = 48;
    int i = 0;
    int x = 40;  // Starting X position
    int y = 10;  // Y position
    //prints the options for the user
    drawBoxText(35, y+3, "[Backspace] Del");
    drawBoxText(52, y+3, "[Enter] Confirm");
    drawBoxText(43, y+6, "[ESC] Back     ");

    while ( i < 5 && (c=getch()) != '\r' ){ //converts the pin to asterisk when printing
        if ( c != '\b'){
            input[i++] = c;
                if (c=='\x1b'){
                return '\x1b';          // returns to the calling function when esc is pressed
                }
                else if(i==5){ //limits the number of digits
                i--;
                start--;
                cout << "\b";
                }
                else if (c!='1' && c!='2' && c!='3' && c!='4' && c!='5' && c!='6' && c!='7' && c!='8' && c!='9' && c!='0'){
                cout << '\b';           // wont display other string inputs aside 0-9
                i--;
                continue;
                }
        gotoxy(start++, 7);
        cout << "*"; //displays asterisk for every character
        }
        else if (i>0){ //if user presses backspace, delete a character
            i--;
            start--;
            printf("\b \b");
        }
    }
    if(c=='\r' && i==0){
        return inputPinInterface();
    }
    input[i] = '\0';
    pin = stoi(input); //converts characters to integer
    return pin; //returns the pin input
}










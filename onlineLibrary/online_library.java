package com.company;
import java.util.Scanner;
import java.util.Random;
import static java.lang.Thread.sleep;

class library{
    private String[] books = new String[100];
    private int totalNoOfBooks;
    public int noOfBooks;
    private int adminPin = 1972;
    //public int tryToUnlock;
    private int options;
    private int issueOptions;
    private String name;
    private String[] issueDataBook = new String[100];
    private boolean issueStatus = false;
    private int noOfIssue = 0;
    private int returnOptions;
    private int noOfReturns;
    private int fixNoOfIssue;

    public library(){
        this.books[0] = "Algorithm for Beginners";
        this.books[1] = "C++ Advanced Level";
        this.books[2] = "Java for Beginners";
        this.books[3] = "Python Programming";
        this.books[4] = "Physics Wallah Module";
        this.books[5] = "JavaScript Advanced Programming";
        this.books[6] = "S Chand - 12";
        this.books[7] = "S.L. Arora";

        this.noOfBooks = 8;
        this.totalNoOfBooks = 8;
        Scanner name = new Scanner(System.in);
        System.out.print("Enter your name : ");
        this.name = name.nextLine();
        System.out.println(" ");
    }

    public void selectOptions() throws InterruptedException{
        System.out.println("\uD83D\uDD34 NOTE : Access Library by using following options : ");
        System.out.println("                                            \uD83D\uDD38 1 for Available Books");
        System.out.println("                                            \uD83D\uDD38 2 for Add Book");
        System.out.println("                                            \uD83D\uDD38 3 for Request Book");
        System.out.println("                                            \uD83D\uDD38 4 for Issue Book");
        System.out.println("                                            \uD83D\uDD38 5 for Return Issued Book");
        System.out.println("                                            \uD83D\uDD38 6 for Admin Panel Access");
        System.out.println(" ");

        Scanner Options = new Scanner(System.in);
        System.out.print("Select the options : ");
        this.options = Options.nextInt();
        System.out.println(" ");
        int totalOptions = 6;
        if (options <= totalOptions && options > 0){
            switchCase();
        } else {
            System.out.println("❌ Wrong Option selected");
            System.out.println(" ");
            selectOptions();
        }
    }

    public void switchCase() throws InterruptedException {
        switch (options){
            case 1 -> availableBooks(true);
            case 2 -> addBook(false, "no");
            case 3 -> requestBook(true);
            case 4 -> issueBook();
            case 5 -> returnBookInfo();
            case 6 -> adminPanel();
            default -> {
                System.out.println("❌ Error Found ❌");
                System.out.println(" ");
                selectOptions();
            }
        }
    }

    public void allBooks(String arr, boolean bookCheck){
        if (bookCheck) {
            this.books[noOfBooks] = arr;
        } else {
            this.books[totalNoOfBooks] = arr;
        }
    }

    public void availableBooks(boolean checkAvailability) throws InterruptedException{
        System.out.println("\uD83D\uDCDA Available Books : ");
        int serialNo = 1;
        for ( String studyMaterial : books){
            if (studyMaterial == null){
                continue;
            } else {
                System.out.println("      " + serialNo + ") " + studyMaterial);
                serialNo++;
            }
        }
        if (checkAvailability) {
            System.out.println(" ");
            selectOptions();
        } else {
            System.out.println(" ");
        }
    }
    public void addBook(boolean securityCheck,String amanBook) throws InterruptedException{
        boolean lockCheck = adminLock(securityCheck);
        if ( lockCheck && !securityCheck) {
            String newBook = bookName();
            allBooks(newBook,true);
            System.out.println("Adding Book....................");
            sleep(1500);
            System.out.println("Book '" + books[noOfBooks] + "' added Successfully ✅");
            System.out.println(" ");
        } else if (lockCheck && securityCheck) {
            String newBook = amanBook;
            allBooks(newBook,true);
            System.out.println("Adding Book....................");
            sleep(1500);
            System.out.println("Book '" + books[noOfBooks] + "' added Successfully ✅");
            System.out.println(" ");
        } else {
            System.out.println("Adding Book...................");
            sleep(1500);
            System.out.println("Adding a new Book '" + books[noOfBooks] + "' Failed ❌");
            System.out.println(" ");
        }
        noOfBooks++;
        totalNoOfBooks++;
        selectOptions();
    }

    public void requestBook(boolean check2) throws InterruptedException {
        System.out.println("\uD83D\uDFE2 NOTE : Enter the correct book name , if it is available then it will be added " +
                "by admin , otherwise your request will be denied.");
        String requestNewBook = bookName();
        System.out.println("\uD83D\uDDA5\uFE0F Requesting....................");
        sleep(1500);
        Random rand = new Random();
        int requestRandom = rand.nextInt(2);
        if ( requestRandom == 0 ){
            System.out.println("Admin Declined ❌ your Request");
            System.out.println(" ");
        } else if ( requestRandom == 1 ) {
            System.out.println("Admin Approved ✅ your Request");
            System.out.println("\uD83D\uDDA5\uFE0F Processing.................");
            sleep(1500);
            addBook(check2 , requestNewBook);
        } else {
            System.out.println("❌ Error Found ❌");
            System.out.println(" ");
        }
        selectOptions();
    }

    public String bookName(){
        Scanner bookName = new Scanner(System.in);
        System.out.print("Enter the Book Name : ");
        String BookName = bookName.nextLine();
        return BookName;
    }

    public void issueBookData(String issueBookName){
        this.issueDataBook[noOfIssue] = issueBookName;
    }

    public void selectIssueOptions() throws InterruptedException{
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the Book number : ");
        int issueTimePass = sc.nextInt();
        int totalBooksCount = noOfBooks + 1;

        if (issueTimePass <= totalBooksCount){
            this.issueOptions = issueTimePass;
        } else {
            System.out.println("❌ Wrong Number entered ❌");
            System.out.println(" ");
            selectOptions();
        }
    }
    public void issueBookInfo() throws InterruptedException{
        availableBooks(false);
        System.out.println("\uD83D\uDFE2 NOTE : Hey "+name+" , suppose if you want to issue 'C++ Advanced Level' " +
                "then you have to enter number '2'");
        //String issueBookName = bookName();
    }

    public void issueBook() throws InterruptedException{
        if (issueStatus){
            System.out.println("\uD83D\uDFE2 NOTE : "+name+" , you have already issued "+noOfIssue+" book." +
                    "\nSo we have to request to the Admin to issue next one , otherwise return the first one then issue new one");
            System.out.println("Requesting....................");
            sleep(1500);
            Random sc = new Random();
            int issueCheck = sc.nextInt(3);

            if ( issueCheck == 0 || issueCheck == 2 ){
                System.out.println("❌ Admin declined to issue another book");
                System.out.println(" ");
                selectOptions();
            } else {
                System.out.println("✅ Admin accepted your request to issue");
                System.out.println(" ");
                this.issueStatus = false;
                issueBook();
            }
        } else {
            issueBookInfo();
            selectIssueOptions();
            String issueBookName = books[issueOptions-1];
            System.out.println("Processing....................");
            sleep(1500);
            System.out.println("Issuing........................");
            sleep(1500);
            System.out.println("✅ " + name + " , you have successfully issued '" + issueBookName + "'");
            books[issueOptions-1] = null;
            String temp = books[issueOptions-1];
            books[issueOptions-1] = books[noOfBooks-1-noOfIssue];
            books[noOfBooks-1-noOfIssue] = temp;
            issueBookData(issueBookName);
            System.out.println(" ");
            this.issueStatus = true;
            this.noOfIssue = noOfIssue + 1;
            this.fixNoOfIssue = fixNoOfIssue+1;
            this.totalNoOfBooks = totalNoOfBooks -1;
            selectOptions();
        }
    }

    public void returnBookInfo() throws InterruptedException{
        if ( noOfIssue == 0 ){
            System.out.println("❌ No Book Issued ❌");
            System.out.println(" ");
            selectOptions();
        } else if ( noOfIssue > 0 && noOfIssue < 100 ){
            System.out.println("✅ Number of Issued Book : "+noOfIssue);
            System.out.println("\uD83D\uDCDA Issued Book are as follow : ");
            int serial = 1;
            for ( String availableReturnBook : issueDataBook){
                if ( availableReturnBook == null ){
                    continue;
                } else {
                    System.out.println("      "+serial+") "+availableReturnBook);
                    serial++;
                }
            }
            System.out.println(" ");
            System.out.println("\uD83D\uDFE2 NOTE : Hey "+name+" , suppose you want to return 1st book " +
                    "then you have to enter '1'");
            returnBookOptions();
        } else {
            System.out.println("❌ Error Found ❌");
            System.out.println(" ");
            selectOptions();
        }
    }

    public void returnBookOptions() throws InterruptedException{
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the Issued Book number : ");
        this.returnOptions = sc.nextInt();
       if ( returnOptions > 0 && returnOptions <= noOfIssue){
           returnBook();
       } else {
           System.out.println("❌ Wrong issued book number entered ❌");
           System.out.println(" ");
           selectOptions();
       }
    }

    public void returnBook() throws InterruptedException{
        if ( returnOptions-1 == fixNoOfIssue-1-noOfReturns){
            String returnTimePassName = issueDataBook[returnOptions-1];
            this.noOfIssue = noOfIssue - 1;
            System.out.println("Processing....................");
            sleep(1500);
            System.out.println("Returning........................");
            sleep(1500);
            System.out.println(name + " , you have successfully returned the book '"+returnTimePassName+"' ");
            allBooks(returnTimePassName,false);
            this.totalNoOfBooks++;
            noOfReturns++;
        } else {
            String returnTimePassName = issueDataBook[returnOptions - 1];
            issueDataBook[returnOptions - 1] = null;
            String temp = issueDataBook[returnOptions - 1];
            issueDataBook[returnOptions - 1] = issueDataBook[fixNoOfIssue - 1 - noOfReturns];
            issueDataBook[fixNoOfIssue - 1 - noOfReturns] = temp;
            this.noOfIssue = noOfIssue - 1;
            System.out.println("Processing....................");
            sleep(1500);
            System.out.println("Returning........................");
            sleep(1500);
            System.out.println(name + " , you have successfully returned the book '" + returnTimePassName + "' ");
            allBooks(returnTimePassName,false);
            this.totalNoOfBooks++;
            noOfReturns++;
            selectOptions();
        }
        issueDataBook[returnOptions-1] = null;
        selectOptions();
    }

    public void adminPanel() throws InterruptedException{
        System.out.println("✅ Coming Soon ✅");
        selectOptions();
    }

    public boolean adminLock(boolean requestCheck) throws InterruptedException{
        int userPin;
        int tryToUnlock = 0;
        Scanner lock = new Scanner(System.in);
        if (requestCheck){
            return true;
        } else {
            System.out.println("\uD83D\uDD34 NOTE : "+name+" , you are trying to access Admin features." +
                    " Pls enter Admin Pin to access it.");
            for ( int i = tryToUnlock ; i < 3 ; i++ ){
                System.out.print("Enter Admin Pin : ");
                userPin = lock.nextInt();
                if ( userPin == adminPin ){
                    System.out.println("\uD83D\uDDA5\uFE0F Scanning....................");
                    sleep(1500);
                    System.out.println("✅ Admin Panel Unlocked ✅");
                    System.out.println(" ");
                    return true;
                } else {
                    System.out.println("\uD83D\uDDA5\uFE0F Scanning....................");
                    sleep(1500);
                    System.out.printf("\uD83D\uDFE2 NOTE : You have %d more chances to Unlock",3 - (++tryToUnlock));
                    System.out.println(" ");
                    System.out.println(" ");
                }
            }
        }
        System.out.println("❌ Access Denied ❌");
        System.out.println(" ");
        selectOptions();
        return false;
    }
}
public class online_library {

    public static void main(String[] args) throws InterruptedException {

        /*
        You have to implement a library using Java Class "Library"
        Methods: addBook, issueBook, returnBook, showAvailableBooks
        Properties: Array to store the available books ✅,
        Array to store the issued books
        */
        library deadcraft = new library();
        deadcraft.selectOptions();

    }
}


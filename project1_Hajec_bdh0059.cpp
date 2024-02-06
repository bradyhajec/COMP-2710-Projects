//Author: Brady Hajec
//Name: project1_Hajec_bdh0059.cpp
//Auburn ID: bdh0059@auburn.edu
//To Compile: g++ project1_Hajec_bdh0059.cpp
//This program returns a sheet displaying information on how long a user will need to pay off a loan
//I used a BroCode Youtube Video called "C++ Full Course for Free" to learn the basic syntax of C++
//I used a BroCode Youtube Video called "C++ Full Course for Free" to understand how to use loops and variable initalizations in C++
//I used the hints document for the various sections throughout the code
/*used chatGPT in correspondance with Stack Overflow and conversations with Shelby Hampton
*to figure out how to clear the invalid inputs 
*of non-integer values from the input buffer so I didnt have infinite loop
*/



#include <iostream>
/*by adding namespace std, it is not needed 
* to include it in front of statements such as std::cout
*/
using namespace std;


//main is the entry point of the porgram
int main() {

    // VARIABLE INITIALIZATION

    /*Variables
    *Loan Amount 
    *Interest Rate
    *Monthy Payments
    */

    double loanAmount = -1;

    //is the user inputted interest, the rate as a decimal value for calulations, and the amount of interest calculated 
    double interestRate = -1;
    double interestRatePercent;
    double interestAmt;
    double totalInterestPaid;

    double monthyPayments = -1;

    //month variable will be incremented as payments are made 
    int month;
    double principal;

    // CURRENCY FORMATTING
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // USER INPUT
    // NOTE: For valid input, the loan, interest, and monthly payment must
    // be positive. The monthly payment must also be large enough to
    // terminate the loan.

    //This checks to make sure the loan is a positive amount, keeps prompting use until one is entered
    while (loanAmount <= 0) {
        cout << "Loan Amount: ";
        cin >> loanAmount;
        /*
        *the methods such as fail() and clear() were found using stack overflow along with
        *explainations from chat GPT and Shelby Hamptonto implement them correctly to deal with non-integer inputs
        */
        if (cin.fail()) {
            cin.clear();
            //discards the invalid characters in the buffer 
            while (cin.get() != '\n') {
                continue;
            }
            loanAmount = -1;
        }
        if (loanAmount <= 0) {
            cout << "Invalid Loan Amount" << endl;
        }
    }

    //this checks to make sure that the interest rate is a positive amount
    while (interestRate < 0) {
        cout << "Interest Rate (% per year): ";
        cin >> (interestRate);
        
        /*
        *the methods such as fail() and clear() were found using stack overflow along with
        *explainations from chat GPT and Shelby Hampton to implement them correctly to deal with non-integer inputs
        */
        if (cin.fail()) {
            cin.clear();
            //discards the
            while (cin.get() != '\n') {
                continue;
            }
            interestRate = -1;
        }
        if (interestRate < 0) {
            cout << "Invalid Interest Rate" << endl;
        }
    }
    
    //calculation for interest rate
    interestRate /= 12;
    interestRatePercent = interestRate / 100;

    //left side of OR checks to make sure that the monthy payment is a positive amount
    //right side of OR checks to make sure the the monthy payment is not less than monthly interest
    while (monthyPayments <= 0 || monthyPayments <= (loanAmount * (interestRatePercent))) {
        cout << "Monthly Payments: ";
        cin >> monthyPayments;
        
        /*
        *the methods such as fail() and clear() were found using stack overflow along with
        *explainations from chat GPT and Shelby Hampton to implement them correctly to deal with non-integer inputs
        */
        if (cin.fail()) {
            
            cin.clear();
            //discards the
            while (cin.get() != '\n') {
                continue;
            }
            cout << "Invalid Payment" << endl;
            monthyPayments = -1;
        }
        if (monthyPayments <= 0 || monthyPayments <= (loanAmount * (interestRatePercent))){
            cout << "Invalid Monthly Payment" << endl;
        }
    }

    //create a new line and flush buffer
    cout << endl;

    // AMORTIZATION TABLE
    cout << "*****************************************************************\n"
    << "\tAmortization Table\n"
    << "*****************************************************************\n"
    << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";


    //while loop that outputs the calculations for monthly payments until the loan is paid off
    while (loanAmount > 0) {

        //this is the first case when no payments have been made and its in the first month
        if (month == 0) {
            cout << month++ << "\t$" << loanAmount;
            if (loanAmount < 1000) cout << "\t"; // Formatting MAGIC
                cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
        }
        //this is where the calculations for the loan and payments will be made 
        else {

            //this is if the loan plus interest is less than monthly payment 
            if (loanAmount * (1 + interestRatePercent) < monthyPayments) {
                                
                //is the loan owed before interest is applied 
                principal = loanAmount;
                //if the loan is less than the usual monthly payment, the next payment is the same as the loan
                interestAmt = loanAmount * interestRatePercent;
                //monthly payment for when loan plus interest is less than usual monthly payment
                monthyPayments = loanAmount + interestAmt; 
                //should equal zero when subtracted from priciple
                loanAmount = loanAmount - principal;
                //adding to total interest paid
                totalInterestPaid += interestAmt;
            }

            //this else is for the general case when the loan plus interest is greater than monthly payments
            else {
                
                //calculating the amount of interest owed
                interestAmt = loanAmount * interestRatePercent;
                //calculating the principle which is the amount owed after interest is paid
                principal = monthyPayments - interestAmt;
                //new loan amount after the principal is subtracted from total
                loanAmount = loanAmount - principal;
                ///adding to total interest paid
                totalInterestPaid += interestAmt;
            }

            //output the values for the chart as calculated above
            //if else statement is for formatting
            if (loanAmount >= 1000){
                cout << month << "\t$" << loanAmount << "\t$" << monthyPayments << "\t" << interestRate << "\t$" << interestAmt << "\t\t$" << principal << "\n";
            }
            else {
                 cout << month << "\t$" << loanAmount << "\t\t$" << monthyPayments << "\t" << interestRate << "\t$" << interestAmt << "\t\t$" << principal << "\n";
 
            }
            month++;

        }

        
    }

    //final summary of information
    cout << "****************************************************************\n";
    cout << "\nIt takes " << --month << " months to pay off "
    << "the loan.\n"
    << "Total interest paid is: $" << totalInterestPaid;
    cout << endl << endl;

    //lets main know it executed all the way
    return 0;
}


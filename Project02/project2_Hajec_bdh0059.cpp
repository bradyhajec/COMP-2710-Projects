//Author: Brady Hajec
//Name: project2_Hajec_bdh0059.cpp
//Auburn ID: bdh0059@auburn.edu
//To Compile: g++ project2_Hajec_bdh0059.cpp
//This program is a duel simulator that takes advantages of random numbers and various test cases
//I used a BroCode Youtube Video called "C++ Full Course for Free" to learn about random number generators
//I used a BroCode Youtube Video called "C++ Full Course for Free" to learn points and call by reference
//conversed with Shelby Hampton throughout to clairfy topics such as where to initalize srand(time(0))
//conversed with Shelby Hampton about having methods return an int so that they could be tested with assert
//used chatGPT to ask where srand(time(0)) was suppose to be declared
//asked chatGPT if it was possible to impletement methods above main rather than declaring prototypes since C++ is prodecureal call


# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>

using namespace std;

//CONSTANT DELCARATION
const int NUM_DUELS = 10000; 
const double aaron_accuracy = 33.3333;
const double bob_accuracy = 50;
const double charlie_accuracy = 100;

//method implementations 

//function to pause while testing 
void to_continue() {
    "Press any Enter to continue...";
    cout << "Press Enter to continue...";
    cin.ignore().get(); //Pause Command for Linux Terminal  
}

//method to shoot at target
bool shot_success(double accuracy) {

    int shot_Fired = rand() % 100;

    if (shot_Fired < accuracy) {
        return true;
    }

    return false;
}

//check to see if there are 2 people alive to continute the duels
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {

     return A_alive && B_alive || A_alive && C_alive || B_alive && C_alive;

}

//following methods use call by referece to change the status of the players if they are shot
int Aaron_shoots1(bool& B_alive, bool& C_alive) {

    if (C_alive) {
        if (shot_success(aaron_accuracy)) {
            C_alive = false;
        }
        //indicated that C_alive was checked and choosen
        return 3;
    }
    else if (B_alive) {
        if (shot_success(aaron_accuracy)) {
            B_alive = false;
        }
        //indicated that B_alive was choose bc B alive and C dead
        return 2;
    }

    return 0;
}

int Bob_shoots(bool& A_alive, bool& C_alive) {

    if (C_alive) {
        if (shot_success(bob_accuracy)) {
            C_alive = false;
        }
        //indicated that C_alive was checked and choosen
        return 3;
    }
    else if (A_alive) {
        if (shot_success(bob_accuracy)) {
            A_alive = false;
        }
        //indicated that B_alive was choose bc B alive and C dead
        return 1;
    }

    return 0;
}

int Charlie_shoots(bool& A_alive, bool& B_alive) {

    if (B_alive) {
        if (shot_success(charlie_accuracy)) {
            B_alive = false;
        }
        //indicated that C_alive was checked and choosen
        return 2;
    }
    else if (A_alive) {
        if (shot_success(charlie_accuracy)) {
            A_alive = false;
        }
        //indicated that B_alive was choose bc B alive and C dead
        return 1;
    }

    return 0;
}

int Aaron_shoots2(bool& B_alive, bool& C_alive) {
    
    //if they are both alive its still round 1 and need to miss the shot
    if (B_alive && C_alive) {
        //return without shooting
        return 0;
    }
    else {
        return Aaron_shoots1(B_alive, C_alive);
    }
}

//method that simulates the duel
int duel_sim(int strategy) {

    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;

    //duel commences if there is still more than one person alive
    while (at_least_two_alive(A_alive, B_alive, C_alive)) {

        //if Aaron is alive he shoots first
        if (A_alive) {
            if (strategy == 2) {
                Aaron_shoots2(B_alive, C_alive);
            }
            else if (strategy == 1) {
                Aaron_shoots1(B_alive, C_alive);
            }
        }
        //if Bob is alive he shoots next 
        if (B_alive) {
            Bob_shoots(A_alive, C_alive);
        }
        //if C is alive he shoots last
        if (C_alive) {
            Charlie_shoots(A_alive, B_alive);
        }
    }

    //if there are not at least two alive, there is only one
    if (A_alive) {
        return 1;
    } 
    else if (B_alive) {
        return 2;
    }
    else {
        return 3;
    }

}

void better_strat(int wins1, int wins2){

    if (wins2 > wins1) {
        cout << "\nStrategy 2 is better than Strategy 1\n";
    }
    else if (wins1 >  wins2) {
        cout << "\nStrategy 2 is better than Strategy 1\n";

    }
    else {
        cout << "\nStrategies 1 and 2 has the same result for Aaron\n";
    }

}

//test case declarations
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots1(void);
void test_Charlie_shoots1(void);
void test_Aaron_shoots2(void);

int run_duel_sim(int strategy);

//main method to call the tests
int main() {

    //random number generator declaration in main so that it is seeded only once during execution 
    srand(time(0));

    cout << "*** Welcome to Brady's Duel Simulator ***\n";

    //alive status delcared in test methods
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots1();  
    test_Charlie_shoots1();
    test_Aaron_shoots2();  


    //duel sim
    int wins1 = run_duel_sim(1);
    int wins2 = run_duel_sim(2);
    
    better_strat(wins1, wins2);

    return 0;

}

/* Implementation of the test driver for at_least_two_alive() */
void test_at_least_two_alive(void) {

    cout << "Unit Testing 1: Function - at_least_two_alive()\n";

    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";

    to_continue();

}

/* Implementation of the test driver for test_Aaron_shoots1() */
void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";

    
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool C_alive = true;
    bool B_alive = true;
    assert(3 == Aaron_shoots1(B_alive, C_alive));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    C_alive = true;
    B_alive = false;
    assert(3 == Aaron_shoots1(B_alive, C_alive));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    C_alive = false;
    B_alive = true;
    assert(2 == Aaron_shoots1(B_alive, C_alive));
    cout << "\t\tAaron is shooting at Bob\n";

    to_continue();


}

/* Implementation of the test driver for test_Bob_shoots1() */
void test_Bob_shoots1(void) {
    cout << "Unit Testing 3: Function Bob_shoots1(Aaron_alive, Charlie_alive)\n";

    
    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    bool C_alive = true;
    bool A_alive = true;
    assert(3 == Bob_shoots(A_alive, C_alive));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    C_alive = true;
    A_alive = false;
    assert(3 == Bob_shoots(A_alive, C_alive));
    cout << "\t\tBob is shooting at Charlie\n";

    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    C_alive = false;
    A_alive = true;
    assert(1 == Bob_shoots(A_alive, C_alive));
    cout << "\t\tBob is shooting at Aaron\n";

    to_continue();


}

/* Implementation of the test driver for test_Charlie_shoots1() */
void test_Charlie_shoots1(void) {

    cout << "Unit Testing 4: Function Charlie_shoots1(Aaron_alive, Bob_alive)\n";

    
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    bool A_alive = true;
    bool B_alive = true;
    assert(2 == Charlie_shoots(A_alive, B_alive));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 2: Aaron dead, Bob alive\n";
    A_alive = false;
    B_alive = true;
    assert(2 == Charlie_shoots(A_alive, B_alive));
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 3: Aaron alive, Bob dead\n";
    A_alive = true;
    B_alive = false;
    assert(1 == Charlie_shoots(A_alive, B_alive));
    cout << "\t\tCharlie is shooting at Aaron\n";

    to_continue();


}

/* Implementation of the test driver for test_Aaron_shoots2() */
void test_Aaron_shoots2(void) {

    cout << "Unit Testing 5: Function Aaron_shoots5(Bob_alive, Charlie_alive)\n";

    
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool C_alive = true;
    bool B_alive = true;
    assert(0 == Aaron_shoots2(B_alive, C_alive));
    cout << "\t\tAaron intentionally misses his first shot\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    C_alive = true;
    B_alive = false;
    assert(3 == Aaron_shoots2(B_alive, C_alive));
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    C_alive = false;
    B_alive = true;
    assert(2 == Aaron_shoots2(B_alive, C_alive));
    cout << "\t\tAaron is shooting at Bob\n";

}

/* Implementation of the test driver that runs the duel_sim() method */
int run_duel_sim(int strategy) {

    cout << "\nReady to test strategy " << strategy << " (run 10000 times):\n";
    to_continue();

    int duel_winner;
    int a_total = 0, b_total = 0, c_total = 0;

    if (strategy == 1) {
        for (int i = 0; i < NUM_DUELS; i++) {
            duel_winner = duel_sim(1);
            if (duel_winner == 1) {
                a_total += 1;
            }
            if (duel_winner == 2) {
                b_total += 1;
            }
            if (duel_winner == 3) {
                c_total += 1;
            }
        }

    }

    if (strategy == 2) {
        for (int i = 0; i < NUM_DUELS; i++) {
            int duel_winner = duel_sim(2);
            if (duel_winner == 1) {
                a_total += 1;
            }
            if (duel_winner == 2) {
                b_total += 1;
            }
            if (duel_winner == 3) {
                c_total += 1;
            }
        }
    }

    cout << "\nAaron won " << a_total << "/10000 duels or " << (((double) a_total / NUM_DUELS) * 100) << "%";
    cout << "\nBob won " << b_total << "/10000 duels or " << (((double) b_total / NUM_DUELS) * 100) << "%"; 
    cout << "\nCharlie won " << c_total << "/10000 duels or " << (((double) c_total / NUM_DUELS) * 100) << "%"; 
    cout << "\n";

    return a_total;

}
// advising.cpp
// Purpose: Query advising bureaucracy
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

struct Node {
    string name;
    Node *supervisee_1;
    Node *supervisee_2;
    int advisee_count;
};

const string PRINT = "p";
const string ADD_A = "a";
const string ADD_F = "f";
const string TOTAL = "t";
const string SLACKER = "s";
const string QUIT = "q";

Node *new_node(string name);
Node *read_file(string filename);
void print_advisees(Node *curr_node, string bureaucracy);
Node *find_node(Node *curr_node, string name);
void delete_tree(Node* curr_node);
int total_advisees(Node *curr_node, string fac_name);
void slackers(Node *curr_node);

//STYLE NOTE: You do not have to worry about making main() fit in 30 lines for
//this assignment. 
int main(){
    //Prompt the user for the data file name
    string filename;
    cout << "Enter data file name: ";
    cin >> filename;
    Node *boss = read_file(filename);

    //Loop to continually prompt for queries
    string c;
    string fac_name;
    cout << "Enter a query: ";
    while (cin >> c) {
        if (c == PRINT) {
            print_advisees(boss, "");
        } else if (c == TOTAL) {
            cin >> fac_name;
            int total = total_advisees(boss, fac_name); 
            if (total == -1) {
                cout << fac_name << " doesn't work here!" << endl; 
            } else {
                cout << fac_name << " is responsible for " <<  
                total  << " advisee(s)." << endl;
            }
        } else if (c == SLACKER) {
            slackers(boss);
        } else if (c == QUIT) {
            break;
            
        } else if (c == ADD_A) {
            
            ///// (OPTIONAL) YOUR CODE GOES HERE ///// 
            
        } else if (c == ADD_F) {

            ///// (OPTIONAL) YOUR CODE GOES HERE /////
            
        } else {
            cout << c << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    }

    delete_tree(boss);

    return 0;
} 

// slackers
// pointer to current node
//void return
void slackers(Node *curr_node){
    if(curr_node == nullptr){
     return;
    }
    if (curr_node->advisee_count == 0 && curr_node->supervisee_1 == 
        nullptr && curr_node->supervisee_2 == nullptr) {
        cout << "Slacker: " << curr_node->name << endl;
    }  
    slackers(curr_node->supervisee_1);
    slackers(curr_node->supervisee_2);
}

// total_advisees 
// pointer to current node, name of faculty
// number of advisees assigned to the faculty
int total_advisees(Node *curr_node, string fac_name) {
    if (curr_node == nullptr) {
        return -1;
    }
    
    int count = 0;

    if (curr_node->name == fac_name) {
        count += curr_node->advisee_count;

        if (curr_node->supervisee_1 != nullptr) {
            count += total_advisees(curr_node->supervisee_1, curr_node->supervisee_1->name);
        }

        if (curr_node->supervisee_2 != nullptr) {
            count += total_advisees(curr_node->supervisee_2, curr_node->supervisee_2->name);
        }

        return count;
    }


    if (curr_node->supervisee_1 != nullptr) {
        count += total_advisees(curr_node->supervisee_1, fac_name);
    }

    if (curr_node->supervisee_2 != nullptr) {
        count += total_advisees(curr_node->supervisee_2, fac_name);
    }

    return count;
}

// delete_tree
// a pointer to the current node in the tree that needs to be deleted
// no return value
void delete_tree(Node* curr_node) {
    if (curr_node == nullptr) {
        return;
    }

    delete_tree(curr_node->supervisee_1);
    delete_tree(curr_node->supervisee_2);

    delete curr_node;
}

//Print the tree path of every person who has advisees
void print_advisees(Node *curr_node, string bureaucracy){
    //Base Case: If we are at a person who has advisees, print the count
    if(curr_node->advisee_count > 0){
        cout << bureaucracy;
        cout << curr_node->name + "->";
        cout << curr_node->advisee_count << endl;
    //Recursive Cases: If we are at a person who doesn't have advisees, recurse to their subtrees
    }else{
        if(curr_node->supervisee_1 != nullptr){
            string bureaucracy_left = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_1, bureaucracy_left);
        }

        if(curr_node->supervisee_2 != nullptr){
            string bureaucracy_right = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_2, bureaucracy_right);
        }
    }
}

//Read file and build tree structure, returning root "boss" node.
//STYLE NOTE: You do not have to worry about paring down read_file() to a
//30-line limit for this assignment.
Node *read_file(string filename){
    //Open the given file
    ifstream infile(filename.c_str());
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: " 
             << filename << endl;
        exit(EXIT_FAILURE);
    }

    //Read the first line of the file
    string supervisor;
    string supervisee;

    infile >> supervisor;
    infile >> supervisee;
    Node *boss = new_node(supervisor);
    bool first_line = true;
    
    //Process each line of the file
    while(!infile.eof()){
        Node *supervisor_node;

        //Initialize the root node if we're on the first line of the file
        if(first_line){
            supervisor_node = boss;
            first_line = false;
        }else{
            supervisor_node = find_node(boss, supervisor);
        }

        //Check if we're dealing with an advisor or a supervisor
        if(supervisee == "Advisee"){
            supervisor_node->advisee_count++;
        }else{
            //Determine if the supervisee should be the first or second supervisee
            if(supervisor > supervisee){
                supervisor_node->supervisee_1 = new_node(supervisee);
            }else{
                supervisor_node->supervisee_2 = new_node(supervisee);
            }
        }

        //Read the next line
        infile >> supervisor;
        infile >> supervisee;
    }

    infile.close();

    return boss;
}

//Finds and returns the node with the given name
Node *find_node(Node *curr_node, string name){
    //Base Case: If curr_node is the person we're looking for, return it 
    if(curr_node->name == name){
        return curr_node;
    //Recursive Cases: Search either the left or right subtree for the name
    }else if(curr_node->name > name){
        if(curr_node->supervisee_1 == nullptr) return nullptr;
        return find_node(curr_node->supervisee_1, name);
    }else{
        if(curr_node->supervisee_2 == nullptr) return nullptr;
        return find_node(curr_node->supervisee_2, name);
    }

    return nullptr;
}

//Returns a new node that is blank except for the provided name
Node *new_node(string name){
    Node *new_node = new Node;

    new_node->name = name;
    new_node->supervisee_1 = nullptr;
    new_node->supervisee_2 = nullptr;
    new_node->advisee_count = 0;

    return new_node;
}

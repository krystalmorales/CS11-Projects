/*
* phone_tree.cpp
* Purpose: This program will determine if all parents from input file are called or if there is an error
* Submitted by: {Krystal Morales, kmoral02}
*/

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct Parents {
    string name;
    int time;
    string name2;
    Parents *parent;
};

Parents *read_parents(string filename, int *parent_count);
Parents *match_parents(Parents *contact_list, int parent_count);
void phone_chain(Parents *contact_list, int parent_count);
void init_contacts(Parents *contact_list, int parent_count);

int main(int argc, char *argv[]) {
    // Make sure a file exists
    if (argc < 2) {
        cerr << "ERROR: Expecting file name as a command line-argument." << endl;
        exit(EXIT_FAILURE);
    }

    int parent_count;
    Parents *contact_list = read_parents(argv[1], &parent_count);

    phone_chain(contact_list, parent_count);
    
    delete [] contact_list;
    return 0;
}

/*
 * Description: This function reads a file of parent information 
 *              into an array of Parent structs
 * Input: The name of the file to read from, and the address of the
 *        integer that will store the total count of parents
 * Output: A pointer to the finished array of Parents structs
 */
Parents *read_parents(string filename, int *parent_count) {

    ifstream infile(filename.c_str());
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: "
        << filename << endl;
        exit(EXIT_FAILURE);
    }

    int count_parents;
    infile >> count_parents;
    *parent_count = count_parents;

    Parents *contact_list = new Parents[*parent_count];

    init_contacts(contact_list, *parent_count);


    for (int i = 0; i < *parent_count; i++) {
        infile >> contact_list[i].name >> contact_list[i].time >> contact_list[i].name2;
        contact_list[i].parent = nullptr;
    }

    infile.close();

    return contact_list;
}

/*
 * Description: This function determines the phone chain and who the 
 *    first caller in the phone chain is
 * Input: The Parennts array, the total size of that array
 * Output: A pointer to the Parents with the first caller in the phone *    chain and the order of the calls
 */
Parents *match_parents(Parents *contact_list, int parent_count) {
   for (int i = 0; i < parent_count; i++) {
       for (int j = 0; j < parent_count; j++) {
           if (i != j && contact_list[i].name2 == contact_list[j].name) {
                if (contact_list[i].parent == nullptr) {
                    contact_list[i].parent = &contact_list[j];
                }
           }
       }
   }
   Parents* first_caller = nullptr;
    for (int i = 0; i < parent_count; i++) {
        bool is_caller = true;
        for (int j = 0; j < parent_count; j++) {
            if (i != j && contact_list[j].parent == &contact_list[i]) {
                is_caller = false;
                break;
            }
        }
        if (is_caller) {
            first_caller = &contact_list[i];
            break;
        }
    }
    return first_caller;
}

/*
 * Description: This function determines which parents were left out of *   the phone chain and the total amout it will tke to complete the call
 * Input: The Parennts array, the total size of that array
 * Output: void
 */
void phone_chain(Parents *contact_list, int parent_count) {
    Parents *first_caller = match_parents(contact_list, parent_count);
    
    if (first_caller != nullptr) {
        Parents *current_caller = first_caller;
        int total_calls = 0;
        int time = 0;
        int total_time = 0;

        while (current_caller->name2 != first_caller->name) {
            if (current_caller->parent != nullptr) {
                total_calls++;
                time = current_caller->time; 
                total_time += time;

                current_caller->parent = nullptr;
                
                string next_caller_name = current_caller->name2;
                current_caller = nullptr;
                for (int i = 0; i < parent_count; i++) {
                    if (contact_list[i].name == next_caller_name) {
                        current_caller = &contact_list[i];
                        break;
                    }
                }
            }
            else {
                break; 
            }
        }
        int print_time;
        print_time = total_time - time;

        if (total_calls < parent_count ) {
            cout << "Curse you, Harold Hacker!" << endl;
        }
        if (total_calls == parent_count) {
            cout << "Starting with " << first_caller->name << " the phone tree will succeed in " << print_time << " seconds!" << endl;
        }
    }
}

/*
 * Description: This function initializes the Parents struct to empty
 * Input: The Parennts array, the total size of that array
 * Output: void
 */
void init_contacts(Parents *contact_list, int parent_count) {
    for (int i = 0; i < parent_count; i++) {
        contact_list[i].name = "";
        contact_list[i].time = 0;
        contact_list[i].parent = nullptr;
    }
}
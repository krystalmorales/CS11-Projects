/*
lineage.cpp
This program will determine how different strands of DNA may
be connected over multiple mutations.
Krystal Morales (krmoral02)
*/
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
struct Gene;

struct Mutation {
    int cost;
    Gene *target;
};

struct Gene {
    string sq;
    bool seen; //Used in recursive functions to avoid loops
    Mutation *muts;
};

const string EVOLVE = "e";
const string E_STEPS = "es";
const string ENE_EVOLVE = "ene";
const string PATH = "path";
const string QUIT = "q";


int  create_graph(Gene **);
void populate_nodes(Gene *dna, ifstream *inf, int num_nodes);
void populate_links(Gene *dna, ifstream *inf, int num_nodes);
int  index_of(Gene *, string, int);
void init(Gene *, int);
bool evolution(Gene *dna, string gene, string target, int num_nodes);
int evo_steps(Gene *dna, string source, string tg, int num_nodes);
bool energetic_evo (Gene *dna, string source, string tg, int energy, int num_nodes);
string evo_path(Gene *dna, string source, string tg, int num_nodes);

int main(){

    Gene *dna;

    //After this line executes, dna is a pointer to the array of gene
    //information read in from a given data file, and num_nodes contains the
    //number of genes stored in that array. 
    int num_nodes = create_graph(&dna);

    //USE dna AND num_nodes AFTER THIS LINE TO CONTINUE THE COMPUTATION

    string query;
    string s_gene;
    string t_gene;
    int energy;
    cout << "Enter a query: ";
    cin.ignore();


    while (getline(cin, query)) {
        stringstream ss(query);
        ss >> query;

        if (query == EVOLVE) {
            ss >> s_gene >> t_gene;
            evolution(dna, s_gene, t_gene, num_nodes);
        } else if (query == E_STEPS){
            ss >> s_gene >> t_gene;
            int steps = evo_steps(dna, s_gene, t_gene, num_nodes);
            if(steps != -1) {
            cout << "It will take " << steps << " evolutionary steps to " <<
            "get from " << s_gene << " to " << t_gene << endl;
        } else {
            cout << "It will take -1 evolutionary steps " <<
            "to get from " << s_gene << " to " << t_gene << endl;
            }
        } else if (query == ENE_EVOLVE) {
            ss >> s_gene >> t_gene >> energy;
            energetic_evo(dna, s_gene, t_gene, energy, num_nodes);
        } else if (query == PATH) {
            ss >> s_gene >> t_gene;
            evo_path(dna, s_gene, t_gene, num_nodes);
        } else if (query == QUIT) {
            for (int i = 0; i < num_nodes; i++) {
                if (dna[i].muts != nullptr) {
                delete dna[i].muts;
                }
            }
            delete [] dna;
            return 0;
        } else {
            cout << query << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    }
    delete [] dna;
    return 0;
}

// Creates graph and stores it inside of array at passed location.
// create_graph 
// Input: An uninitialized pointer to a Gene pointer.
// Description: Read in a file provided the user and use the data to populate an
//              array of Genes.
// Output: Populates the array pointed to by *dna_p with the contents of a data
//         file, and returns the number of array elements
int create_graph(Gene **dna_p){
    string filename;
    cout << "Enter data file name: ";
    cin >> filename;

    ifstream inf(filename);
    if (inf.fail()) {
        cerr << "ERROR OPENING FILE: Exiting Program" << endl;
        exit(EXIT_FAILURE);
    }
    
    int num_nodes;
    inf >> num_nodes;
    inf.ignore(); 
    
    // Create and populate the nodes in the array
    *dna_p = new Gene[num_nodes];
    init(*dna_p, num_nodes);
    populate_nodes(*dna_p, &inf, num_nodes);

    // Reset the file to read the links
    inf.close();
    inf.open(filename);
    inf >> num_nodes;
    inf.ignore();

    populate_links(*dna_p, &inf, num_nodes);
    
    return num_nodes;
}

// init 
// Input: A pointer to an uninitialized array of genes and the size of 
//        that array.
// Description: Initializes the array of genes with non-garbage information.
// Output: Initializes the array pointed to by 'dna'.
void init(Gene *dna, int num_nodes){
    for (int i = 0; i < num_nodes; i++) {
        dna[i].sq = "";
        dna[i].seen = false;
        dna[i].muts = nullptr;
    }
}

// populate_nodes
// Input: A pointer to an array of genes, a pointer to a file, 
//        and the size of the array.
// Description: Read the file and populate the genes in the array with their
//              sequence information.
// Output: Populates the sequence information for the gene array pointed to by
//         'dna'. Moves the file pointer further into the file.
void populate_nodes(Gene *dna, ifstream *inf, int num_nodes){
    string line;
    stringstream sstr;
    for (int i = 0; i < num_nodes; i++) {
        getline(*inf, line);
        sstr.str(line);
        sstr >> dna[i].sq;
        sstr.clear();
    }
}

// populate_links
// Input: A pointer to an array of genes, a pointer to a file, 
//        and the size of the array.
// Description: Read the file and populate the mutation information between
//              genes in the array. We assume the data file only contains
//              well-formed input.
// Output: Populates the mutation information for the gene array pointed to by
//         'dna'. Moves the file pointer further into the file.
void populate_links(Gene *dna, ifstream *inf, int num_nodes){
    string line, seq, mut_seq;
    stringstream sstr;
    int cost;
    for (int i = 0; i < num_nodes; i++) {
        getline(*inf, line);

        sstr.str(line);
        sstr >> seq;//Skip over first gene name on each line
        
        // Add a mutation if it exists
        sstr >> mut_seq >> cost;
        if (!sstr.fail()) {
            int mut_index = index_of(dna, mut_seq, num_nodes);
            dna[i].muts = new Mutation;
            dna[i].muts->cost = cost;
            dna[i].muts->target = &dna[mut_index];
        }
        //Prepare to read another line from this string stream
        sstr.clear();
    }
}

// index_of
// Input: An array of genes, a gene sequence, and the size of the array.
// Description: Find the index of the given sequence in the array.
// Output: The index of the sequence in the array, or -1 if the sequence is not
//         in the array.
int index_of(Gene *dna, string seq, int num_nodes){
  for (int i = 0; i < num_nodes; i++) {
    if (dna[i].sq == seq) {
      return i;
    }
  }
  return -1;
}

// evolution
// Input: Gene *dna, source gene, target gene, and the size of the array.
// Description: Determine if source caan mutate to target
// Output: boolean indicating whether source gene can mutate to target gene
bool evolution(Gene *dna, string source, string tg, int num_nodes) {
    int src_index = index_of(dna, source, num_nodes);
    int tgt_index = index_of(dna, tg, num_nodes);

    Gene *src = &dna[src_index];

    Mutation *mutation = src->muts;

    if(src_index == -1 || tgt_index == -1) {
        cout << source << " cannot evolve into " << tg << endl;
        return false;
    }
    
    if(src-> sq == source && mutation->target->sq == tg) {
        cout << source << " can evolve into " << tg << endl;
        return true;
    }

    if(src->seen == false){
        cout << source << " cannot evolve into " << tg << endl;
        return false;
    }

    src->seen = true;
    
    return evolution(dna, mutation->target->sq, tg, num_nodes);

    src->seen = false;

    return false;
}

// evo_steps
// Input: Gene *dna, source gene, target gene, and the size of the array.
// Description: Determine the number of steps required to mutate
// Output: int indicating the number of steps required to mutate
int evo_steps(Gene *dna, string source, string tg, int num_nodes) {

    int src_index = index_of(dna, source, num_nodes);
    int tgt_index = index_of(dna, tg, num_nodes);

    Gene *src = &dna[src_index];
    Mutation *mutation = src->muts;

    if(src_index == -1 || tgt_index == -1) {
        return -1;
    }

    if(src->sq == source && src->muts == nullptr) {
        return -1;
    }

    if (src->sq == source && src->muts != nullptr) {
        if (mutation->target->sq == tg) {
        return 1;
        }
    }

    if (src->seen) {
        return -1;
    }

    src->seen = true;

    int min_steps = -1;
    int steps = evo_steps(dna, mutation->target->sq, tg, num_nodes);
    if (steps != -1) {
        min_steps = steps+1;
    }

    mutation = mutation->target->muts;

    src->seen = false;
    return min_steps;
}

// energetic_evo
// Input: Gene *dna, string source, string tg, int energy, int num_nodes
// Description: Determine if energy is enough to mutate gene
// Output: bool indicating if energy is enough to mutate
bool energetic_evo (Gene *dna, string source, string tg, int energy, int num_nodes){    
    int src_index = index_of(dna, source, num_nodes);
    int tgt_index = index_of(dna, tg, num_nodes);

    Gene *src = &dna[src_index];
    Mutation *mutation = src->muts;

    if (src_index == -1 || tgt_index == -1) {
        cout << source << " cannot evolve into " << tg << " with at most " <<
        energy << " evolutionary cost" << endl;
        return false;
    }

    if (src->muts == nullptr) {
        cout << source << " cannot evolve into " << tg << " with at most " <<
        energy << " evolutionary cost" << endl;
        return false;
    }

    if (src->sq == source && mutation->target->sq == tg) {
        if(mutation->cost <= energy) {
            cout << source << " can evolve into " << tg << " with at most " <<
            energy << " evolutionary cost" << endl;
            return true;
        } 
        if (mutation->cost > energy) {
            cout << source << " cannot evolve into " << tg << " with at most " <<
            energy << " evolutionary cost" << endl;
            return false;
        }
    }

    if(src->seen == false) {
        cout << source << " can evolve into " << tg << " with at most " <<
        energy << " evolutionary cost" << endl;
        return true;
    }

    src->seen = true;

    return energetic_evo(dna, mutation->target->sq, tg, energy, num_nodes);

    src->seen = false;
    
    return false;
}

// evo_path
// Input: Gene *dna, string source, string tg, int num_nodes
// Description: Determine the sequence of mutaton
// Output: string indicating the sequence of mutation
string evo_path(Gene *dna, string source, string tg, int num_nodes) {
    int src_index = index_of(dna, source, num_nodes);
    int tgt_index = index_of(dna, tg, num_nodes);

    Gene *src = &dna[src_index];
    Mutation *mutation = src->muts;

    if(src_index == -1 || tgt_index == -1) {
        cout << "There is no path from " <<  source << " to " << tg << endl;
        return "";
    }

    if(src->sq == source && src->muts == nullptr) {
        cout << "There is no path from " <<  source << " to " << tg << endl;
        return "";
    }

    if (src->sq == source && mutation->target->sq == tg) {
        cout << source << " -> " << tg << endl;
        return source;
    }

    if(src->seen == false) {
        cout << "There is no path from " <<  source << " to " << tg << endl;
        return "";
    }

    src->seen = true;

    return evo_path(dna, mutation->target->sq, tg, num_nodes);

    src->seen = false;
    
    return "";
}
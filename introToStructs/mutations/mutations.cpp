/*
mutations.cpp
This program will prompt user for a query and based on the query 
provided by user the program will print out the results of the query.
Krystal Morales, kmoral02
*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Gene;

Gene *read_sample(string filename, int *num_genes);
void init_gene(Gene *gene_data, int num_genes);
void populate_gene(Gene *gene_data, int num_genes, ifstream *file_p);
void populate_mutations(Gene *gene_data, int num_genes, ifstream *file_p);
Gene *find_gene(Gene *gene_data, int num_genes,
                string gene_looking_for);
void print_gene(Gene *gene_data, int num_genes);
void can_mutate(Gene *gene_data, int num_genes, string s_gene, string t_gene);
void mutation_w_energy(Gene *gene_data, int num_genes, string s_gene, 
                        string t_gene, int energy);


const string PRINT_SAMPLE = "p";
const string QUIT = "q";
const string MUTATE = "m";
const string MUTATION_ENERGY = "me";

const int POSSIBLE_MUTATIONS = 5;

struct Mutations {
    string m_mutation;
    int m_energy;
    Gene *source_gene;
};

struct Gene {
    string gene;
    Mutations mutations[POSSIBLE_MUTATIONS];
};

int main () {
    string filename;
    cout << "Enter data file name: ";
    cin >> filename;
    cin.ignore();

    int num;
    Gene *all_genes = read_sample(filename, &num);

    string query;
    string s_gene;
    string t_gene;
    int energy;

    cout << "Enter a query: ";

    while (getline(cin, query)) {
        stringstream ss(query);
        ss >> query;

        if (query == PRINT_SAMPLE) {
            print_gene(all_genes, num); 
        } else if (query == MUTATE) {
            ss >> s_gene >> t_gene;
            can_mutate(all_genes, num, s_gene, t_gene);
        } else if (query == MUTATION_ENERGY) {
            ss >> s_gene >> t_gene >> energy;
            mutation_w_energy(all_genes, num, s_gene, t_gene, energy);
        } else if (query == QUIT) {
            delete [] all_genes;
            return 0;
        } else {
            cout << query << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    } 

    return 0;
}

Gene *read_sample(string filename, int *num_genes) {
    ifstream infile(filename.c_str());
    if(infile.fail()) {
        cerr << "ERROR READING FILE: Exiting Program" << endl;
        exit(EXIT_FAILURE);
    }

    infile >> *num_genes;
    infile.ignore();

    //Allocate and populate memory for genes 
    Gene *new_gene = new Gene[*num_genes];
    init_gene(new_gene, *num_genes);
    populate_gene(new_gene, *num_genes, &infile);
    
    infile.close();
    infile.open(filename);
    infile >> *num_genes;
    infile.ignore();

    populate_mutations(new_gene, *num_genes, &infile);

    return new_gene;
}

void init_gene(Gene *gene_data, int num_genes){
    for (int i = 0; i < num_genes; i++) {
        gene_data[i].gene = "";
        for (int j = 0; j < POSSIBLE_MUTATIONS; j++) {
            gene_data[i].mutations[j].m_mutation = "";
            gene_data[i].mutations[j].m_energy = 0;
            gene_data[i].mutations[j].source_gene = nullptr;
        }
    }
}

void populate_gene(Gene *gene_data, int num_genes, ifstream *file_p) {
    string gene_sequence, line_info;

    stringstream sstream;

    for (int i = 0; i< num_genes; i++) {
        getline(*file_p, line_info);
        sstream.str(line_info);

        sstream >> gene_sequence;
        gene_data[i].gene = gene_sequence;

        int mutation_index = 0;
        while (sstream >> gene_sequence) {
            gene_data[i].mutations[mutation_index].m_mutation = gene_sequence;
            sstream >> gene_data[i].mutations[mutation_index].m_energy;

            mutation_index++;
        }

        sstream.clear();
    }
}

void populate_mutations(Gene *gene_data, int num_genes, 
                       ifstream *file_p) {
    string gene_sequence, gene_mutations, line_info;
    int gene_energy;
    
    stringstream sstream;

    for (int i = 0; i< num_genes; i++) {
        getline(*file_p, line_info);
        sstream.str(line_info);

        sstream >> gene_sequence;
        gene_data[i].gene = gene_sequence;

        int mutation_index = 0;
        while(sstream >> gene_mutations >> gene_energy) {
            gene_data[i].mutations[mutation_index].m_mutation 
            = gene_mutations;
            gene_data[i].mutations[mutation_index].m_energy = gene_energy;

            Gene *gen_p = find_gene(gene_data, num_genes, gene_mutations);
            gene_data[i].mutations[mutation_index].source_gene = gen_p;

            mutation_index++;

        }
        sstream.clear();
    }
}

Gene *find_gene(Gene *gene_data, int num_genes, 
                string gene_looking_for) {
    for (int i = 0; i < num_genes; i++) {
        if(gene_data[i].gene == gene_looking_for) {
            return &gene_data[i];
        }
    }
    return nullptr;
}

void print_gene(Gene *gene_data, int num_genes) {
    for (int i = 0; i < num_genes; i++) {
        cout << "== " << gene_data[i].gene << " ==" << endl;
        cout << "Mutations:" << endl;

        bool has_mutations = false;
        
        for (int j = 0; j < POSSIBLE_MUTATIONS; j++) {
            if (!gene_data[i].mutations[j].m_mutation.empty()) {
                has_mutations = true;
                cout << gene_data[i].mutations[j].m_mutation;
                cout << " - Cost: " << 
                gene_data[i].mutations[j].m_energy << endl;
            } 
         }
        if (!has_mutations) { 
            cout << "None" << endl;
        }
    }
}

void can_mutate(Gene *gene_data, int num_genes, string s_gene, string t_gene) {
    bool mutatation_found = false;

    for (int i = 0; i < num_genes; i++) {
        if (gene_data[i].gene == s_gene) {
            for (int j = 0; j < POSSIBLE_MUTATIONS; j++) {
                if (gene_data[i].mutations[j].m_mutation == t_gene) {
                    mutatation_found = true;
                    cout << s_gene << " can mutate into " << t_gene << endl;
                    break;
                } 
            }
            break;
        }
    } 
    if (!mutatation_found) {
        cout << s_gene << " cannot mutate into " << t_gene << endl;
    }
}

void mutation_w_energy(Gene *gene_data, int num_genes, string s_gene, 
                        string t_gene, int energy) {
    bool mutatation_possible = false;

    for (int i = 0; i < num_genes; i++) {
        if (gene_data[i].gene == s_gene) {
            for (int j = 0; j < POSSIBLE_MUTATIONS; j++) {
                if (gene_data[i].mutations[j].m_mutation == t_gene &&
                    energy >= gene_data[i].mutations[j].m_energy) {
                    mutatation_possible = true;
                    cout << s_gene << " can mutate into " << t_gene 
                    << " with evolutionary cost " << energy << endl;
                    break;
                } else if (gene_data[i].mutations[j].m_mutation == t_gene &&
                    energy < gene_data[i].mutations[j].m_energy) {
                        mutatation_possible = true;
                        cout << s_gene << " can mutate into " << t_gene 
                        << " but not with evolutionary cost " << energy << endl;
                    }
            }
            break;
        }
    }

    if (!mutatation_possible) {
        cout << s_gene << " cannot mutate into " << t_gene << endl;
    } 
}
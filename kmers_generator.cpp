#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

int WriteFile(string fname, map<string, int> m) {       
        int count = 0;
        if (m.empty())
        {
            return 0;
        }

        FILE *fp = fopen(fname.c_str(), "w");
        if (!fp)
        {
            return -errno;
        }

        for(map<string, int>::iterator it = m.begin(); it != m.end(); it++) 
        {
            fprintf(fp, "%s:%d\n", it->first.c_str(), it->second);
            count++;
        }

        fclose(fp);
        return count;
}


int main()
{
    int kmer_len = 10;
    string input_file = "SARS-CoV-2.fasta";
    string output_file = "5mers_from_cpp.json";

    map<string, int> kmer_dict;
    string w = "";
    string kmer = "";

    ifstream infile(input_file);
    string line;

    int counter = 0;
    while (getline(infile, line))
    {
        if (line[0] == '>')
        {
            cout << line << endl;
        } else {
            w += line;
            while (w.length() > kmer_len)
            {
                kmer = w.substr(0, kmer_len);
                for (int i=0; i<kmer.length(); i++)
                    kmer[i] = toupper(kmer[i]);

                if (kmer_dict.find(kmer) == kmer_dict.end())
                {
                    kmer_dict[kmer] = 1;
                } else {
                    kmer_dict[kmer] += 1;
                }
                w.erase(0, 1);
            }
        }
    }

    cout << "Writing to a JSON file ..." << endl;
    WriteFile(output_file, kmer_dict);

    cout << "Code completed sucessfully!" << endl;
    return 0;
}
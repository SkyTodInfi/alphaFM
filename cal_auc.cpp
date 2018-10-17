#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "src/Utils/utils.h"

using namespace std;

int main(int argc, char* argv[])
{
    string line;
    uint64_t n_pos = 0, n_neg = 0, accumulated_neg = 0, satisfied_pair = 0;
    int label, nth_bin, n_bins = 10000;
    vector<int> pos_histogram(n_bins, 0), neg_histogram(n_bins, 0);
    double score, bin_width = 1.0 / n_bins;
    vector<string> strVec;
    
    while(getline(cin, line))
    {
        strVec.clear();
        utils::split_string(line, ' ', &strVec);
        if(strVec.size() != 2) continue;
        label = stoi(strVec[0]);
        score = stod(strVec[1]);
        nth_bin = (int)(score / bin_width);
        if(label > 0) 
        { 
            pos_histogram[nth_bin] += 1;
            n_pos += 1;
        }
        else
        {
            neg_histogram[nth_bin] += 1;
            n_neg += 1;
        }
    }
    for(int i = 0; i < n_bins; i++)
    {
        satisfied_pair += (pos_histogram[i] * accumulated_neg + pos_histogram[i] * neg_histogram[i] * 0.5);
        accumulated_neg += neg_histogram[i];
    }
    cout << "total line:" << n_pos + n_neg << " auc:" << (double)satisfied_pair / (n_pos * n_neg) << endl;
    return 0;
}


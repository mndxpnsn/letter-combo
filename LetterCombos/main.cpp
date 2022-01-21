//
//  main.cpp
//  LetterCombos
//
//  Created by mndx on 03/01/2022.
//  Compute the number of m-letter combinations such that
//  the m letters in the combination are in alphabetical order.
//

#include <iostream>

typedef struct memo_table {
    bool is_set;
    int val;
} m_table;

int num_combos_dp(int m, int n, m_table** memo_table) {
    int result = 0;
    
    //Handle cases m < 0 and m > n
    if(m < 0 || m > n) {
        return result;
    }
    
    //Get results from memo table if available
    if(memo_table[m][n].is_set) {
        return memo_table[m][n].val;
    }
    
    //Base case
    if(m == 0) {
        return n * (n - 1) / 2;
    }
    
    //Recursive step
    if(m > 0) {
        for(int p = 1; p <= n; ++p) {
            result = result + num_combos_dp(m - 1, n - p, memo_table);
        }
    }
    
    //Store results in memo table
    memo_table[m][n].is_set = true;
    memo_table[m][n].val = result;
    
    return result;
}

m_table** init_memo_table(int size) {
    m_table** memo_table = new m_table*[size+1];
    
    for(int m = 0; m < size + 1; ++m) {
        memo_table[m] = new m_table[size+1];
    }
    
    for(int m = 0; m < size + 1; ++m) {
        for(int n = 0; n < size + 1; ++n) {
            memo_table[m][n].is_set = false;
            memo_table[m][n].val = 0;
        }
    }
    
    return memo_table;
}

int num_combos(int num_l, int size_a_bet, m_table** memo_table) {
    
    return num_combos_dp(num_l - 2, size_a_bet, memo_table);
}

int main(int argc, const char * argv[]) {
    
    //Initialize size alphabet and number of letters in combo
    int size_a_bet = 26;
    int num_l_in_combo = 7; //Number of letters in combo. num_l_in_combo > 1
    
    //Initialize memo table
    m_table** memo_table = init_memo_table(size_a_bet);
    
    //Compute number of combinations
    int num_of_combos = num_combos(num_l_in_combo, size_a_bet, memo_table);
    
    //Print results
    std::cout << "result: " << num_of_combos << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}

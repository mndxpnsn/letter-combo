//
//  main.cpp
//  LetterCombos
//
//  Created by mndx on 03/01/2022.
//  Compute the number of m-letter combinations such that
//  the m letters in the combination are in alphabetical order.
//

#include <math.h>
#include <iostream>

int ops = 0;

typedef struct memo_table {
    bool is_set;
    long val;
} m_table;

long num_combos_dp_exc(int m, int n, m_table** memo_table) {
    long result = 0;
    
    ops++;
    
    //Handle case m < 2
    if(m < 2) {
        return result;
    }
    
    //Get results from memo table if available
    if(memo_table[m][n].is_set) {
        return memo_table[m][n].val;
    }
    
    //Base case
    if(m == 2) {
        return n * (n - 1) / 2;
    }
    
    //Recursive step
    if(m > 2) {
        for(int p = 1; p <= n; ++p) {
            result = result + num_combos_dp_exc(m - 1, n - p, memo_table);
        }
    }
    
    //Store results in memo table
    memo_table[m][n].is_set = true;
    memo_table[m][n].val = result;
    
    return result;
}

long num_combos_dp_inc(int m, int n, m_table** memo_table) {
    long result = 0;
    
    ops++;
    
    //Handle case m < 2
    if(m < 2) {
        return result;
    }
    
    //Get results from memo table if available
    if(memo_table[m][n].is_set) {
        return memo_table[m][n].val;
    }
    
    //Base case
    if(m == 2) {
        return n * (n + 1) / 2;
    }
    
    //Recursive step
    if(m > 2) {
        for(int p = 1; p <= n; ++p) {
            result = result + num_combos_dp_inc(m - 1, p, memo_table);
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

long num_combos_exc(int num_l, int size_a_bet, m_table** memo_table) {
    //Computer the number of possible words of size num_l of
    //alphabet with size size_a_bet where combinations are
    //exclusive, so combinations such as 'aa' are not valid.
    //Letters in the word must be strictly greater than
    //preceding letters.
    
    //Case number of letters m greater than alphabet
    if(num_l > size_a_bet) {
        return 0;
    }
    
    return num_combos_dp_exc(num_l, size_a_bet, memo_table);
}

long num_combos_inc(int num_l, int size_a_bet, m_table** memo_table) {
    //Computer the number of possible words of size num_l of
    //alphabet with size size_a_bet where combinations are
    //inclusive, so combinations such as 'aa' are valid.
    //Letters in the word are greater than or equal to
    //preceding letters.
    
    //Case number of letters m greater than alphabet
    if(num_l > size_a_bet) {
        return 0;
    }
    
    return num_combos_dp_inc(num_l, size_a_bet, memo_table);
}

int main(int argc, const char * argv[]) {
    
    //Initialize size alphabet and number of letters in combo
    int size_a_bet = 26;
    int num_l_in_combo = 4; //Number of letters in combo. num_l_in_combo > 1
    
    //Initialize memo table
    m_table** memo_table = init_memo_table(size_a_bet);
    
    //Compute number of combinations
    long num_of_combos = num_combos_exc(num_l_in_combo, size_a_bet, memo_table);
    
    //Print results
    std::cout << "ops: " << ops << std::endl;
    std::cout << "result: " << num_of_combos << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}

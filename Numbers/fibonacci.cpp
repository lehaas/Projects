

#include <iostream>
#include <stdlib.h>
#include <vector>

void compute_fibonacci(int n, std::vector<int> &sequence);

int main(int argc, char *   argv[]){

    int n_th;
    std::cout << "Until where do you wish to receive the Fibonacci Sequence? ";
    std::cin >> n_th;

    std::vector<int> sequence;
    compute_fibonacci(n_th, sequence);
    for(int i=0; i < sequence.size(); i++)
        std::cout << sequence.at(i) << ", ";
    std::cout << std::endl;
}

void compute_fibonacci(int n, std::vector<int> &sequence) {
    if (n == 0) 
        return ;
    if (sequence.size() < 2) {
        sequence.push_back(1);
        compute_fibonacci(n-1, sequence);
    } else {
        sequence.push_back(sequence[sequence.size() - 1] + sequence[sequence.size() - 2]);
        compute_fibonacci(n-1, sequence);

    }
}
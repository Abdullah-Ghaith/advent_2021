#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class submarine {
    private:
        uint64_t horizontal = 0;
        uint64_t depth = 0;
        uint64_t aim = 0;
    public:
        void move(string input)
        {
            switch (input[0])
            {
            case 'f':
                this->horizontal += (int)input[8]-'0';
                this->depth += this->aim*((int)input[8]-'0');
                break;
            case 'd':
                this->aim += (int)input[5]- '0';
                break;
            case 'u':
                this->aim -= (int)input[3]- '0';
                break;
            }
        }
        void answer()
        {
           cout << (this->horizontal)*(this->depth);
        }
};

int main()
{
    string line; 
    ifstream data_file;
    submarine adv2_sub;
    data_file.open("adv2_data.txt");
    if (data_file.is_open()) {
        while (getline(data_file,line) ) {
            adv2_sub.move(line);
        }
        adv2_sub.answer();
        data_file.close();
    }
}
#include <iostream>
#include <fstream>
#include <vector>
#include<cmath>
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
        void avd2_answer()
        {
           cout << (this->horizontal)*(this->depth);
        }
};

int dom_bit(vector<string> oxygen_nums, int column)
{   
    int ones_count=0;
    for (int i = oxygen_nums.size()-1; i >= 0; i--)
    {
        ones_count += ((int)oxygen_nums[i][column]-'0'); 
    }
    if (ones_count == oxygen_nums.size()/2 || ones_count > oxygen_nums  .size()/2 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int sub_bit(vector<string> co2_nums, int column)
{   
    int ones_count=0;
    for (int i = co2_nums.size()-1; i >= 0; i--)
    {
        ones_count += ((int)co2_nums[i][column]-'0'); 
    }
    if (ones_count == co2_nums.size()/2 || ones_count > co2_nums.size()/2 )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    string line;
    vector<string> oxygen_nums;
    vector<string> co2_nums;
    ifstream data_file;
    uint64_t bit_counts[12] = {0};
    uint32_t line_count = 0;
    data_file.open("adv3_data.txt");
    if (data_file.is_open()) {
        while (getline(data_file,line)) {
            oxygen_nums.push_back(line);
            line_count++;
            for(int i = 0; i < 12; i++)
            {
                bit_counts[i] += ((int)line[i]-'0');
            }
        }
    }
    uint64_t gamma_rate_setup[12] = {0};
    uint64_t gamma_rate = 0;
    uint64_t epsilon_rate_setup[12] = {0};
    uint64_t epsilon_rate = 0;
    for(int i = 0; i < 12; i++)
    {
        if (bit_counts[i] > (line_count/2)) 
        {
            gamma_rate_setup[i] = 1;
            gamma_rate += gamma_rate_setup[i]*(pow(2,11-i));
        }
        else
        {
            epsilon_rate_setup[i] = 1;
            epsilon_rate += epsilon_rate_setup[i]*(pow(2,11-i));
        }
    }
    
    co2_nums = oxygen_nums;

    int column = 0;
    while(oxygen_nums.size()!= 1)
    {
        int dom_bit_val = dom_bit(oxygen_nums, column);
        for(int i = oxygen_nums.size()-1; i >= 0; i--)
        {
            if(int(oxygen_nums[i][column]-'0') != dom_bit_val)
            {
                oxygen_nums.erase(oxygen_nums.begin() + i);
            }
        }
        column++;    
    }
    
    column = 0;
    while(co2_nums.size()!= 1)
    {
        int sub_bit_val = sub_bit(co2_nums, column);
        for(int i = co2_nums.size()-1; i >= 0; i--)
        {
            if(int(co2_nums[i][column]-'0') != sub_bit_val)
            {
                co2_nums.erase(co2_nums.begin() + i);
            }
        }
        column++;    
    }
    uint64_t oxygen_ans = 0;
    uint64_t co2_ans = 0;
    
    for(int i = 0; i < 12; i++)
    {
        oxygen_ans += (int)(oxygen_nums[0][i]-'0')*(pow(2,11-i));
        co2_ans += (int)(co2_nums[0][i]-'0')*(pow(2,11-i));
    }
    data_file.close();
}


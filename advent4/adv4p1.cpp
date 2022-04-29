#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cmath>
using namespace std;

#define NUM_ROWS 5
#define NUM_COLS 5
#define BOARD_SIZE 25
#define MAX_BOARDS 1000

void adv4_ans(uint64_t sum, uint64_t last_num)
{
    cout << sum * last_num;
}

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
class bingo_board {
    private:
        uint64_t unused_sum = 0;
    public:
        uint8_t curr_position = 0;
        uint8_t numbers[BOARD_SIZE] = {0}; 
        vector<string> numbers_string;
        bingo_board()
        {
            curr_position = 0;
            unused_sum = 0;
            numbers[BOARD_SIZE] = {0};
            numbers_string; 
        }
        bingo_board(uint8_t u_sum_i)
        {
            curr_position = 0;
            unused_sum = u_sum_i;
            numbers[BOARD_SIZE] = {0};
            numbers_string;
        } 
        void set_num(uint8_t num)
        {
            numbers[curr_position] = num;
            curr_position++;
        }
        void string_to_nums()
        {
            for(int i = 0; i < BOARD_SIZE; i++)
            {
                numbers[i] = stoi(numbers_string[i]);
            }
        }
        void record_number(uint8_t number)
        {
            for (int i = 0; i<BOARD_SIZE; i++)
            {
                if (numbers[i] == number)
                {
                    numbers[i] = 0;
                }
            }
        }
        uint64_t return_sum()
        {
            for (int i = 0; i<BOARD_SIZE; i++)
            {
                unused_sum += numbers[i];
            }
            return unused_sum;
        }
        bool check_win()
        {
            if (!numbers[0] && !numbers[1] && !numbers[2] && !numbers[3] && !numbers[4]) //row #1
                return true;
            else if (!numbers[5] && !numbers[6] && !numbers[7] && !numbers[8] && !numbers[9]) //row #2
                return true;
            else if (!numbers[10] && !numbers[11] && !numbers[12] && !numbers[13] && !numbers[14]) //row #3
                return true;
            else if (!numbers[15] && !numbers[16] && !numbers[17] && !numbers[18] && !numbers[19]) //row #4
                return true;
            else if (!numbers[20] && !numbers[21] && !numbers[22] && !numbers[23] && !numbers[24]) //row #5
                return true; 

            else if (!numbers[0] && !numbers[5] && !numbers[10] && !numbers[15] && !numbers[20]) //col #1
                return true;
            else if (!numbers[1] && !numbers[6] && !numbers[11] && !numbers[16] && !numbers[21]) //col #2
                return true;
            else if (!numbers[2] && !numbers[7] && !numbers[12] && !numbers[17] && !numbers[22]) //col #3
                return true;
            else if (!numbers[3] && !numbers[8] && !numbers[13] && !numbers[18] && !numbers[23]) //col #4
                return true;
            else if (!numbers[4] && !numbers[9] && !numbers[14] && !numbers[19] && !numbers[24]) //col #5
                return true;

            return false;
        }

};

void reset_s_vector(vector<string>* passed_vector)
{
    int vector_size = passed_vector->size();
    for(int i = 0; i < vector_size; i++)
    {
        passed_vector->pop_back();
    }
}

int main()
{
    string line;
    ifstream data_file;
    vector<string> lotto_nums_string;
    vector<uint8_t> lotto_nums;
    vector<bingo_board> bingo_boards;
    uint8_t curr_num = 0;
    uint16_t num_boards = 0;

    for(int i = 0; i < MAX_BOARDS; i++)
    {
        bingo_boards.push_back(bingo_board()); 
    }

    data_file.open("adv4_data.txt");

    if (data_file.is_open()) 
    {
        getline(data_file, line);  //get lotto_nums in first go
        string delim = ",";
        uint8_t pos = 0;

        while(line != "" && (pos = line.find(delim)) ) 
        {
            lotto_nums_string.push_back(line.substr(0, pos));
            lotto_nums.push_back(stoi(lotto_nums_string.back()));
            line.erase(0, pos + delim.length());
        }
        getline(data_file, line); //blank line
        while(!data_file.eof())
        {   
            
            for (int i = 0; i < NUM_ROWS; i++)
            {
                getline(data_file, line);
                reset_s_vector(&lotto_nums_string);
                for (int j = 0; j < NUM_COLS; j++)
                {
                    lotto_nums_string.push_back(line.substr(j*3, 2));
                    bingo_boards[num_boards].set_num(stoi(lotto_nums_string.back()));
                }
            }
            num_boards++;
            getline(data_file, line); //blank line
        }
    }
    data_file.close();
    bool game_over = false;
    while(!game_over)
    {
        for(int j = 0; j < lotto_nums.size(); j++) //for every lotto number
        {
            for(int i = 0; i < num_boards; i++) //for every board
            {   
                game_over = bingo_boards[i].check_win(); //check if board won
                if(!game_over)
                    {
                        bingo_boards[i].record_number(lotto_nums[j]);
                    }
                else //game_over
                {
                    adv4_ans(bingo_boards[i].return_sum(), curr_num);
                    i = 100;
                    j = 100;
                }
            }
            curr_num = lotto_nums[j];
        }

    }


}

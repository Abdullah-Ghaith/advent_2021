#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    string line; 
    vector<int> nums;
    ifstream data_file;
    int count = 0;
    data_file.open("adv1_data.txt");
    if (data_file.is_open()) {
        while (getline (data_file,line) ) {
            nums.push_back(stoi(line));
        }
        data_file.close();
        int position = 0;
        int size = nums.size();

        while((position + 3)<size) {
            int sum_A = nums[position] + nums[position+1] + nums[position+2]; 
            int sum_B = nums[position+1] + nums[position+2] + nums[position+3]; 
            if (sum_B > sum_A){
                count++;
            }
            position++;
        }
        cout << count;
    }
}
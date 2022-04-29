#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cmath>
using namespace std;

class lantern_fish{
    public:
        uint8_t internal_timer;

        lantern_fish()
        {
            internal_timer = 100;
        }
        lantern_fish(uint64_t internal_timer_i)
        {
            this->internal_timer = internal_timer_i;
        }
        
};

class fish_school{
    public:
        vector<lantern_fish> school;
        vector<lantern_fish> school_2;
        vector<lantern_fish> babies;
        fish_school()
        {
            vector<lantern_fish> empty(0, 0);
            school = empty;
            babies = empty;  
        }
        fish_school(vector<lantern_fish> lantern_fish_vec_i)
        {
            vector<lantern_fish> empty(0, 0); //add a vector reserve
            school = lantern_fish_vec_i;
            babies = empty;
        }
        //check fish about to birth (=0), reset timer (=6), add to babies vector
        //add babies at the end of decrementing as they do not start counting until next day
        void age(uint16_t days);

        void adv6_ans()
        {
            cout << school.size();
        }
    
};

void fish_school::age(uint16_t days)
        {
            for(uint8_t j = 0; j < days; j++)
            {
               
                   for(uint64_t i = 0; i < school.size(); i++) //age all fish
                   {
                       if(school[i].internal_timer == 0){
                           school[i].internal_timer = 6; //reset
                           babies.push_back(lantern_fish(8)); //add baby
                       }
                       else{
                           school[i].internal_timer--;
                       }
                   }
               
               for(int curr_baby = 0; curr_baby < babies.size(); curr_baby++) //add all babies to the school
               { 
                 school.push_back(babies[curr_baby]);  
               }
               vector<lantern_fish> empty(0, 0);
               babies = empty;
            }
        }

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
    ifstream data_file;
    string curr_lantern_fish_s;
    vector<lantern_fish> base_school(0, lantern_fish(0));
    data_file.open("adv6_data.txt");

    while(getline(data_file, curr_lantern_fish_s, ','))
    {
       base_school.push_back(lantern_fish(stoi(curr_lantern_fish_s)));
    }

    fish_school curr_school(base_school);
    //curr_school.age(256);
    curr_school.adv6_ans();
    data_file.close();


}

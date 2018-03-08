/***************************************************
 *                                                 *
 * Rolling Average Filter for General Robotics Use *
 * Author: Charles Ju                              *
 *                                                 *             
 ***************************************************/
#include <ArduinoSTL.h>
// #include <algorithm.h>
// #include <iostream.h>  
// #include <String.h>
// using namespace std;  

typedef struct {
    //List of numbers
    float *num;
    //Size of rolling average
    int size;
} RollingAverage_Internal_State;

class RollingAverage {
public:
    //Constructor
    //Input:
    //  size: size of the average
    RollingAverage(int size){
        avg.size = size;
        avg.num = new float [size];
        for(int i = 0; i < size; i++){
            avg.num[i] = 0;
        }
    }
    //Returns the median value in list
    float median(){
        float num_cpy [avg.size];
        std::copy(avg.num, avg.num + avg.size, num_cpy);
        std::sort(num_cpy, num_cpy + avg.size);
        return num_cpy[int(avg.size/2)];
    }

    //Returns the number in the index n of the rolling array
    float getNum(int n){
        return avg.num[n];
    }

    //Returns the average of all numbers in the rolling array
    float average(){
        int sum = 0;
        for(int i = 0; i < avg.size; i++){
            sum += avg.num[i];
        }
        return sum / avg.size;
    }

    //Shifts all numbers up one index and add value to the beginning of the array
    float add(float n){
        for(int i = avg.size - 1; i > 0; i--){
            avg.num[i] = avg.num[i-1];
        }
        avg.num[0] = n;
    }

private:
    //private struct of the rolling array
    RollingAverage_Internal_State avg;

};

//Printouts for debugging purposes
// int main(){
//     RollingAverage avg(5);
//     avg.add(6);
//     avg.add(1);
//     avg.add(8);
//     avg.add(4);
//     avg.add(2);
//     cout << avg.median() << endl;
    
//     return 0;
// };
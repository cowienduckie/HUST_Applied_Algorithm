//Classification Vehicle Routing Problem
#include <iostream>
#include <vector>
#include <algorithm>

#define ull unsigned long long
#define m 1000000007

using namespace std;

//Global variables
int cus_num = 0, truck_num = 0, max_cap = 0; ull route = 0;

vector <int> order;
vector <int> store;
vector <int> truck;

//Functions
int cap(int cus){

    int tmp = 0;

    for (int i = 0; i < cus_num; ++i){

        if (cus & (1 << i)){

            tmp += order[i];
        }
    }

    return tmp;
}

bool isInclude(int i, int cus){

    for (int j = 0; j < cus_num; ++j){

        if (i & (1 << j)){

            if ( !(cus & (1 << j)) ){

                return false;
            }
        }
    }

    return true; 
}

ull fact(int x){

    if (x == 1 || x == 0) return 1;

    return (x * fact(x - 1)) % m;
}

void checkRoute(){

    ull tmp = 1;

    for (int i = 1; i <= truck_num; ++i){

        int counter = 0;

        for (int j = 0; j < cus_num; ++j){
            
            if (truck[i] & (1 << j)){

                ++counter;
            }
        }

        tmp = (tmp * fact(counter)) % m;
    }

    route = (route + tmp) % m;
}

void vrp(int ind, int cus, int pos){

    for (int i = pos; i < store.size(); ++i){

        if (ind == truck_num){

            if (cus == store[i]){

                truck[ind] = cus;

                return checkRoute();
            }
        }
        else if (isInclude(store[i], cus)){
            
            truck[ind] = store[i];

            vrp(ind + 1, cus - store[i], i + 1);
        }
    }
}

//
int main(int argc, char **argv){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //INPUT
    cin >> cus_num >> truck_num >> max_cap;

    for (int i = 1; i <= cus_num; ++i){

        int tmp = 0;  cin >> tmp;

        order.push_back(tmp);
    }

    //
    for (int i = 1; i <= (1 << cus_num) - 1; ++i){

        if (cap(i) <= max_cap){

            store.push_back(i);
        }
    }

    truck.resize(truck_num + 1);

    vrp(1, (1 << cus_num) - 1, 0);

    //OUTPUT
    cout << route;

    return 0;
}
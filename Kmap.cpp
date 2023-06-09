// Karnaugh Map implementation

# include <iostream>
# include <vector>
# include <algorithm>
# include <cmath>
using namespace std;

vector<bool> visited;

vector<int> convertBinary(int n){
    if(n == 0){
        return {0};
    }

    vector<int> ans;

    while(n != 0){
        ans.push_back(((n%2 == 1)? 1:0));
        n = n/2;
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

int convertDecimal(vector<int> n){
    int ans = 0;

    int degree = (n.size() - 1);
    for(auto i : n){
        ans += i*pow(2, degree);
        degree --;
    }

    return ans;
}

bool PrimeImplicants(vector<int> input, int n, int variableCount, vector<int> &unique_1){
    visited[n] = true;

    vector<int> binary = convertBinary(n);  // Converting tapped number 'n' into binary

    // For converting it into 4-bit or 3-bit or 2-bit binary based on variableCount
    vector<int> bits;
    for(int i = 0; i < (variableCount - binary.size()); i++){
        bits.push_back(0);
    }
    for(int i = (variableCount - binary.size()); i < variableCount; i++){
        bits.push_back(binary[i - variableCount + binary.size()]);
    }

    // For getting next paired number
    vector<int> adjNo;
    for(auto i : bits){
        adjNo.push_back(i);
    }

    for(auto &i : adjNo){
        i = !i;
        int idx = convertDecimal(adjNo);
        if(abs(input[idx]) == 1){
            visited[n] = false;
            return false;
        }
        i = !i;
    }

    unique_1.push_back(n);   // Sending unique 1's
    return true;
}

bool uniqueGroupOf2(vector<int> input, int n, int variableCount, vector<vector<int>> &unique_2){
    visited[n] = true;

    vector<int> binary = convertBinary(n);  // Converting tapped number 'n' into binary

    // For converting it into 4-bit or 3-bit or 2-bit binary based on variableCount
    vector<int> bits;
    for(int i = 0; i < (variableCount - binary.size()); i++){
        bits.push_back(0);
    }
    for(int i = (variableCount - binary.size()); i < variableCount; i++){
        bits.push_back(binary[i - variableCount + binary.size()]);
    }

    // For getting next paired number
    vector<int> adjNo;
    for(auto i : bits){
        adjNo.push_back(i);
    }

    int count = 0;
    vector<int> arr;
    for(auto &i : adjNo){
        i = !i;
        int idx = convertDecimal(adjNo);
// cout<<idx<<" : "<<input[idx]<<" : ";
        if(abs(input[idx]) == 1){
            arr.push_back(idx);
            visited[idx] = true;
            count ++;
        }
        i = !i;
// cout<<count<<" Hi"<<endl;
        
        if(count > 1){
            visited[n] = false;
            for(auto &i : arr){
                if(input[i] == -1){
                    continue;
                }
                visited[i] = false;
            }

            return false;
        }
    }

    unique_2.push_back({n, arr[0]});   // Sending Unique 2's

    return true;
}

bool uniqueGroupOf4(vector<int> input, int n, int variableCount, vector<vector<int>> &unique_4){
    visited[n] = true;

    vector<int> binary = convertBinary(n);  // Converting tapped number 'n' into binary

    // For converting it into 4-bit or 3-bit or 2-bit binary based on variableCount
    vector<int> bits;
    for(int i = 0; i < (variableCount - binary.size()); i++){
        bits.push_back(0);
    }
    for(int i = (variableCount - binary.size()); i < variableCount; i++){
        bits.push_back(binary[i - variableCount + binary.size()]);
    }

    // For getting next paired number
    int adjNo[variableCount];
    for(int i = 0; i < variableCount; i++){
        adjNo[i] = bits[i];
    }

    int count = 0;
    vector<vector<int>> arr;
    
    for(int i = 0; i < variableCount; i++){
        for(int j = (i + 1); j < variableCount; j++){
            vector<int> idx;
            int temp1 = adjNo[i];
            int temp2 = adjNo[j];
            for(int k = 0; k < 4; k++){
                if(k == 0){
                    adjNo[i] = 0;
                    adjNo[j] = 0;
                }
                else if(k == 1){
                    adjNo[i] = 0;
                    adjNo[j] = 1;
                }
                else if(k == 2){
                    adjNo[i] = 1;
                    adjNo[j] = 0;
                }
                else if(k == 3){
                    adjNo[i] = 1;
                    adjNo[j] = 1;
                }

                vector<int> v = {adjNo[0], adjNo[1], adjNo[2], adjNo[3]};
                idx.push_back(convertDecimal(v));

                adjNo[i] = temp1;
                adjNo[j] = temp2;
            }

            if((abs(input[idx[0]]) == 1) && (abs(input[idx[1]]) == 1) && (abs(input[idx[2]]) == 1) && (abs(input[idx[3]]) == 1))
            {
                arr.push_back({idx[0], idx[1], idx[2], idx[3]});

                visited[idx[0]] = true;
                visited[idx[1]] = true;
                visited[idx[2]] = true;
                visited[idx[3]] = true;

                count ++;
            }

            idx.clear();

            if(count > 1){
                visited[n] = false;
                for(auto row : arr){
                    for(auto col : row){
                        if(input[col] == -1){
                            continue;
                        }
                        visited[col] = false;
                    }
                }
                return false;
            }
        }
    }

    unique_4.push_back({arr[0][0], arr[0][1], arr[0][2], arr[0][3]});   // Sending Unique 4's

    return true;
}

bool uniqueGroupOf8(vector<int> input, int n, int variableCount, vector<vector<int>> &unique_8){
    visited[n] = true;

    vector<int> binary = convertBinary(n);  // Converting tapped number 'n' into binary

    // For converting it into 4-bit or 3-bit or 2-bit binary based on variableCount
    vector<int> bits;
    for(int i = 0; i < (variableCount - binary.size()); i++){
        bits.push_back(0);
    }
    for(int i = (variableCount - binary.size()); i < variableCount; i++){
        bits.push_back(binary[i - variableCount + binary.size()]);
    }

    // For getting next paired number
    int adjNo[variableCount];
    for(int i = 0; i < variableCount; i++){
        adjNo[i] = bits[i];
    }

    int count = 0;
    vector<vector<int>> arr;
    
    for(int i = 0; i < variableCount; i++){
        for(int j = (i + 1); j < variableCount; j++){
            for(int l = (j + 1); l < variableCount; l++){
                vector<int> idx;
                int temp1 = adjNo[i];
                int temp2 = adjNo[j];
                int temp3 = adjNo[l];
                for(int k = 0; k < 8; k++){
                    if(k == 0){
                        adjNo[i] = 0;
                        adjNo[j] = 0;
                        adjNo[l] = 0;
                    }
                    else if(k == 1){
                        adjNo[i] = 0;
                        adjNo[j] = 0;
                        adjNo[l] = 1;
                    }
                    else if(k == 2){
                        adjNo[i] = 0;
                        adjNo[j] = 1;
                        adjNo[l] = 0;
                    }
                    else if(k == 3){
                        adjNo[i] = 0;
                        adjNo[j] = 1;
                        adjNo[l] = 1;
                    }
                    else if(k == 4){
                        adjNo[i] = 1;
                        adjNo[j] = 0;
                        adjNo[l] = 0;
                    }
                    else if(k == 5){
                        adjNo[i] = 1;
                        adjNo[j] = 0;
                        adjNo[l] = 1;
                    }
                    else if(k == 6){
                        adjNo[i] = 1;
                        adjNo[j] = 1;
                        adjNo[l] = 0;
                    }
                    else if(k == 7){
                        adjNo[i] = 1;
                        adjNo[j] = 1;
                        adjNo[l] = 1;
                    }
    
                    vector<int> v = {adjNo[0], adjNo[1], adjNo[2], adjNo[3]};
                    idx.push_back(convertDecimal(v));
    
                    adjNo[i] = temp1;
                    adjNo[j] = temp2;
                    adjNo[l] = temp3;
                }
    // cout<<input[idx[0]]<<input[idx[1]]<<input[idx[2]]<<input[idx[3]]<<input[idx[4]]<<input[idx[5]]<<input[idx[6]]<<input[idx[7]]<<endl;
                if((abs(input[idx[0]]) == 1) && (abs(input[idx[1]]) == 1) && (abs(input[idx[2]]) == 1) && (abs(input[idx[3]]) == 1) && (abs(input[idx[4]]) == 1) && (abs(input[idx[5]]) == 1) && (abs(input[idx[6]]) == 1) && (abs(input[idx[7]]) == 1))
                {
                    arr.push_back({idx[0], idx[1], idx[2], idx[3], idx[4], idx[5], idx[6], idx[7]});
    
                    visited[idx[0]] = true;
                    visited[idx[1]] = true;
                    visited[idx[2]] = true;
                    visited[idx[3]] = true;
                    visited[idx[4]] = true;
                    visited[idx[5]] = true;
                    visited[idx[6]] = true;
                    visited[idx[7]] = true;
    
                    count ++;
                }
    
                idx.clear();
    
                if(count > 1){
                    visited[n] = false;
                    for(auto row : arr){
                        for(auto col : row){
                            if(input[col] == -1){
                                continue;
                            }
                            visited[col] = false;
                        }
                    }
                    return false;
                }
            }
        }
    }

    unique_8.push_back({arr[0][0], arr[0][1], arr[0][2], arr[0][3], arr[0][4], arr[0][5], arr[0][6], arr[0][7]});   // Sending Unique 8's

    return true;
}

int main()
{
    vector<int> unique_1;
    vector<vector<int>> unique_2;
    vector<vector<int>> unique_4;
    vector<vector<int>> unique_8;
    vector<vector<int>> leftOver;

    int variableCount = 4;
    // cout<<"Enter the number of variables : ";
    // cin>>variableCount;

    int size = pow(2, variableCount);
// {2, 1, 2, 1, 0, 2, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}
    vector<int> input/*(size)*/ = {-1, 1, -1, 1, 0, -1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1};

    // cout<<"For DontCare enter -1 as output"<<endl;
    // for(int i = 0; i < size; i++){
    //     int x;
    //     cout<<"Enter output for "<<i<<" : ";
    //     cin>>x;
        
    //     input[i] = x;
    // }

    visited = vector<bool>(size, false);

    // For DontCare
    for(int i = 0; i < size; i++){
        if(input[i] == -1){
            visited[i] = true;
        }
    }

    for(int i = 0; i < size; i++){
        if((input[i] == 1) && (!visited[i])){
            cout<<"Tapped on "<<i<<" : "<<endl;
            if(PrimeImplicants(input, i, variableCount, unique_1)){
                cout<<"Unique group of 1 is possible"<<endl;
            }
        }
    }
    cout<<endl;

    for(int i = 0; i < size; i++){
        if((input[i] == 1) && (!visited[i])){
            cout<<"Tapped on "<<i<<" : "<<endl;
            if(uniqueGroupOf2(input, i, variableCount, unique_2)){
                cout<<"Unique group of 2 is possible"<<endl;
            }
        }
    }
    cout<<endl;

    for(int i = 0; i < size; i++){
        if((input[i] == 1) && (!visited[i])){
            cout<<"Tapped on "<<i<<" : "<<endl;
            if(uniqueGroupOf4(input, i, variableCount, unique_4)){
                cout<<"Unique group of 4 is possible"<<endl;
            }
        }
    }
    cout<<endl;
    
    if(variableCount != 2){
        for(int i = 0; i < size; i++){
            if((input[i] == 1) && (!visited[i])){
                cout<<"Tapped on "<<i<<" : "<<endl;
                if(uniqueGroupOf8(input, i, variableCount, unique_8)){
                    cout<<"Unique group of 8 is possible"<<endl;
                }
            }
        }
    }

    for(int i = 0; i < size; i++){
        if((input[i] == 1) && (!visited[i])){
            cout<<"Tapped on "<<i<<" : "<<endl;
            if(uniqueGroupOf8(input, i, variableCount, leftOver)){
                cout<<"Group of 8 is possible for left-over"<<endl;
            }
            else if(uniqueGroupOf4(input, i, variableCount, leftOver)){
                cout<<"Group of 4 is possible for left-over"<<endl;
            }
            else if(uniqueGroupOf2(input, i, variableCount, leftOver)){
                cout<<"Group of 2 is possible for left-over"<<endl;
            }
        }
    }

cout<<"unique_1 : "<<endl;
    for(auto i : unique_1){
        cout<<i<<" ";
    }cout<<endl;

cout<<"unique_2 : "<<endl;
    for(auto i : unique_2){
        for(auto j : i){
            cout<<j<<" ";
        }cout<<endl;
    }

cout<<"unique_4 : "<<endl;
    for(auto i : unique_4){
        for(auto j : i){
            cout<<j<<" ";
        }cout<<endl;
    }

cout<<"unique_8 : "<<endl;
    for(auto i : unique_8){
        for(auto j : i){
            cout<<j<<" ";
        }cout<<endl;
    }

cout<<"LeftOver : "<<endl;
    for(auto i : leftOver){
        for(auto j : i){
            cout<<j<<" ";
        }cout<<endl;
    }

    return 0;
}
/*********************************************************************8
 * Hunter Sawyer Final Project for Cloud security
 * 
 * 
 * 2311454904407092407092395441475456190789281233954413042104070921235921285061907891907892311423114475456293910293910475456361241338493292852028303404095490419078954904298571123592
*/

#include"asymetric_key_gen.h"
#include"symm.h"
#include "stdlib.h"
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

struct access_key_info
{
    int e = 59;
    int d = 295283;
    int n = 485357;

    int integrity = 280183;
};
access_key_info access_key_info_O;
asymetric_key_gen key_generator;



string open_access_control(){
    fstream fin,fout;

    fin.open("security",fstream::in);

    if (fin.is_open()){
        char c;
        vector<int> encrypted_message;
        string s;
        while (fin >> noskipws >> c){

            if (c == ',')
            {
                encrypted_message.push_back(stoi(s));
                s = "";
            }else{
              s+=c;  
            }
            
            
        }


    fin.close();

    cout<<endl;
    for (auto& i: encrypted_message)
    {
        cout<<i;
    }
    cout<<endl<<encrypted_message.size()<<endl;

    std::string message =  key_generator.decoder(access_key_info_O.d,encrypted_message,access_key_info_O.n);


    return message;
    }
}

vector<vector<string>> parse_priviledge(string security_contents){

    string S;
 
    std::stringstream X(security_contents);

    vector<vector<string>> parsed_array (5, vector<string>(0));



    int access_counter = 1;
    

    //type being a representation of whether the string is a security level or a file. with 0 being a level and 1 being a file
    int type = 0;

    getline(X,S);

    while (getline(X,S))
    {
        if (S == "{")
        {
            type +=1;
        }else if (S == "}")
        {
            type-=1;
        }else{
            if (access_counter == 0)
            {
                parsed_array[access_counter][0] =S;
                access_counter +=1;
            }else if (access_counter == 1)
            {
                
            }
            
        }
        
        
        
        
    }

    

}


int check_for_access(int requested_access_level){
    
    string access_file_contents = open_access_control();


    if (stoi(access_file_contents.substr(0,(to_string(access_key_info_O.integrity).length()) == access_key_info_O.integrity)))
    {
        vector<vector<string>> access_matrix;
        access_matrix = parse_priviledge(access_file_contents);
    }else{
        return -1;
    }
    

}



int main(int argc, char* argv[]){
    edcode edcrypter(argc,argv);

    key_generator.encrypt_file(access_key_info_O.e,"security",access_key_info_O.n);



    string message = open_access_control();


    cout<<endl<<message;

     cout << check_for_access(5);

    key_generator.decrypt_file(access_key_info_O.d,"security",access_key_info_O.n);   

   

    //cout<<open_access_control();

    //cout << sizeof(edcrypter.files)/sizeof(edcrypter.files[0]) + "\n";

    /*cout<<"enter your access level";
    int level;
    cin>>level;



    char c;
    cout << "\n";
    cout << "Enter Your Choice : -> \n";
    cout << "1. encrypt \n";
    cout << "2. decrypt \n";
    cout << "3. encryptall \n";
    cin >> c;
    cin.ignore();
 
    switch (c) {
        case '1': {
            string file_name;
            cout << "enter name";
            cin >> file_name;
            edcrypter.encrypt(file_name);
            break;
        }
        case '2': {
            string file_name;
            cout << "enter name \n";
            cin >> file_name;
            edcrypter.decrypt(file_name);
            break;
        }
        case '3':{
            edcrypter.encrypt_all();
        }
    }
    */

}






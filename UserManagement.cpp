/*********************************************************************8
 * Hunter Sawyer Final Project for Cloud security
 * 
 * 
 * 2311454904407092407092395441475456190789281233954413042104070921235921285061907891907892311423114475456293910293910475456361241338493292852028303404095490419078954904298571123592
*/

#include"asymetric_key_gen.h"
#include"symm.h"
//#include "stdlib.h"
#include<iostream>
#include<sstream>
#include<vector>
#include<random>

using namespace std;

struct access_key_info
{
    int e = 59;
    int d = 295283;
    int n = 485357;

    //integrity check at the top of every file to verify it has not been tampered with
    int integrity = 280183;

    int user_private_key = -1;
    int user_access_index = -1;

    vector<vector<string>> security_matrix;
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


    std::string message =  key_generator.decoder(access_key_info_O.d,encrypted_message,access_key_info_O.n);


    return message;
    }
}

vector<vector<string>> parse_priviledge(string security_contents){

    
    string S;
 
    std::stringstream X(security_contents);

    vector<vector<string>> parsed_array (0, vector<string>(0));


    int rows,columns = 0;

    //counts the number of security types there are.
    int sec_counter = 0;

    //counts the max number of files for resizing
    int file_counter = 0;
    

    //type being a representation of whether the string is a security level or a file. with 0 being a level and 1 being a file
    int type = 0;

    getline(X,S);

    while (getline(X,S))
    {
        //cout<<"S: "<<S<<endl;
        if (S == "{")
        {
            type +=1;

            //cout<<"{"<<endl;
        }else if (S == "}")
        {
            type-=1;
            //cout<<"}"<<endl;
        }else{
            if (type == 0)
            {
                //cout<<"T0"<<endl;
                parsed_array.push_back(vector<string>({S}));
                sec_counter+=1;
                
            }else if (type == 1)
            {
                //cout<<"T1: "<<endl;
                parsed_array[sec_counter-1].push_back(S);
            }
                        
        }
        
    }

    return parsed_array;

}


string random_string_generation(int length){


    const string list = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    random_device RD;
    mt19937 generator(RD());

    uniform_int_distribution<> distribution(0,list.size() -1);

    string SR;


    for (int i = 0; i < length; ++i)
    {
        SR += list[distribution(generator)];
    }

    return SR;

}

int check_for_access(string requested_access_level){
    
    string access_file_contents = open_access_control();

    cout<<access_file_contents.substr(0,(to_string(access_key_info_O.integrity).length()));


    if (std::stoi(access_file_contents.substr(0,(to_string(access_key_info_O.integrity).length()))) == access_key_info_O.integrity)
    {


        cout<<"inner";
        cout<<access_key_info_O.security_matrix.size();
        for (int i = 0; i < access_key_info_O.security_matrix.size(); i++)
        {
            cout<<"innerdinner";
            cout<<access_key_info_O.security_matrix[i][0];
            if (access_key_info_O.security_matrix[i][0].find(requested_access_level) != string::npos)
            {
                //can be modified for longer string sizes if the key is kept short
                string RS = random_string_generation(6);

                string access_info = access_key_info_O.security_matrix[i][0];

                string public_key =access_info.substr(access_info.find(',')+1);

                int n = stoi(public_key.substr(public_key.find(',')+1));
                int Pub_key_int = stoi(public_key.substr(0,public_key.find(',')));



                cout<<endl<<public_key<<endl<<Pub_key_int<<endl<<n;


                cout<<"enter your private key";
                int private_key;
                cin>>private_key;

                vector<int> encrypted = key_generator.encoder(Pub_key_int,RS,n);

                cout<<key_generator.decoder(private_key,encrypted,n);

                if (RS == key_generator.decoder(private_key,encrypted,n))
                {
                    access_key_info_O.user_access_index = i;
                    access_key_info_O.user_private_key = private_key;

                    cout<<endl<<"private key accepted"<<endl;
                    return 0;
                }else{
                    return -1;
                }
                

            }else
            {
            return -1;
            }
            
        }
        

        
    }else{
        return -1;
    }
    

}





int main(int argc, char* argv[]){

    //key_generator.encrypt_file(access_key_info_O.e,"security",access_key_info_O.n);

    edcode edcrypter(argc,argv);

    string message = open_access_control();

    

    vector<vector<string>> priviledge_matrix= parse_priviledge(message);

    access_key_info_O.security_matrix = priviledge_matrix;



    


    /*

    
    

    */


    /*for (int i = 0; i < priviledge_matrix.size(); i++)  
    { 
        for (int j = 0; j < priviledge_matrix[i].size(); j++) 
        { 
            cout << priviledge_matrix[i][j] << " "; 
        }     
        cout << endl; 
    } 
    */


   // key_generator.decrypt_file(access_key_info_O.d,"security",access_key_info_O.n);   

   

    //cout<<open_access_control();

    //cout << sizeof(edcrypter.files)/sizeof(edcrypter.files[0]) + "\n";


    string user;
    cout<<"enter your security_level";

    string access_level = "security_1";


    while (check_for_access(access_level)!=0)
    {
        cout<<"enter access level";
        cin>>access_level;
    }
    
    
    

    char c;
    cout << "\n";
    cout << "Enter Your Choice : -> \n";
    cout << "1. encrypt \n";
    cout << "2. decrypt \n";
    cout << "3. encryptall \n";
    cout << "4. generate key pair\n";
    cin >> c;
    cin.ignore();
 
    switch (c) {
        case '1': {
            string file_name;
            cout << "enter name";
            cin >> file_name;
            

            bool valid = 0;
            for (int i = 0; i < access_key_info_O.security_matrix[access_key_info_O.user_access_index].size(); i++)
            {
                if (access_key_info_O.security_matrix[access_key_info_O.user_access_index][i] == file_name)
                {
                    valid = true;
                    break;
                }
                
            }
            if (valid)
            {
                key_generator.encrypt_file(access_key_info_O.e,file_name,access_key_info_O.n);
            }
                    
             

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

        case '4':{
            double * keys = key_generator.generate_key_pair();

            cout << keys[0]<<","<<keys[1]<<","<<keys[2];
        }
    }
    

}






/*********************************************************************8
 * Hunter Sawyer Final Project for Cloud security
 * 
 * 
 * 2311454904407092407092395441475456190789281233954413042104070921235921285061907891907892311423114475456293910293910475456361241338493292852028303404095490419078954904298571123592
*/

#include"asymetric_key_gen.h"
#include"symm.h"
#include "stdlib.h"
#include<vector>

using namespace std;

struct access_key_info
{
    int e = 59;
    int d = 295283;
    int n = 485357;
};
access_key_info access_key_info_O;
asymetric_key_gen key_generator;

string open_access_control(){
    fstream fin,fout;

    fin.open("security",fstream::in);

    if (fin.is_open()){
        char c;
        vector<int> encrypted_message;
        while (fin >> noskipws >> c){
            encrypted_message.push_back((int)c - '0');
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

int check_for_access(int requested_access_level){
    

}



int main(int argc, char* argv[]){
    edcode edcrypter(argc,argv);

    //key_generator.encrypt_file(access_key_info_O.e,"security",access_key_info_O.n);



    string message = open_access_control();

    cout<<endl<<message;
    
    

    
    /*std::string unencrypted_message = "hello \nworlds\n\nhh -- Lkjame\nend";
    cout << unencrypted_message<<endl;
    
    std::vector<int> encrypted_message = key_generator.encoder(access_key_info_O.e,unencrypted_message,access_key_info_O.n);

    for (auto& p : encrypted_message)
        cout << p;
    cout<<endl<<encrypted_message.size();

    string message_end = key_generator.decoder(access_key_info_O.d,encrypted_message,access_key_info_O.n);

    cout << "final message " << message_end;

    */

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






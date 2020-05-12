
#include<string>
#include<iostream>
#include<fstream>
# define MAX 1000
using namespace std;

typedef struct
{
    string word;
    string version;
    string production;
    bool production_print;
}
candidate;
void reading_file(candidate [],int word_count);
int call_NP(candidate[],int j,int word_count,int check_bit );
void call_VB(candidate[],int j,int word_count);
int call_PP(candidate[], int j, int word_count);
int  Nominal(candidate[], int j, int word_count);
void print_production_structure( candidate[], int word_count);
int VPNPPPs(candidate[],int word_count, int t);
void call_Invalid(void);
bool count_NP = false;
bool count_PP = false;
bool count_VP = false;
bool count_Nominal = false;
bool count_VPNPPP = false; 
void call_toupper(string &s);
int index = 0;
int main(void)
{

    cout <<"PROJECT    :    CFG IMPLEMENTATION \n";
    cout <<"SUBJECT    :    THEORY OF COMPUTATION\n";
    cout << endl;


    string input_user;
    cout << "Enter a sentence :  ";
    getline(cin,input_user);
    cout << endl;
    int x = input_user.length();
    string array[1000];
    int j = 0;
    string individual;
    int word_count = 0;
    for (int i = 0, n = input_user.length(); i < n; i++)
      {
        if (input_user[i] != ' ')
        {
            individual = individual + input_user[i];
            if (i == n -1)
            {
                array[j] = individual;
                word_count++;
            }
        }
        else if (input_user[i]== ' '  )
        {
            array[j] = individual;
           // cout << array[j];
            j++;
            individual = "";
            word_count++;
        }
      }
    //cout << word_count << endl;
    //int MAX = word_count;
candidate candidates[MAX]; 
    
    for (int i = 0; i < word_count; i++)
    {
        candidates[i].word = array[i];
        candidates[i].version = "";
        candidates[i].production = "";
        candidates[i].production_print = false;

    }
    reading_file(candidates,word_count);
    
    int y0 = call_NP(candidates, 0,word_count,0);
    
    call_VB(candidates, y0,word_count);
    cout << endl;
    cout << "S NP VP" << endl;

    print_production_structure(candidates, word_count);
    
    cout << endl;
    return 0 ;
    
 }
void reading_file(candidate candidates[],int word_count)
{
    string duplicate[8] = { "Noun","Adjective","Verb","Preposition","Conjunction","Determiners","ProperNoun","Pronouns" };
//    bool found = false;
    bool flag = false;
    int j = 0;
    ifstream point;
    std::string s;
    string _local;
    string file_name[8] = {"noun.txt","adjective.txt","verb.txt","preposition.txt","conjunction.txt","determiners.txt","propernoun.txt","pronouns.txt"};
    for (int j = 0; j < word_count; j++)
    {
    
        for (int i = 0; i < 8; i++)
        {

            point.open(file_name[i]);
            if (point.fail())
            {
                //cout << "file not opened\t"<<file_name[i]<<endl;

            }
            else
            {
                //cout << "File opened \t"<<file_name[i]<<endl;
                


                while (!point.eof())
                {
                    point >> s;
                    //getline(point, s);
                    _local = candidates[j].word;
                   call_toupper(_local);
                    if (s == _local)
                    {
                  
                         candidates[j].version = duplicate[i];
                        //cout << duplicate[i] <<"\n";
                        if (candidates[j].version == "Adjective" || candidates[j].version == "Pronouns" || candidates[j].version == "Determiners" || candidates[j].version == "Noun")
                        {
                            candidates[j].production = "NP";
                            break;
                        }
                        if (candidates[j].version == "ProperNoun")
                        {
                            candidates[j].production = "NP";
                            break;
                        }
                        if (candidates[j].version == "Verb")
                        {
                            candidates[j].production = "VP";
                            break;
                        }
                        if (candidates[j].version == "Preposition")
                        {
                            candidates[j].production = "PP";
                            break;
                        }
                        break;
                    }
                    
                }
                
            point.close();
            
            }

        }
    
}
}
int call_NP(candidate candidates[], int j,int word_count,int check_bit)
 {
    if (candidates[j].version == "Determiners")
    {
        count_NP = true;
        
        j++;
        j=Nominal(candidates,j,word_count);
        if (count_Nominal == false)
        {
            cout << "Invalid Sentence Structure \n";
            cout << endl;
            cout << endl;
            call_Invalid();
            cout << endl; 
            exit(1);
        }
        //cout << word_count;
        if ( check_bit == 0 )
        {
            if (j != word_count && (count_VP == true || count_PP == true ) )
            {
                cout << "Invalid Sentence Structure \n";
                cout << endl;
                cout << endl;
                call_Invalid();
                cout << endl;
                exit(1);
            }

        }
    }
    else if (candidates[j].version == "ProperNoun")
    {
        count_NP = true;
        
        j++;
    }
    else
    {//adjective ondition is missing .filing thori theek kni h  
        count_NP = true;
        
        
        j++;
    }
    if (count_NP == false) 
    {
        cout << "Invalid Sentence Structure\n\n\n";
        call_Invalid();
        cout << endl;
        exit(1);
    }
    else if (count_NP == true)
    {
        count_NP = false;
        
    }
    return j;


}
void call_VB(candidate candidates[], int j, int word_count)
{

    int y = VPNPPPs(candidates, word_count,j);
    if (candidates[j].version == "Verb" && candidates[j+1].production == "NP" && count_VPNPPP == true)
    {
        
        j++;
        candidates[j].production_print = true;
        j = call_NP(candidates,j,word_count,1);
     
        j=call_PP(candidates,j,word_count);
     
        count_VP = true;
        if (j != word_count )
        {
            cout << "Invalid Sentence Structure\n\n\n";
            call_Invalid();
            cout << endl;
            exit(1);
        }
        return;
    }

    
    
        if (candidates[j].version == "Verb" && candidates[j + 1].production == "NP")
        {
    
            j++;
            j = call_NP(candidates, j, word_count, 0);
            
            count_VP = true;

            if (j != word_count)
            {
                cout << "Invalid Sentence Structure\n\n\n";
                call_Invalid();
                exit(1);
            }
            return;
        }

        if (candidates[j].version == "Verb" && candidates[j + 1].production == "PP")
        {
            j++;
            j = call_PP(candidates, j, word_count);
            count_VP = true;
            if (j != word_count)
            {
                cout << "Invalid Sentence Structure  \n\n\n";
                call_Invalid();
                exit(1);
            }
            return;
        }
   

        if (candidates[j].production == "VP") {
            count_VP = true;
            if (j != word_count - 1)
            {
                cout << "Invalid Sentence Structure \n\n\n";
                call_Invalid();
                cout << endl;
                exit(1);
            }
            return;
        }
    
        if (count_VP == false)
       {
        cout << "Invalid Sentence Structure\n\n\n";
        call_Invalid();
        cout << endl;
        exit(1);
        }
    
}

int call_PP(candidate candidates[], int j,int word_count)
{
    if (candidates[j].production == "PP" && candidates[j+1].production == "NP")
    {
            
        count_PP = true;
             
        j++;
              
        j = call_NP(candidates, j, word_count,0);
       }
 
        

    
    if (j != word_count )
    {
        
        cout << "Invalid Sentence Structure\n\n\n";
        call_Invalid();
        cout << endl;
        exit(1);
    }
    if ( count_PP == false)
    {                                                                   // non benefit 
        cout << "Invalid Sentence Structure\n\n\n";
        call_Invalid();
        cout << endl;
        exit(1);
    }
    
    return j ;

}
int Nominal(candidate candidates[], int j, int word_count)
{
    if (j >= word_count || candidates[j].production != "NP")
    {
        
        return j;
    }
    else
    {
        
        if (candidates[j].version == "Noun")
        {
            candidates[j].production = "Nominal";
            count_Nominal = true;
            

            j++;
        j =    Nominal(candidates, j, word_count);
        }
    }
}
void print_production_structure(candidate candidates[], int word_count)
{
    string recurrency = "";
    bool is_occupied = false;
    string array = "";
    bool istrue = false;
    bool is_false = false;
    for (int i = 0; i < word_count; i++)
    {
        is_occupied = false;
        if (i + 1 > word_count)
        {
            cout << array << " " << candidates[i].version << endl;
            cout << array << " " << candidates[i].word << endl;
            return;
        }
        if (i == 0)
        {
            is_occupied = true;
            if (candidates[i].version == "Determiners")
            {
                cout << candidates[i].version << " Nominals VP" ;
                if (count_VPNPPP == true)
                {
                    cout << " NP PP ";

                }
                
                cout << endl;    
                istrue = true;
                cout << candidates[i].word << " Nominal VP";
                if (count_VPNPPP == true)
                {
                    cout << " NP PP ";

                }
                cout << endl;

            
            }
            else
            {
                cout << candidates[i].version << "s VP";
                if (count_VPNPPP == true)
                {
                   cout << " NP  PP";
                }
                cout << endl;
                cout << candidates[i].word << " VP";
                if (count_VPNPPP == true)
                {
                    cout << " NP PP";
                }
                cout << endl;
            }
        
        }
         if (candidates[i].production == "VP")
        {
             is_occupied = true;
             istrue = false;
            if (count_VPNPPP == true)
            {
            cout << array <<" "<< candidates[i].version <<" NP PP"<<endl;
            cout << array <<" " << candidates[i].word << " NP PP" << endl;
            }
            else
            {
                cout << array <<" " << candidates[i].version << " " << candidates[i+1].production << endl;
                cout << array <<" " << candidates[i].word   <<" " << candidates[i+1].production << endl;

                
            }
        }
         if (istrue == true && candidates[i].production != "VP" && i != 0 )
        {
            
             is_occupied = true;
                if (candidates[i + 1].production == "Nominal")
                {
                    
                    cout << array << "  " <<candidates[i].version << " Nominal " << " VP";
                    if (count_VPNPPP == true)
                    {
                     cout    << " NP PP "<<endl;

                    }
                    cout << endl;
                    cout << array << " " << candidates[i].word << " Nominal" << " VP";
                    if (count_VPNPPP == true)
                    {
                        cout << "NP PP " << endl;

                    }
                    cout << endl;
                }
                else
                {

                    cout << array <<" " << candidates[i].version << " VP";
                    if (count_VPNPPP == true)
                    {
                        cout << " NP  PP";
                    }
                    cout << endl;
                    cout << array <<" "<<candidates[i].word << " VP";
                    if (count_VPNPPP == true)
                    {
                        cout << " NP PP";
                    }
                    cout << endl;
                 
                }
        }
 
     
        else if (is_occupied == false)
        {
            if (count_VPNPPP == true && (candidates[i].production_print == false || candidates[i + 1].production_print == false))
            {
                cout << array << " " << candidates[i].version << " " << candidates[i + 1].production;
                if (candidates[i + 1].production != "PP" && is_false== false && count_VPNPPP)
                {
                    cout << " PP\n";
                }
                else
                {
                    is_false = true;
                }
                    cout << endl;
                cout << array << " " << candidates[i].word << " " << candidates[i + 1].production;
                if (candidates[i + 1].production != "PP" && is_false == false) 
                {
                    cout << " PP\n";
                }
                else
                {
                    is_false = true;
                }
                    cout << endl;
            }
            else
            {
                cout << array << " " << candidates[i].version << "  " << candidates[i + 1].production << endl;
                cout << array << " " << candidates[i].word << "  " << candidates[i + 1].production << endl;
            }
        }
            array = array + " " + candidates[i].word;
    }
}
int VPNPPPs(candidate candidates[],int word_count,int j)
{
    if (candidates[j + 1].production == "NP")
    {

        int i = j + 1;
        for (int t = i; t < word_count; t++)
        {
            if (candidates[t].production == "PP")
            {
                count_VPNPPP = true;
                return t;
                
            }
        }
    }
}
// remem
void call_toupper(string &s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >='A' && s[i] <= 'Z')
        {
            s[i] += 32;
        }
    }
}
void call_Invalid(void)
    {
        cout << "NOTE:\n";
        cout << "1) If sentence is invalid,make sure if sentence structure is a/c to CFG PRODUCTIONS.\n";
        cout << "2)  Check if words in Sentence are included in required .txt file\n";
        cout << "3) Use Camel Notation for ProperNoun\n";
    }












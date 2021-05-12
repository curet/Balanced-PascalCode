// JOSE C.S. CURET

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

class Pascal{
private:

    const string BEGIN = "begin";
    const string END = "end";
    const string OPEN_CURLY_BRACKETS = "{";
    const string CLOSE_CURLY_BRACKETS  = "}";
    const string OPEN_PARENTHESIS = "(";
    const string CLOSE_PARENTHESIS = ")";
    const string OPEN_BRACKETS = "[";
    const string CLOSE_BRACKETS = "]";
    const string POSSIBLE_SYMBOLS = {OPEN_CURLY_BRACKETS[0], CLOSE_CURLY_BRACKETS[0],
                                     OPEN_PARENTHESIS[0], CLOSE_PARENTHESIS[0],
                                     OPEN_BRACKETS[0], CLOSE_BRACKETS[0]};
    stack <string> st;
    string pascalCode;

public:

    Pascal(){ pascalCode = ""; st = fileIntoStack();}
    int catchReservedWord(const int& iterPosition, string reservedWord);
    bool openingSymbol(const string& value);
    string oppositeSymbol(const string& value);
    stack <string> fileIntoStack();
    bool isBalanced();

};


int main() {

    Pascal first;

    if (first.isBalanced()) cout << "The Pascal code is balanced!" << endl;
    else cout << "The Pascal code is NOT balanced!" << endl;

    return 0;
}

int Pascal::catchReservedWord(const int& iterPosition, string reservedWord){

    int init = 0,  iter = iterPosition, jump = 0;

    if(pascalCode[iter] == reservedWord[0]){

        bool equalReserved = true;
        for(int i = 0; i < reservedWord.size(); i++, iter++, jump++){

            if(pascalCode[iter] != reservedWord[i]){
                equalReserved = false;
            }
        }


        if(pascalCode[iter - 1] == reservedWord[reservedWord.size() - 1]){
            if(reservedWord == END){

                if((pascalCode[iter] != ';') && (pascalCode[iter] != '.') && (!isspace(pascalCode[iter]))){
                    equalReserved = false;
                }

            }else {

                if(!isspace(pascalCode[iter])){
                    equalReserved = false;
                }

            }

        }

        if(equalReserved){ st.push(reservedWord); return jump - 1;}
        else{ return init; }

    }

    return 0;
}

stack <string> Pascal::fileIntoStack(){

    ifstream openFile;
    string nameOfFile;

    cout << "Please enter the name of the file: ";
    cin >> nameOfFile;

    openFile.open(nameOfFile);
    while(!openFile){

        openFile.clear();
        cout << "Input failed!" << endl;
        cout << "Please try again: ";

        cin >> nameOfFile;
        openFile.open(nameOfFile);
    }


    string getCode;

    while(getline(openFile, getCode))
        pascalCode += getCode;

    openFile.close();

    if(pascalCode.empty()) return st;
    else{

        for(int i = 0; i < pascalCode.size(); i++){

            if(pascalCode[i] == 'b' || pascalCode[i] == 'e'){
               i += catchReservedWord(i, BEGIN);
               i += catchReservedWord(i, END);
            }

            for(char s : POSSIBLE_SYMBOLS){

                if(pascalCode[i] == s){

                    string tmp;
                    tmp.push_back(s);
                    st.push(tmp);
                    tmp.clear();
                }
            }
        }
    }


    return st;
}

bool Pascal::openingSymbol(const string& value){

    if(value == OPEN_BRACKETS || value == OPEN_CURLY_BRACKETS ||
       value == OPEN_PARENTHESIS || value == BEGIN) return true;

    return false;
}

string Pascal::oppositeSymbol(const string& value){

    string oppositeValue;

    if(openingSymbol(value)){

        if (value == OPEN_BRACKETS){return CLOSE_BRACKETS;}
        else if (value == OPEN_CURLY_BRACKETS){return CLOSE_CURLY_BRACKETS;}
        else if(value == OPEN_PARENTHESIS){ return CLOSE_PARENTHESIS;}
        else{return END;}

    }else{
        if (value == CLOSE_BRACKETS){return OPEN_BRACKETS;}
        else if (value == CLOSE_CURLY_BRACKETS){return OPEN_CURLY_BRACKETS;}
        else if(value == CLOSE_PARENTHESIS){ return OPEN_PARENTHESIS;}
        else{return BEGIN;}
    }

}

bool Pascal::isBalanced(){

    if(st.empty()) return true;

    stack <string> reversedStack;

    while(!st.empty()){
        reversedStack.push(st.top());
        st.pop();
    }

    stack <string> checkStatus;

    while(!reversedStack.empty()){

        if(openingSymbol(reversedStack.top())){
            checkStatus.push(reversedStack.top());
            reversedStack.pop();
        }else{
            if(checkStatus.empty()){
                return false;
            }else{
                if(checkStatus.top() != oppositeSymbol(reversedStack.top())){
                    return false;
                }else{
                    reversedStack.pop();
                    checkStatus.pop();
                }
            }

        }
    }

    if(!checkStatus.empty()) return false;

    return true;
}

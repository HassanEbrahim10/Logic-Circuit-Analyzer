#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>      
using namespace std;

vector<char> size(string s)
{
    set<char> st;
    for(char c : s)
    {
        if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') )
        {
            st.insert(c);
        }
    }
    return vector<char>(st.begin(), st.end());
}
void decrement(vector<bool>& bits) 
{
    for (int i = bits.size() - 1; i >= 0; i--) 
    {
        if (bits[i] == 1) {
            bits[i] = 0;
            break;
        } else 
        {
            bits[i] = 1;
        }
    }
}

string Edit_Equ (string s){
    string edit_equ ;
    vector<string> v;
    for(size_t i = 0; i < s.size();){
        if(s.substr(i, 3) == "∧") 
        {
            v.push_back("&");
            i += 3;
        }
        else if(s.substr(i, 3) == "∨") 
        {
            v.push_back("|");
            i += 3;
        }
        else 
        {
            v.push_back(string(1, s[i]));
            i++;
        }
    }
    for (auto x : v)
    {   
        if(x != " ")
            edit_equ += x;
    }
    return edit_equ;
}

bool calculate(vector<char> v)
{
    for (int i = 1; i < v.size(); i += 2)
    {
        if (v[i] == '&')
        {
            bool left  = (v[i - 1] == '1');
            bool right = (v[i + 1] == '1');
            bool res = left & right;
            v[i - 1] = res ? '1' : '0';
            v.erase(v.begin() + i, v.begin() + i + 2);
            i -= 2;
        }
    }
    bool result = (v[0] == '1');
    for (int i = 1; i < v.size(); i += 2)
    {
        bool next = (v[i + 1] == '1');
        result = result | next;
    }
    return result;
}

bool update (string s ,  vector<bool> bits , vector<char> inputs ){
    vector<char> v;
        for(int i = 0 ; i < s.size() ; i++)
            {   
                bool valid = false ;
                if(s[i] == '~')
                {
                    i++; if (i >= s.size()) break;
                    if (s[i] == '1' || s[i] == '0')
                        {
                            v.push_back(s[i] == '1' ? '0' : '1');
                            continue;
                        }     
                    for (size_t j = 0; j < inputs.size(); j++) 
                    {
                        if(inputs[j] == s[i]) 
                        {   
                            v.push_back(bits[j] ? '0' : '1');
                            valid = true ;
                            break;
                        }
                    }
                }
                else 
                {
                    for (size_t j = 0; j < inputs.size(); j++) 
                    {
                        if (inputs[j] == s[i]) 
                        {
                            if(bits[j] == 1)  v.push_back('1');
                            else  v.push_back('0');
                            valid = true ;
                            break;
                        }   
                    }
                }
                if(!valid) v.push_back(s[i]);
            }
        return calculate(v);
}

string go (vector<int> x , string s , vector<bool> bits , vector<char>& inputs)
{
    int end   = x[x.size()-1] - 1; 
    int start = x[x.size()-2] + 1;
    x.pop_back();
    x.pop_back();
    string part = s.substr(start, end - start + 1);
    bool result = update(part , bits , inputs);
    return result ? "1" : "0";
}

bool solver (string s ,const vector<bool> bits , vector<char> inputs)
{
    vector<int> range;
    bool check = false;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            check = true;
            range.push_back(i);
        }
        else if (s[i] == ')' && check)
        {
            range.push_back(i);
            int l = range[range.size() - 2];
            int r = range[range.size() - 1];
            string value = go(range, s, bits, inputs);
            s.replace(l, r - l + 1, value);
            return solver(s, bits, inputs);
        }
    }
    return update(s, bits, inputs);
}

void Check_tautology (vector<vector<int>> data , int rows , int columns , vector<char> inputs)
{
    int check = 0;
    bool ans = false;
    vector<int> Inputs_Satisfiable ;
    for(int i = 0 ; i < rows ; i++)
    {
        if(data[i][columns-1] == 1) 
        {
            check +=1;
            Inputs_Satisfiable.push_back(i);
        }
    }
    if(check == rows) 
    {
        cout << "\nThe expression is a Tautology!\n";
        cout << "Tip: You can try changing one gate (AND/OR/NOT) to see how it affects the output.\n";
    }
    else if(check < rows && check > 0)
    {
        cout << "\nSatisfiable with values:\n";
        for(int i = 0 ; i < Inputs_Satisfiable.size() ; i++)
        {
            for(int j = 0 ; j < inputs.size() ; j++)
            {
                cout << "\t" << inputs[j] << ": " << (data[Inputs_Satisfiable[i]][j] ? 'T' : 'F') ;
            }
            cout << "\n";
        }
    }
    else
    {
        cout << "\nThe expression is a Unsatisfiable!\n";
        cout << "Tip: You can try changing one gate (AND/OR/NOT) to see how it affects the output.\n";
    }
}

void check_equivalent (vector<vector<int>> Circuit_1 ,vector<vector<int>> Circuit_2 ,int rows , int columns , vector<char> inputs)
{
    bool check = true;
    for(int i = 0 ; i < rows ; i++){
        if(Circuit_1[i][columns-1] != Circuit_2[i][columns-1]) check = false;
    }
    if(check == false) 
    {
        cout << "The two logical expressions are not equivalent.";
        return  ;
    }
    else 
    {
        cout << "The two logical expressions are equivalent.";
        Check_tautology(Circuit_1 , rows , columns , inputs);
    }
}

vector<vector<int>> Truth_Table(string input, vector<bool> bits, vector<char> inputs)
{   
    vector<bool> temp_bits = bits;
    int rows = 1 << temp_bits.size();
    int columns = inputs.size() + 1;
    vector<vector<int>> data(rows, vector<int>(columns, 0));
    cout << "Truth Table:\n";
    cout << "===========================================================\n";    
    for (char c : inputs)
    {
        cout << "\t" << c << "\t\t|\t";
    }
    cout << "  Output\n";
    cout << "===========================================================\n";    
    for (int r = 0; r < rows; r++)
    {
        for (int i = 0; i < inputs.size(); i++)
        {
            cout << "\t" << (temp_bits[i] ? 'T' : 'F') << "\t\t|\t";
            data[r][i] = temp_bits[i];
        }   
        string expr = input;
        bool result = solver(expr, temp_bits, inputs);
        cout << "\t" << (result ? 'T' : 'F') << endl;
        data[r][inputs.size()] = result;
        decrement(temp_bits);
    }
    cout << "===========================================================\n";
    return data;
}

string buildCircuit(const string& choice)
{
    cin.ignore();
    string input;

    if (choice == "E") {
        cout << "Enter Logic Equation (OR : ∨ , AND : ∧): ";
        getline(cin, input);
    } 
    else {
        int n_inputs;
        cout << "How many inputs (1-3)? ";
        cin >> n_inputs;
        if(n_inputs < 0 || n_inputs > 3) {
            cout << "Error: number of inputs must be between 0 and 3.\n";
            return "";
        }

        vector<string> inputs(n_inputs);
        for(int i = 0; i < n_inputs; i++) {
            cout << "Enter name of input " << (i+1) << ": ";
            cin >> inputs[i];
        }

        int total_gates;
        cout << "Enter total gates available: ";
        cin >> total_gates;
        if(total_gates <= 0) {
            cout << "Error: total gates must be > 0.\n";
            return "";
        }

        int n_levels;
        cout << "Enter number of levels: ";
        cin >> n_levels;
        if(n_levels <= 0) {
            cout << "Error: number of levels must be > 0.\n";
            return "";
        }

        vector<string> gates;
        int used_gates = 0;

        for(int level = 1; level <= n_levels; level++) {
            int gates_in_level;
            cout << "How many gates in level " << level << "? ";
            cin >> gates_in_level;

            used_gates += gates_in_level;
            if(used_gates > total_gates) {
                cout << "Error: gates used exceed total available.\n";
                return "";
            }

            for(int g = 0; g < gates_in_level; g++) {
                string op;
                cout << "Enter operator (∧, ∨, ~): ";
                cin >> op;

                vector<string> available = inputs;
                available.insert(available.begin(), "1");
                available.insert(available.begin(), "0");                
                for(auto& gate : gates) available.push_back(gate);

                if(op == "~") {
                    cout << "Choose input for NOT:\n";
                    for(int i = 0; i < available.size(); i++)
                        cout << i+1 << ") " << available[i] << "\n";

                    int ch;
                    cin >> ch;
                    gates.push_back("~(" + available[ch-1] + ")");
                }
                else if(op == "∧" || op == "&" || op == "∨" || op == "|") {
                    int c1, c2;

                    cout << "Choose first input:\n";
                    for(int i = 0; i < available.size(); i++)
                        cout << i+1 << ") " << available[i] << "\n";
                    cin >> c1;

                    cout << "Choose second input:\n";
                    for(int i = 0; i < available.size(); i++)
                        cout << i+1 << ") " << available[i] << "\n";
                    cin >> c2;

                    if(op == "∧" || op == "&")
                        gates.push_back("(" + available[c1-1] + " ∧ " + available[c2-1] + ")");
                    else
                        gates.push_back("(" + available[c1-1] + " ∨ " + available[c2-1] + ")");
                }
                else {
                    cout << "Error: invalid operator.\n";
                    return "";
                }
            }
        }

        if(used_gates != total_gates) {
            cout << "Error: used gates != total available.\n";
            return "";
        }

        input = gates.back();
    }

    return input;
}

int diff_count(const string& a, const string& b)
{
    int diff = 0;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i]) diff++;
    return diff;
}

bool merge_terms(const string& a, const string& b, string& result)
{
    if (diff_count(a, b) != 1) return false;
    result = a;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            result[i] = '-';
    return true;
}

vector<string> extract_minterms(
    const vector<vector<int>>& data,
    int rows,
    int columns)
{
    vector<string> minterms;
    for (int i = 0; i < rows; i++)
    {
        if (data[i][columns - 1] == 1)
        {
            string term = "";
            for (int j = 0; j < columns - 1; j++)
                term += (data[i][j] ? '1' : '0');
            minterms.push_back(term);
        }
    }
    return minterms;
}

vector<string> simplify(const vector<string>& minterms)
{
    vector<string> current = minterms;
    set<string> prime_implicants;

    while (!current.empty())
    {
        vector<bool> used(current.size(), false);
        set<string> next;

        for (int i = 0; i < current.size(); i++)
        {
            for (int j = i + 1; j < current.size(); j++)
            {
                string merged;
                if (merge_terms(current[i], current[j], merged))
                {
                    used[i] = used[j] = true;
                    next.insert(merged);
                }
            }
        }
        for (int i = 0; i < current.size(); i++)
            if (!used[i])
                prime_implicants.insert(current[i]);
        current = vector<string>(next.begin(), next.end());
    }
    return vector<string>(prime_implicants.begin(), prime_implicants.end());
}

string term_to_expr(const string& term, const vector<char>& inputs)
{
    string expr = "";
    for (int i = 0; i < term.size(); i++)
    {
        if (term[i] == '-') continue;
        if (!expr.empty()) expr += " ∧ ";
        if (term[i] == '0')
            expr += "~" + string(1, inputs[i]);
        else
            expr += inputs[i];
    }
    return expr.empty() ? "1" : expr;
}

string K_map(const vector<vector<int>>& data,int rows,int columns,vector<char> inputs)
{
    auto minterms = extract_minterms(data, rows, columns);
    if (minterms.empty()) return "0";
    auto simplified = simplify(minterms);
    string result = "";
    for (auto& t : simplified)
    {
        if (!result.empty()) result += " ∨ ";
        result += "(" + term_to_expr(t, inputs) + ")";
    }
    return result;
}


string source (string input, vector<bool> bits, vector<char> inputs )
{   
    int rows = 1 << bits.size();
    int columns = inputs.size() + 1;
    vector<vector<int>> data(rows, vector<int>(columns, 0));
    for (int r = 0; r < rows; r++)
    {
        for (int i = 0; i < inputs.size(); i++)
        {
            data[r][i] = bits[i];
        }   
        string expr = input;
        bool result = solver(expr, bits, inputs);
        data[r][inputs.size()] = result;
        decrement(bits);
    }
    return K_map(data , rows , columns , inputs);
}

int main() {
    string choice;
    cout << "Do you want to enter the circuit as an equation or answer questions? (E/Q): ";
    cin >> choice;
    string circuit = buildCircuit(choice);
    vector<char> inputs = size(circuit);
    int no_of_inputs= inputs.size();
    vector<bool> bits(no_of_inputs, true);  // initialize all bits to 1
    string circuit_2 = Edit_Equ(circuit);
    
    int rows = 1 << bits.size();
    int columns = inputs.size() + 1;

    cout << "\nCircuit: " << circuit << endl;
    vector<vector<int>> Circuit_1 = Truth_Table(circuit_2 , bits , inputs );
    
    cout << "\n\n";
    // ==========================================================================
    bool ask ;
    cout << "Do you want to check whether your simplified equation is equivalent to the circuit? (0/1) \n0 -NO\n1 -Yes\n";
    cin >> ask;
    if(ask)
    {
        cout << "Do you want to enter the circuit simplification as an equation or answer questions? (E/Q): ";
        cin >> choice;
        string circuit_simplified = buildCircuit(choice);
        string circuit_simplified_2 = Edit_Equ(circuit_simplified);
    
        cout << "\nCircuit before simplification: " << circuit_simplified << endl;
        vector<vector<int>> circuit_simplified_1 = Truth_Table(circuit_simplified_2 , bits , inputs );
        
        cout << "\n__________________________________________________________________________________\n";
        
        check_equivalent(Circuit_1 ,circuit_simplified_1 , rows , columns , inputs);
    }
    else
    {
        string simplified_equation = source(circuit_2 , bits , inputs);
        cout << "\nCircuit after simplification: " << simplified_equation << endl;
        simplified_equation = Edit_Equ(simplified_equation);
        vector<vector<int>> simplified_equation_1 = Truth_Table(simplified_equation , bits , inputs );
        check_equivalent(Circuit_1 ,simplified_equation_1 , rows , columns , inputs);
    }
    return 0;
}

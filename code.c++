#include <iostream> 
#include <string> 
using namespace std; 
bool expression(string& input, size_t& pos); 
bool term(string& input, size_t& pos); 
bool factor(string& input, size_t& pos); 
bool primary(string& input, size_t& pos); 
bool expression(string& input, size_t& pos) 
{ 
// Check for a term 
   if (!term(input, pos)) 
       return false; 
// Check for zero or more operators and terms 
   while (pos < input.size() && (input.substr(pos, 2) == "==" || input.substr(pos, 2) == "!=" || input[pos] == '<' || input[pos] == '>' || input.substr(pos, 2) == "<=" || input.substr(pos, 2) == ">=")) {
       pos += 2; // Consume the operator 
       if (!term(input, pos)) 
           return false; 

   }return true; 
}
bool term(string& input, size_t& pos) 
{ 
// Check for a factor 
     if (!factor(input, pos)) 
        return false; 
// Check for zero or more operators and factors 
     while (pos < input.size() && (input[pos] == '+' || input[pos] == '-')) 
    { 
         ++pos; // Consume the operator 
         if (!factor(input, pos)) 
             return false; 
    } return true; 
} 
bool factor(string& input, size_t& pos) 
{ 
// Check for a primary expression 
    if (!primary(input, pos)) 
        return false; 
// Check for zero or more operators and primary expressions 
    while (pos < input.size() && (input[pos] == '*' || input[pos] == '/' || input[pos] == '%')) 
    { 
        ++pos; // Consume the operator 
        if (!primary(input, pos)) 
            return false; 
    } 
    return true; 
} 
bool primary(string& input, size_t& pos) 
{ 
// Check for an integer literal or variable name
    if (pos < input.size() && (isdigit(input[pos]) || isalpha(input[pos]))) 
    { 
        ++pos; // Consume the token 
        return true; 
    } 
// Check for a sub-expression in parentheses 
    if (pos < input.size() && input[pos] == '(') 
    { 
        ++pos; // Consume the '(' 
        if (!expression(input, pos)) 
            return false; 
        if (pos >= input.size() || input[pos] != ')') 
            return false; // ')' expected but not found 
        ++pos; // Consume the ')' 
        return true; 
    } 
// Invalid primary expression 
    return false; 
} 
bool statement(string& input, size_t& pos) 
{
    // Check for a valid if-else statement 
    if (input.substr(pos, 2) != "if") 
       return false; 
    pos += 2; // Consume the 'if' keyword 
    if (pos >= input.size() || input[pos] != '(') 
        return false; 
    ++pos; // Consume the '(' 
    if (!expression(input, pos)) 
        return false; 
    if (pos >= input.size() || input[pos] != ')') 
        return false; 
    ++pos; // Consume the ')' 
    if (!statement(input, pos)) 
        return false; 
    if (pos < input.size() && input.substr(pos, 4) == "else") 
    { 
        pos += 4; // Consume the 'else' keyword 
        if (!statement(input, pos)) 
        return false; 
    } 
    return true; 
} 
int main() 
{ 
string input; 
cout << "Enter an if-else statement: "; 
getline(cin, input); 
size_t pos = 0; 
bool success = statement(input, pos); 
if (success && pos == input.size()) 
    cout << "Syntax is correct" << endl; 
else 
    cout << "Syntax is incorrect" << endl; 
return 0; 
}

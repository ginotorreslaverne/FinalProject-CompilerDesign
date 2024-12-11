// -----------------------------------------------------------------------------------------------------------------------
//                                               Name Gino Torres 
//                                               Course CMPS 455, Fall 2024
//                                               Assignment Final Project
//                                               Due date December/13/2024
// Purpose: 
/* 
Basic Grammar
(1) E->E+T
(2) E’->T
(3) T->T*F
(4) T->F
(5) F->(E)
(6) F->id

Please implement the following algorithms
(i) Closure(I)
(ii) Follow(S)
(iii) Goto(State,X)
(iv) CanonicalSet(I)
(v) SLR_parse_tables(grammar)

Please organize a team and implement

(1)          Lexical analyzer

(2)          Parser

(3)        Code generator

 

And test the following source code:

 4+7*14+(7+6)*3

Output the intermediate codes.
*/
//------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <sstream>
#include <regex>

using namespace std;

// Token types
enum TokenType 
{
    ID,       // Identifier
    NUMBER,   // Numeric literal
    PLUS,     // +
    STAR,     // *
    LPAREN,   // (
    RPAREN,   // )
    END,      // End of input
    INVALID   // Invalid token
};

// Struct to represent a Token
struct Token 
{
    TokenType type;
    string value;

    Token(TokenType t, const string& v) : type(t), value(v) {}
};

// Token names for debugging
map<TokenType, string> tokenNames = 
{
    {ID, "ID"},
    {NUMBER, "NUMBER"},
    {PLUS, "PLUS"},
    {STAR, "STAR"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {END, "END"},
    {INVALID, "INVALID"}
};

vector<Token> lexicalAnalyzer(const string& input) 
{
    vector<Token> tokens;
    size_t i = 0;

    while (i < input.size()) 
    {
        char c = input[i];

        // Skip whitespace
        if (isspace(c)) 
        {
            i++;
            continue;
        }

        // Match identifiers (letters or letter followed by digits)
        if (isalpha(c)) 
        {
            string id;
            while (i < input.size() && (isalnum(input[i]))) 
            {
                id += input[i];
                i++;
            }
            tokens.emplace_back(ID, id);
        }
        // Match numbers
        else if (isdigit(c))
         {
            string num;
            while (i < input.size() && isdigit(input[i])) 
            {
                num += input[i];
                i++;
            }
            tokens.emplace_back(NUMBER, num);
        }
        // Match operators and symbols
        else if (c == '+') 
        {
            tokens.emplace_back(PLUS, "+");
            i++;
        } 
        else if (c == '*') 
        {
            tokens.emplace_back(STAR, "*");
            i++;
        } 
        else if (c == '(') 
        {
            tokens.emplace_back(LPAREN, "(");
            i++;
        } 
        else if (c == ')') 
        {
            tokens.emplace_back(RPAREN, ")");
            i++;
        }
        // End of input
        else if (c == '$') 
        {
            tokens.emplace_back(END, "$");
            i++;
        }
        // Invalid token
        else 
        {
            tokens.emplace_back(INVALID, string(1, c));
            i++;
        }
    }

    // Add end of input token
    tokens.emplace_back(END, "$");
    return tokens;
}

int main() 
{
    string input;
    cout << "Enter input string: ";
    getline(cin, input);

    // Step 1: Tokenize input
    vector<Token> tokens = lexicalAnalyzer(input);

    // Step 2: Display tokens
    cout << "\nTokens:\n";
    for (const auto& token : tokens) {
        cout << "Type: " << tokenNames[token.type] << ", Value: " << token.value << endl;
    }

    // Step 3: Integrate with parser (future implementation)
    return 0;
}

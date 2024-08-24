#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to convert a string to lowercase
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Main chatbot function
void chatbot() {
    cout << "Hello! I'm a simple chatbot. Type 'exit' to end the conversation." << endl;
    
    while (true) {
        cout << "You: ";
        string userInput;
        getline(cin, userInput);
        
        // Convert user input to lowercase to make the matching case-insensitive
        string lowerInput = toLowerCase(userInput);
        
        // Check for exit condition
        if (lowerInput == "exit") {
            cout << "Chatbot: Goodbye! Have a great day!" << endl;
            break;
        }

        // Basic greetings
        else if (lowerInput == "hello" || lowerInput == "hi" || lowerInput == "hey") {
            cout << "Chatbot: Hello! How can I help you today?" << endl;
        }

        // Asking about the chatbot's name
        else if (lowerInput.find("name") != string::npos) {
            cout << "Chatbot: I'm just a simple chatbot without a name." << endl;
        }

        // Asking about the weather
        else if (lowerInput.find("weather") != string::npos) {
            cout << "Chatbot: I can't check the weather, but I hope it's nice where you are!" << endl;
        }

        // Asking how the chatbot is doing
        else if (lowerInput.find("how are you") != string::npos) {
            cout << "Chatbot: I'm just a bunch of code, but thanks for asking! How are you?" << endl;
        }

        // Asking about the time (simple response, not actually fetching time)
        else if (lowerInput.find("time") != string::npos) {
            cout << "Chatbot: I can't check the time, but it's always a good time to chat!" << endl;
        }

        // Default response for unrecognized input
        else {
            cout << "Chatbot: I'm not sure how to respond to that. Can you ask something else?" << endl;
        }
    }
}

int main() {
    chatbot();
    return 0;
}

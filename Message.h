#include <iostream>
#include <list>

#pragma once

using namespace std;

// Message class responsible for delivering messages from anywhere in the program to the main screen through Mailbox class

class Message
{

    private:
        string body;
        bool sticky;

    public:
        Message(string text, bool sticky);
        ~Message() {};
        string message();
        bool is_sticky();

};

class MailBox
{

    private:
        list<Message*> messages;
        int* day;

    public:
        MailBox(int* day);
        ~MailBox();
        void create_message(string body, bool is_sticky = false);
        void clear_messages(bool all = false);
        list<Message*> get_messages();

};

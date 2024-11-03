#include "Message.h"

using namespace std;

Message::Message(string text, bool sticky = false){
    this->body = text;
    this->sticky = sticky;
}

string Message::message(){
    return this->body;
}

bool Message::is_sticky(){
    return this->sticky;
}

MailBox::MailBox(int* day){
    this->day = day;
}

MailBox::~MailBox(){

    for(auto itr = this->messages.begin(); itr != this->messages.end(); itr++)
    {
        delete *itr;
        itr = this->messages.erase(itr);
    }

}

void MailBox::create_message(string body, bool is_sticky){

    string msg_body = "Day " + to_string(*this->day) + ": " + body;
    this->messages.push_back(new Message(msg_body, is_sticky));

}

void MailBox::clear_messages(bool all){
    for(auto itr = this->messages.begin(); itr != this->messages.end();)
    {
        if((*itr)->is_sticky() && !all){
            itr++;
            continue;
        }else{
            delete *itr;
            itr = (this->messages).erase(itr);
        }
    }
}

list<Message*> MailBox::get_messages(){
    return this->messages;
}

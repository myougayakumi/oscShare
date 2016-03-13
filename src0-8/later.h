#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

class LaterSender {
public:
    ofxOscSender sender;
    string ip = "";
    int port = 0;
    bool started    = false;
    bool firstTime  = true;

    LaterSender(){}
    
    //setter
    bool ipSet = false;
    void setIp(string _ip){
        if(ipSet) return;
        ip = _ip;
        ipSet = true;
    }
    bool portSet = false;
    void setPort(int _port){
        if(portSet) return;
        port = _port;
        portSet = true;
    }
    
    //getter
    string getIp(){
        return ip;
    }
    int getPort(){
        return port;
    }
    
    bool setuped = false;
    bool setup(){
        if(!ipSet or !portSet or setuped) return false;
        sender.setup(ip, port);
        setuped = true;
        return true;
    };
    
    void sendMessage(ofxOscMessage m){
        sender.sendMessage(m);
    }
};

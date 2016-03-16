#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

class LaterSender {
public:
    vector<ofxOscSender> sender;
    string  ip      = "";
    vector<int> ports;
    
    LaterSender(){}
    
    //setter
    bool ipSet = false;
    void setIp(string _ip){
        if(ipSet) return;
        ip = _ip;
        ipSet = true;
    }
    void addPorts(vector<int> _ports){
        ports.resize(_ports.size());
        for(int i=0; i<ports.size(); i++)
            ports[i] = _ports[i];
    }
    void addPort(int port){
        //if(isSetup) return;
        ports.push_back(port);
    }
    bool isSetup = false;
    void setupAll(){
        sender.resize(ports.size());
        for(int i=0; i<sender.size(); i++) {
            sender[i].setup(ip, ports[i]);
        }
        isSetup = true;
    }
    //getter
    string getIp(){
        return ip;
    }
    vector<int> getPorts(){
        return ports;
    }
    
    void sendMessageAll(ofxOscMessage m){
        for(auto s : sender)
            s.sendMessage(m);
    }
};

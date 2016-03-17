#include "ofApp.h"
#include "LocalAddressGrabber.h"

string localhost = LocalAddressGrabber::getIpAddress("en0");

vector<int> portList = {3000, 3100, 3200, 3300, 3400, 3500};
//3000 using broadcast
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    receiver.resize(      portList.size());
    receiverHub.resize(   portList.size());
    testSender.resize(    portList.size());
    senderFromHub.resize( portList.size());
    loggers.resize(       portList.size());
    
    for(int i=0; i<portList.size(); i++){
        receiver[i].setup(portList[i]);
        receiverHub[i].setup(portList[i]+1);
        //sender[i].setup("localhost", portList[i]+1);
        testSender[i].setup("localhost", portList[i]);
        senderFromHub[i].setup("localhost", portList[i]+10);
    }
    
    //get broadcast
    vector<string> splited = ofSplitString(localhost, ".");
    if(splited[0] == "169" && splited[1] == "254"){
        splited[2] = "255";
    }
    splited[3] = "255";
    broadcast = ofJoinString(splited, ".");
    senderBroad.setup(broadcast, 3000);
    
    //latersender
    laterSender.resize(10);
    for(int i=0; i<laterSender.size(); i++) {
        for(int j=0; j<portList.size(); j++) {
            laterSender[i].addPort(portList[j]+1);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    //    while(receiverHub.hasWaitingMessages()){
    //        ofxOscMessage m;
    //        receiverHub.getNextMessage(m);
    //        senderLocal.sendMessage(m);
    //        
    //
    //    }
    while(receiver[0].hasWaitingMessages()){
        ofxOscMessage m;
        receiver[0].getNextMessage(m);
        //loggers[0].setLog(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/oscShare/push"){
            string  ip   = m.getArgAsString(0);
            
            //check already connected
            bool already = false;
            for(auto s : laterSender){
                if(ip   == s.getIp())   already   = true;
            }
            if(!already){
                if(connected >= laterSender.size()) return;
                laterSender[connected].setIp(ip);
                laterSender[connected].setupAll();
                connected++;
            }
        }else if(m.getAddress() == "/oscShare/pull"){
            sendMyData();
        }else{
            //senderMe.sendMessage(m);
            //loggers[0].setLog(m);
            for(int i=0; i<connected; i++)
                laterSender[i].sendMessageAll(m);
        }
    }
    for(int i=0; i<receiver.size(); i++){
        while(receiver[i].hasWaitingMessages()){
            ofxOscMessage m;
            receiver[i].getNextMessage(m);
            for(int j=0; j<connected; j++)
                laterSender[j].getSender(i).sendMessage(m);
        }
    }
    
    //hub
    for(int i=0; i<receiverHub.size(); i++){
        while(receiverHub[i].hasWaitingMessages()){
            ofxOscMessage m;
            receiverHub[i].getNextMessage(m);
            loggers[i].setLog(m);
            senderFromHub[i].sendMessage(m);
        }
    }
    
    
}
void ofApp::sendMyData(){
    ofxOscMessage m;
    m.setAddress("/oscShare/push");
    m.addStringArg(localhost);
    senderBroad.sendMessage(m);
    senderFromHub[0].sendMessage(m);
    
}
void ofApp::sendRequest(){
    ofxOscMessage m;
    m.setAddress("/oscShare/pull");
    m.addIntArg(0);
    senderBroad.sendMessage(m);
}
//--------------------------------------------------------------
void ofApp::draw(){
    int height = 0;
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) , 20,height += 20);
    ofDrawBitmapStringHighlight(localhost,   20, height += 20);
    ofDrawBitmapStringHighlight(broadcast,   20, height += 20);
    ofDrawBitmapStringHighlight("press SPACE to connect other oscShare", 20, height += 20);
    ofDrawBitmapStringHighlight("press t     to send test message", 20, height += 20);
    ofDrawBitmapStringHighlight("you can send -> [localhost **00] -> spread[eachhost **01] -> each[localhost **10]", 20, height += 20);
    ofDrawBitmapStringHighlight("you can receive at **10", 20, height += 20);
    
    
    
    height += 30;
    string portStr;
        for(auto port : portList){
            portStr += ", ";
            portStr += ofToString(port);
        }
    ofDrawBitmapStringHighlight(portStr,20, height+=10);
    
    for(int i=0; i<laterSender.size(); i++) {
        string text;
        text += laterSender[i].getIp();
        ofDrawBitmapStringHighlight(text, 30, height += 21);
    }
    
    ofDrawBitmapStringHighlight(ofToString(portList[logNum]+1), 400, 20);
    loggers[logNum].drawLog(400, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        sendMyData();
    }
    if(key == ' '){
        sendRequest();
    }
    if(key == 't'){
        for(int i=0; i<testSender.size(); i++) {

            ofxOscMessage m ;
            m.setAddress("/test");
            m.addStringArg("hello from " + localhost+ "! "  + ofToString(i));
            testSender[i].sendMessage(m);
        }
    }
    if(key == OF_KEY_LEFT) {
        if(logNum == 0) return;
        logNum--;
    }
    if(key == OF_KEY_RIGHT) {
        if(logNum == portList.size()-1) return;
        logNum++;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

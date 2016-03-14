#include "ofApp.h"
#include "LocalAddressGrabber.h"

string localhost = LocalAddressGrabber::getIpAddress("en0");

#define PORT 3000


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    
    receiver.setup(PORT);
    receiverHub.setup(PORT + 1);
    
    vector<string> splited = ofSplitString(localhost, ".");
    if(splited[0] == "169" && splited[1] == "254"){
        splited[2] = "255";
    }
    splited[3] = "255";
    broadcast = ofJoinString(splited, ".");
    sender.setup(broadcast, PORT);
    senderTest.setup("localhost", 3000);
    senderMe.setup("localhost", 3001);
    senderLocal.setup("localhost", 3010);
    laterSender.resize(10);
    LocalAddressGrabber::availableList(lists);

}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiverHub.hasWaitingMessages()){
        ofxOscMessage m;
        receiverHub.getNextMessage(m);
        senderLocal.sendMessage(m);
        
        // unrecognized message: display on the bottom of the screen
        string msg_string;
        msg_string = m.getAddress();
        msg_string += ": ";
        for(int i = 0; i < m.getNumArgs(); i++){
            // get the argument type
            msg_string += m.getArgTypeName(i);
            msg_string += ":";
            // display the argument - make sure we get the right type
            if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                msg_string += ofToString(m.getArgAsInt32(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                msg_string += ofToString(m.getArgAsFloat(i));
            }
            else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                msg_string += m.getArgAsString(i);
            }
            else{
                msg_string += "unknown";
            }
        }
        // add to the list of strings to display
        msg_strings[current_msg_string] = msg_string;
        timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
        current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
        // clear the next line
        msg_strings[current_msg_string] = "";

    }

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(m);
        
		// check for mouse moved message
		if(m.getAddress() == "/oscShare/push"){
			// both the arguments are int32's
            string  ip   = m.getArgAsString(0);
			int     port = m.getArgAsInt32(1);
            
            //check already connected
            bool already = false;
            for(auto s : laterSender){
                bool sameIp   = false;
                bool samePort = false;
                if(ip   == s.getIp())   sameIp   = true;
                if(port == s.getPort()) samePort = true;
                
                if(sameIp && samePort) already = true;
            }
            bool isMyself = (ip == localhost) && (port == PORT);
            if(!already && !isMyself){
                if(connected >= laterSender.size()) return;
                laterSender[connected].setIp(ip);
                laterSender[connected].setPort(port);
                laterSender[connected].setup();
                connected++;
            }
        }else if(m.getAddress() == "/oscShare/pull"){
            sendMyData();
        }else{
            //senderMe.sendMessage(m);
            for(int i=0; i<connected; i++)
                laterSender[i].sendMessage(m);
            
        }
	}
    
}
void ofApp::sendMyData(){
    ofxOscMessage m;
    m.setAddress("/oscShare/push");
    m.addStringArg(localhost);
    m.addIntArg(3001);
    sender.sendMessage(m);
    
}
void ofApp::sendRequest(){
    ofxOscMessage m;
    m.setAddress("/oscShare/pull");
    m.addIntArg(0);
    sender.sendMessage(m);
}
//--------------------------------------------------------------
void ofApp::draw(){
    int height = 0;
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) , 20,height += 20);
    ofDrawBitmapString(localhost,   20, height += 20);
    ofDrawBitmapString(broadcast,   20, height += 20);
    ofDrawBitmapStringHighlight("press SPACE to connect other oscShare", 20, height += 20);
    ofDrawBitmapStringHighlight("press t     to send test message", 20, height += 20);
    height += 40;
    for(int i=0; i<laterSender.size(); i++) {
        string text;
        text += laterSender[i].getIp();
        text += " ";
        text += ofToString(laterSender[i].getPort());
        ofDrawBitmapStringHighlight(text, 20, height + i*20);
    }
    
    
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef())
			msg_strings[i] = "";
		ofDrawBitmapStringHighlight(msg_strings[i], 350, 40 + 15 * i);
	}
    
    int y = 200;
    ofDrawBitmapStringHighlight(ofToString(lists.size()),100,30);
    ofLog() << lists.size() << lists[0];
    for(auto i : lists){
        ofDrawBitmapStringHighlight(i, 60,y+=20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        sendMyData();
    }
    if(key == ' '){
        sendMyData();
        sendRequest();
    }
    if(key == 't'){
        ofxOscMessage m ;
        m.setAddress("/test");
        m.addStringArg("hello from " + localhost+ "!");
        senderTest.sendMessage(m);
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

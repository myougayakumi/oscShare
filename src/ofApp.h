#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "later.h"
#include "Logger.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector<ofxOscReceiver>  receiver, receiverHub;
    vector<ofxOscSender>    sender, testSender, senderFromHub;
    ofxOscSender senderBroad;
    
    
    void sendMyData();
    void sendRequest();
    
    vector<LaterSender> laterSender;
    
    string broadcast;
    int connected = 0;
    vector<string> lists;
    
    vector<Logger> loggers;
    int logNum=0;
    
};

#include "ofMain.h"
#include "ofxOsc.h"

#define NUM_MSG_STRINGS  20

class Logger {
    //view
    int current_msg_string = 0;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
public:
    Logger(){};
    
    void setLog(ofxOscMessage m){
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
    void drawLog(int x, int y){
        
        for(int i = 0; i < NUM_MSG_STRINGS; i++){
            if(timers[i] < ofGetElapsedTimef())
                msg_strings[i] = "";
            ofDrawBitmapStringHighlight(msg_strings[i], x, y + 15 * i);
        }

    }
    
};

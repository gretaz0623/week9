#include "ofApp.h"

float* fftSmoothed;
ofSoundPlayer sound;
ofFbo fbo;
const int numBands = 512;
//float spectrum[numBands];

void ofApp::setup() {
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    ofSetBackgroundColor(32, 38, 38);
    
    sound.load("song.mp3");
    while(!sound.isLoaded());
    sound.play();
    
    fftSmoothed = new float[numBands];
    for (int i = 0; i < numBands; i++) {
        fftSmoothed[i] = 0.0f;
    }
    
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
}
float count1;
float roll;
void ofApp::update() {
    float *val = ofSoundGetSpectrum(numBands);

     
    count1 += fftSmoothed[1];
    
    for (int i = 0; i < numBands; i++) {
        fftSmoothed[i] *= 0.96f;
        fftSmoothed[i] = max(fftSmoothed[i] * ofRandom(0.02, 0.05), val[i]);
    }
    
}
float rX = 0;
float rY = 0;
float rZ = 0;
float a = ofRandom(0,5);
float x,y,z;
float sTime = ofGetElapsedTimef();

void ofApp::draw() {
    fbo.begin();
    ofPushStyle();
    ofSetColor(0,0,0,10);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofPopStyle();
    
    ofPushMatrix();
    
    ofSetBackgroundColor(32, 38, 38);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotate(count1);

    float radius = 90;
    for (int i = 0; i < numBands/16; i++) {
        float x = radius * cos(ofDegToRad(i));
        float y = radius * sin(ofDegToRad(i));
        float size = fftSmoothed[i] * ofRandom(100, 200);
        size *= ofRandom(-0.5, 0.5);
        
        int c = ofRandom(30,80);
        ofSetColor(c, 90, 209);
        ofDrawCircle(x, y, size);
    }
    
    ////#define BLUE 56 90 209
    ////#define YELLOW 237 182 25
    ////#define PURPLE 208 198 233
    ////#define RED 240 68 37
    ////#define BG 32 38 38
    
    float radius2 = ofRandom(90, 180);
    for (int i = 32; i < numBands/2; i += 2) {
        float time = sTime * a + ofGetElapsedTimef();
        rX = ofSignedNoise(time * 0.3) * radius2;
        rY = ofSignedNoise(time * 0.4) * radius2;
        rZ = ofSignedNoise(time * 0.1) * radius2;

        x = ofSignedNoise(time * 0.2) * fftSmoothed[i];
        y = ofSignedNoise(time * 0.4) * fftSmoothed[i];
        z = ofSignedNoise(time * 0.6) * fftSmoothed[i];
        
        float a = radius2 * sin(ofDegToRad(i )) +  fftSmoothed[i] * ofRandom(300, 400);
        float b = radius2 * cos(ofDegToRad(i )) +  fftSmoothed[i] * ofRandom(300, 400);
        float a2 = radius2 * sin(ofDegToRad(i));
        float b2 = radius2 * cos(ofDegToRad(i ));
        
        
        ofTranslate(x,y,z);
        ofScale(1,1,1);
        ofRotateX(rX);
        ofRotateY(rY);
        ofRotateZ(rZ);
        
        int c = ofRandom(200,255);
        ofSetColor(c, 182, 25);
        ofDrawLine(a,b,a2,b2);
        

//        ofDrawRectangle(x, y, size, size);
    }
    
    
    float radius3 = ofRandom(180, 360);
    for (int i = 256; i < numBands; i++) {
        float x = radius3 * sin(ofDegToRad(i)) +  fftSmoothed[i] * ofRandom(300, 400);
        float y = radius3 * cos(ofDegToRad(i)) +  fftSmoothed[i] * ofRandom(300, 400);
        float x2 = radius3 * sin(ofDegToRad(i));
        float y2 = radius3 * cos(ofDegToRad(i));
        float size = fftSmoothed[i] * ofRandom(300, 400);
        size *= ofRandom(-1, 1);
    
        int c = ofRandom(40,100);
        ofSetColor(240, c, 37);
        ofDrawLine(x, y, x2, y2);
        ofSetColor(208, 198, 233,ofRandom(180,255));
        ofDrawRectangle(x2+30,y2+30, size, size);
        
        
    }
    ofPopMatrix();
    
    fbo.end();
    
    fbo.draw(0,0);

 }
    
    




//#include "ofApp.h"
//float count1;
//float roll;
//
//vector <curve> curves;
//ofFbo fbo;
//float x,y,z;
//
//curve::curve(){
//    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
//    
//    p0 = ofPoint(ofRandom(10,ofGetWidth()),ofRandom(10,ofGetWidth()));
//    p1 = ofPoint(ofRandom(10,ofGetHeight()),ofRandom(10,ofGetHeight()));
//    sTime = ofGetElapsedTimef();
//    t = ofPoint(ofGetWidth()/2,ofGetHeight()/2,0);
//    
//
//    
//    
//    fbo.begin();
//    ofClear(255,255,255, 0);
//    fbo.end();
//    
////    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
//}
//float rX = 0;
//float rY = 0;
//float rZ = 0;
//float a = ofRandom(0,5);
//
//void curve::setup(){
//    
//    
//}
//void curve::update(){
//    float time =  ofGetElapsedTimef() + sTime;
//    rX = ofSignedNoise(time * 0.1) * 360.0;
//    rY = ofSignedNoise(time * 0.15) * 360.0;
//    rZ = ofSignedNoise(time * 0.2) * 360.0;
//    
//    dScale =(1-ofNoise(time * 0.2));
//    dScale1 =(1-ofNoise(time * 0.5));
//    dScale2 =(1-ofNoise(time * 0.3));
//    
//    x = ofSignedNoise(time * 0.2) *ofRandom(5,10);
//    y = ofSignedNoise(time * 0.4) * ofRandom(5,10);
//    z = ofSignedNoise(time * 0.6) *ofRandom(5,10);
//    
//    
//    t += ofPoint(x,y,z);
//  
//    
//}
//void curve::update2(){
//    float time =ofGetElapsedTimef();
//    rX = ofSignedNoise(time * 0.3) * 180.0;
//    rY = ofSignedNoise(time * 0.4) * 180.0;
//    rZ = ofSignedNoise(time * 0.1) * 180.0;
//    
//    dScale =(1-ofNoise(time * 0.2));
//    dScale1 =(1-ofNoise(time * 0.2));
//    dScale2 =(1-ofNoise(time * 0.2));
//    
//    x = ofSignedNoise(time * 0.2) *ofRandom(1,5);
//    y = ofSignedNoise(time * 0.4) * ofRandom(1,5);
//    z = ofSignedNoise(time * 0.6) *ofRandom(1,5);
//    
//    
//    t += ofPoint(x,y,z);
// 
//    
//}
//
//void curve::draw() {
//    fbo.begin();
//    ofPushStyle();
//    ofSetColor(0,0,0,1);
//    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
//    ofPopStyle();
//    
//    ofPushMatrix();
//    ofTranslate(t.x,t.y,t.z);
//    ofScale(1,1,1);
//    ofRotateX(rX);
//    ofRotateY(rY);
//    ofRotateZ(rZ);
//    
//    ofSetColor(color2);
//    ofDrawLine(p0,p1);
//    ofPopMatrix();
//    
//    fbo.end();
//    
//    fbo.draw(0,0);
//}
//
//void curve::draw2(){
//    fbo.begin();
//    ofPushStyle();
//    ofSetColor(0,0,0,10);
//    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
//    ofPopStyle();
//    
//    ofPushMatrix();
//    ofTranslate(t.x,t.y,t.z);
//    ofScale(dScale, dScale1, dScale2);
//    ofRotateX(rX);
//    ofRotateY(rY);
//    ofRotateZ(rZ);
//    
//    ofSetColor(color2);
//    ofDrawCircle(p0,ofRandom(10,40));
//    ofPopMatrix();
//    
//    fbo.end();
//    
//    fbo.draw(0,0);
//    
//    
//}
//
//
//void ofApp::add(ofPoint l){
//             curve myCurve;
//        myCurve.t = l;
//        curves.push_back(myCurve);
//
//}
//
////--------------------------------------------------------------
//void ofApp::setup(){
//
//    song.load("sea.mp3");
//    while(!song.isLoaded());
//    song.play();
//
//    song.setVolume(0.4f);
//    
//    fftSmoothed = new float[8192];
//    for (int i = 0; i < 8192; i++){
//        fftSmoothed[i] = 0;
//    }
//    
//    nBandsToGet = 512;
//   
//    count1 = 0.0f;
//    roll = 0.0f;
//    
//    add(ofPoint(x, y));
//
//
//}
//float *val;
//float avgSound;
//
////--------------------------------------------------------------
//void ofApp::update(){
//    ofSetBackgroundColor(32, 38, 38);
//
//    ofSoundUpdate();
//    
//    avgSound = 0;
//    val = ofSoundGetSpectrum(nBandsToGet);
//    
//    // smooth fft and calc average volume
//    for (int i = 0;i < nBandsToGet; i++){
//        fftSmoothed[i] *= 0.96f;
//        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
//        avgSound += fftSmoothed[i];
//        }
//    
//
//    
//    
//    avgSound /= nBandsToGet;
//    curves.clear();
//    count1 += fftSmoothed[7];
//    roll += 2.0f;
//    
//    for(int i =0; i < fftSmoothed[1]; i++){
//       curves[i].update();
//       curves[i].color2 = 56,90,209;
//
//        }
//    
//    for(int i =0; fftSmoothed[10] < i < fftSmoothed[27]; i++){
//        curves[i].update2();
//        curves[i].color2 = 237,182,25;
//
//    }
//    
////    if(fftSmoothed[10] > 0.07f) {
////        curves.push_back(myCurve);
////    } else if (curves.size() > 0) {
////        curves.erase(curves.begin()+(int)ofRandom(curves.size()-1));
////    }
////    
////#define BLUE 56 90 209
////#define YELLOW 237 182 25
////#define PURPLE 208 198 233
////#define RED 240 68 37
////#define BG 32 38 38
//
////    if (avgSound > 0.07)
////       
////    else if (avgSound > 0.04)
////        interp = 237,182,25;
////    else if (avgSound > 0.01)
////        interp = 240,68,37;
////    else
////        interp = 32,38,38;
//}
//
//    int angle = 0;
//    int angle2 = 360;
//
//float getX (int deg, int radius) {
//
//    angle++;
//    float x = radius * cos(ofDegToRad(angle)) + ofGetWidth()/2;
//    return (x);
//}
//
//float getY (int deg, int radius) {
//    angle--;
//    float y = radius * sin(ofDegToRad(angle2)) + ofGetHeight()/2;
//    return (y);
//    
//    
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//    int r = 100;  // radius
//    
//    // draw the fft results:
//
//    
//    // cos & sin take RADIANS.
//    // 2pi radians would be 2 x 57.2958 x 3.1416 = 360 degrees
//    // Therefore to draw a whole circle you would use 0-TWO_PI to draw a whole circle
//    
//    for (int i = 0;i < nBandsToGet; i++){
//        float x1 = getX(i, r);
//        float y1 = getY(i, r);
//        float x2 = getX(i, r +  200 * val[i]);
//        float y2 = getY(i, r + 200 * val[i]);
//    }
//
//    for(int i =0; i < nBandsToGet; i++){
//            ofDrawRectangle(100+i*2,ofGetHeight()-100,2,(-1*val[i])*3000);
//        
//         }
//
//    
////        angle++;
////        float x = 200 * cos(ofDegToRad(angle)) + ofGetWidth()/2;
////        return (x);
//
////    float waving = ofMap(count1,-10,10,0,ofGetWidth()/2);
//    ofRotate(3);
//    ofSetColor(255,255,255);
//    for(int i =0; i < fftSmoothed[1]; i++){
//       ofDrawCircle(100+i*2 ,ofGetHeight()/2,(-1*fftSmoothed[i])*3000);
//                   curves[i].draw();
//    }
//    
//
//    
//    for(int i =0; fftSmoothed[10]< i < fftSmoothed[27]; i++){
//        curves[i].draw2();
//    }
//
//    
//  
//}
//
////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){ 
//
//}

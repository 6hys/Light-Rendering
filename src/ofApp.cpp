#include "ofApp.h"
#include "dvdfbo.h"
#include "cube.h"
#include "cone.h"
#include "cylinder.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofBackground(0);
    ofSetFrameRate(60);

    ofEnableDepthTest();
    ofEnableLighting();
    ofEnableNormalizedTexCoords();

    // turn on smooth lighting
    ofSetSmoothLighting(true);

    // center of the screen
    center = { ofGetWidth() * .5, ofGetHeight() * .5, 0 };

    // start in the center of the screen
    lightSphere.set(20, 16);
    lightSphere.setPosition(center.x, center.y, 0);

    sphere.set(250, 24);
    sphere.setPosition(center.x, center.y, -300);

    phongShader.load("shader/phong");
    flatShader.load("shader/flat");
    gouraudShader.load("shader/gouraud");
    toonShader.load("shader/toon");

    materialColor = ofColor(170.0, 68.0, 101.0, 255.0);
    lightColor = ofColor(240.0, 223.0, 173.0, 255.0);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    // Text setup.
    switch (mode)
    {
    case 0:
        ofDrawBitmapString("phong shader", 5, 12);
        ofDrawBitmapString(isSpecular ? "draw specular: YES" : "draw specular: NO", 5, 48);
        ofDrawBitmapString("press A to toggle specular", 5, 60);
        break;
    case 1:
        ofDrawBitmapString("gouraud shader", 5, 12);
        ofDrawBitmapString(isSpecular ? "draw specular: YES" : "draw specular: NO", 5, 48);
        ofDrawBitmapString("press A to toggle specular", 5, 60);
        break;
    case 2:
        ofDrawBitmapString("flat shader", 5, 12);
        break;
    case 3:
        ofDrawBitmapString("toon shader", 5, 12);
        break;
    }
    ofDrawBitmapString("press SPACE to go to next shader", 5, 24);

    // Draw location of point light
    ofSetColor(lightColor);
    lightSphere.draw();

    switch (mode)
    {
    case 0: // blinn-phong
    {
        phongShader.begin();

        phongShader.setUniform1i("isSpecular", isSpecular ? 1 : 0);

        phongShader.setUniform4f("color",
            ofMap(materialColor.r, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.g, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.b, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.a, 0.0, 255.0, 0.0, 1.0));

        // offset positions by -center because (0,0) is top left(?) here and central(?) for the shader (i think)
        phongShader.setUniform3f("lightPosition", lightSphere.getPosition().x - center.x, lightSphere.getPosition().y - center.y, lightSphere.getPosition().z);
        phongShader.setUniform3f("cameraPosition", 0.0f, 0.0f, ofGetHeight() * 0.866f);

        phongShader.setUniform4f("lightColor",
            ofMap(lightColor.r, 0.0, 255.0, 0.0, 1.0),
            ofMap(lightColor.g, 0.0, 255.0, 0.0, 1.0),
            ofMap(lightColor.b, 0.0, 255.0, 0.0, 1.0),
            ofMap(lightColor.a, 0.0, 255.0, 0.0, 1.0));

        phongShader.setUniform1f("shininess", 50.f);
        break;
    }
    case 1: // gouraud

        gouraudShader.begin();

        gouraudShader.setUniform3f("lightPosition", lightSphere.getPosition().x - center.x, lightSphere.getPosition().y - center.y, lightSphere.getPosition().z);

        gouraudShader.setUniform1i("isSpecular", isSpecular ? 1 : 0);

        gouraudShader.setUniform4f("color",
            ofMap(materialColor.r, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.g, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.b, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.a, 0.0, 255.0, 0.0, 1.0));

        gouraudShader.setUniform4f("lightColor",
            ofMap(lightColor.r, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.g, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.b, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.a, 0.0, 255.0, 0.0, 0.9));

        gouraudShader.setUniform1f("shininess", 250.f);
        break;
    case 2: // flat
        
        flatShader.begin();

        flatShader.setUniform1i("isSpecular", isSpecular ? 1 : 0);

        flatShader.setUniform4f("color",
            ofMap(materialColor.r, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.g, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.b, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.a, 0.0, 255.0, 0.0, 1.0));

        // offset positions by -center because (0,0) is top left(?) here and central(?) for the shader (i think)
        flatShader.setUniform3f("lightPosition", lightSphere.getPosition().x - center.x, lightSphere.getPosition().y - center.y, lightSphere.getPosition().z);
        flatShader.setUniform3f("cameraPosition", 0.0f, 0.0f, ofGetHeight() * 0.866f);

        flatShader.setUniform4f("lightColor",
            ofMap(lightColor.r, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.g, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.b, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.a, 0.0, 255.0, 0.0, 0.9));

        flatShader.setUniform1f("shininess", 50.f);
        break;
    case 3:
        toonShader.begin();

        toonShader.setUniform3f("lightPosition", lightSphere.getPosition().x - center.x, lightSphere.getPosition().y - center.y, lightSphere.getPosition().z);
        
        toonShader.setUniform4f("color",
            ofMap(materialColor.r, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.g, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.b, 0.0, 255.0, 0.0, 1.0),
            ofMap(materialColor.a, 0.0, 255.0, 0.0, 1.0));

        toonShader.setUniform4f("lightColor",
            ofMap(lightColor.r, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.g, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.b, 0.0, 255.0, 0.0, 0.9),
            ofMap(lightColor.a, 0.0, 255.0, 0.0, 0.9));
        break;
    default: // no shader
        break;
    }

    // Draw sphere
    sphere.draw();

    switch (mode)
    {
    case 0: // blinn-phong
    {
        // plane behind
        if (isSpecular)
        {
            phongShader.setUniform4f("color", 0.0f, 0.0f, 0.0f, 1.0f);
        }
        else
        {
            phongShader.setUniform4f("color",
                ofMap(lightColor.r, 0.0, 255.0, 0.0, 1.0),
                ofMap(lightColor.g, 0.0, 255.0, 0.0, 1.0),
                ofMap(lightColor.b, 0.0, 255.0, 0.0, 1.0),
                1.0f);
        }
        phongShader.setUniform1f("shininess", 1.f);
        ofDrawPlane(vec3(center.x, center.y, -550), ofGetWidth(), ofGetHeight());

        phongShader.end();
        break;
    }
    case 1: // gouraud per vertex

        // plane
        gouraudShader.setUniform4f("color",
            ofMap(lightColor.r, 0.0, 255.0, 0.0, 1.0),
            ofMap(lightColor.g, 0.0, 255.0, 0.0, 1.0),
            ofMap(lightColor.b, 0.0, 255.0, 0.0, 1.0),
            1.0f);

        ofDrawPlane(vec3(center.x, center.y, -550), ofGetWidth(), ofGetHeight());

        gouraudShader.end();

        break;

    case 2: // flat

        // plane behind

        flatShader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

        ofDrawPlane(vec3(center.x, center.y, -550), ofGetWidth(), ofGetHeight());

        flatShader.end();

        break;

    case 3: // toon

        // plane
        toonShader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

        ofDrawPlane(vec3(center.x, center.y, -550), ofGetWidth(), ofGetHeight());

        toonShader.end();

        break;

    default: // no shader
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 32) // SPACE
    {
        mode++;
        mode = mode % 4;
    }

    else if (key == 'a' || key == 'A')
    {
        isSpecular = !isSpecular;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    lightSphere.setPosition(x, y, 0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

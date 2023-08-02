
#include "ofApp.h"

#include <stdlib.h>     /* srand, rand */

#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){

	frame.load("util/frame.png");

	ofSetVerticalSync(false);

	setupDirectory();

	ofBackground(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::setupDirectory() {

	dirImages.allowExt("jpg");
	dirImages.listDir("images/");
	
	dirVideos.allowExt("mov");
	dirVideos.listDir("movies/");
	

	if (dirImages.size() || dirVideos.size()) {
		// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		gallery.assign(dirImages.size() + dirVideos.size(), Media(ofImage(), ofVideoPlayer(), 0, 0));
	}

	for (int i = 0; i < (int)dirImages.size(); i++) {
		gallery[i].setVideoFlag(false);
		gallery[i].getImage()->load(dirImages.getPath(i));

		//metadata to-do
	}

	for (int i = 0; i < (int)dirVideos.size(); i++) {

		int index = i + dirImages.size();
		ofImage videoThumbnail;

		gallery[index].setVideoFlag(true);

		gallery[index].getVideo()->load(dirVideos.getPath(i));
		gallery[index].getVideo()->play();
		gallery[index].getVideo()->setPaused(true);

		gallery[index].getVideo()->setLoopState(OF_LOOP_NORMAL);
		gallery[index].getVideo()->setSpeed((float) 1);

		//videoThumbnail.setFromPixels(gallery[index].getVideo()->getPixels());
		//gallery[index].setImage(videoThumbnail);

		//metadata to-do
	}

	currentMedia = rand() % gallery.size();
	//currentMedia = 50;
}
//--------------------------------------------------------------
void ofApp::update(){
	if (gallery[currentMedia].isVideoContent()) {
		gallery[currentMedia].getVideo()->setPaused(false);
		gallery[currentMedia].getVideo()->update();
	}
	frame.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xFFFFFF);

	if (gallery[currentMedia].isVideoContent()) {

		float ratio = gallery[currentMedia].getVideo()->getHeight() / gallery[currentMedia].getVideo()->getWidth();

		drawSecondaryMedia(512, 384, 380, 380 * ratio);
		
		gallery[currentMedia].getVideo()->draw((512 - 380 / 2), (384 - 380 * ratio / 2), 380, 380 * ratio);
		
		gallery[currentMedia].getVideo()->setPaused(false);

		frame.draw((512 - 500 / 2), (384 - 500 * ratio / 2), 500, 500 * ratio);

		
	}
	else {

		float ratio = gallery[currentMedia].getImage()->getHeight() / gallery[currentMedia].getImage()->getWidth();

		drawSecondaryMedia(512, 384, 380, 380 * ratio);
		
		gallery[currentMedia].getImage()->draw((512 - 380 / 2), (384 - 380 * ratio / 2), 380, 380 * ratio);

		frame.draw((512 - 500 / 2), (384 - 500 * ratio / 2), 500, 500 * ratio);

		
	}

	ofSetHexColor(0x000000);
	ofDrawBitmapString("wtffff", 20, 20);
	ofDrawBitmapString("Current Media: " + ofToString(currentMedia) + "/" + ofToString(gallery.size()-1), 20, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case OF_KEY_LEFT:
			if (currentMedia > 0) {
				if (gallery[currentMedia].isVideoContent()) {
					gallery[currentMedia].getVideo()->setPaused(true);
				}
				currentMedia--;
				
			}
			break;
		case OF_KEY_RIGHT:
			if (currentMedia < gallery.size() - 1) {
				if (gallery[currentMedia].isVideoContent()) {
					gallery[currentMedia].getVideo()->setPaused(true);
				}
				currentMedia++;
				
			}
			break;
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

void ofApp::drawSecondaryMedia(int x, int y, float width, float height) {

	float minimumDistance = sqrt((pow((width/2), 2)) + (pow((height/2), 2)) + (pow((sqrt(2) * 50), 2)));

	float distance = 100 + minimumDistance;
	//float distance = 450;

	float division = distance / 3;

	int desiredWidth = 100;

	std::vector<Media> neighbours = findNeighbours(gallery[currentMedia]);


	for (int i = 0; i < 3; i++) {
		if (neighbours[i].isVideoContent()) {
			float ratio = neighbours[i].getVideo()->getHeight() / neighbours[i].getVideo()->getWidth();
			neighbours[i].getVideo()->draw(x + (i+1) * division - desiredWidth/2, y - (2-i) * division - desiredWidth/2, desiredWidth, desiredWidth * ratio);
		}
		else {
			float ratio = neighbours[i].getImage()->getHeight() / neighbours[i].getImage()->getWidth();
			neighbours[i].getImage()->draw(x + (i+1) * division - desiredWidth/2, y - (2 - i) * division - desiredWidth/2, desiredWidth, desiredWidth * ratio);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (neighbours[i+3].isVideoContent()) {
			float ratio = neighbours[i+3].getVideo()->getHeight() / neighbours[i+3].getVideo()->getWidth();
			neighbours[i+3].getVideo()->draw(x + (i + 1) * division - desiredWidth / 2, y + (2 - i) * division - desiredWidth/2, desiredWidth, desiredWidth * ratio);
		}
		else {
			float ratio = neighbours[i+3].getImage()->getHeight() / neighbours[i+3].getImage()->getWidth();
			neighbours[i+3].getImage()->draw(x + (i + 1) * division - desiredWidth / 2, y + (2 - i) * division - desiredWidth/2, desiredWidth, desiredWidth * ratio);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (neighbours[i+6].isVideoContent()) {
			float ratio = neighbours[i+6].getVideo()->getHeight() / neighbours[i+6].getVideo()->getWidth();
			neighbours[i+6].getVideo()->draw(x - (i + 1) * division - desiredWidth / 2, y - (2 - i) * division - desiredWidth / 2, desiredWidth, desiredWidth * ratio);
		}
		else {
			float ratio = neighbours[i+6].getImage()->getHeight() / neighbours[i+6].getImage()->getWidth();
			neighbours[i+6].getImage()->draw(x - (i + 1) * division - desiredWidth / 2, y - (2 - i) * division - desiredWidth / 2, desiredWidth, desiredWidth * ratio);
		}
	}

	for (int i = 0; i < 3; i++) {
		if (neighbours[i + 9].isVideoContent()) {
			float ratio = neighbours[i + 9].getVideo()->getHeight() / neighbours[i + 9].getVideo()->getWidth();
			neighbours[i + 9].getVideo()->draw(x - (i + 1) * division - desiredWidth / 2, y + (2 - i) * division - desiredWidth / 2, desiredWidth, desiredWidth * ratio);
		}
		else {
			float ratio = neighbours[i + 9].getImage()->getHeight() / neighbours[i + 9].getImage()->getWidth();
			neighbours[i + 9].getImage()->draw(x - (i + 1) * division - desiredWidth / 2, y + (2 - i) * division - desiredWidth / 2, desiredWidth, desiredWidth * ratio);
		}
	}
}

std::vector<Media> ofApp::findNeighbours(Media primaryMedia) {

	std::vector<Media> result;
	result.assign(12, Media(ofImage(), ofVideoPlayer(), 0, 0));

	if (currentMedia < 6) {

		int leftDifference = 6 - currentMedia;

		for (int i = 1; i <= currentMedia; i++) {
			result[i-1] = gallery[currentMedia-i];
		}
		for (int i = 1; i <= 6 + leftDifference; i++) {
			result[i - 1 + currentMedia] = gallery[currentMedia + i];
		}

	}
	else if (currentMedia > (gallery.size() - 1 - 6)) {

		int rightDifference = gallery.size() - 1 - currentMedia;

		for (int i = 1; i < rightDifference; i++) {
			result[i - 1] = gallery[currentMedia + i];
			result[i - 1 + rightDifference] = gallery[currentMedia - i];
		}

		for (int i = 1; i < 12 - rightDifference * 2; i++) {
			result[i - 1 + rightDifference * 2] = gallery[currentMedia - rightDifference - 1];
		}
	}
	else {
		for (int i = 1; i <= 6; i++) {
			result[i - 1] = gallery[currentMedia - i];
			result[i + 5] = gallery[currentMedia + i];
		}
	}

	return result;
}

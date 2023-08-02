#include "Media.h"

Media::Media(ofImage img, ofVideoPlayer vid, int xPos, int yPos)
{
	image = img;
	video = vid;
	x = xPos;
	y = yPos;
}

int Media::getX()
{
	return x;
}

int Media::getY()
{
	return y;
}

void Media::setMediaPosition(int xPos, int yPos){
	x = xPos;
	y = yPos;
}

bool Media::isVideoContent() {
	return isVideo;
}

void Media::setVideoFlag(bool flag) {
	isVideo = flag;
}

ofImage* Media::getImage() {
	return &image;
}

void Media::setImage(ofImage img) {
	image = img;
}

ofVideoPlayer * Media::getVideo(){
	return &video;
}

float Media::getLuminanceImage(){
	int imgWidth = image.getWidth();
	int imgHeight = image.getHeight();
	int nPixels = imgHeight * imgWidth;

	float luminance = 0.0;
	float avgLuminance = 0.0;

	for (int i = 0; i < imgWidth; i++){
		for (int j = 0; j < imgHeight; j++){
			luminance = image.getColor(i, j).getLightness();
			avgLuminance += luminance;
		}
	}
	avgLuminance /= nPixels;

	return avgLuminance;
}

float Media::getColorImage(){
	int imgWidth = image.getWidth();
	int imgHeight = image.getHeight();
	int nPixels = imgHeight * imgWidth;

	float color = 0.0;
	float avgColor = 0.0;

	for (int i = 0; i < imgWidth; i++) {
		for (int j = 0; j < imgHeight; j++) {
			color = image.getColor(i, j).getHue();
			avgColor += color;
		}
	}
	avgColor /= nPixels;
	return avgColor;
}

float Media::getLuminanceVideo(){
	float luminance = 0.0;
	float avgLuminance = 0.0;
	int nFrames = video.getTotalNumFrames();

	int frame = 0;
	while (frame<nFrames){
		ofImage frameImage;
		video.setFrame(frame);
		ofPixels pixels = video.getPixels();
		frameImage.setFromPixels(pixels);

		int frameWidth = frameImage.getWidth();
		int frameHeight = frameImage.getHeight();
		int framePixels = frameWidth * frameHeight;
	
		for (int i = 0; i < frameWidth; i++) {
			for (int j = 0; j < frameHeight; j++) {
				luminance = image.getColor(i, j).getLightness();
				avgLuminance += luminance;
			}
		}
		avgLuminance /= framePixels;
		frame++;
	}
	return avgLuminance;
}

float Media::getColorVideo(){
	float color = 0.0;
	float avgColor = 0.0;
	int nFrames = video.getTotalNumFrames();

	int frame = 0;
	while (frame < nFrames) {
		ofImage frameImage;
		video.setFrame(frame);
		ofPixels pixels = video.getPixels();
		frameImage.setFromPixels(pixels);

		int frameWidth = frameImage.getWidth();
		int frameHeight = frameImage.getHeight();
		int framePixels = frameWidth * frameHeight;

		for (int i = 0; i < frameWidth; i++) {
			for (int j = 0; j < frameHeight; j++) {
				color = image.getColor(i, j).getHue();
				avgColor += color;
			}
		}
		avgColor /= framePixels;
		frame++;
	}
	return avgColor;
}

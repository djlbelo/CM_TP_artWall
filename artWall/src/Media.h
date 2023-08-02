#pragma once

#include "ofMain.h"

class Media {
	public:
		Media(ofImage img, ofVideoPlayer vid, int xPos, int yPos);
		int getX();
		int getY();
		void setMediaPosition(int xPos, int yPos);
		bool isVideoContent();
		void setVideoFlag(bool flag);

		ofImage* getImage();
		void setImage(ofImage img);
		ofVideoPlayer* getVideo();
		void setThumbnail(std::vector<ofImage> vec); //to-do
		std::vector<ofImage> getMovIcon(); //to-do
		float getLuminanceImage();
		float getColorImage();
		float getLuminanceVideo();
		float getColorVideo();

	private:
		ofImage image;
		ofVideoPlayer video;
		int x;
		int y;
		bool isVideo;
		std::vector<ofImage> movIcon; //why is this um crlh dum vector?
};